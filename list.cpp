#include <iostream>
#include <cstdio>

using namespace std;

template <class T>
class list
{
private:
	struct list_st
	{
		T* data;
		list_st *prev;
		list_st *next;

		list_st(T a) : data(new T(a)), prev(NULL), next(NULL) {}
		list_st() : data(NULL), prev(NULL), next(NULL) {}
	};

	list_st *head, *tail;
	long long _size;

public:
	class iterator
	{
	private:
		list_st *_item;
	
	public:
		iterator(list_st *item) : _item(item) {}

		T& operator*(void) { return *(_item->data); }
		bool operator==(iterator rhs) { return rhs._item == _item; } // This works. Remember.
		bool operator!=(iterator rhs) { return rhs._item != _item; }

		iterator operator++() 
		{
		   	_item = _item->next; 
			return iterator(_item); 
		}

		iterator operator--() 
		{
		   	_item = _item->prev;
		   	return iterator(_item); 
		}
		
		iterator operator++(int) 
		{ 
			iterator res(_item); 
			_item = _item->next;
			return res;
	   	}

		iterator operator--(int) 
		{
			iterator res(_item);
			_item = _item->prev;
			return res;
		}
	};

	list() : _size(0), head(new list_st()), tail(head) {}
	list(long long size, T a) : _size(0), head(new list_st()), tail(head) 
	{
		for (long long i = 0; i < size; i++) push_back(a);
	}

	~list() 
	{
		if (_size == 0) return;
		list_st *tmp = head;
		while (head != tail && head->next != NULL) 
		{
			head = head->next;
			if (tmp->data != NULL) delete tmp->data;
			delete tmp;
			tmp = head;
		}

		delete head;
	}

	iterator begin() { return iterator(head); }
	iterator end() { return iterator(tail); }

	void push_back(T a) 
	{
		if (_size == 0)
		{
			head = new list_st(a);
			head->next = tail;
			tail->prev = head;
			_size = 1;
			return;
		}

		list_st *tmp = new list_st(a);
		list_st *b = tail->prev;
		
		b->next = tmp;
		tmp->prev = b;

		tmp->next = tail;
		tail->prev = tmp;

		_size++;
	}

	void push_front(T a) 
	{
		if (_size == 0)
		{
			push_back(a);
			return;
		}

		list_st *tmp = new list_st(a);
		head->prev = tmp;
		tmp->next = head;
		head = tmp;
		_size++;
	}

	// TODO: Handle _size == 0
	T pop_back() 
	{
		if (_size == 1) return pop_front();

		list_st *tmp = tail->prev;
		list_st *a = tmp->prev;
		tail->prev = a;

		T res = *(tmp->data);
		_size--;

		delete tmp->data;
		delete tmp;
		return res;
	}

	// TODO: Handle _size == 0
	T pop_front() 
	{
		list_st *tmp = head;
		head = head->next;
		T res = *(tmp->data);
		_size--;
		delete tmp->data;
		delete tmp;
		return res;
	}

	T front() { return *(head->data); }
	T back() { return *(tail->data); }

	long long size() { return _size; }
	bool empty() { return _size == 0; }
};

int main()
{
	list<int> a;
	for (int i = 0; i < 400; i++) a.push_back(i);
	for (list<int>::iterator j = --a.end(); j != a.begin(); j--)
		cout << (*j) << ' ';

	cout << endl;
	list<int> b(2, 2);
	for (list<int>::iterator j = --b.end(); j != b.begin(); j--)
		cout << (*j) << ' ';
	
	return 0;
}
