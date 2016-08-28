#pragma once

#include "Core/Debug/Error.h"
#include "Core/Containers/PriorityQueueFn.h"

#include <vector>

// basic heap based priority queue implementation
template<class T>
class PriorityQueue
{
public:
	PriorityQueue(int maxSize);
	bool empty() const;

	// to insert an item into the queue it gets added to the end of the heap
	// and then the heap is reordered
	void insert(const T item)
	{
		RIO_ASSERT(size + 1 <= maxSize, "");
		++size;
		heap[size] = item;
		reorderUpwards(heap, size);
	}

	// to get the max item the first element is exchanged with the lowest
	// in the heap and then the heap is reordered from the top down. 
	T pop()
	{
		this->swap(heap[1], heap[size]);
		reorderDownwards(heap, 1, size - 1);
		return heap[size--];
	}

	// so we can take a peek at the first in line
	const T& peek() const
	{
		return heap[1];
	}
private:
	// given a heap and a node in the heap, this function moves upwards
	// through the heap swapping elements until the heap is ordered
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
				//move the current node down the tree
				nd = child;
			}

			else
			{
				break;
			}
		}
	}

	std::vector<T> heap;
	int size;
	int maxSize;
};