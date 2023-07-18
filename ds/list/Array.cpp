#include "Array.h"
#include <memory.h>
#include <vector>

void CreateArray(int)
{
	// 一维
	constexpr int size = 100;
	int arr[size] = { 0 };

	// 二维
	int arr2D[3][size] = { 0 };
}

void CreateArray(float)
{
	// 一维
	constexpr int size = 100;
	int* arr = new int[size];
	memset(arr, 0, sizeof(int) * size);
	delete[] arr;

	// 二维
	int** arr2D = new int* [size];
	for (int i = 0; i < size; i++) // row
		arr2D[i] = new int[size];
	for (int i = 0; i < size; i++) // row element
	{
		for (int j = 0; j < size; j++) // column element
		{
			arr2D[i][j] = 0;
		}
	}

}

void CreateArray(char)
{
	// 一维
	constexpr int size = 100;
	std::vector<int> arr(size, 0);

	// 二维
	std::vector<std::vector<int>> arr2D(size, std::vector<int>(size, 0));
	for (int i = 0; i < size; i++) // row
	{
		for (int j = 0; j < size; j++) // column
		{
			arr2D[i][j] = 0;
		}
	}
}
