#pragma once
#include "serial_container.hpp"
#include <ostream>
#include <fstream>


template<typename T, template<typename> typename CONT>
void test_find(std::ostream &str, CONT<T>& list_cont, T _value)
{
	str << "find:" << _value << std::endl;
	auto is_even = [&](T v) {return v == _value; };

	auto itr = std::find_if(list_cont.begin(), list_cont.end(), is_even);
	if (itr != list_cont.end())
	{
		str << "Found!" << std::endl;
	}
	else
	{
		str << "Not found!" << std::endl;
	}
}


template<typename T, template<typename> typename CONT>
void test_container(std::ostream& str, CONT<T>& cont)
{

	str << cont << std::endl;
	str << cont.size() << std::endl;
	cont.erase(2);
	cont.erase(3);
	cont.erase(4);
	str << cont << std::endl;
	cont.insert(10, 0);
	str << cont << std::endl;
	cont.insert(20, 4);
	str << cont << std::endl;
	cont.push_back(30);
	str << cont << std::endl;


	for (const auto& item : cont)
	{
		str << item << " ! ";
	}
	str << std::endl;

	for (auto iter = cont.begin(); iter != cont.end(); ++iter)
	{
		str << *iter << " ";
	}
	for (int i = 0; i < 2; i++) str << std::endl;

	CONT<T> val(std::move(cont));

	test_find(str, val, 7);
	str << std::endl;
	test_find(str, val, 19);
	str << std::endl;
}

bool eq_file(std::string name1, std::string name2)
{
	std::fstream file1;
	file1.open(name1, std::ios::in);

	std::fstream file2;
	file2.open(name2, std::ios::in);

	if (file1 && file2)
	{
		char ch1, ch2;
		bool result = true;
		while (file1.get(ch1) && file2.get(ch2))
		{
			if (ch1 != ch2)
			{
				return false;
			}
		}
	}
	else
		return false;
	return true;

}