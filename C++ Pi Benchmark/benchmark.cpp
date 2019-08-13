#include "benchmark.h"
#include <future>
#include <tuple>
#include <chrono>
#include <thread>
#include <random>
#include <iostream>

unsigned long isqrt(unsigned long x)
{
	register unsigned long op, res, one;

	op = x;
	res = 0;

	one = 1 << 30;
	while (one > op)
		one >>= 2;

	while (one != 0)
	{
		if (op >= res + one)
		{
			op -= res + one;
			res += one << 1;
		}
		res >>= 1;
		one >>= 2;
	}

	return res;
}

int CalculatePi::benchmark(unsigned int threads, bool FPU)
{
	std::cout << "Running benchmark across " << threads << " threads..." << std::endl;

	std::future<std::tuple<unsigned long, unsigned long>>* thr = new std::future<std::tuple<unsigned long, unsigned long>>[threads];
	volatile bool running = true;

	if (FPU)
		for (unsigned int i = 0; i < threads; i++)
			thr[i] = std::async(std::launch::async, calculateFPU, &running);
	else
		for (unsigned int i = 0; i < threads; i++)
			thr[i] = std::async(std::launch::async, calculateINT, &running);

	std::this_thread::sleep_for(std::chrono::seconds(30));

	unsigned long total = 0;
	unsigned long in = 0;
	running = false;

	for (unsigned int i = 0; i < threads; i++)
	{
		std::tuple<unsigned long, unsigned long> ret = thr[i].get();
		total += std::get<0>(ret);
		in += std::get<1>(ret);
	}

	std::cout << "Calculated following value for pi: " << ((double)in / (double)total) * 4 << std::endl;
	return total / 100000;
}

std::tuple<unsigned long, unsigned long> CalculatePi::calculateFPU(volatile bool* run)
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_real_distribution<> dist(0, 1);
	unsigned long total = 0;
	unsigned long in = 0;

	while (*run)
	{
		double x = dist(e2);
		double y = dist(e2);
		total++;

		if (std::sqrt(std::pow(x, 2) + std::pow(y, 2)) < 1)
			in++;
	}
	return std::tuple<int, int>(total, in);
}

std::tuple<unsigned long, unsigned long> CalculatePi::calculateINT(volatile bool* run)
{
	std::random_device rd;
	std::mt19937 e2(rd());
	std::uniform_int_distribution<> dist(0, INT16_MAX);
	unsigned long total = 0;
	unsigned long in = 0;

	while (*run)
	{
		unsigned long x = dist(e2);
		unsigned long y = dist(e2);
		total++;

		if (isqrt(x * x + y * y) < INT16_MAX)
			in++;
	}

	return std::tuple<unsigned long, unsigned long>(total, in);
}

int CalculatePi::benchmark(bool FPU)
{
	unsigned int threads = std::thread::hardware_concurrency();
	return this->benchmark(threads, FPU);
}