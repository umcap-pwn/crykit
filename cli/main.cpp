#include "otp.hpp"
#include "skel.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <getopt.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>

struct Config {
    std::string cipher_name;  // --cipher / -c
    bool encrypt_mode = true; // --encrypt (default) / --decrypt
    std::string input_file;   // позиционный аргумент, или stdin
    std::string output_file;  // --output / -o, или stdout
    std::string key_file;     // --key / -k

    std::map<std::string, std::string> cipher_params;

    std::string key_out_file; // --key-out / -K
};

[[noreturn]] static void die(const std::string& msg) {
    std::cerr << "Ошибка: " << msg << std::endl;
    exit(1);
}

static void print_usage(const char* prog) {
    printf(
        "Использование: %s [опции] [<ввод>]\n"
        "\n"
        "Шифрует/дешифрует файл/stdin с помощью выбранного шифра\n"
        "\n"
        "Общие опции:\n"
        "  -c, --cipher <name>   Используемый шифр (skel, otp, …)\n"
        "  -e, --encrypt         Режим шифрования, взаимоискл. с -d "
        "(стандартн.)\n"
        "  -d, --decrypt         Режим дешифрования, взаимоискл. с -e \n"
        "  -o, --output <file>   Записать вывод в файл (иначе: stdout)\n"
        "  -k, --key <file>      Считать ключ из файла\n"
        "  -K, --key-out <file>  Записать сгенерированный ключ в файл (OTP)\n"
        "  -P, --param <kv>      Шифроспецефичные параметры в форме "
        "ключ=значение\n"
        "  -h, --help            Покказать это сообщение\n"
        "\n"
        "Если <input> не указан или '-', считывает файлы из stdin.\n",
        prog);
}

static bool read_file(const std::string& path, std::string& content) {
    std::ifstream f(path, std::ios::binary);
    if (!f)
        return false;
    content.assign(std::istreambuf_iterator<char>{f}, {});
    return true;
}

static bool write_file(const std::string& path, const std::string& content) {
    std::ofstream f(path, std::ios::binary);
    if (!f)
        return false;
    f.write(content.data(), static_cast<std::streamsize>(content.size()));
    return f.good();
}

static bool obtain_key(const Config& cfg, std::string& key) {
    if (!cfg.key_file.empty()) {
        if (!read_file(cfg.key_file, key))
            die("Невозможно считать файл ключа: " + cfg.key_file);
        return true;
    }
    return false;
}

static struct option opts[] = {
    {"cipher", required_argument, nullptr, 'c'},
    {"encrypt", no_argument, nullptr, 'e'},
    {"decrypt", no_argument, nullptr, 'd'},
    {"output", required_argument, nullptr, 'o'},
    {"key", required_argument, nullptr, 'k'},
    {"key-out", required_argument, nullptr, 'K'},
    {"param", required_argument, nullptr, 'P'},
    {"help", no_argument, nullptr, 'h'},
    {nullptr, 0, nullptr, 0},
};

int main(int argc, char** argv) {

    Config cfg;
    int opt;

    while ((opt = getopt_long(argc, argv, ":c:edo:k:K:P:h", opts, nullptr)) !=
           -1) {
        switch (opt) {
        case 'c':
            cfg.cipher_name = optarg;
            break;
        case 'e':
            cfg.encrypt_mode = true;
            break;
        case 'd':
            cfg.encrypt_mode = false;
            break;
        case 'o':
            cfg.output_file = optarg;
            break;
        case 'k':
            cfg.key_file = optarg;
            break;
        case 'K':
            cfg.key_out_file = optarg;
            break;
        case 'P': {
            const char* eq = strchr(optarg, '=');
            if (!eq || eq == optarg)
                die("--param expects name=value, got: " + std::string(optarg));
            std::string name(optarg, eq - optarg);
            std::string val(eq + 1);
            cfg.cipher_params[name] = val;
            break;
        }
        case 'h':
            print_usage(argv[0]);
            return 0;
        case '?':
            die(std::string("Неизвестная опция: -") +
                static_cast<char>(optopt));
        case ':':
            die(std::string("Опции -") + static_cast<char>(optopt) +
                " Необходим аргумент");
        default:
            die("Некорректная последовательность аргументов");
        }
    }

    if (optind < argc) {
        cfg.input_file = argv[optind++];
        if (optind < argc)
            die("Некорректный позиционный аргумент: " +
                std::string(argv[optind]));
    }

    if (cfg.cipher_name.empty())
        die("Не указан шифр; используйте --cipher <name>");

    std::string input;
    if (!cfg.input_file.empty()) {
        if (!read_file(cfg.input_file, input))
            die("Невозможно считать ввод из файла: " + cfg.input_file);
    } else {
        input.assign(std::istreambuf_iterator<char>{std::cin}, {});
    }

    std::string key;
    bool key_provided = obtain_key(cfg, key);

    std::string output;
    bool ok = false;

    if (cfg.cipher_name == "skel") {
        if (cfg.encrypt_mode)
            ok = cipher::skel::encrypt(key, input, output);
        else
            ok = cipher::skel::decrypt(key, input, output);
    }

    else if (cfg.cipher_name == "otp") {
        cipher::otp::rng rng_type = cipher::otp::AUTO;
        auto it = cfg.cipher_params.find("rng");
        if (it != cfg.cipher_params.end()) {
            const auto& v = it->second;
            if (v == "AUTO")
                rng_type = cipher::otp::AUTO;
            else if (v == "DEV_URANDOM")
                rng_type = cipher::otp::DEV_URANDOM;
            else if (v == "MT19937")
                rng_type = cipher::otp::MT19937;
            else if (v == "ALL_ONES")
                rng_type = cipher::otp::ALL_ONES;
            else if (v == "SSL_RANDOM")
                rng_type = cipher::otp::SSL_RANDOM;
            else
                die("Unknown OTP rng value: " + v);
        }

        if (cfg.encrypt_mode && !key_provided) {
            std::string generated_key;
            ok = cipher::otp::otp(input, output, generated_key, rng_type);
            if (ok) {
                if (!cfg.key_out_file.empty()) {
                    if (!write_file(cfg.key_out_file, generated_key))
                        die("Cannot write generated key to " +
                            cfg.key_out_file);
                }
            }
        } else {
            if (!key_provided) {
                die("Необходим путь к файлу ключа. Укажите в --key");
            }
            if (cfg.encrypt_mode)
                ok = cipher::otp::encrypt(key, input, output);
            else
                ok = cipher::otp::decrypt(key, input, output);
        }
    } else {
        die("Неизвестный шифр: " + cfg.cipher_name +
            " (доступные опции: skel, otp)");
    }
    if (!ok)
        die("Не удалось зашифровать файл");

    if (!cfg.output_file.empty()) {
        if (!write_file(cfg.output_file, output))
            die("Невомзожно записать в файл: " + cfg.output_file);
    } else {
        std::cout.write(output.data(),
                        static_cast<std::streamsize>(output.size()));
    }

    return 0;
}
