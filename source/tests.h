#pragma once
#include <vector>

class TestSystem {
private:
	using TestPtr = bool (*)();
	static std::vector<TestPtr> tests;

	static bool test1(); // ���� �� ����������������� 3�3
	static bool test_time(size_t how_many_times = 1); // ���� �� ����������� � ����� ����������

	static void add_tests();
public:
	static void run_all_tests();
};