#ifndef CPP_GREEDYANT_H
#define CPP_GREEDYANT_H
#include "Ant.h"

class GreedyAnt : public Ant
{
public:
    GreedyAnt(int deadline, int numberOfLibraries);
    int nextLibrary(std::vector<Library> &libraries, int iter, double p) override;
};

#endif // CPP_GREEDYANT_H
