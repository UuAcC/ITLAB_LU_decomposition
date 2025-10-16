#include <iostream>
using namespace std;

typedef double Type;

class SquareMatrix {
private:
	size_t size;
	Type* array;
	static constexpr size_t TypeSize = sizeof(Type);
public:
	SquareMatrix(size_t s, Type* in_arr = nullptr) : size(s) { 
		array = new Type[size * size]{}; 
		if (in_arr != nullptr)
			std::copy(in_arr, in_arr + size * size, array);
	}
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

	// пока самая простая реализация для тестов
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

	SquareMatrix get_LU() {
		Type* A = new Type[size * size];
		std::copy(array, array + size * size, A);
		size_t k_iter_max = size - 1;
		for (size_t k = 0; k < k_iter_max; k++) {
			for (size_t i = k + 1; i < size; i++)
				A[i * size + k] /= A[k * size + k];
			for (size_t j = k + 1; j < size; j++) {
				for (size_t i = k + 1; i < size; i++)
					A[i * size + j] -= A[i * size + k] * A[k * size + j];
			}
		}
		SquareMatrix res(size, A); delete[] A;
		return res;
	}

	friend void print_LU(const SquareMatrix& m) {
		Type* arr = m.array;
		const size_t n = m.size;
		cout << "Matrix L:\n";
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				if (j < i) cout << arr[i * n + j];
				else cout << (int)(i == j);
				cout << " ";
			}
			cout << endl;
		}
		cout << "Matrix U:\n";
		for (size_t i = 0; i < n; i++) {
			for (size_t j = 0; j < n; j++) {
				if (j >= i) cout << arr[i * n + j];
				else cout << 0;
				cout << " ";
			}
			cout << endl;
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
				ostr << m.array[i * n + j] << " ";
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

	SquareMatrix LU = A.get_LU();
	print_LU(LU);

	return 0;
}