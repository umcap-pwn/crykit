#pragma once
#include <string>
namespace cipher::hill{

    bool encrypt(std::string& s_key, const std::string &plaintext, std::string &cipher);
    bool decrypt(std::string& s_key, std::string& cipher, std::string& plaintext);
}
