#pragma once

#include <string>
#include "hash.h"

namespace Math {

    struct Vec3 {
        double x{0.0};
        double y{0.0};
        double z{0.0};

        constexpr void operator+=(const Vec3& other){
            x += other.x;
            y += other.y;
            z += other.z;
        }

        // https://www.matematikk.net/side/Skalarprodukt
        constexpr void operator*=(const Vec3& other){
            x *= other.x;
            y *= other.y;
            z *= other.z;
        }

        // https://en.wikipedia.org/wiki/Divergence
        constexpr void operator/=(const Vec3& other){
            x /= other.x;
            y /= other.y;
            z /= other.z;
        }

        constexpr bool operator==(const Vec3& other) const{
            return
                    x == other.x &&
                    y == other.y &&
                    z == other.z;
        }

        constexpr void operator*=(const double &scalar){
            x *= scalar;
            y *= scalar;
            z *= scalar;
        }

        constexpr size_t hash() const {
            size_t seed = 0;
            Math::hashCombine(seed, x);
            Math::hashCombine(seed, y);
            Math::hashCombine(seed, z);
            return seed;
        }

        std::string toString();
    };
}