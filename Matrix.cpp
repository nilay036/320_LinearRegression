#include "Matrix.h"
#include <iostream>
#include <cstddef>
#include <stdlib.h>
#include <string>
using namespace std;

//default constructor
template <class T>
Matrix<T>::Matrix()
{
	numRows = 0;
	numCols = 0;	
	data = allocateData();
}

//main  constructor
template <class T>
Matrix<T>::Matrix(int r, int c)
{
	if(r <= 0 || c <= 0)
		cout << "can't make an array with negative/zero number of rows/columns" << endl;
	else
	{
		numRows = r;
		numCols = c;
		data = allocateData();
	}
}
template <class T>
T** Matrix<T>::allocateData() const
{
	T** array = new T*[numRows]; //creat the array that stores the rows
	for(int i = 0; i < numRows; i++)
		array[i] = new T[numCols]();
       			//create each row, which is num columns long, and initializes elements to 0
	return array;
}

template <class T>
Matrix<T>::~Matrix()
{
	for( int i = 0; i < numRows; i++)
		delete[] data[i]; //delete each row
	delete[] data; //delete the array of rows
}

//copy  constructor
template <class T>
Matrix<T>::Matrix(const Matrix& copy)
{
	numRows = copy.numRows;
	numCols = copy.numCols;
	data = allocateData();
	for(int i = 0; i < copy.numRows; i++)
		for (int j = 0; j < copy.numCols; j++)
			data[i][j] = copy.data[i][j];
}

template <class T>
Matrix<T>& Matrix<T>::operator =(const Matrix& rhs)
{
	Matrix copy(rhs);
	numRows = copy.numRows;
	numCols = copy.numCols;
	data = allocateData();
	swapData(copy);
}

template <class T>
void Matrix<T>::swapData(Matrix<T>& temp)
{
	T** tempData = data;
	data = temp.data;
	temp.data = tempData;
}

template <class T>
ostream& operator <<(ostream& os, Matrix<T>& rhs)
{
	return os <<rhs.printMatrix();
}

template <class T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& rhs)
{
	if(numCols != rhs.numRows)
		throw "left hand side's number of columns != right hand side's number of rows";
	Matrix<T> output = Matrix(numRows, rhs.numCols);
	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < rhs.numCols; j++)
			for(int k = 0; k < numCols; k++)
				output[i][j] += data[i][j] * rhs[k][j]; 
	data = output.data;
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& rhs)
{
	if(numRows != rhs.numRows || numCols != rhs.numCols)
		throw "the rows and columns don't match";
	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < numCols; j++)
			data[i][j] += rhs[i][j];
	return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& rhs)
{
	if(numRows != rhs.numRows || numCols != rhs.numCols)
		throw "the rows and columns don't match";
	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < numCols; j++)
			data[i][j] -= rhs[i][j];
	return *this;
}

template <class T>
const Matrix<T> Matrix<T>::operator *(const Matrix<T>& rhs) const
{
	if(numCols != rhs.numRows)
		throw "left hand side's number of columns != right hand side's number of rows";
	Matrix<T> output = Matrix(numRows, rhs.numCols);
	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < rhs.numCols; j++)
			for(int k = 0; k < numCols; k++)
				output[i][j] += data[i][j] * rhs[k][j]; 
	return output;
	//return Matrix(*this) *= rhs; why does this cause invalid frees / reads?
}
template <class T>
const Matrix<T> Matrix<T>::operator +(const Matrix<T>& rhs)const
{
	return Matrix(*this) += rhs;
}

template <class T>
const Matrix<T> Matrix<T>::operator -(const Matrix<T>& rhs)const
{
	return Matrix(*this) -= rhs;
}


template <class T>
T*& Matrix<T>::operator [](const int& row)const
{
	//change the index to size_t?
	return data[row];
}

template <class T>
const Matrix<T>& Matrix<T>::pad()
{
	int newSize = 2;
	while( (newSize < numRows || newSize < numCols) && newSize > 0)//>0 so that if the int rolls over it ends
		newSize*=2;

	T** oldData = data;
	int oldRows = numRows;
	int oldCols = numCols;
	numRows = numCols = newSize;
	
	data = allocateData();
	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < numCols; j++)
		{
			if(i >= oldRows || j >= oldCols)
				if(i == j)
					data[i][j] = 1;
				else
					data[i][j] = 0;
			else
				data[i][j] = oldData[i][j];
		}
	for(int i = 0; i < oldRows; i++)
		delete [] oldData[i];
	delete [] oldData;
	return *this;
}
template <class T>
const Matrix<T>* Matrix<T>::transpose()
{
	cout << "r: " << numRows << " c: " << numCols << endl;
	Matrix<T>* transposed = new Matrix<T>(*this);
	for(int i = 0; i < numRows; i++)
		for(int j = i; j < numCols; j++)//j starts at i because it swaps the top and bottom triangle
			swap((*transposed)[i][j], (*transposed)[j][i]);
	return transposed;
}

//template <class T>
//Matrix<T>& Matrix<T>::invese()

template <class T>
void Matrix<T>::fillMatrix(string type, T value)
{
	
	for(int i = 0; i < numRows; i++)
		for(int j = 0; j < numCols; j++)
		{
			if(type == "full")
				data[i][j] = value;

			if(type == "diagonal")
			{
				if(i == j)
					data[i][j] = value;
				else
					data[i][j] = 0;
			}
			if(type == "upper-triangle")
			{
				if(j > i)
					data[i][j] = value;
				else
					data[i][j] = 0;
			}
			if(type == "lower-triangle")
			{
				if(i > j)
					data[i][j] = value;
				else
					data[i][j] = 0;
			}
			if(type == "random")
				data[i][j] = (rand() % value) + 1;
		}
}
template <class T>
string Matrix<T>::printMatrix() const
{
	string out = "";
	for(int i = 0; i < numRows; i++)
	{
		out += "| ";
		for(int j = 0; j < numCols; j++)
			out += to_string(data[i][j]) + " ";
		out += "|\n";
	}
	return out;
}



