#include "hill.hpp"
#include <cstdint>
#include <stdexcept>

class GF28{
    uint8_t v;
    static uint8_t gf_mul(uint8_t a, uint8_t b){
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
public:
    GF28(uint8_t v=0 ) : v(v) {}
    uint8_t value() const {return v;}

    GF28 operator+(GF28 o) const {return v ^ o.v;}
    GF28 operator-(GF28 o) const {return v ^ o.v;}
    GF28 operator+=(GF28 o) { v ^= o.v; return *this; }
    GF28 operator-=(GF28 o) { v ^= o.v; return *this; }

    GF28 operator*(GF28 o) const {return GF28(gf_mul(v, o.v));}
    GF28 operator*=(GF28 o) {v = gf_mul(v, o.v); return *this;;}

    GF28 inv() const{
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
    GF28 operator/(GF28 o) const {return *this * o.inv();}
    bool operator==(GF28 o) const {return v==o.v;}
    bool operator!=(GF28 o) const {return v!=o.v;}

};
