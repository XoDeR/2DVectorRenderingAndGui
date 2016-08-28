#pragma once

#include <ostream>
#include <vector>
#include "Core/Debug/Error.h"

//// used to swap two values
//template<class T>
//void swap(T& a, T& b)
//{
//	T temp = a;
//	a = b;
//	b = temp;
//}

// given a heap and a node in the heap, this function moves upwards
// through the heap swapping elements until the heap is ordered
template<class T>
void reorderUpwards(std::vector<T>& heap, int nd)
{
	// move up the heap swapping the elements until the heap is ordered
	while ((nd > 1) && (heap[nd / 2] < heap[nd]))
	{
		this->swap(heap[nd / 2], heap[nd]);
		nd /= 2;
	}
}

// given a heap, the heap size and a node in the heap, this function
// reorders the elements in a top down fashion by moving down the heap
// and swapping the current node with the greater of its two children
// (provided a child is larger than the current node)
template<class T>
void reorderDownwards(std::vector<T>& heap, int nd, int heapSize)
{
	// move down the heap from node nd swapping the elements until the heap is reordered
	while (2 * nd <= heapSize)
	{
		int child = 2 * nd;

		// set child to largest of nd's two children
		if ((child < heapSize) && (heap[child] < heap[child + 1]))
		{
			++child;
		}

		// if this nd is smaller than its child, swap
		if (heap[nd] < heap[child])
		{
			this->swap(heap[child], heap[nd]);
			// move the current node down the tree
			nd = child;
		}

		else
		{
			break;
		}
	}
}