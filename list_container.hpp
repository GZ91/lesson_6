#pragma once
#include <ostream>

template <typename T>
class List_container
{
public:
	struct Node
	{
		Node* next = nullptr;
		Node* prev = nullptr;
		T value;
	};

	class iterator : public std::iterator <
		std::input_iterator_tag,
		T,
		T,
		const Node*,
		T>
	{
	private:
		Node *num;
	public:
		explicit iterator(Node* _num) :num(_num) {}
		iterator(const iterator& val)  {this->num = val.num; }
		iterator operator++()
		{
			if (num != nullptr)
			{
				this->num = this->num->next;
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator retval = *this;
			if (num != nullptr)
			{
				this->num = this->num->next;
			}
			return retval;
		}
		bool operator==(iterator other) const { return this->num == other.num; }
		bool operator!=(iterator other) const { return !(*this == other); }
		T operator*() const {
			if (this->num != nullptr) return this->num->value;
			return T();
		}

	};
	List_container(std::initializer_list<T>);
	List_container() :size_container{ 0 }, begin_node{ nullptr }, end_node{ nullptr }, current_node{ nullptr }{}
	void push_back(T);
	void insert(T, int);
	void erase(int);
	int size();
	T get(int);
	iterator begin() {return iterator(this->begin_node);}
	iterator end() {return iterator(nullptr); }
	T operator[](int);
	~List_container();


private:

	int size_container;
	Node* end_node;
	Node* current_node;
	Node* begin_node;
};



template <typename T>
List_container<T>::List_container(std::initializer_list<T> init) :size_container{ 0 }, begin_node{ nullptr }, end_node{ nullptr }, current_node{ nullptr }
{
	for (auto iter = init.begin(); iter != init.end(); ++iter)
	{
		push_back(*iter);
	}
}

template <typename T>
void List_container<T>::push_back(T value)
{
	Node* n = new Node;
	n->value = value;
	if (this->end_node != nullptr)
	{
		n->prev = this->end_node;
		this->end_node->next = n;
	}
	this->end_node = n;
	size_container++;
	if (begin_node == nullptr) 
	{
		this->begin_node = n;
		this->current_node = n;
	}
}

template <typename T>
void List_container<T>::insert(T value, int index)
{
	if (!(index < this->size_container && index >= 0))
	{
		exit(1);
	}
	Node* n = this->begin_node;
	for (int i = 0; i < index; i++)
	{
		n = n->next;
	}
	Node* new_node = new Node;
	new_node->value = value;
	new_node->next = n;
	new_node->prev = n->prev;
	if (n->prev != nullptr)
	{
		n->prev->next = new_node;
	}
	n->prev = new_node;
	if (index == 0)
	{
		this->begin_node = new_node;
	}
	this->size_container++;
}

template <typename T>
void List_container<T>::erase(int index)
{
	if (!(index < this->size_container && index >= 0))
	{
		exit(1);
	}
	
	Node* n = this->begin_node;
	for (int i = 0; i < index; i++)
	{
		n = n->next;
	}
	if (n->prev != nullptr)
	{
		n->prev->next = n->next;
	}
	if (n->next != nullptr)
	{
		n->next->prev = n->prev;
	}
	
	this->size_container--;
	if (index == 0)
	{
		this->begin_node = n->next;
	}
	delete n;
	
}

template <typename T>
int List_container<T>::size()
{
	return this->size_container;
}

template <typename T>
T List_container<T>::get(int index)
{
	if (!(index < size_container && index >= 0))
	{
		exit(1);
	}
	Node* n = this->begin_node;
	for (int i = 0; i < index; i++)
	{
			n = n->next;	
	}
	return n->value;
}

template <typename T>
T List_container<T>::operator[] (int index)
{
	return get(index);
}

template <typename T>
List_container<T>::~List_container()
{
	Node* n = this->begin_node;
	while (true)
	{
		if (this->begin_node == nullptr)
		{
			break;
		}
		n = this->begin_node->next;
		delete this->begin_node;
		this->begin_node = n;
	}
}

template <typename T>
std::ostream& operator <<(std::ostream& cout, List_container<T>& r_v)
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