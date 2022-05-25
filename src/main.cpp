#include <iostream>
#include <random>

#include "graph.h"

using namespace PZ;

int main(int argc, char *argv[]) {

	if (argc != 4) {
		std::cerr << "usage: " << argv[0] << " n t p" << std::endl;
		return EXIT_FAILURE;
	}

	const unsigned int n = atoi(argv[1]);
	const unsigned int t = atoi(argv[2]);
	const double p = atof(argv[3]);

	std::random_device rd;
	RandomEngine randomEngine(rd());

	Graph graph(rd(), n);

	/* Stage 1; read network */
	unsigned int from, to;
	while (std::cin >> from >> to) {
		graph.addEdge(from, to);
	}

	/* Stage 2; forward-process */
	std::uniform_int_distribution<unsigned int> U(0, n - 1);
	const unsigned int patientZero = U(randomEngine);

	graph.forwardProcess(t, p, patientZero);

	if (graph.countInfected() <= 1) {
		std::cout << "only " << graph.countInfected() << " infected generated." << std::endl;
		return EXIT_FAILURE;
	}

	/* Strage 3; reconstruct patient zero */
	std::vector<unsigned int> matches;
	for (unsigned int i = 1; i <= t + 1; ++i) {
		matches.clear();
		graph.reconstruct(i, matches);
		if (matches.size() > 0) {
			std::cout << "found " << matches.size() << " candidates for time " << i << std::endl;
			break;
		} else
			std::cout << "no candidates for time " << i << std::endl;
	}

	bool found = false;
	for (auto match : matches)
		if (match == patientZero) {
			found = true;
			break;
		}

	if (found)
		std::cout << "identified patient zero." << std::endl;
	else
		std::cout << "did not identify patient zero." << std::endl;

	for (auto match : matches)
		std::cout << "match at distance: " << graph.BFS(patientZero, match) << std::endl;

	return EXIT_FAILURE;
}
