#ifndef ANT_H
#define ANT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <random>
#include <unordered_set>
#include "Library.h"

class Ant
{
protected:
	int m_deadline{};
	std::vector<int> m_path;
	std::vector<int> m_signedIn;
	int m_totalValue{};

public:
	static std::map<std::pair<int, int>, std::pair<double, int>> pheromones;
	static std::map<std::pair<int, int>, double> deltaPheromones;
	static std::vector<std::pair<double, int>> bookPheromones;
	static std::vector<double> bookDeltaPheromones;

	Ant() = default;
	Ant(int deadline, int numberOfLibraries);
	virtual int nextLibrary(std::vector<Library> &libraries, int iter, double p) = 0;
	int mutate(std::vector<Library> &libraries, int deadline, bool localSearch = false);
	int totalValue(std::vector<Library> &libraries, int deadline);
	void calculatePheromonesDeltas(std::vector<Library> &libraries, int bestValue, int deadline);
	void clear(int deadline);
	std::vector<int> GetPath() { return m_path; };
	inline int getTotalValue() { return m_totalValue; };
	inline bool operator<(const Ant &ant) const { return m_deadline > ant.m_deadline; }
};

#endif
