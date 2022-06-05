#include <iostream>
#include "serial_container.hpp"
#include "list_container.hpp"
#include "singly_linked_list_container.hpp"
#include "util.hpp"
#include <fstream>

int main()
{
	std::fstream file;
	file.open("file.txt", std::ios::out);

	Serial_container<int> serial_cont{ 0,1,2,3,4,5,6,7,8,9 };
	test_container(file, serial_cont);

	List_container<int> list_cont{ 0,1,2,3,4,5,6,7,8,9 };
	test_container(file, list_cont);

	Singly_linked_list_container<int> sin_list_cont{ 0,1,2,3,4,5,6,7,8,9 };
	test_container(file, sin_list_cont);
	file.close();

	if (eq_file("file.txt", "benchmark.txt"))
	{
		std::cout << "Successfully" << std::endl;
	}
	else
	{
		std::cout << "Fail!!!" << std::endl;
		return 1;
	}
}


