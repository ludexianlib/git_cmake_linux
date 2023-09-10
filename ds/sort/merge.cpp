template <typename T>
void mergeSortRecursive(T arr[], T reg[], int start, int end)
{
	if (start >= end)
		return;

	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	mergeSortRecursive(arr, reg, start1, end1);
	mergeSortRecursive(arr, reg, start2, end2);

	int k = start;
	while (start1 <= end1 && start2 <= end2)
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
	while (start1 <= end1)
		reg[k++] = arr[start1++];
	while (start2 <= end2)
		reg[k++] = arr[start2++];	

	for (k = start; k <= end; k++)
		arr[k] = reg[k];
}

template <typename T>
void mergeSort(T arr[], const int len)
{
	T *reg = new T[len];
	mergeSortRecursive<T>(arr, reg, 0, len - 1);
	delete[] reg;
}