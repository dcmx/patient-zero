#include <iostream>
#include <random>
#include <vector>

typedef std::mt19937_64 RandomEngine;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		std::cerr << "usage: " << argv[0] << " n d" << std::endl;
		return EXIT_FAILURE;
	}

	const unsigned int n = atoi(argv[1]);
	const unsigned int d = atof(argv[2]);

	std::vector<unsigned int> stubs(n);
    std::vector<unsigned int> free(n);

    for (unsigned int i = 0; i < n; ++i) {
        stubs[i] = d;
        free[i] = i;
    }

    std::random_device rd;
    RandomEngine randomEngine(rd());

    while (free.size() > 0) {
        const int last = free.size() - 1;
        std::uniform_int_distribution<unsigned int> uniformDistribution(0, last);

        const unsigned int pick = uniformDistribution(randomEngine);

        if (stubs[free[last]] == 1 && pick == last)
            continue;

		std::cout << free[last] << " " << free[pick] << std::endl;

        --stubs[free[last]];
        if (stubs[free[last]] == 0)
            free.pop_back();

        --stubs[free[pick]];
        if (stubs[free[pick]] == 0) {
            for (unsigned int i = pick; i < last; ++i)
                free[i] = free[i + 1];
            free.pop_back();
        }

    }
    stubs.clear();
    free.clear();

	return EXIT_SUCCESS;
}
