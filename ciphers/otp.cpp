#include "otp.hpp"
#include <cstddef>
#include <cstring>
#include <random>
#include <string>
#include <utility>
#include <sys/random.h>
#include <openssl/rand.h>

// Use UNIX getrandom(2) instead of stl-implemented std::random_device
#define OTP_RAND_GLIBC

namespace cipher::otp {

    bool otp(const std::string &plaintext, std::string &cipher, std::string &key, rng type) {

        size_t len = plaintext.length();
        std::string generated_key(len, '\0');

        switch (type) {
            case AUTO:
            case MT19937: {
                auto rand = std::mt19937();
                for (char &c: generated_key)
                    c = rand();
                }
                break;

            case ALL_ONES:
                std::memset(generated_key.data(), 1, generated_key.length());
                break;

            case DEV_URANDOM: {
                #ifdef OTP_RAND_GLIBC
                int err = getrandom(generated_key.data(), generated_key.length(), 0);
                if (err == -1)
                    return false;
                #else
                auto rand = std::random_device();
                for (char &c: generated_key)
                    c = rand();
                #endif // OTP_RAND_GLIBC
                }
                break;

            case SSL_RANDOM: {
                auto rand = RAND_bytes((unsigned char*)generated_key.data(), generated_key.length());
                if (rand == 0)
                    return false;
                }
                break;

            default:
                std::unreachable();
        }

        bool ok = encrypt(generated_key, plaintext, cipher);
        if (!ok)
            return false;

        key = generated_key;
        return true;
    }

    bool encrypt(const std::string& key, const std::string& plaintext, std::string& cipher) {

        if (key.size() != plaintext.size())
            return false;

        std::string output(plaintext.size(), '\0');

        const char *ptext_dat = plaintext.data();
        const char *key_dat = key.data();
        char *out_dat = output.data();

        for (size_t i = 0; i < key.size(); i++) {
            out_dat[i] = static_cast<char>(ptext_dat[i] ^ key_dat[i]);
        }

        cipher = output;
        return true;
    }

    bool decrypt(const std::string &key, const std::string &cipher, std::string &plaintext) {

        if (key.size() != cipher.size())
            return false;

        std::string output(cipher.size(), '\0');

        const char *cipher_dat = cipher.data();
        const char *key_dat = key.data();
        char *out_dat = output.data();

        for (size_t i = 0; i < key.size(); i++) {
            out_dat[i] = static_cast<char>(cipher_dat[i] ^ key_dat[i]);
        }

        plaintext = output;
        return true;
    };

}
