#include "hill.hpp"
#include "gfutils.hpp"
#include "utils.hpp"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <openssl/bn.h>
#include <random>
#include <stdexcept>
#include <string>

namespace cipher::hill{

    Matrix<GF28> keygen(std::string& s_key, size_t n){
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<uint8_t> dist(1, 255);
        while (true) {
                Matrix<GF28> key(n, n);
                for (size_t i = 0; i < n; ++i)
                    for (size_t j = 0; j < n; ++j){
                        s_key.push_back(uint8_t(dist(rng)));
                        key.at(i, j) = GF28(s_key[i*n+j]);
                    }
                try {
                    key.inv();
                    return key;
                } catch (const std::runtime_error&) {
                }
            }
    }

    Matrix<GF28> keyget(std::string data, size_t& n){
        double check = std::sqrt(data.size());
        if (floor(check*check)!=data.size()){throw std::invalid_argument("Invalid key: matrix is not square");}
        n = static_cast<size_t>(check);
        Matrix<GF28> m(n, n);
        for (size_t i = 0; i<n; ++i){
            for(size_t j = 0; j<n; ++j){
                m.at(i, j) = data[i*n+j];
            }
        }
        return m;
    }

    Matrix<GF28> block_to_matrix(std::string& data, size_t offset, size_t n){
        Matrix<GF28> m(n, 1);
        for (size_t i=0; i<n; i++){
            m.at(i, 0) = GF28(static_cast<uint8_t>(data[offset+i]));
        }
        return m;
    }
    std::string matrix_to_block(const Matrix<GF28> m, size_t n){
        std::string result;
        result.reserve(n);
        for (size_t i =0; i<n; i++){
            result.push_back(static_cast<char>(m.at(i, 0).value()));
        }
        return result;
    }

    Matrix<GF28> enc_block(const Matrix<GF28>& key, const Matrix<GF28>& block){
        return key*block;
    }



    bool encrypt(std::string& s_key, const std::string &plaintext, std::string &cipher){
        size_t n;
        Matrix<GF28> key;
        if (s_key.empty()){
            n = 16;
            key = keygen(s_key, n);
        }
        else {
            key = keyget(s_key, n);
        }
        std::string text = utils::pad(plaintext, n);

        for (size_t offset = 0; offset<text.size(); offset+=n){
            Matrix<GF28> block = block_to_matrix(text, offset, n);
            Matrix<GF28> encrypted_block = enc_block(key, block);
            cipher+=matrix_to_block(encrypted_block, n);
        }
        return true;

    }

    bool decrypt(std::string& s_key, std::string& cipher, std::string& plaintext){
        size_t n;
        Matrix<GF28> key = keyget(s_key, n);
        Matrix<GF28> inv_key = key.inv();
        std::string text;
        for (size_t offset=0; offset<cipher.size(); offset+=n){
            Matrix<GF28> block = block_to_matrix(cipher, offset, n);
            Matrix<GF28> decrypted_block = enc_block(inv_key, block);
            text += matrix_to_block(decrypted_block, n);
        }
        plaintext = utils::depad(text);
        return true;
    }

}
