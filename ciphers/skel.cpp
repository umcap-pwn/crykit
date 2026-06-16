// Скелет реализации шифра, используется вместе с хедером.
// Копируем, меняем имя файла и всех функций. Профит

// Обязательно подлкючаем одноименный хедер
#include "skel.hpp"
#include <cstring>

// Каждый шифр будет лежать в собственном неймспейсе, а все они - в общем cipher
namespace cipher::skel {

bool encrypt(const std::string& key, const std::string& plaintext,
             std::string& cipher) {
    // ... реализация шифра здесь
    cipher.clear();
    size_t n = key.length() % 20 + 1;
    for (unsigned int i = 0; i < strlen(plaintext.data()); i++) {
        cipher.push_back((static_cast<unsigned char>(plaintext[i]) + n) % 256);
    }
    // Функция возвращает bool. Если необходимо, можно заменить на void и
    // try-catch В будущем может быть переопределено
    return true;
}

bool decrypt(const std::string& key, const std::string& cipher,
             std::string& plaintext) {
    // ... реализация здесь
    plaintext.clear();
    size_t n = key.length() % 20 + 1;
    for (unsigned int i = 0; i < strlen(cipher.data()); i++) {
        plaintext.push_back((static_cast<unsigned char>(cipher[i]) - n) % 256);
    }
    return true;
};

} // namespace cipher::skel
