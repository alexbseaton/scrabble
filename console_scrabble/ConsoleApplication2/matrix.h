#pragma once
#include "stdafx.h"
#include <vector>
template <typename T>
class Matrix 
{

public:
	// Constructor, creates a rows by columns matrix
	// of default constructed T
	Matrix(int rows, int columns);

	//~Matrix();

	// Get methods for the entry at (row, column)
	T& operator() (int row, int column); // to set
	T operator() (int row, int column) const; // to get

	//Data
private:
	int m_rows; //number of rows
	int m_columns; // numbers of columns
	std::vector<T> m_entries; // where we store the data
	// format:
	// matrix 
	// (1 2 3)
	// (4 5 6)
	// would be stored as
	// (1 2 3 4 5 6)

};

#include "matrix.tpp"