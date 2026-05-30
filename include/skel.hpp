// Скелет хедера шифра.
// Использование - скопировать, изменить все "skel" на имя вашего шифра и жить счастливо.
// ! ИСПОЛЬЗОВАТЬ СОВМЕСТНО С cypher-skel.cpp !

#ifndef CIPHERS_SKEL_HPP
#define CIPHERS_SKEL_HPP
#include <string>

namespace cipher::skel {

    // Обязательные методы, должны быть реализованы для каждого ключа
    bool encrypt(const std::string& key, const std::string& plaintext, std::string& cipher);
    bool decrypt(const std::string& key, const std::string& cipher, std::string& plaintext);

    // Опциональне методы а-ля generateKey, display и т.д.
    // Здесь должны быть только те, доступ к которым нужен извне. Внутренние функции оставьте в .cpp
}

#endif
