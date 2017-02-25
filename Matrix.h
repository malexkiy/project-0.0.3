#pragma once
class Matrix
{
private:
	size_t _rows;
	size_t _cols;
	int *_data;
	Matrix(size_t, size_t, int*);

public:
	Matrix();
	Matrix(size_t, size_t);
	~Matrix();

	void fill(const char* fileName);
	void print() const;
	Matrix operator+(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	Matrix& operator=(const Matrix&);
};

