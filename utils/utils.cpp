#include "utils.hpp"
#include <string>
#include <stdexcept>

namespace utils{

    //Паддинг (PKCS#7)
    std::string pad(std::string& data, size_t block_size){
        if (block_size == 0 || block_size > 255) {
            throw std::invalid_argument("PKCS#7 padding: block_size must be in range [1, 255]");
        }
        std::size_t data_len = data.size();
            std::size_t padding_len = block_size - (data_len % block_size);
            if (padding_len == 0) {
                padding_len = block_size;
            }

            std::string padded = data;
            padded.append(padding_len, static_cast<char>(padding_len));
            return padded;
    }
    //Удаление паддинга
    std::string depad(std::string& data){
        size_t data_len = data.size();
        unsigned char pad_len = static_cast<unsigned char>(data[data_len - 1]);
        //Проверяем, что все байты паддинга равны pad_len
        for (std::size_t i = data_len - pad_len; i < data_len; ++i) {
            if (static_cast<unsigned char>(data[i]) != pad_len) {
                throw std::runtime_error("Invalid PKCS#7 padding: inconsistent padding bytes");
            }
        }

        return data.substr(0, data_len - pad_len);
    }

}
