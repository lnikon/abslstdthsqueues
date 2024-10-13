# Description
This example contains implementations of two thread-safe queue. One relies on abseil synchronization primitives,\
and the other one on std::. Both implementations are conceptually the same, but TSan gives two warnings\
on abseil implementation, and reports zero issues for std:: implementation.

# Build

`conan install . --output-folder=build --build=missing --profile=default`\
`cmake --preset conan-release`\
`cmake --build ./build`


# Run

`./build/AbslMain`\
`./build/StdMain`
