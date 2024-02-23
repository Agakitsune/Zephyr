
#pragma once

#include "math/math.hpp"

namespace zephyr::graphics {

    using color = math::vec4uc;

    namespace minecraft {

        static constexpr color dark_blue = math::vec4uc(0, 0, 170, 255);
        static constexpr color dark_green = math::vec4uc(0, 170, 0, 255);
        static constexpr color dark_aqua = math::vec4uc(0, 170, 170, 255);
        static constexpr color dark_red = math::vec4uc(170, 0, 0, 255);
        static constexpr color dark_purple = math::vec4uc(170, 0, 170, 255);
        static constexpr color gold = math::vec4uc(255, 170, 0, 255);
        static constexpr color gray = math::vec4uc(170, 170, 170, 255);
        static constexpr color dark_gray = math::vec4uc(85, 85, 85, 255);
        static constexpr color blue = math::vec4uc(85, 85, 255, 255);
        static constexpr color green = math::vec4uc(85, 255, 85, 255);
        static constexpr color aqua = math::vec4uc(85, 255, 255, 255);
        static constexpr color red = math::vec4uc(255, 85, 85, 255);
        static constexpr color light_purple = math::vec4uc(255, 85, 255, 255);
        static constexpr color yellow = math::vec4uc(255, 255, 85, 255);

    }

    static constexpr color black = math::vec4uc(0, 0, 0, 255);
    static constexpr color white = math::vec4uc(255, 255, 255, 255);

    // Primary colors
    static constexpr color red = math::vec4uc(255, 0, 0, 255);
    static constexpr color green = math::vec4uc(0, 255, 0, 255);
    static constexpr color blue = math::vec4uc(0, 0, 255, 255);

    // Secondary colors
    static constexpr color yellow = math::vec4uc(255, 255, 0, 255);
    static constexpr color cyan = math::vec4uc(0, 255, 255, 255);
    static constexpr color magenta = math::vec4uc(255, 0, 255, 255);

    // Tertiary colors
    static constexpr color orange = math::vec4uc(255, 128, 0, 255);
    static constexpr color chartreuse = math::vec4uc(128, 255, 0, 255);
    static constexpr color spring_green = math::vec4uc(0, 255, 128, 255);
    static constexpr color azure = math::vec4uc(0, 128, 255, 255);
    static constexpr color violet = math::vec4uc(128, 0, 255, 255);
    static constexpr color rose = math::vec4uc(255, 0, 128, 255);

    // Quaternary colors
    static constexpr color vermilion = math::vec4uc(255, 64, 0, 255);
    static constexpr color amber = math::vec4uc(255, 191, 0, 255);
    static constexpr color lime = math::vec4uc(191, 255, 0, 255);
    static constexpr color harlequin = math::vec4uc(64, 255, 0, 255);
    static constexpr color erin = math::vec4uc(0, 255, 64, 255);
    static constexpr color aquamarine = math::vec4uc(0, 255, 191, 255);
    static constexpr color capri = math::vec4uc(0, 191, 255, 255);
    static constexpr color cerulean = math::vec4uc(0, 64, 255, 255);
    static constexpr color indigo = math::vec4uc(64, 0, 255, 255);
    static constexpr color purple = math::vec4uc(191, 0, 255, 255);
    static constexpr color cerise = math::vec4uc(255, 0, 191, 255);
    static constexpr color crimson = math::vec4uc(255, 0, 64, 255);

    // Quinary colors
    static constexpr color scarlet = math::vec4uc(255, 32, 0, 255);
    static constexpr color persimmon = math::vec4uc(255, 96, 0, 255);
    static constexpr color orange_peel = math::vec4uc(255, 160, 0, 255);
    static constexpr color golden_yellow = math::vec4uc(255, 224, 0, 255);
    static constexpr color lemon = math::vec4uc(224, 255, 0, 255);
    static constexpr color spring_bud = math::vec4uc(160, 255, 0, 255);
    static constexpr color bright_green = math::vec4uc(96, 255, 0, 255);
    static constexpr color neon_green = math::vec4uc(32, 255, 0, 255);
    static constexpr color jade = math::vec4uc(0, 255, 32, 255);
    static constexpr color emerald = math::vec4uc(0, 255, 96, 255);
    static constexpr color mint = math::vec4uc(0, 255, 160, 255);
    static constexpr color turquoise = math::vec4uc(0, 255, 224, 255);
    static constexpr color sky_blue = math::vec4uc(0, 224, 255, 255);
    static constexpr color cornflower = math::vec4uc(0, 160, 255, 255);
    static constexpr color cobalt = math::vec4uc(0, 96, 255, 255);
    static constexpr color sapphire = math::vec4uc(0, 32, 255, 255);
    static constexpr color iris = math::vec4uc(32, 0, 255, 255);
    static constexpr color veronica = math::vec4uc(96, 0, 255, 255);
    static constexpr color amethyst = math::vec4uc(160, 0, 255, 255);
    static constexpr color phlox = math::vec4uc(224, 0, 255, 255);
    static constexpr color fuschia = math::vec4uc(255, 0, 224, 255);
    static constexpr color deep_pink = math::vec4uc(255, 0, 160, 255);
    static constexpr color raspberry = math::vec4uc(255, 0, 96, 255);
    static constexpr color amaranth = math::vec4uc(255, 0, 32, 255);

    // Grayscale colors
    static constexpr color black_olive = math::vec4uc(39, 39, 39, 255);
    static constexpr color onyx = math::vec4uc(51, 51, 51, 255);
    static constexpr color charcoal = math::vec4uc(64, 64, 64, 255);
    static constexpr color dark_slate_gray = math::vec4uc(79, 79, 79, 255);
    static constexpr color gunmetal = math::vec4uc(86, 86, 86, 255);
    static constexpr color liver = math::vec4uc(102, 102, 102, 255);
    static constexpr color dim_gray = math::vec4uc(105, 105, 105, 255);
    static constexpr color taupe = math::vec4uc(112, 112, 112, 255);
    static constexpr color gray = math::vec4uc(128, 128, 128, 255);
    static constexpr color silver = math::vec4uc(192, 192, 192, 255);
    static constexpr color white_smoke = math::vec4uc(224, 224, 224, 255);
    static constexpr color gainsboro = math::vec4uc(240, 240, 240, 255);

}
