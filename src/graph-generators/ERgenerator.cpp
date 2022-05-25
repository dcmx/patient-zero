#include <iostream>
#include <random>

typedef std::mt19937_64 randomEngine;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " n p" << std::endl;
		return EXIT_FAILURE;
	}

	const unsigned int n = atoi(argv[1]);
	const double p = atof(argv[2]);

	std::random_device rd;
	randomEngine randomEngine(rd());

	std::bernoulli_distribution distribution(p);

	for (unsigned int i = 0; i < n; ++i)
		for (unsigned int j = 0; j < i; ++j)
			if (distribution(randomEngine))
				std::cout << i << " " << j << std::endl;

	return EXIT_SUCCESS;
}
