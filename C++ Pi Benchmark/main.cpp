#include "benchmark.h"
#include <iostream>
#include <conio.h>
#include <string>

int main(int argc, char** argv)
{
	unsigned int threads = 0;
	bool FPU;
	char FPU_char;
	int score = 0;
	CalculatePi calculator;

	std::cout << "Would you like to stress the FPU (F) or the INT (I)?" << std::endl;
	std::cin >> FPU_char;

	if (tolower(FPU_char) == 'f')
	{
		FPU = true;
		std::cout << "Running FPU test." << std::endl;
	}
	else if (tolower(FPU_char) == 'i')
	{
		FPU = false;
		std::cout << "Running INT test." << std::endl;
	}
	else
	{
		std::cout << "Invalid input, assuming INT." << std::endl;
		FPU = false;
	}
	
	std::cout << "Enter thread count to run test, or enter 0 to automatically run with the number of threads detected on your CPU:" << std::endl;
	std::cin >> threads;

	if (threads == 0)
		score = calculator.benchmark(FPU);
	else
		score = calculator.benchmark(threads, FPU);
		
	std::cout << "Score: " << score << std::endl << "Press any key to continue..." << std::endl;

	_getch();
}