#include "tests.h"
#include "square_matrix.h"

#include <chrono>
using namespace chrono;

#define TP steady_clock::time_point 
#define NOW steady_clock::now()

std::vector<bool(*)()> TestSystem::tests;

void TestSystem::add_tests() {
	tests.push_back(TestSystem::test1);
}

void TestSystem::run_all_tests() {
	std::cout << "TestSystem:\n\n";
	add_tests(); bool last_res;
	for (auto TestPtr : tests) {
		last_res = (*TestPtr)();
		std::cout << ((last_res) ? "true" : "false") << endl;
	}
	test_time();
}

bool TestSystem::test1() {
	const size_t n = 3;
	Type arr[n * n]{ 
		2, 3, 1, 
		4, 7, 7, 
		6, 18, 22 
	};
	SquareMatrix A(n, arr);
	SquareMatrix LU(A);

	get_LU(LU);

	SquareMatrix L(n), U(n);
	LU.decompose_LU(L, U);
	SquareMatrix Res = L * U;

	print_LU(LU);
	std::cout << endl << Res;

	std::cout << "Test1: ";
	return A == Res;
}

bool TestSystem::test_time() {
	auto now = system_clock::now();
	srand(now.time_since_epoch().count());

	TP start_init = NOW;
	const size_t n = 3000;
	SquareMatrix A(n);
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			A(i, j) = static_cast<double>(rand()); // используем random
		}
	} std::cout << "\nTime for init random matrix: "
		<< duration_cast<milliseconds>(NOW - start_init).count() << "ms";

	TP start_LU = NOW;
	get_LU(A);
	std::cout << "\nTime for LU decomposition: "
		<< duration_cast<milliseconds>(NOW - start_LU).count() << "ms";

	std::cout << "\nTotal time: "
		<< duration_cast<milliseconds>(NOW - start_init).count() << "ms";

	return true;
}
