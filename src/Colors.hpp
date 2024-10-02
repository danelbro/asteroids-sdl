#pragma once

#include "SDL_Interface.hpp"

namespace utl {
    namespace customCols
    {
        const Colour bg{ 0x10, 0x13, 0x26, 0xff }; // midnight
        const Colour debug{ 0x00, 0xff, 0xff, 0xff }; // cyan
        const Colour asteroid_col{ 0xff, 0xff, 0xff, 0xff }; // white
        const Colour bullet_col{ 0x00, 0xff, 0x00, 0xff }; // green
        const Colour player_col{ 0xff, 0xff, 0x00, 0xff }; // yellow
        const Colour enemy_col{ 0xff, 0x00, 0x00, 0xff }; // red
        const Colour text_col{ 0x99, 0xd9, 0xea, 0xff }; // light blue
    } // namespace customCols
} // namespace utl
