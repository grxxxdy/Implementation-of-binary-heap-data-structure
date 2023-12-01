#ifndef UNTITLED_DYNAMICARRAY_H
#define UNTITLED_DYNAMICARRAY_H
#include "Data.cpp"

struct DynamicArray						// Динамічний масив
{
	int maxAmount;
	Data* array;
	int amount;

	DynamicArray();

	void reallocate(int size);

	void push_back(Data* catt);

	Data* pop_back();

	Data* get(int index);

	int size();

	/*void print();*/

	void clear();

	void push_front(Data* catt);

	Data* pop_front();

	void insert(Data* catt, int index);

	void remove(int index);

	~DynamicArray();
};

#endif //UNTITLED_DYNAMICARRAY_H