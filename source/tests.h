#pragma once
#include <vector>

class TestSystem {
private:
	using TestPtr = bool (*)();
	static std::vector<TestPtr> tests;

	static bool test1(); // тест на работоспособность 3х3
	static bool test_time(); // тест на оптимизацию и время выполнения

	static void add_tests();
public:
	static void run_all_tests();
};