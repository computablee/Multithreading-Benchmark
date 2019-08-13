#pragma once
#include <tuple>

class CalculatePi
{
private:
	static std::tuple<unsigned long, unsigned long> calculateFPU(volatile bool* run);
	static std::tuple<unsigned long, unsigned long> calculateINT(volatile bool* run);
public:
	int benchmark(unsigned int threads, bool FPU);
	int benchmark(bool FPU);
};