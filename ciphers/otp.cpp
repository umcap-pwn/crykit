#include "otp.hpp"

namespace cipher::otp {

    bool encrypt(const std::string& key, const std::string& plaintext, std::string& cipher) {

        if (key.size() != plaintext.size())
            return false;

        std::string output(plaintext.size(), '\0');

        const char *ptext_dat = plaintext.data();
        const char *key_dat = key.data();
        char *out_dat = output.data();

        for (int i = 0; i < key.size(); i++) {
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

        for (int i = 0; i < key.size(); i++) {
            out_dat[i] = static_cast<char>(cipher_dat[i] ^ key_dat[i]);
        }

        plaintext = output;
        return true;
    };

}
