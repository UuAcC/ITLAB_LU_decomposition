#pragma once

#include <iostream>
using namespace std;

typedef double Type;

class SquareMatrix {
private:
	size_t size;
	Type* array;
	static constexpr size_t TypeSize = sizeof(Type);
public:
	SquareMatrix(size_t s, Type* in_arr = nullptr);
	~SquareMatrix();

	SquareMatrix(const SquareMatrix& m);
	SquareMatrix& operator=(const SquareMatrix& m);

	SquareMatrix(SquareMatrix&& m) noexcept;
	SquareMatrix& operator=(SquareMatrix&& m) noexcept;

	Type& at(size_t i, size_t j);
	const Type& at(size_t i, size_t j) const;

	// пока самая простая реализация для тестов
	SquareMatrix operator*(const SquareMatrix& m);
	bool operator==(const SquareMatrix& m);

	SquareMatrix get_LU();
	void decompose_LU(SquareMatrix& L, SquareMatrix& U);

	friend void print_LU(const SquareMatrix& m);

	friend istream& operator>>(istream& istr, SquareMatrix& m);
	friend ostream& operator<<(ostream& ostr, SquareMatrix& m) noexcept;
};