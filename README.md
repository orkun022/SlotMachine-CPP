# Slot Machine · C++17

A portable terminal game built with standard C++17. It uses **virtual credits only**, with validated input, a reproducible random seed option, and automated CLI checks.

## Build and play

With a C++17 compiler and Make:

```sh
make
./slot-machine
```

Or compile directly:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 main.cpp -o slot-machine
```

On Windows with MinGW, compile with `g++ -std=c++17 main.cpp -o slot-machine.exe` and run `slot-machine.exe`.

## Rules

Start with 100 virtual credits. Bet a whole number from 1–10 per spin, within your balance. Three matching symbols return 5× the bet; two matching symbols return 2×. Returns include the stake. Non-matching spins lose the stake. Enter `q`, `Q`, or end-of-input to quit. Sessions have a 10,000-spin limit.

```sh
./slot-machine --help
./slot-machine --seed 42
```

The same seed and inputs reproduce a session on the same C++ standard-library implementation. Symbol distributions can differ across library implementations. This is a programming exercise; it has no monetary value, purchases, or payment integration.

## Checks

```sh
make test
make clean
```

Tests use Python's standard-library `unittest` and check invalid input, end-of-input handling, seed validation and reproducible sessions. GitHub Actions compiles and runs them. Build from source; generated executables are excluded from the current source tree.
