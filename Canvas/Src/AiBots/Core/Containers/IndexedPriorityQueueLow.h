#pragma once

#include "Core/Debug/Error.h"
#include "Core/Containers/PriorityQueueFn.h"

#include <vector>

// priority queue based on an index into a set of keys
// the queue is maintained as a 2-way heap
// the priority in this implementation is the lowest valued key
template<class KeyType>
class IndexedPriorityQueueLow
{
public:
	// you must pass the constructor a reference to the std::vector the PQ
	// will be indexing into and the maximum size of the queue.
	IndexedPriorityQueueLow(std::vector<KeyType>& keyList, int maxSize)
		: keyList(keyList)
		, maxSize(maxSize)
	{
		heap.assign(maxSize + 1, 0);
		heapInverted.assign(maxSize + 1, 0);
	}

	bool empty() const
	{
		return (size == 0);
	}

	// to insert an item into the queue it gets added to the end of the heap
	// and then the heap is reordered from the bottom up.
	void insert(const int idx)
	{
		RIO_ASSERT(size + 1 <= maxSize, "");
		++size;
		heap[size] = idx;
		heapInverted[idx] = size;
		reorderUpwards(size);
	}

	// to get the min item the first element is exchanged with the lowest
	// in the heap and then the heap is reordered from the top down. 
	int pop()
	{
		this->swap(1, size);
		reorderDownwards(1, size - 1);
		return heap[size--];
	}

	// if the value of one of the client key's changes then call this with 
	// the key's index to adjust the queue accordingly
	void changePriority(const int idx)
	{
		reorderUpwards(heapInverted[idx]);
	}
private:
	void swap(int a, int b)
	{
		int temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;
		// change the handles too
		heapInverted[heap[a]] = a;
		heapInverted[heap[b]] = b;
	}

	void reorderUpwards(int nd)
	{
		// move up the heap swapping the elements until the heap is ordered
		while ((nd > 1) && (keyList[heap[nd / 2]] > keyList[heap[nd]]))
		{
			this->swap(nd / 2, nd);
			nd /= 2;
		}
	}

	void reorderDownwards(int nd, int heapSize)
	{
		// move down the heap from node nd swapping the elements until the heap is reordered
		while (2 * nd <= heapSize)
		{
			int child = 2 * nd;

			// set child to smaller of nd's two children
			if ((child < heapSize) && (keyList[heap[child]] > keyList[heap[child + 1]]))
			{
				++child;
			}

			// if this nd is larger than its child, swap
			if (keyList[heap[nd]] > keyList[heap[child]])
			{
				this->swap(child, nd);
				// move the current node down the tree
				nd = child;
			}

			else
			{
				break;
			}
		}
	}

	std::vector<KeyType>& keyList;
	std::vector<int> heap;
	std::vector<int> heapInverted;
	int size = 0;
	int	maxSize;
};