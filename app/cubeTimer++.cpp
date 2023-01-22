#include "cube.hpp"                     // for numTurns, numCubeFaces, Cube...
#include "cubeStates.hpp"               // for CubeSymmetry, X_CCW, Y_CCW
#include "enum.hpp"                     // for BiEnum
#include "scrambler.hpp"                // for Scrambler

#include <CLI/App.hpp>                  // for App, CLI11_PARSE
#include <CLI/CLI.hpp>
#include <algorithm>                    // for fill_n
#include <array>                        // for array
#include <cstdio>                       // for size_t, setbuf, NULL, stdin
#include <cstdlib>                      // for EXIT_SUCCESS
#include <exception>                    // for exception
#include <fmt/core.h>                   // for print, basic_string_view
#include <internal_use_only/config.hpp> // for project_name, project_version
#include <memory>                       // for allocator
#include <spdlog/spdlog.h>              // for error, info
#include <stdexcept>                    // for invalid_argument, out_of_range
#include <string_view>                  // for basic_string_view
#include <sys/ioctl.h>                  // for ioctl, FIONREAD
#include <termios.h>                    // for tcgetattr, tcsetattr, termios

int kbhit() {
	static bool      initflag = false;
	static const int STDIN    = 0;

	if (!initflag) {
		struct termios term;
		tcgetattr(STDIN, &term);
		term.c_lflag &= ~ICANON;
		tcsetattr(STDIN, TCSANOW, &term);
		setbuf(stdin, NULL);
		initflag = true;
	}

	int nbbytes;
	ioctl(STDIN, FIONREAD, &nbbytes);
	return nbbytes;
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
		Scrambler                                     cubeScrambler{};
		constexpr size_t                              max_num_scrambles  = 5;
		size_t                                        numScramblesTested = 0;
		std::array< size_t, numCubeFaces * numTurns > stats{};
		stats.fill(0);
		while (numScramblesTested < max_num_scrambles) {
			if (numScramblesTested % 100000 == 0) {
				spdlog::info("{} scrambles tested", numScramblesTested);
			}
			Scrambler::scramble_stats(cubeScrambler.generate_scramble(), stats);
			++numScramblesTested;
		}

		fmt::print("Scramble stats:\n");
		for (size_t i = 0; i < numCubeFaces; ++i) {
			const char faceNote = cubeFaceNotation[CubeFace(i)];
			for (size_t j = 0; j < numTurns; ++j) {
				const char turnNote = (FaceTurn(j) == FaceTurn::CLOCKWISE)
				                        ? ' '
				                        : turnNotation[FaceTurn(j)];
				fmt::print(
					"{}{}: {}\n", faceNote, turnNote, stats.at(i * numTurns + j)
				);
			}
		}

		CubeSymmetry myState = Identity;
		fmt::print("{}\n", myState);
		fmt::print("{}\n", myState & X_CCW);
		fmt::print("{}\n", myState & (2 * X_CCW));

		CubeSymmetry X_CW = -X_CCW;
		fmt::print("{}\n", (X_CW & X_CCW) == Identity);

		fmt::print("{}\n", (-X_CCW & Y_CCW & X_CCW) == Z_CCW);
		CubeSymmetry myX = -Y_CCW & Z_CCW & Y_CCW;
		fmt::print("{}\n", myX == X_CCW);
		CubeSymmetry myY = -Z_CCW & X_CCW & Z_CCW;
		fmt::print("{}\n", myY == Y_CCW);

		/*	do {
		        while (kbhit() == 0) {}
		        const char key_press = std::getchar();
		        if (key_press == 27) { break; }

		        fmt::print("{}\n", cubeScrambler.generate_scramble());
		    } while(true);
		    */
	} catch (const std::exception& e) {
		spdlog::error("Unhandled exception in main: {}", e.what());
	}
	return EXIT_SUCCESS;
}
