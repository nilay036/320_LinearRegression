#ifndef MATRIX_H
#define MATRIX_H
#include <stdlib.h>
#include <string>
using namespace std;

template <class T>
class Matrix
{
	//private:
	public:
		T** data;
		int numCols = 0;
		int numRows = 0;
	//public:
		Matrix();
		Matrix(int, int);
		~Matrix();
		Matrix(const Matrix&);
		
		T** allocateData() const;
		void swapData(Matrix&);

		T*& operator [] (const int&) const;
		Matrix& operator = (const Matrix&);
		bool operator == (const Matrix&) const;

		Matrix& operator *= (const Matrix&);
		Matrix& operator += (const Matrix&);
		Matrix& operator -= (const Matrix&);
		
		const Matrix operator * (const Matrix&) const;
		const Matrix operator + (const Matrix&) const;
		const Matrix operator - (const Matrix&) const; 

		//scalar ops
		Matrix& operator *= (const T&);
		const Matrix operator * (const T&) const;
		template <class D>
		friend 	ostream& operator <<(ostream&, Matrix<D>&);
		
		const Matrix& pad();
		const Matrix* transpose();
		Matrix& inverse();

		void fillMatrix(string, T);
		string printMatrix() const;

};
#endif
