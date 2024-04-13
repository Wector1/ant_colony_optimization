#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include "Book.h"

class Library
{
    std::vector<Book> m_books;
    std::vector<int> m_prefixSums;
	std::vector<double> m_pheromonesPrefixSums;
    int m_numberOfBooks;
    int m_signUpTime;
    int m_booksPerDay;
	int m_maxTime;

public:
	Library();
    Library(int n, int scanTime, int perDay);
    void addBook(int number, int value);
    void calculateTotalTime();
    void calculatePrefixSums();
	void calculatePheromonesPrefixSums();
    double getApproxValue(int time);
	double getBookPheromones(int time);
    int getNumberOfBooksScanned(int deadline);

    inline int getSignUpTime() { return m_signUpTime; }
    inline std::vector<Book> getAllBooks() { return m_books; }
};

#endif
