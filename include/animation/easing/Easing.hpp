
#pragma once

#include <functional>

#include "animation/easing/function/Back.hpp"
#include "animation/easing/function/Bounce.hpp"
#include "animation/easing/function/Circ.hpp"
#include "animation/easing/function/Cubic.hpp"
#include "animation/easing/function/Elastic.hpp"
#include "animation/easing/function/Expo.hpp"
#include "animation/easing/function/Linear.hpp"
#include "animation/easing/function/Quad.hpp"
#include "animation/easing/function/Quart.hpp"
#include "animation/easing/function/Quint.hpp"
#include "animation/easing/function/Sine.hpp"

namespace zephyr::animation {

    class Easing {
        std::function<float(float)> function;
        float step = 0.03125f;
        float value = 0.0f;

        #ifdef ZEPHYR_DEBUG
            const char *name = "";

            static const std::unordered_map<float(*)(float), const char *> names;
        #endif

        public:
            Easing() = default;
            Easing(std::function<float(float)> function);
            Easing(std::function<float(float)> function, int step);

            Easing(const Easing &other) = default;
            Easing(Easing &&other) = default;

            Easing &operator=(const Easing &other) = default;
            Easing &operator=(Easing &&other) = default;

            float current();
            float next();
            bool finished() const;
            void reset();

            #ifdef ZEPHYR_DEBUG
                const char *getName() const;
            #endif
    };

}
