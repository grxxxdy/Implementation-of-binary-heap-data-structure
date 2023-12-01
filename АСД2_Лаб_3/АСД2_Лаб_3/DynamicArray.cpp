#include <iostream>
#include "DynamicArray.h"

using namespace std;

DynamicArray::DynamicArray()
{
	maxAmount = 1;
	array = new Data[maxAmount];
	amount = 0;
}

void DynamicArray::reallocate(int size)
{
	Data* temp = new Data[size];

	for (int i = 0; i < amount; i++)
	{
		temp[i] = array[i];
	}

	delete[] array;

	array = temp;
}

void DynamicArray::push_back(Data* catt)
{
	if (amount >= maxAmount)
	{
		maxAmount = (amount * 2);

		reallocate(maxAmount);
	}

	array[amount] = (*catt);

	amount++;
}

Data* DynamicArray::pop_back()
{
	if (amount <= 0)
	{
		cout << "Array already empty" << endl;
		return nullptr;
	}
	else
	{
		amount--;
		return &array[amount];
	}
}

Data* DynamicArray::get(int index)
{
	if (index >= amount || index < 0)
	{
		return nullptr;
	}
	else
	{
		return &array[index];
	}
}

int DynamicArray::size()
{
	return amount;
}

/*void print()
{
	if (amount == 0)
	{
		cout << "Массив порожній" << endl;
		return;
	}

	for (int i = 0; i < amount; i++)
	{
		cout << "Кіт " << (i + 1) << ":" << endl;
		cout << "Кличка: " << array[i].name << endl;
		cout << "Кількість корму в день: " << array[i].food << " Кг" << endl;
		cout << "Пухнастість: " << array[i].fur << "%\n" << endl;
	}
}*/

void DynamicArray::clear()
{
	amount = 0;
	maxAmount = 1;
	reallocate(maxAmount);
}

void DynamicArray::push_front(Data* catt)
{
	if (amount >= maxAmount)
	{
		maxAmount = (amount * 2);

		reallocate(maxAmount);
	}

	memmove(array + 1, array, sizeof(Data) * amount);

	array[0] = (*catt);

	amount++;
}

Data* DynamicArray::pop_front()
{
	if (amount <= 0)
	{
		cout << "Allready empty" << endl;
		return nullptr;
	}
	else
	{
		Data temp = array[0];

		memmove(array, array + 1, sizeof(Data) * (amount - 1));

		amount--;

		return &temp;
	}
}

void DynamicArray::insert(Data* catt, int index)
{
	if (index < 0 || index >= amount)
	{
		cout << "Error" << endl;
		return;
	}
	else if (index == 0)
	{
		push_front(catt);
	}
	else if (index == (amount - 1))
	{
		push_back(catt);
	}


	if (amount >= maxAmount)
	{
		maxAmount = (amount * 2);

		reallocate(maxAmount);
	}

	for (int i = amount; i > index; i--)
	{
		array[i] = array[i - 1];
	}

	array[index] = (*catt);

	amount++;
}

void DynamicArray::remove(int index)
{
	if (index < 0 || index >= amount)
	{
		cout << "Error" << endl;
		return;
	}
	else if (index == 0)
	{
		pop_front();
	}
	else if (index == (amount - 1))
	{
		pop_back();
	}

	amount--;

	for (int i = index; i < amount; i++)
	{
		array[i] = array[i + 1];
	}
}

DynamicArray::~DynamicArray()
{
	delete[] array;
}