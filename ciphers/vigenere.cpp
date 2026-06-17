#include "vigenere.hpp"
#include <random>

namespace cipher::vigenere {

unsigned char encrypt_byte(unsigned char plain_byte, unsigned char key_byte) {
    return static_cast<unsigned char>(plain_byte + key_byte);
}

unsigned char decrypt_byte(unsigned char cipher_byte, unsigned char key_byte) {
    return static_cast<unsigned char>(cipher_byte - key_byte);
}

bool encrypt(const std::string& key, const std::string& plaintext, std::string& cipher) {
    if (key.empty()) return false;
    cipher.resize(plaintext.size());
    for (std::size_t i = 0; i < plaintext.size(); ++i) {
        unsigned char p = static_cast<unsigned char>(plaintext[i]);
        unsigned char k = static_cast<unsigned char>(key[i % key.size()]);
        cipher[i] = static_cast<char>(encrypt_byte(p, k));
    }
    return true;
}

bool decrypt(const std::string& key, std::string& plaintext, const std::string& cipher) {
    if (key.empty()) return false;
    plaintext.resize(cipher.size());
    for (std::size_t i = 0; i < cipher.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(cipher[i]);
        unsigned char k = static_cast<unsigned char>(key[i % key.size()]);
        plaintext[i] = static_cast<char>(decrypt_byte(c, k));
    }
    return true;
}

std::string encrypt(const std::string& key, std::string& cipher) {
    if (key.empty()) return {};
    std::string plain = cipher;
    encrypt(key, plain, cipher);
    return cipher;
}

std::string decrypt(const std::string& key, std::string& plaintext) {
    if (key.empty()) return {};
    std::string encrypted = plaintext;
    decrypt(key, plaintext, encrypted);
    return plaintext;
}

bool generateKey(int keylen, std::string& key) {
    if (keylen <= 0) return false;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);
    key.resize(keylen);
    for (int i = 0; i < keylen; ++i) {
        key[i] = static_cast<char>(dist(rng));
    }
    return true;
}

std::string generateKey(int keylen) {
    std::string key;
    if (!generateKey(keylen, key)) return {};
    return key;
}

}