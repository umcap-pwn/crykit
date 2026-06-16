#ifndef CIPHERS_VIGENERE_HPP
#define CIPHERS_VIGENERE_HPP
#include <string>
#include <random>

//vigenere


namespace cipher::vigenere {

    bool encrypt(const std::string& key, const std::string& plaintext, std::string& cipher);
    bool decrypt(const std::string& key, std::string& plaintext, const std::string& cipher);
    std::string encrypt(const std::string& key, std::string& cipher);
    std::string decrypt(const std::string& key, std::string& plaintext);

    bool generateKey(int keylen, std::string& key);
    std::string generateKey(int keylen);
    // Опциональне методы а-ля generateKey, display и т.д.
    // Здесь должны быть только те, доступ к которым нужен извне. Внутренние функции оставьте в .cpp
}

#endif
