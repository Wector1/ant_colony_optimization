#include "Ant.h"
#include <iostream>

double pow(double base, int exponent)
{
    double res = 1;
    for (int i = 0; i < exponent; i++)
    {
        res *= base;
    }
    return res;
}

Ant::Ant(int deadline, int numberOfLibraries)
    : m_signedIn(numberOfLibraries), m_deadline(deadline)
{
    m_totalValue = 0;
}

int Ant::mutate(std::vector<Library> &libraries, int deadline, bool localSearch)
{
	// if localSearch == true, then we only mutate neighbors
    int bestValue = totalValue(libraries, deadline);
    int iterations = 0;

    for (int i = 0; (i < (localSearch ? m_path.size() - 1 : 1000)) && iterations < (localSearch ? 10 : 50); i++)
    {
        int idx1, idx2;
        if (localSearch)
        {
            idx1 = i;
            idx2 = i + 1;
            std::swap(m_path[idx1], m_path[idx2]);
        }
        else
        {
            idx1 = rand() % m_path.size();
            idx2 = rand() % m_path.size();
            std::swap(m_path[idx1], m_path[idx2]);
        }

        int total = totalValue(libraries, deadline);

        if (total > bestValue)
        {
            bestValue = total;
            ++iterations;
            i = 0;
        }
        else
        {
            std::swap(m_path[idx1], m_path[idx2]);
        }
    }
    totalValue(libraries, deadline);
    return bestValue;
}

int Ant::totalValue(std::vector<Library> &libraries, int deadline)
{
    int total{};
    std::unordered_set<int> scanned;
    for (auto &lib : m_path)
    {
        int numOfScanned = libraries[lib].getNumberOfBooksScanned(deadline);
        deadline -= libraries[lib].getSignUpTime();
        int scannedFromThisLib{};
        for (auto &[bookIdx, bookValue] : libraries[lib].getAllBooks())
        {
            if (!scanned.count(bookIdx))
            {
                scanned.insert(bookIdx);
                total += bookValue;
                if (++scannedFromThisLib >= numOfScanned)
                    break;
            }
        }
    }
    m_totalValue = total;
    return m_totalValue;
}

void Ant::calculatePheromonesDeltas(std::vector<Library> &libraries, int bestValue, int deadline)
{
    int totalValue = getTotalValue();
    for (int i = 0; i < m_path.size() - 1; i++)
    {
        deltaPheromones[std::make_pair(i, m_path[i])] += (1 / (1 + (double)(bestValue - totalValue) /
                                                                                 std::min(totalValue, bestValue)));
    }
    std::unordered_set<int> scanned;
    for (auto &lib : m_path)
    {
        int numOfScanned = libraries[lib].getNumberOfBooksScanned(deadline);
        deadline -= libraries[lib].getSignUpTime();
        int scannedFromThisLib{};
        for (auto &[bookIdx, bookValue] : libraries[lib].getAllBooks())
        {
            if (!scanned.count(bookIdx))
            {
                scanned.insert(bookIdx);
                bookDeltaPheromones[bookIdx] += (1 / (1 + (double)(bestValue - totalValue) / std::min(bestValue, totalValue))) / 1000;
                if (++scannedFromThisLib >= numOfScanned)
                    break;
            }
        }
    }
}

void Ant::clear(int deadline)
{
    m_deadline = deadline;
    for (auto &it : m_signedIn)
        it = false;
    m_path.clear();
    m_totalValue = 0;
    deltaPheromones.clear();
    for (auto &it : bookDeltaPheromones)
        it = 0;
}

std::map<std::pair<int, int>, std::pair<double, int>> Ant::pheromones;
std::map<std::pair<int, int>, double> Ant::deltaPheromones;

std::vector<std::pair<double, int>> Ant::bookPheromones;
std::vector<double> Ant::bookDeltaPheromones;
