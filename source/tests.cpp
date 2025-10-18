#include "tests.h"
#include "square_matrix.h"

#include <chrono>
#include <random>

std::vector<bool(*)()> TestSystem::tests;

void TestSystem::add_tests() {
	tests.push_back(TestSystem::test1);
	tests.push_back(TestSystem::test_time);
}

void TestSystem::run_all_tests() {
	cout << "TestSystem:\n\n";
	add_tests(); bool last_res;
	for (auto TestPtr : tests) {
		last_res = (*TestPtr)();
		cout << ((last_res) ? "true" : "false") << endl;
	}
}

bool TestSystem::test1() {
	const size_t n = 3;
	Type arr[n * n]{ 
		2, 3, 1, 
		4, 7, 7, 
		6, 18, 22 
	};
	SquareMatrix A(n, arr);
	SquareMatrix LU = A.get_LU();

	SquareMatrix L(n), U(n);
	LU.decompose_LU(L, U);
	SquareMatrix Res = L * U;

	//print_LU(LU);
	//cout << endl << Res;
	cout << "Test1: ";
	return A == Res;
}

bool TestSystem::test_time() {

	cout << "Test time: ";
	return true;
}
