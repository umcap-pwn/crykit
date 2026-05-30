// Скелет реализации шифра, используется вместе с хедером.
// Копируем, меняем имя файла и всех функций. Профит

// Обязательно подлкючаем одноименный хедер
#include "skel.hpp"

// Каждый шифр будет лежать в собственном неймспейсе, а все они - в общем cipher
namespace cipher::skel {

    bool encrypt(const std::string &key, const std::string &plaintext, std::string &cipher) {
        // ... реализация шифра здесь
        size_t n = key.length() % 20 + 1;
        for (int i = 0; i < plaintext.length(); i++) {
            cipher.push_back(plaintext[i] + n);
        }
        // Функция возвращает bool. Если необходимо, можно заменить на void и try-catch
        // В будущем может быть переопределено
        return true;
    }

    bool decrypt(const std::string &key, const std::string &cipher, std::string &plaintext) {
        // ... реализация здесь
        size_t n = key.length() % 20 + 1;
        for (int i = 0; i < plaintext.length(); i++) {
            plaintext.push_back(cipher[i] - n);
        }
        return true;
    };

}