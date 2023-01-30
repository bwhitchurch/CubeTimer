# Changelog

#[Unreleased](https://github.com/bwhitchurch/CubeTimer/compare/0.1.1...HEAD)

## New Features

- feat: reflective enums through preprocessor shenanigans. [`7d34190`](https://github.com/bwhitchurch/CubeTimer/commit/7d34190747b18cabc922cf4bad7c1ce38c7e5b6a)

## Fixes

- Fix: check for constexpr string support [`c1c9cda`](https://github.com/bwhitchurch/CubeTimer/commit/c1c9cdaa66722f1f56c57ed2d08b5dad9bc5418f)
- Fix: checking constexpr string support (again) [`cb92232`](https://github.com/bwhitchurch/CubeTimer/commit/cb92232cab8b56503f67cd4ef72bd09006984911)
- fix: constexpr string check changed to ifdef [`78bdc18`](https://github.com/bwhitchurch/CubeTimer/commit/78bdc184ab927b76b3fa0bf987f7267765917c52)

## Miscellaneous

- Change: cube header makes use of enum utils. [`9b0f1a6`](https://github.com/bwhitchurch/CubeTimer/commit/9b0f1a644d1720c5d9cd796d8867fd476183e103)
- Enum things [`8320a5e`](https://github.com/bwhitchurch/CubeTimer/commit/8320a5ee7d8ffa4e60959c8de8ed9dcadecc7703)
- Change: Finished reworking scrambler to use new enum and cubeMove classes [`e0edfb1`](https://github.com/bwhitchurch/CubeTimer/commit/e0edfb1b2f518fd5ef3a43b6c988eeb1a40dc062)
- enum.hpp is dead [`f268ef2`](https://github.com/bwhitchurch/CubeTimer/commit/f268ef27d5541603acb786a228f410548e4e52f0)
#[0.1.1](https://github.com/bwhitchurch/CubeTimer/compare/0.1.0...0.1.1)

## New Features

- Add: build and test github action [`9abdf56`](https://github.com/bwhitchurch/CubeTimer/commit/9abdf5625baa201edb13cab1a4e2500f5ac396fe)

## Minor Changes

- dev: some basic ci [`adde650`](https://github.com/bwhitchurch/CubeTimer/commit/adde6502800a7ca5425df555e5ffed572a7dab2f)

## Miscellaneous

- Added a devcontainer [`d385ae1`](https://github.com/bwhitchurch/CubeTimer/commit/d385ae1286ea190dca818ad0048f5a6c7fc1a8f2)
#[0.1.0]()

## New Features

- add: changelog file [`c509fb5`](https://github.com/bwhitchurch/CubeTimer/commit/c509fb5d43dbb69b4d3320a10fb44701b9021bfb)

## Fixes

- fix: scrambler no longer generates invalid states. [`8fec1f2`](https://github.com/bwhitchurch/CubeTimer/commit/8fec1f21fa42cfb7d4a586743f06d422125916b4)

## Minor Changes

- dev: bump version number [`96c04e2`](https://github.com/bwhitchurch/CubeTimer/commit/96c04e22854909f6f4540728f23f8523025bf748)

## Miscellaneous

- Tweaked clang configs and made sure all files were compliant with new styles [`3621101`](https://github.com/bwhitchurch/CubeTimer/commit/36211013a9b643c26633c5fd9979a88fc5f01af3)
- Why did I leave my working tree dirty? [`528732c`](https://github.com/bwhitchurch/CubeTimer/commit/528732cd351071def42604c5add3499352a72318)
- Start of a working scrambler [`a26964c`](https://github.com/bwhitchurch/CubeTimer/commit/a26964c325d2bd63e69aff699bdc721aef60e106)
- Added compiler cache to ignores. Also add project clang-format and clang-tidy config files [`d78999c`](https://github.com/bwhitchurch/CubeTimer/commit/d78999c1ebcfb4be666513641b98431855da0915)
- More project skeleton for using cmake/conan. Basic stub for library code in src, app code in app, and configured headers in configured_files [`5ce25cc`](https://github.com/bwhitchurch/CubeTimer/commit/5ce25cc2cdf29dbda1b9399279688f8b058230af)
- Added documentation for enum [`2a600d1`](https://github.com/bwhitchurch/CubeTimer/commit/2a600d111fc1d93206cad15695472dec93d8c126)
- Added unit test directory, coverage options and doxygen settings [`2c17c6e`](https://github.com/bwhitchurch/CubeTimer/commit/2c17c6ed93e24c8e5d0bf864807862dd750a0879)
- Barebones CLI and logger skeleton. [`7cdc982`](https://github.com/bwhitchurch/CubeTimer/commit/7cdc982ca5db47d0e6793e5cbe44125011407252)
- Added UNLICENSE [`331f0fa`](https://github.com/bwhitchurch/CubeTimer/commit/331f0fa3bf4e0645a2ef9ddaf2f60a81a6284d5f)
- conan and dependency setup. HelloWorld program stub to get build system moving [`978242e`](https://github.com/bwhitchurch/CubeTimer/commit/978242ee34e68d4f9c1a6551ef590abf736d4e33)
- Minimal CMakeLists stub and start of project .gitignore [`0375dd9`](https://github.com/bwhitchurch/CubeTimer/commit/0375dd9f52dcbf3a044e6f0feb70a418da86c048)
- Added CLI11 dependency and changed conan generator to cmake_multi_find_package [`28d63f8`](https://github.com/bwhitchurch/CubeTimer/commit/28d63f8d6dcbdb99949dcbd3009a60e95a33682f)
- Created repository with readme file [`6badf1e`](https://github.com/bwhitchurch/CubeTimer/commit/6badf1e8bf05f7875f06a8dfca5bfe62f9372f1b)
- Moved test output files to build/test [`6aadc58`](https://github.com/bwhitchurch/CubeTimer/commit/6aadc58bc596afce0faaa538356b90c2624da1d9)
- Add compile_commands.json to gitignores [`1dd3ab9`](https://github.com/bwhitchurch/CubeTimer/commit/1dd3ab99622a96a1998ded119b0aa4e4cbe11b28)
