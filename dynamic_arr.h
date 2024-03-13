#pragma once
#include <iostream>

using namespace std;


template <typename T>
class dynamic_arr {
private:
	void realocate();
public:
	int size;
	int size_max;
	T* arr;
	bool reached_max();
	void push(T obj, int i);
	void push(T obj);
	T& operator[](int);
	friend ostream& operator<<(ostream& os, const dynamic_arr& tabliczka)
	{
		for (int i = 0; i < (tabliczka.size); i++)
			os << (*tabliczka.arr[i]) << endl;
		return os;
	}
	void clear();
	void resize(int s);
	void bsort();
	void swap(T& elem1, T& elem2);
	void quickSort(int pocz, int koniec);
	int partition(int pocz, int koniec);
	dynamic_arr()
	{
		size = 0;
		size_max = 1;
		arr = (T*)calloc(size, sizeof(T));
	}
	dynamic_arr(int s)
	{
		size = 0;
		size_max = s;
		arr = (T*)calloc(s, sizeof(T));
	}
	~dynamic_arr()
	{
		clear();
	}
};
template <typename T> T& dynamic_arr<T>::operator[](int i)//nie dziala:(
{
	return arr[i];
}

template <typename T> bool dynamic_arr<T>::reached_max()
{
	if (size + 1 >= size_max)
		return 1;
	return 0;
}

template<typename T> void dynamic_arr<T>::resize(int s)
{
	size = s;
	size_max = s;
	arr = (T*)calloc(s, sizeof(T));
}
template <typename T> void dynamic_arr<T>::realocate()
{
	arr = (T*)realloc(arr, size_max * 2 * sizeof(T));
	size_max *= 2;
}

template <typename T> void dynamic_arr<T>::push(T obj, int i)
{
	if (reached_max())
		realocate();
	arr[i] = obj;
	size += 1;
}
template <typename T> void dynamic_arr<T>::push(T obj)
{
	if (reached_max())
		realocate();
	size += 1;
	arr[size - 1] = obj;
}

template <typename T> void dynamic_arr<T>::clear()
{
	free(arr);
	size = 0;
	size_max = 1;
	arr = (T*)calloc(size, sizeof(T));

}
template <typename T> void dynamic_arr<T>::swap(T& elem1, T& elem2)
{
	T pom = elem1;
	elem1 = elem2;
	elem2 = pom;
}
template <typename T> void dynamic_arr<T>::bsort()
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}

}
template <typename T> void dynamic_arr<T>::quickSort(int pocz, int koniec) {
	if (pocz < koniec) {
		int pivot = partition(pocz, koniec);

		// Rekurencyjne sortowanie przed i za pivotem
		quickSort(pocz, pivot - 1);
		quickSort(pivot + 1, koniec);
	}
}

template <typename T> int dynamic_arr<T>::partition(int pocz, int koniec) {
	T pivot = arr[koniec]; 
	int i = pocz - 1;

	for (int j = pocz; j < koniec; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	i++;
	swap(arr[i], arr[koniec]);
	return i;
}
