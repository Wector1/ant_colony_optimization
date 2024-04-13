#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>
#include "Ant.h"
#include "AntColonyOptimization.h"
#include "Library.h"
#include "GreedyAnt.h"
#include <chrono>

void solve(double p)
{
    auto startClock = std::chrono::high_resolution_clock::now();

	// reading data
    int numOfBooks, numOfLibraries, days;
    std::cin >> numOfBooks >> numOfLibraries >> days;
    Ant::bookDeltaPheromones.resize(numOfBooks);
    Ant::bookPheromones.resize(numOfBooks);
    std::vector<Library> libraries(numOfLibraries);
    std::vector<int> values(numOfBooks);

    for (int i = 0; i < numOfBooks; i++)
    {
        std::cin >> values[i];
    }

    for (int i = 0; i < numOfLibraries; i++)
    {
        int n, t, m;
        std::cin >> n >> t >> m;

        libraries[i] = Library(n, t, m);

        for (int j = 0; j < n; j++)
        {
            int num;
            std::cin >> num;
            libraries[i].addBook(num, values[num]);
        }
        libraries[i].calculatePrefixSums();
    }

    PheromoneAnt::generator.seed(20);
    srand(24);

    auto greedyAnt = std::shared_ptr<Ant>(new GreedyAnt(days, numOfLibraries));

    while (greedyAnt->nextLibrary(libraries, 0, 0.05) != -1);

    ACO testInstance(1, days, p, numOfLibraries);
    testInstance.iteration(libraries, 0);
    auto startClockOneIter = std::chrono::high_resolution_clock::now();
    testInstance.iteration(libraries, 1);
    auto endClockOneIter = std::chrono::high_resolution_clock::now();

    int numberOfAnts = std::min(std::max(2, 10 * 1000000 / (int)std::chrono::duration_cast<std::chrono::microseconds>(endClockOneIter - startClockOneIter).count()), 1000);

    ACO instance(numberOfAnts, days, p, numOfLibraries);
    instance.set_best(libraries, greedyAnt);

	int best = 0;
	int iter_no_change = 10;
	int max_iter_no_change = 10;
    for (int i = 0;; i++)
    {
        auto startClockIter = std::chrono::high_resolution_clock::now();

        if (i % 5 == 0 && i != 0)
        {
            instance.mutate(libraries, i);
        }
        if (i % 10 == 0 && i != 0)
        {
            instance.mutate(libraries, i, true);
        }

        instance.iteration(libraries, i);

        auto endClock = std::chrono::high_resolution_clock::now();

		if (instance.getBest() > best) {
            best = instance.getBest();
			iter_no_change = -1;
		}
		iter_no_change++;
        if (iter_no_change > 10)
            break;
    }

    auto path = instance.GetBestPath();
    int deadline = days;
    std::cout << path.size() << std::endl;
    std::set<int> scanned;
    for (auto &idx : path)
    {

        int signedIn = libraries[idx].getNumberOfBooksScanned(deadline);
        deadline -= libraries[idx].getSignUpTime();
        int scannedFromThisLib{};
        std::vector<int> toCout;
        auto books = libraries[idx].getAllBooks();
        for (auto &[number, value] : books)
        {
            if (!scanned.count(number))
            {

                toCout.push_back(number);
                scanned.insert(number);
                if (++scannedFromThisLib >= signedIn)
                    break;
            }
        }

        if (!toCout.empty())
        {
            std::cout << idx << ' ' << toCout.size() << std::endl;
            for (auto &number : toCout)
                std::cout << number << ' ';
        }
        else
        {
            std::cout << idx << ' ' << 1 << std::endl;
            std::cout << books[0].number;
        }

        std::cout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    PheromoneAnt::m_alfa = 8;
    PheromoneAnt::m_beta = 4;
    PheromoneAnt::m_gamma = 2;
    solve(0.1);
}
