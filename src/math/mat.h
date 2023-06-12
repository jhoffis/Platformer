#pragma once

#include <string>
#include "vec3.h"

namespace Math {
    struct Mat {
        static constexpr int SIZE = 4;
        float elements[SIZE*SIZE]{};

        constexpr void operator+=(const Mat& other) {
            for (auto i = 0; i < SIZE * SIZE; i++)
                elements[i] += other.elements[i];
        }

        constexpr void operator*=(const float &scalar) {
            for (auto & element : elements)
                element *= scalar;
        }

        constexpr void set(int x, int y, float value) {
            elements[y*SIZE + x] = value;
        }

        constexpr void translate(Math::Vec3 vector) {
            Mat translate{};
            translate.set(3, 0, (float) vector.x);
            translate.set(3, 1, (float) vector.y);
            translate.set(3, 2, (float) vector.z);
            this *= translate;
        }

        constexpr void identity() {
            for (auto &element: elements)
                element = 0;
            elements[0] = 1;
            elements[SIZE + 1] = 1;
            elements[2 * SIZE + 2] = 1;
            elements[3 * SIZE + 3] = 1;
        }

        constexpr Mat() {
            identity();
        }

        std::string toString();
    };
}