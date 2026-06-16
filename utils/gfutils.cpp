#include "gfutils.hpp"
#include <cstdint>
#include <stdexcept>

uint8_t GF28::gf_mul(uint8_t a, uint8_t b){
    uint8_t result = 0;
            while (b) {
                if (b & 1)
                    result ^= a;
                b >>= 1;
                bool high = a & 0x80;
                a <<= 1;
                if (high)
                    a ^= 0x1B; //редукция: 0x11B & 0xFF
            }
            return result;
}
GF28 GF28::inv() {
    if (v==0) throw std::domain_error("GF(2^8): inverse of zero");
    GF28 result(1), base(*this);
    uint8_t exp = 254;
        while (exp) {
            if (exp & 1) result *= base;
            base *= base;
            exp >>= 1;
        }
        return result;

}
