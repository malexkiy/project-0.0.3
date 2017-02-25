#include "Matrix.h"
#include <iostream>
#include <fstream>
using namespace std;


Matrix::Matrix()
{
	_rows = 0;
	_cols = 0;
	_data = nullptr;
}


Matrix::Matrix(size_t rows, size_t cols)
{
	_rows = rows;
	_cols = cols;
	_data = new int[_rows*_cols]();
}


Matrix::Matrix(size_t rows, size_t cols, int *data)
{
	_rows = rows;
	_cols = cols;
	_data = data;
}


Matrix::~Matrix()
{
	delete[] _data;
}


void Matrix::fill(const char* fileName)
{
	ifstream file(fileName, ios_base::binary);

	if (!file.is_open())
		throw "Failed to open file\n";

	size_t r, c, size;
	file.read((char*)&r, sizeof(r));
	file.read((char*)&c, sizeof(c));
	size = 2 * sizeof(size_t) + r * c * sizeof(_data[0]);

	file.seekg(0, ios_base::end);
	if (size != file.tellg())
		throw "Invalid file!\n";

	file.seekg(2 * sizeof(size_t));
	
	delete[] _data;
	_rows = r;
	_cols = c;
	_data = new int[_rows*_cols]();

	file.read((char*)_data, _rows * _cols * sizeof(_data[0]));

	file.close();
}


void Matrix::print() const
{
	if (_data == nullptr || _rows == 0 || _cols == 0)
		throw "Matrix has not been initialized!\n";

	cout << endl;
	for (size_t r = 0; r < _rows; r++)
	{
		for (size_t c = 0; c < _cols; c++)
		{
			cout << _data[c + r*_cols] << "\t";
		}
		cout << endl;
	}
}


Matrix Matrix::operator+(const Matrix& m) const
{
	if (_data == nullptr || _rows == 0 || _cols == 0)
		throw "Matrix has not been initialized!\n";
	if (m._data == nullptr || m._rows == 0 || m._cols == 0)
		throw "Matrix has not been initialized!\n";
	if ((_rows != m._rows) || (_cols != m._cols))
		throw "Sizes are not equal!\n";

	int *data = new int[_rows*_cols];

	for (size_t i = 0; i < _rows * _cols; i++)
	{
		data[i] = _data[i] + m._data[i];
	}

	return Matrix(_rows, _cols, data);
}


Matrix Matrix::operator*(const Matrix& m) const
{
	if (_data == nullptr || _rows == 0 || _cols == 0)
		throw "Matrix has not been initialized!\n";
	if (m._data == nullptr || m._rows == 0 || m._cols == 0)
		throw "Matrix has not been initialized!\n";
	if (_cols != m._rows)
		throw "Matrices can not be multiplied!\n";

	int *data = new int[_rows*m._cols];
	int sum;
	int *m1_c, *m1_base, *m2_r, *m2_base, *data_out;
	
	m1_base = _data;
	data_out = data;
	for (size_t r = 0; r < _rows; r++)
	{
		m2_base = m._data;
		for (size_t c = 0; c < m._cols; c++)
		{
			sum = 0;
			m1_c = m1_base;
			m2_r = m2_base;
			for (size_t i = 0; i < _cols; i++)
			{
				sum += *m1_c * *m2_r;
				m1_c++;
				m2_r += m._cols;
			}
			*data_out++ = sum;
			m2_base++;
		}
		m1_base += _cols;
	}

	return Matrix(_rows, m._cols, data);
}


Matrix& Matrix::operator=(const Matrix& m)
{
	delete[] _data;
	_rows = m._rows;
	_cols = m._cols;
	_data = new int[_rows*_cols];
	memcpy(_data, m._data, _rows * _cols * sizeof(_data[0]));

	return *this;
}
