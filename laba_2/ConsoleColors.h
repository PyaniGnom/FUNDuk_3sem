#ifndef LABA_2_CONSOLECOLORS_H
#define LABA_2_CONSOLECOLORS_H


#include <fmt/color.h>

constexpr static fmt::text_style CONSOLE_RED_COLOR = fmt::fg(fmt::color::red);
constexpr static fmt::text_style CONSOLE_BLACK_COLOR = fmt::fg(fmt::color::dark_gray);
constexpr static fmt::text_style CONSOLE_DONE_COLOR = fmt::fg(fmt::color::forest_green);
constexpr static fmt::text_style CONSOLE_FAIL_COLOR = fmt::fg(fmt::color::indian_red);
constexpr static fmt::text_style CONSOLE_PROCESS_COLOR = fmt::fg(fmt::color::aqua);


#endif //LABA_2_CONSOLECOLORS_H
