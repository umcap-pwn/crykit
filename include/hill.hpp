#include <cstdint>

class GF28{
    uint8_t v;
    static uint8_t gf_mul(uint8_t a, uint8_t b);
    public:
        GF28(uint8_t v=0 ) : v(v) {}
        uint8_t value() const {return v;}

        GF28 operator+(GF28 o) const {return v ^ o.v;}
        GF28 operator-(GF28 o) const {return v ^ o.v;}
        GF28 operator+=(GF28 o) { v ^= o.v; return *this; }
        GF28 operator-=(GF28 o) { v ^= o.v; return *this; }

        GF28 operator*(GF28 o) const {return GF28(gf_mul(v, o.v));}
        GF28 operator*=(GF28 o) {v = gf_mul(v, o.v); return *this;;}

        GF28 inv();
        GF28 operator/(GF28 o) const {return *this * o.inv();}
        bool operator==(GF28 o) const {return v==o.v;}
        bool operator!=(GF28 o) const {return v!=o.v;}


};
