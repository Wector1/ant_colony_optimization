#include "PheromoneAnt.h"

PheromoneAnt::PheromoneAnt(int deadline, int numberOfLibraries) : Ant(deadline, numberOfLibraries)
{
}

int PheromoneAnt::pickLibrary(std::vector<std::pair<double, int>> &probabilities)
{
    double sum = probabilities.back().first;

    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    double randNum = distribution(generator) * sum;

    int idx{};
    for (int i = (int)probabilities.size(); i > 0; i /= 2)
    {
        while (idx + i < (int)probabilities.size() && probabilities[idx + i - 1].first <= randNum)
            idx += i;
    }

    return probabilities[idx].second;
}

int PheromoneAnt::nextLibrary(std::vector<Library> &libraries, int iter, double p)
{
    std::vector<std::pair<double, int>> probabilities;
    probabilities.emplace_back(0, -1);

    double previous{};
    for (int i = 0; i < libraries.size(); i++)
    {
        if (!m_signedIn[i])
        {
            double prob = calculateProbability(libraries[i], i, iter, p);
            if (prob == -1.0)
                continue;

            probabilities.emplace_back((prob + previous), i);
            previous = probabilities.back().first;
        }
    }
    if (probabilities.size() == 1)
        return -1;

    int pickedLibrary = pickLibrary(probabilities);

    m_signedIn[pickedLibrary] = true;
    m_deadline -= libraries[pickedLibrary].getSignUpTime();
    m_path.emplace_back(pickedLibrary);

    return pickedLibrary;
}

double PheromoneAnt::calculateProbability(Library &lib, int idx, int iter, double p)
{

    double totalValue = lib.getApproxValue(m_deadline);
    if (totalValue == -1.0)
        return -1.0;

    double numOfPheromones, numOfBooksPheromones = lib.getBookPheromones(m_deadline);
	numOfPheromones = pheromones.count({m_path.size(), idx})
						  ? pheromones[std::make_pair(m_path.size(), idx)].first * std::pow(1.0 - p, iter - (double)pheromones[std::make_pair(m_path.size(), idx)].second)
						  : 1 * std::pow(1.0 - p, (double)iter);
    // }

    double probability = pow(totalValue, m_alfa) * pow(numOfPheromones, m_beta) * pow(numOfBooksPheromones, m_gamma);

    return probability;
}

int PheromoneAnt::m_alfa;
int PheromoneAnt::m_beta;
int PheromoneAnt::m_gamma;
std::default_random_engine PheromoneAnt::generator;
