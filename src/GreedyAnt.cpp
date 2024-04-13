#include "Ant.h"
#include "GreedyAnt.h"

GreedyAnt::GreedyAnt(int deadline, int numberOfLibraries) : Ant(deadline, numberOfLibraries) {}
int GreedyAnt::nextLibrary(std::vector<Library> &libraries, int iter, double p)
{

    int bestIdx = -1;
    double bestValue{};
    for (int i = 0; i < libraries.size(); i++)
    {
        if (!m_signedIn[i])
        {
            double approxValue = libraries[i].getApproxValue(m_deadline);
            if (approxValue == -1.0)
                continue;

            if (approxValue > bestValue)
            {
                bestValue = approxValue;
                bestIdx = i;
            }
        }
    }

    if (bestIdx == -1)
    {
        return -1;
    }

    int pickedLibrary = bestIdx;

    m_signedIn[pickedLibrary] = true;
    m_deadline -= libraries[pickedLibrary].getSignUpTime();
    m_path.emplace_back(pickedLibrary);

    return pickedLibrary;
}

