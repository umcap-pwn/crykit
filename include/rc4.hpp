#ifndef CIPHERS_RC4_HPP
#define CIPHERS_RC4_HPP
#include <array>
#include <cstdint>
#include <string>

struct RC4State {
    uint8_t S[256];
    uint8_t j;
    uint8_t i;
};

namespace cipher::rc4 {

RC4State rc4_ksa(std::string key);
bool encrypt(const std::string& key, const std::string& plaintext,
             std::string& cipher);
bool decrypt(const std::string& key, const std::string& cipher,
             std::string& plaintext);
void rc4_prga(RC4State& state, std::string_view plain, std::string& cipher);

} // namespace cipher::rc4

#endif // CIPHERS_RC4_HPP
