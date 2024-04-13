#ifndef PHEROMONE_ANT_H
#define PHEROMONE_ANT_H
#include "Ant.h"
class PheromoneAnt: public Ant
{
public:
    static int m_alfa, m_beta, m_gamma;
    static std::default_random_engine generator;
	PheromoneAnt() = default;
	PheromoneAnt(int deadline, int numberOfLibraries);
	double calculateProbability(Library &lib, int idx, int iter, double p);
	static int pickLibrary(std::vector<std::pair<double, int>> &probabilities);
    int nextLibrary(std::vector<Library> &libraries, int iter, double p) override;
};
#endif
