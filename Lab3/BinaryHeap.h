#pragma once
#include "List.h"
#include "Iterator.h"

class BinaryHeap
{
private:
	int* Heap;
	size_t size;
	size_t max_size;
	void heapify(size_t);
	void resize_heap();
public:

	BinaryHeap();
	~BinaryHeap();

	void insert_ready_heap(int*, size_t);
	bool contains(int);
	void insert(int);
	void remove(int);
	void print_heap();
	bool isHeap(size_t);

	Iterator* create_dft_iterator();
	Iterator* create_bft_iterator();

	class bft_iterator : public Iterator
	{
	public:
		bft_iterator(BinaryHeap*);
		int next() override;
		bool has_next() override;
	private:
		BinaryHeap* data;
		size_t index = 0;
	};

	class dft_iterator : public Iterator
	{
	public:
		dft_iterator(BinaryHeap*);
		int next() override;
		bool has_next() override;
	private:
		BinaryHeap* data;
		size_t index = 0;
		BiList stack_right;
	};
};
