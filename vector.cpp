#include <iostream>
#include <cstdio>

using namespace std;

template <class T>
class vector
{
private:
	T **data;
	long long _size;
	long long _capacity;

	void remove_all()
	{
		for (int i = 0; i < _size; i++) delete data[i];
		if (_capacity > 0) delete[] data;
	}

	void resize()
	{
		_capacity *= 2;

		T **temp;
		temp = new T*[_capacity];

		for (long long i = 0; i < _size; i++) temp[i] = data[i];
		T **a = data; data = temp; delete[] a;
	}

	void size_zero_push(T a)
	{
		if (_size != 0) return;

		_size = 1;
		if (_capacity <= 0)
		{
			_capacity = 1;
			data = new T*[1];
		}

		data[0] = new T(a);
	}


public:
	vector() : _size(0), _capacity(0) { remove_all(); }
	vector(long long size, T a)
	{
		vector();
		if (size <= 0) return;

		_size = _capacity = size;
		data = new T*[_capacity];
		for (long long i = 0; i < _size; i++) data[i] = new T(a);
	}
	~vector() { remove_all(); }

	/* O(1) */
	void push_back(T a)
	{
		if (_size == 0)
		{
			size_zero_push(a);
			return;
		}

		if (_size == _capacity) resize();
		data[_size++] = new T(a);
	}

	/* O(_size) */
	void push_front(T a)
	{
		if (_size == 0)
		{
			size_zero_push(a);
			return;
		}

		if (_size == _capacity) resize();
		for (int i = _size++; i > 0; i--) data[i] = data[i - 1];
		data[0] = new T(a);
	}

	/* O(1) */
	// TODO: Handle _size == 0
	T pop_back()
	{
		T res = at(--_size); delete data[_size]; return res;
	}

	/* O(_size) */
	// TODO: Handle _size == 0, bug
	T pop_front()
	{
		T res = at(0);
		delete data[0]; 
		for (long long i = 1; i < _size; i++) data[i - 1] = data[i];
		--_size;
		return res;
	}

	T at(int index) { return *(data[index]); }
	T operator[](const int& index) { return at(index); }

	T front() { return at(0); }
	T back() { return at(_size - 1); }

	long long size() { return _size; }
	long long capacity() { return _capacity; }
	bool empty() { return _size == 0; }
};

static int ID = 0;

struct st
{
	int val;
	int id;
	st(int val) : val(val), id(ID++) {}
};

int main()
{
	vector<st> a(5, st(2));

	st b(3);
	for (int i = 0; i < 5; i++) a.push_back(b);

	for (int i = 0; i < a.size(); i++) cout << a[i].id << ' ';
	return 0;
}
