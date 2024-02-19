
#include "animation/easing/Easing.hpp"

#ifdef ZEPHYR_DEBUG
    #include "utils/Debug.hpp"
#endif

namespace zephyr::animation {

    Easing::Easing(std::function<float(float)> function) :
        function(function)
    {
        #ifdef ZEPHYR_DEBUG
            float (**f)(float) = function.target<float(*)(float)>();
            if (f == nullptr) {
                throw std::runtime_error("Invalid easing function");
            }
            name = names.at(*f);
            zephyr::debug("Easing") << "Creating: " << name << std::endl;
        #endif
    }

    Easing::Easing(std::function<float(float)> function, int step) :
        function(function),
        step(1.0f/step)
    {
        #ifdef ZEPHYR_DEBUG
            float (**f)(float) = function.target<float(*)(float)>();
            if (f == nullptr) {
                throw std::runtime_error("Invalid easing function");
            }
            name = names.at(*f);
            zephyr::debug("Easing") << "Creating: " << name << std::endl;
        #endif
    }

    float Easing::current() {
        return function(value);
    }

    float Easing::next() {
        if (value >= 1.0f) {
            return function(1.0f);
        }
        float res = function(value);
        value += step;
        return res;
    }

    bool Easing::finished() const {
        return value >= 1.0f;
    }

    void Easing::reset() {
        value = 0.0f;
    }

    #ifdef ZEPHYR_DEBUG
        const char *Easing::getName() const {
            return name;
        }

        const std::unordered_map<float(*)(float), const char *> Easing::names = {
            {easing::backIn, "BackIn"},
            {easing::backOut, "BackOut"},
            {easing::backInOut, "BackInOut"},
            {easing::bounceIn, "BounceIn"},
            {easing::bounceOut, "BounceOut"},
            {easing::bounceInOut, "BounceInOut"},
            {easing::circIn, "CircIn"},
            {easing::circOut, "CircOut"},
            {easing::circInOut, "CircInOut"},
            {easing::cubicIn, "CubicIn"},
            {easing::cubicOut, "CubicOut"},
            {easing::cubicInOut, "CubicInOut"},
            {easing::elasticIn, "ElasticIn"},
            {easing::elasticOut, "ElasticOut"},
            {easing::elasticInOut, "ElasticInOut"},
            {easing::expoIn, "ExpoIn"},
            {easing::expoOut, "ExpoOut"},
            {easing::expoInOut, "ExpoInOut"},
            {easing::linear, "Linear"},
            {easing::quadIn, "QuadIn"},
            {easing::quadOut, "QuadOut"},
            {easing::quadInOut, "QuadInOut"},
            {easing::quartIn, "QuartIn"},
            {easing::quartOut, "QuartOut"},
            {easing::quartInOut, "QuartInOut"},
            {easing::quintIn, "QuintIn"},
            {easing::quintOut, "QuintOut"},
            {easing::quintInOut, "QuintInOut"},
            {easing::sineIn, "SineIn"},
            {easing::sineOut, "SineOut"},
            {easing::sineInOut, "SineInOut"}
        };
    #endif

};
