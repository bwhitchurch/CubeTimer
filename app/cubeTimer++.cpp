#include "scrambler.hpp"                // for Scrambler

#include "internal_use_only/config.hpp" // for project_name, project_version

#include <cstdio>                       // for fileno, stdin, getchar
#include <cstdlib>                      // for EXIT_SUCCESS
#include <exception>                    // for exception
#include <stdexcept>                    // for invalid_argument, out_of_range
#include <string>                       // for allocator, basic_string
#include <string_view>                  // for basic_string_view
#include <termios.h>                    // for tcsetattr, termios, tcgetattr

#include <sys/select.h>                 // for select, time_t, FD_SET, FD_ZERO
#include <sys/types.h>                  // for uint

#include <fmt/core.h>                   // for format, print, basic_string_...

#include <spdlog/spdlog.h>              // for error

#include <CLI/App.hpp>                  // for App, CLI11_PARSE
#include <CLI/Config.hpp>               // IWYU pragma: keep
#include <CLI/Formatter.hpp>            // IWYU pragma: keep

constexpr int key_escape = 27;

termios initUnbufferedStdin() {
    struct termios old_settings {};

    struct termios new_settings {};

    tcgetattr(fileno(stdin), &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~uint(ICANON) & ~uint(ECHO);
    tcsetattr(fileno(stdin), TCSANOW, &new_settings);
    return old_settings;
}

int kbhit() {
    constexpr time_t timeout_secs  = 10;
    constexpr time_t timeoun_usecs = 0;
    fd_set           read_set{};
    FD_ZERO(&read_set);
    FD_SET(fileno(stdin), &read_set);
    timeval timeout{timeout_secs, timeoun_usecs};
    return select(fileno(stdin) + 1, &read_set, nullptr, nullptr, &timeout);
}

// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, char** argv) {
    try {
        CLI::App app{fmt::format(
            "{} version {}",
            cubetimer::cmake::project_name,
            cubetimer::cmake::project_version
        )};
        bool     print_version = false;
        app.add_flag(
            "--version", print_version, "Print version information and exit."
        );

        CLI11_PARSE(app, argc, argv);

        if (print_version) {
            fmt::print(
                "{} version {}\nCompiled from: {}",
                cubetimer::cmake::project_name,
                cubetimer::cmake::project_version,
                cubetimer::cmake::git_sha
            );
            return EXIT_SUCCESS;
        }
        Scrambler cube_scrambler{};
        /*
        constexpr size_t max_num_scrambles    = 5;
        size_t           num_scrambles_tested = 0;
        std::array< size_t, num_cube_faces * num_turns > stats{};
        stats.fill(0);
        while (num_scrambles_tested < max_num_scrambles) {
            if (num_scrambles_tested % 100000 == 0) {
                spdlog::info("{} scrambles tested", num_scrambles_tested);
            }
            Scrambler::scrambleStats(cube_scrambler.generateScramble(), stats);
            ++num_scrambles_tested;
        }

        fmt::print("Scramble stats:\n");
        for (size_t i = 0; i < num_cube_faces; ++i) {
            const char face_note = cube_face_notation[CubeFace(i)];
            for (size_t j = 0; j < num_turns; ++j) {
                const char turn_note = (FaceTurn(j) == FaceTurn::CLOCKWISE)
                                         ? ' '
                                         : turn_notation[FaceTurn(j)];
                fmt::print(
                    "{}{}: {}\n",
                    face_note,
                    turn_note,
                    stats.at(i * num_turns + j)
                );
            }
        }

        CubeSymmetry my_state = identity;
        fmt::print("{}\n", my_state);
        fmt::print("{}\n", my_state & x_ccw);
        fmt::print("{}\n", my_state & (2 * x_ccw));

        const CubeSymmetry x_cw = -x_ccw;
        fmt::print("{}\n", (x_cw & x_ccw) == identity);

        fmt::print("{}\n", (-x_ccw & y_ccw & x_ccw) == z_ccw);
        const CubeSymmetry my_x = -y_ccw & z_ccw & y_ccw;
        fmt::print("{}\n", my_x == x_ccw);
        const CubeSymmetry my_y = -z_ccw & x_ccw & z_ccw;
        fmt::print("{}\n", my_y == y_ccw);
*/
        const termios old_settings = initUnbufferedStdin();
        while (true) {
            while (kbhit() == 0) {}
            const int key_press = std::getchar();
            if (key_press == key_escape) { break; }

            fmt::print("{}\n", cube_scrambler.generateScramble());
        }
        tcsetattr(fileno(stdin), TCSANOW, &old_settings);
    } catch (const std::exception& e) {
        spdlog::error("Unhandled exception in main: {}", e.what());
    }
    return EXIT_SUCCESS;
}
