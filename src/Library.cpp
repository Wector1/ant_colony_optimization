#include "Library.h"
#include <algorithm>
#include <iostream>
#include "Ant.h"
Library::Library() : m_numberOfBooks(0),
					 m_signUpTime(0),
					 m_booksPerDay(0),
					 m_maxTime(0)
{
}

Library::Library(int n, int scanTime, int perDay) : m_numberOfBooks(n),
													m_signUpTime(scanTime),
													m_booksPerDay(perDay),
													m_maxTime(0)
{
}

void Library::addBook(int number, int value)
{
	m_books.push_back({number, value});
}


void Library::calculatePrefixSums()
{
	std::sort(m_books.begin(), m_books.end());
	int previous = 0;
	for (int i = 0; i < m_numberOfBooks; i += m_booksPerDay)
	{
		int sum{};
		for (int j = 0; j < m_booksPerDay && i + j < m_numberOfBooks; j++)
		{
			sum += m_books[i + j].value;
		}
		m_prefixSums.push_back(sum + previous);
		previous = m_prefixSums.back();
		m_pheromonesPrefixSums.push_back(1);
	}
	m_maxTime = m_numberOfBooks / m_booksPerDay + (m_numberOfBooks % m_booksPerDay > 0);
}

void Library::calculatePheromonesPrefixSums()
{
	double previous = 0;
	for (int i = 0; i < m_numberOfBooks; i += m_booksPerDay)
	{
		double sum{};
		for (int j = 0; j < m_booksPerDay && i + j < m_numberOfBooks; j++)
		{
			sum += Ant::bookPheromones[i + j].first;
		}
		m_pheromonesPrefixSums[i / m_booksPerDay] = sum + previous;
		previous += sum;
	}
}

double Library::getApproxValue(int time)
{
	if (time <= m_signUpTime)
		return -1.0;

	return (double)m_prefixSums[std::min(time - m_signUpTime - 1, m_maxTime - 1)] / m_signUpTime;
}

double Library::getBookPheromones(int time)
{
	return m_pheromonesPrefixSums[std::min(time - m_signUpTime - 1, m_maxTime - 1)];
}


int Library::getNumberOfBooksScanned(int deadline)
{
	return (int)std::min((long long)m_numberOfBooks, (long long)(deadline - m_signUpTime) * m_booksPerDay);
}
