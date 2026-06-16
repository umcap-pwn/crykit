#include <skel.hpp>
#include <cassert>
#include <iostream>

int main() {

    std::string key = "Ключ!";
    std::string plaintext = "Сообщение для зашифровки";
    std::string encrypted, decrypted;

    bool ok = cipher::skel::encrypt(key, plaintext, encrypted);
    assert(ok);
    ok = cipher::skel::decrypt(key, encrypted, decrypted);
    assert(ok);
    assert(decrypted == plaintext);

    std::cout << "Скелет шифра прошел все тесты, йей! :3" << std::endl;
    return 0;
}
