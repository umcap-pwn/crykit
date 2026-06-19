#include "rc4.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <string>

namespace cipher::rc4 {

RC4State rc4_ksa(std::string key) {
    RC4State state;
    state.i = 0;
    state.j = 0;
    uint8_t& j = state.j;
    uint8_t* s = state.S;
    for (int i = 0; i < 256; i++) {
        s[i] = i;
    }
    for (int i = 0; i < 256; i++) {
        j = (j + s[i] + key[i % key.length()]) % 256;
        std::swap(s[i], s[j]);
    }
    return state;
}

bool encrypt(const std::string& key, const std::string& plaintext,
             std::string& cipher) {
    cipher = std::string();
    auto state = rc4_ksa(key);
    rc4_prga(state, plaintext, cipher);
    return true;
}

bool decrypt(const std::string& key, const std::string& cipher,
             std::string& plaintext) {
    plaintext = std::string();
    auto state = rc4_ksa(key);
    rc4_prga(state, cipher, plaintext);
    return true;
}

void rc4_prga(RC4State& state, std::string_view plain, std::string& cipher) {
    uint8_t& i = state.i;
    uint8_t& j = state.j;
    uint8_t* s = state.S;
    for (size_t n = 0; n < plain.length(); n++) {
        i = (i + 1) % 256;
        j = (j + s[i]) % 256;
        std::swap(s[i], s[j]);
        cipher.push_back(plain[n] ^ (s[(s[i] + s[j]) % 256]));
    }
    i = 0;
}

} // namespace cipher::rc4
