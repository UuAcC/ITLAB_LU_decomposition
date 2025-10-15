#include <iostream>
using namespace std;

typedef double Type;

class SquareMatrix {
private:
	size_t size;
	Type* array;
	static constexpr size_t TypeSize = sizeof(Type);
public:
	SquareMatrix(size_t s) : size(s) { array = new Type[size * size]{}; }
	~SquareMatrix() { delete[] array; }

	SquareMatrix(const SquareMatrix& m) {
		size = m.size;
		array = new Type[size * size];
		memcpy(array, m.array, size * size * TypeSize);
	}
	SquareMatrix& operator=(const SquareMatrix& m) {
		if (this == &m) return *this;
		delete[] array;
		size = m.size;
		array = new Type[size * size];
		memcpy(array, m.array, size * size * TypeSize);
	}

	SquareMatrix(SquareMatrix&& m) noexcept {
		size = m.size;
		array = m.array;
		m.size = 0;
		m.array = nullptr;
	}
	SquareMatrix& operator=(SquareMatrix&& m) noexcept {
		if (this == &m) return *this;
		delete[] array;
		size = m.size;
		array = m.array;
		m.size = 0;
		m.array = nullptr;
		return *this;
	}

	Type& at(size_t i, size_t j) {
		if (i < 0 || i >= size || j < 0 || j >= size)
			throw out_of_range("Index should be between 0 and matrix size");
		return array[i * size + j];
	}
	const Type& at(size_t i, size_t j) const {
		if (i < 0 || i >= size || j < 0 || j >= size)
			throw out_of_range("Index should be between 0 and matrix size");
		return array[i * size + j];
	}

	SquareMatrix operator*(const SquareMatrix& m) {
		if (size != m.size)
			throw invalid_argument("Matrix sizes must be equal");

		SquareMatrix res(size);
		const size_t n = size;

		Type* res_arr = res.array;
		Type* this_arr = this->array;
		Type* m_arr = m.array;

		for (size_t i = 0; i < n; ++i) {
			Type* this_row = this_arr + i * n;
			Type* res_row = res_arr + i * n;
			for (size_t k = 0; k < n; ++k) {
				Type this_val = this_row[k];
				Type* m_row = m_arr + k * n;
				for (size_t j = 0; j < n; ++j) {
					res_row[j] += this_val * m_row[j];
				}
			}
		}
		return res;
	}

	void LU_decomposition(bool need_to_print = 0) {
		const size_t n = size;
		const size_t sz = n * (n + 1) / 2;

		Type* L = new Type[sz];
		Type* U = new Type[sz];
		
		Type s;
		for (size_t i = 0; i < n; i++) {
			L[i * (i + 1) / 2 + i] = 1;
		}
		for (size_t i = 0; i < n; i++) {
			Type* L_row = L + (i * (i + 1) / 2);  // Начало i-й строки в L
			Type* U_row = U + (n * i - i * (i - 1) / 2);  // Начало i-й строки в U
			Type* A_row = this->array + i * n; // Начало i-й строки в A
			for (size_t j = 0; j < i; j++) {
				s = 0;
				for (size_t k = 0; k < j; k++) {
					s += L_row[k] * U[n * k - k * (k - 1) / 2 + j];
				}
				L_row[j] = (A_row[j] - s) / U[n * j - j * (j - 1) / 2 + j];
			}
			for (size_t j = i; j < n; j++) {
				s = 0;
				for (size_t k = 0; k < i; k++) {
					s += L_row[k] * U[n * k - k * (k - 1) / 2 + j];
				}
				U_row[j] = A_row[j] - s;
			}
		}
		if (need_to_print) {
			cout << "Matrix L:\n";
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++)
				{
					if (i < j) cout << 0;
					else cout << L[i + (i + 1) / 2 + j];
					cout << ' ';
				}
				cout << endl;
			}
			cout << "Matrix U:\n";
			for (size_t i = 0; i < n; i++) {
				for (size_t j = 0; j < n; j++)
				{
					if (i > j) cout << 0;
					else cout << U[n * i - i * (i - 1) / 2 + j];
					cout << ' ';
				}
				cout << endl;
			}
		}
	}

	friend istream& operator>>(istream& istr, SquareMatrix& m) {
		size_t n = m.size;
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				istr >> m.array[i * n + j];
		return istr;
	}
	friend ostream& operator<<(ostream& ostr, SquareMatrix& m) noexcept {
		size_t n = m.size;
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++)
				ostr << m.array[i * n + j];
			ostr << endl;
		}
		return ostr;
	}
};

int main()
{
	size_t n;
	cout << "Size: "; cin >> n;

	SquareMatrix A(n);
	cout << "Enter matrix A:\n"; cin >> A;

	A.LU_decomposition(1);

	return 0;
}