#ifndef CIPHERS_OTP_HPP
#define CIPHERS_OTP_HPP
#include <string>


namespace cipher::otp {

    enum rng {
        AUTO = 0,
        DEV_URANDOM,
        MT19937,
        ALL_ONES
    };

    // Внутренняя функция шифрования, рассчитывает на абсолютно случайный ключ размером с сообщение.
    // Рекомендуется использовать обёртку
    bool encrypt(const std::string& key, const std::string& plaintext, std::string& cipher);

    // Функция обертки. Использует список существующих генераторов варьируещейся криптостойкости.
    void otp(const std::string &plaintext, std::string &cypher, std::string &key, rng=AUTO);

    bool decrypt(const std::string& key, const std::string& cipher, std::string& plaintext);
}

#endif
