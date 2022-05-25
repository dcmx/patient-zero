#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <vector>
#include <random>
#include <algorithm>

typedef std::mt19937_64 RandomEngine;

namespace PZ {


class Node {
public:
	Node(const unsigned int id) :
			id(id) {
	}

	inline operator int() const {
		return id;
	}
	inline std::vector<unsigned int>::const_iterator begin() const {
		return neighbors.begin();
	}
	inline std::vector<unsigned int>::const_iterator end() const {
		return neighbors.end();
	}
private:
	std::vector<unsigned int> neighbors;
	const unsigned int id;

	void addEdge(unsigned int neighbor) {
		neighbors.push_back(neighbor);
	}

	friend class Graph;

};

class Graph {
public:
	typedef std::vector<Node>::const_iterator NodeIterator;

	inline Graph(long int seed, const unsigned int n = 1) :
			n(0), randomEngine(seed) {
		nodes.reserve(n);
		while (this->n < n)
			addNode();
	}

	inline ~Graph() {
		nodes.clear();
	}
	inline void addNode() {
		nodes.push_back(Node(n));
		++n;
	}
	inline void addEdge(const unsigned int from, const unsigned int to) {
		while (n < from || n < to)
			addNode();
		nodes[from].addEdge(to);
		nodes[to].addEdge(from);
	}

	inline const Node& getNode(const unsigned int id) const {
		return nodes[id];
	}
	inline Node& getNode(const unsigned int id) {
		return nodes[id];
	}

	inline NodeIterator begin() const {
		return nodes.begin();
	}
	inline NodeIterator end() const {
		return nodes.end();
	}

	inline Node operator [](int i) const {
		return nodes[i];
	}
	inline Node& operator [](int i) {
		return nodes[i];
	}

	void forwardProcess(const unsigned int t, const double p, const unsigned int patientZero) {
		std::bernoulli_distribution Bi(p);
		std::vector<bool> recovered(n);
		std::vector<bool> seen(n, false);
		std::vector<unsigned int> newInfected;
		infected.push_back(patientZero);
		recovered[patientZero] = true;
		for (unsigned int round = 0; round < t; ++round) {
			for (unsigned int i : infected) {

				for (unsigned int j : nodes[i]) {
					if (!recovered[j] && Bi(randomEngine)) {
						newInfected.push_back(j);
						recovered[j] = true;
					}
				}
			}
			infected.clear();
			std::swap(infected, newInfected);
		}
	}

	unsigned int countInfected() const {
		return infected.size();
	}

	void BFS(const unsigned int start, const unsigned int depth, std::vector<bool> &visited) {
		std::vector<unsigned int> visitedNodes;
		std::vector<unsigned int> newNodes;
		visited[start] = true;
		visitedNodes.push_back(start);
		for (unsigned int round = 0; round < depth; ++round) {
			for (unsigned int j : visitedNodes) {
				for (unsigned int k : nodes[j]) {
					if (!visited[k]) {
						newNodes.push_back(k);
						visited[k] = true;
					}
				}
			}
			visitedNodes.clear();
			std::swap(visitedNodes, newNodes);
		}
	}

	unsigned int BFS(const unsigned int start, const unsigned int end) {
		if (start == end)
			return 0;
		std::vector<bool> visited(n);
		std::vector<unsigned int> visitedNodes;
		std::vector<unsigned int> newNodes;
		visited[start] = true;
		visitedNodes.push_back(start);
		unsigned int round;
		for (round = 0; round < 1000; ++round) {
			for (unsigned int j : visitedNodes) {
				for (unsigned int k : nodes[j]) {
					if(k == end)
						return round + 1;
					if (!visited[k]) {
						newNodes.push_back(k);
						visited[k] = true;
					}
				}
			}
			visitedNodes.clear();
			std::swap(visitedNodes, newNodes);
		}
		return round;
	}

	void reconstruct(const unsigned int t, std::vector<unsigned int> &matches) {
		std::vector<bool> reachable(n, true);
		bool haveMatches = true;
		for (unsigned int node : infected) {

			std::vector<bool> visited(n, false);
			BFS(node, t, visited);
			haveMatches = false;
			for (unsigned int i = 0; i < reachable.size(); ++i) {
				reachable[i] = reachable[i] && visited[i];
				haveMatches = haveMatches || reachable[i];
			}
			if (!haveMatches)
				return;
		}
		for (unsigned int i = 0; i < reachable.size(); ++i)
			if (reachable[i])
				matches.push_back(i);
	}

private:
	unsigned int n;
	std::vector<Node> nodes;
	std::vector<unsigned int> infected;

	RandomEngine randomEngine;
};

}

#endif /* SRC_GRAPH_H_ */
