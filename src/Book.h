#ifndef BOOK_H
#define BOOK_H

#include <vector>

class Book
{
public:
	int number;
	int value;

	inline bool operator<(const Book &book) const
	{
		return value > book.value;
	}

	inline bool operator==(const Book &book) const
	{
		return number == book.number;
	}

	inline bool operator>(const Book &book) const
	{
		return number > book.number;
	}
};



#endif
