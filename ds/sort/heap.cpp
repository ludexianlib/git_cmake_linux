template <typename T>
void maxHeapify(T arr[], int start, int end)
{
	int parent = start;
	int lchild = parent * 2 + 1;

	while (lchild <= end) {
		if (lchild + 1 <= end && arr[lchild] < arr[lchild + 1])
			lchild++;
		if (arr[parent] > arr[lchild])
			return;
		else {
			std::swap(arr[parent], arr[lchild]);
			parent = lchild;
			lchild = parent * 2 + 1;
		}
	}

}

template <typename T>
void heapSort(T arr[], const int len)
{
	// 初始化堆，i从最后一个父节点开始
	for (int i = len / 2; i >= 0; i--)
		maxHeapify<T>(arr, i, len - 1);

	// 交换堆顶元素，重新创建大顶堆
	for (int i = len - 1; i > 0; i--) {
		std::swap(arr[0], arr[i]);
		maxHeapify<T>(arr, 0, i - 1);
	}
}