#include "hill.hpp"
#include "gfutils.hpp"
#include "utils.hpp"
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <openssl/bn.h>
#include <random>
#include <stdexcept>
#include <string>
#define BLOCK_SIZE 16

namespace cipher::hill{

    Matrix<GF28> keygen(size_t block_size){
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<uint8_t> dist(1, 255);
        while (true) {
                Matrix<GF28> key(block_size, block_size);
                for (size_t i = 0; i < block_size; ++i)
                    for (size_t j = 0; j < block_size; ++j)
                        key.at(i, j) = GF28(dist(rng));
                try {
                    key.inv();
                    return key;
                } catch (const std::runtime_error&) {
                }
            }
    }
    Matrix<GF28> block_to_matrix(std::string& data, size_t offset){
        Matrix<GF28> m(BLOCK_SIZE, 1);
        for (size_t i=0; i<BLOCK_SIZE; i++){
            m.at(i, 0) = GF28(static_cast<uint8_t>(data[offset+i]));
        }
        return m;
    }
    std::string matrix_to_block(const Matrix<GF28> m){
        std::string result;
        result.reserve(BLOCK_SIZE);
        for (size_t i =0; i<BLOCK_SIZE; i++){
            result.push_back(static_cast<char>(m.at(i, 0).value()));
        }
        return result;
    }

    Matrix<GF28> enc_block(const Matrix<GF28>& key, const Matrix<GF28>& block){
        return key*block;
    }

    bool encrypt(const std::string &plaintext, std::string &cipher){
        std::string text = utils::pad(plaintext, BLOCK_SIZE);
        Matrix<GF28> key = keygen(BLOCK_SIZE);
        std::string encrypted;

        for (size_t offset = 0; offset<text.size(); offset+=BLOCK_SIZE){
            Matrix<GF28> block = block_to_matrix(text, offset);
            Matrix<GF28> encrypted_block = enc_block(key, block);
            encrypted+=matrix_to_block(encrypted_block);

        }
        return encrypted;

    }

}
