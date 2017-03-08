#include "stdafx.h"
//#include "matrix.h"
#include <cassert>

template <typename T>
Matrix<T>::Matrix(int rows, int columns)
	: m_rows(rows), 
	  m_columns(columns),
	  m_entries(rows*columns)
{
	// empty on purpose
}

template <typename T>
T& Matrix<T>::operator() (int row, int column) {
	// assert row, column in proper range
	assert(
		(row > 0) && 
		(column > 0) && 
		(row <= m_rows) && 
		(column <= m_columns)
		);
	return m_entries[m_columns*(row - 1) + (column - 1)];
}

template <typename T>
T Matrix<T>::operator() (int row, int column) const {
	// assert row, column in proper range
	assert(
		(row > 0) &&
		(column > 0) &&
		(row <= m_rows) &&
		(column <= m_columns)
		);
	return m_entries[m_columns*(row - 1) + (column - 1)];
}