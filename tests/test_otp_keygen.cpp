#include <otp.hpp>
#include <cassert>
#include <cstring>
#include <iostream>

void test_type(cipher::otp::rng t) {

    std::string key;
    std::string plaintext = "message~";
    std::string encrypted, decrypted;

    bool ok = cipher::otp::otp(key, plaintext, encrypted, t);
    assert(ok);
    assert(key.length() == plaintext.length());
    assert(key.length() == encrypted.length());

    ok = cipher::otp::decrypt(key, encrypted, decrypted);
    assert(ok);
    assert(decrypted == plaintext);

    std::cout << "OTP: генерация ключей методом " << t <<  " работает штатно." << std::endl;
}

int main(int argc, const char **argv) {

    assert(argc == 2);
    const std::string arg (argv[1], strlen(argv[1]));

    if (arg == "auto")
        test_type(cipher::otp::AUTO);
    else if (arg == "urandom")
        test_type(cipher::otp::DEV_URANDOM);
    else if (arg == "mt19937")
        test_type(cipher::otp::MT19937);
    else if (arg == "allones")
        test_type(cipher::otp::ALL_ONES);
    else if (arg == "ssl")
        test_type(cipher::otp::SSL_RANDOM);
    else return -1;
}
