#include "scrambler.hpp"

#include <CLI/CLI.hpp>
#include <cmath>
#include <cstdio>
#include <internal_use_only/config.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <unordered_set>

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

// NOLINTNEXTLINE(bugprone-excetpion-escape)
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
		Scrambler        cubeScrambler{};
		constexpr size_t max_num_scrambles            = 5;
		size_t           numScramblesTested           = 0;
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
