#pragma once

#include <cstdint>

struct SdlColor {
    std::uint8_t r{ };
    std::uint8_t g{ };
    std::uint8_t b{ };
    std::uint8_t a{ };
};

const SdlColor bg{ 0x10, 0x13, 0x26, 0xff }; // midnight
const SdlColor debug{ 0x00, 0xff, 0xff, 0xff}; // cyan
