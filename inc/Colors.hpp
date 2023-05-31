#pragma once

#include <cstdint>

struct SdlColor {
    std::uint8_t r{ };
    std::uint8_t g{ };
    std::uint8_t b{ };
    std::uint8_t a{ };
};

namespace customCols
{
    const SdlColor bg{ 0x10, 0x13, 0x26, 0xff }; // midnight
    const SdlColor debug{ 0x00, 0xff, 0xff, 0xff }; // cyan
    const SdlColor asteroid_col{ 0xff, 0xff, 0xff, 0xff }; // white
    const SdlColor bullet_col{ 0xff, 0xff, 0xff, 0xff }; // white
    const SdlColor player_col{ 0xff, 0xff, 0x00, 0xff }; // yellow
}
