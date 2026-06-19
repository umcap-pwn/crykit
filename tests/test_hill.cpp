#include <hill.hpp>
#include <cassert>

int main() {
    std::string key = "kokokokoko";
    std::string plaintext = "Сообщение для зашифровки";
    std::string encrypted, decrypted;

    bool ok = cipher::hill::encrypt(key, plaintext, encrypted);
    assert(ok);
    ok = cipher::hill::decrypt(key, encrypted, decrypted);
    assert(ok);
    assert(decrypted == plaintext);

    return 0;
}
