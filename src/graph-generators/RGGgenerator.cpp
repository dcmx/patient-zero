#include <iostream>
#include <random>
#include <vector>

typedef std::mt19937_64 randomEngine;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " n r^2Pi" << std::endl;
		return EXIT_FAILURE;
	}

	const unsigned int n = atoi(argv[1]);
	const double r2pi = atof(argv[2]);
	const double r2 = r2pi/3.14159265358979323846;

	std::vector<double> x(n);
	std::vector<double> y(n);

	std::random_device rd;
	randomEngine randomEngine(rd());
	std::uniform_real_distribution<double> U(0.0, std::sqrt((double) n) );

	for (unsigned int i = 0; i < n; ++i) {
		x[i] = U(randomEngine);
		y[i] = U(randomEngine);
	}

	for (unsigned int i = 0; i < n; ++i)
		for (unsigned int j = 0; j < i; ++j) {
			const double dx = x[i]-x[j];
			const double dy = y[i]-y[j];
			if (dx*dx + dy*dy < r2)
				std::cout << i << " " << j << std::endl;
		 }
	return EXIT_SUCCESS;
}
