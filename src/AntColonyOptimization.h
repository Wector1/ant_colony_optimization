#ifndef ANT_COLONY_OPTIMIZATION_H
#define ANT_COLONY_OPTIMIZATION_H
#include <vector>
#include <array>
#include "Ant.h"
#include "GreedyAnt.h"
#include "PheromoneAnt.h"
#include <memory>


class ACO
{
	int m_numberOfAnts;
	double m_p;
	std::vector<std::shared_ptr<Ant>> m_ants;
	int m_deadline;
	int m_best;
	std::vector<int> m_bestPath;
	std::array<std::pair<int, std::shared_ptr<Ant>>, 10> m_bests;
	std::shared_ptr<Ant> m_bestAnt;

public:
	ACO() = default;
	ACO(int numberOfAnts, int deadline, double p, int numberOfLibraries);
	// for purpose of greedy ant
	void set_best(std::vector<Library> &libraries, const std::shared_ptr<Ant>& best);
	void createAnts(int numberOfLibraries);
	void calculateBestValue(std::vector<Library> &libraries);

	void calculatePheromones(std::vector<Library> &libraries, int iter, bool type);
	void iteration(std::vector<Library> &libraries, int index);
	void mutate(std::vector<Library> &libraries, int iter, bool localSearch = false);
	std::vector<int> GetBestPath() { return m_bestPath; }
	int getBest() { return m_best; }
	std::shared_ptr<Ant> getBestAnt() { return m_bestAnt; }
};

#endif
