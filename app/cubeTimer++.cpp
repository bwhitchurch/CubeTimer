#include <CLI/CLI.hpp>
#include <internal_use_only/config.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
void sayHello();

// NOLINTNEXTLINE(bugprone-excetpion-escape)
int main(int argc, char** argv) {
	try {
		CLI::App app{
            fmt::format("{} version {}",
			cubetimer::cmake::project_name,
			cubetimer::cmake::project_version)};
		bool print_version = false;
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
		spdlog::info("Hello World!");
		sayHello();
	} catch (const std::exception& e) {
		spdlog::error("Unhandled exception in main: {}", e.what());
	}
	return EXIT_SUCCESS;
}
