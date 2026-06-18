#include "rc4.hpp"
#include <cassert>
#include <iostream>

int main() {

    std::string key = "key";
    std::string plaintext = "message~";
    std::string encrypted, decrypted;

    bool ok = cipher::rc4::encrypt(key, plaintext, encrypted);
    assert(ok);
    ok = cipher::rc4::decrypt(key, encrypted, decrypted);
    assert(ok);
    assert(decrypted == plaintext);

    std::cout << "RC4: шифрование сообщения работает штатно." << std::endl;
    return 0;
}
