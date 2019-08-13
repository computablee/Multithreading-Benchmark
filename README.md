# Multithreading-Benchmark
This is a benchmark in C++ that calculates single-threaded and multi-threaded throughput of the INT and FPU portions of any given processor.

## Compiling
A makefile is given in the `C++ Pi Benchmark` folder. If you are not using the makefile, the program is intended for `gcc` with the `-O0` flag.

## About
This program is intended for multi-threaded testing. As such, effort is put in to ensure little cross-thread communication. Unfortunately, I have yet to move to Boost, which allows interruptable threads, which will eliminate the need for a `volatile` flag.

It has the ability to test both the INT and the FPU separately, which is important when comparing different architectures of CPUs.
