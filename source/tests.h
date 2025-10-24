#pragma once
#include <vector>

class TestSystem {
private:
	using TestPtr = bool (*)();
	static std::vector<TestPtr> tests;

	// ���� �� ����������������� 3�3
	static bool test1(); 
	static bool test2();
	// ���� �� ����������� � ����� ����������
	static bool test_time(size_t how_many_times = 1, size_t _n = 1000); 

	static void add_tests();
public:
	static void run_all_tests();
};