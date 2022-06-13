#pragma once
#include <ostream>

template <typename T>
class Serial_container
{
public:
	Serial_container();
	Serial_container(Serial_container&& val);
	Serial_container(size_t);
	Serial_container(std::initializer_list<T>);
	void resize(int);
	T* data();
	int capacity();
	void reserve(int);
	void extension();
	void narrowing();	
	void push_back(T);
	void insert(T, int);
	void erase(int);
	int size();
	T get(int);
	T* begin();
	T* end();
	T operator[](int);
	~Serial_container();
	
private:
	T* member;
	int size_container;
	int size_memory;
	int end_index;
};


template <typename T>
Serial_container<T>::Serial_container() :size_container{ 0 }, end_index{ 0 }
{
	int size_for_new = 2;
	this->member = new T[size_for_new];
	this->size_memory = size_for_new;
}

template <typename T>
Serial_container<T>::Serial_container(Serial_container&& val) :size_container{ val.size_container }, end_index{ val.end_index }, member {val.member}, size_memory { val.size_memory }
{
	val.member = nullptr;
	val.size_container = 0;
	val.size_memory = 0;
	val.end_index = 0;
}

template <typename T>
Serial_container<T>::Serial_container(size_t count) :size_container{ 0 }, end_index{ 0 }
{
	this->member = new T[count];
	this->size_memory = count;
}

template <typename T>
Serial_container<T>::Serial_container(std::initializer_list<T> init) :Serial_container(init.size())
{
	for (auto iter = init.begin(); iter != init.end(); ++iter)
	{
		push_back(*iter);
	}
}

template <typename T>
void Serial_container<T>::resize(int count)
{
	if (count > this->size_memory)
	{
		this->reserve(count - this->size_memory);
	}
	else if (count < this->size_memory)
	{
		this->reserve(this->size_memory-count);
	}
	this->end_index = count - 1;
	this->size_container = count;
	this->size_memory = count;

}

template <typename T>
T* Serial_container<T>::data()
{
	return this->member;
}

template <typename T>
int Serial_container<T>::capacity()
{
	return this->size_memory;
}

template <typename T>
void Serial_container<T>::reserve(int count)
{
	int new_size_memory = this->size_container + count;
	T* local_member = new T[new_size_memory];
	for (int i = 0; i < this->size_container && i < new_size_memory; ++i)
	{
		local_member[i] = member[i];
	}
	if (this->member != nullptr)
	{
		delete[] this->member;
	}
	member = local_member;
	this->size_memory = new_size_memory;
}

template <typename T>
void Serial_container<T>::extension()
{
	int new_size_memory = this->size_memory * 2;
	T* local_member = new T[new_size_memory];
	for (int i = 0; i < this->size_container; ++i)
	{
		local_member[i] = member[i];
	}
	delete[] this->member;
	member = local_member;
	this->size_memory = new_size_memory;
}

template <typename T>
void Serial_container<T>::narrowing()
{
	int new_size_memory = this->size_memory / 2;
	T* local_member = new T[new_size_memory];
	for (int i = 0; i < this->size_container; ++i)
	{
		local_member[i] = member[i];
	}
	delete[] this->member;
	member = local_member;
	this->size_memory = new_size_memory;
}

template <typename T>
void Serial_container<T>::push_back(T value) 
{
	if (this->end_index == this->size_memory)
	{
		this->extension();
	}
	this->member[this->end_index] = value;
	end_index++;
	size_container++;
}

template <typename T>
void Serial_container<T>::insert(T value, int index)
{
	if (!(index < this->size_container && index >= 0))
	{
		exit(1);
	}
	else
	{
		if (this->size_memory == this->size_container)
		{
			this->extension();
		}

		for (int i = this->size_container - 1; i > index ; --i)
		{
			this->member[i] = this->member[i-1];
		}
		this->member[index] = value;
		this->size_container++;
		this->end_index++;
	}
	
}

template <typename T>
void Serial_container<T>::erase(int index)
{
	if (!(index < this->size_container && index >= 0))
	{
		exit(1);
	}
	if (index == this->size_container - 1)
	{
		if (this->end_index == this->size_container - 1) end_index--;
	}
	else
	{
		for (int i = index; i < this->size_container - 1; ++i)
		{
			this->member[i] = this->member[i + 1];
		}
	}
	this->size_container--;
	this->end_index--;
	if (this->size_container * 3 < this->size_memory)
	{
		this->narrowing();
	}
}

template <typename T>
int Serial_container<T>::size()
{
	return this->size_container;
}

template <typename T>
T Serial_container<T>::get(int index)
{
	if (!(index < size_container && index >= 0))
	{
		exit(1);
	}
	return this->member[index];;
}

template <typename T>
T* Serial_container<T>::begin()
{
	return &(this->member[0]);
}

template <typename T>
T* Serial_container<T>::end()
{
	return &(this->member[size_container]);
}

template <typename T>
T Serial_container<T>::operator[] (int index)
{
	return get(index);
}


template <typename T>
Serial_container<T>::~Serial_container()
{
	if (member != nullptr) delete[] member;
}


template <typename T>
std::ostream& operator <<(std::ostream& cout, Serial_container<T>& r_v)
{
	for (int i = 0; i < r_v.size(); ++i)
	{
		cout << r_v.get(i);
		if (i != r_v.size() - 1)
		{
			cout << ", ";
		}
	}
	return cout;
}
