#include <otp.hpp>
#include <cassert>
#include <iostream>

int main() {

    std::string key       = "password";
    std::string plaintext = "message~";
    std::string encrypted, decrypted;

    bool ok = cipher::otp::encrypt(key, plaintext, encrypted);
    assert(ok);
    ok = cipher::otp::decrypt(key, encrypted, decrypted);
    assert(ok);
    assert(decrypted == plaintext);

    std::cout << "OTP: xor-шифрование работает штатно." << std::endl;
    return 0;
}
