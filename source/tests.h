#pragma once
#include <vector>

class TestSystem {
private:
	using TestPtr = bool (*)();
	static std::vector<TestPtr> tests;

	static bool test1(); // ���� �� ����������������� 3�3
	static bool test_time(); // ���� �� ����������� � ����� ����������

	static void add_tests();
public:
	static void run_all_tests();
};