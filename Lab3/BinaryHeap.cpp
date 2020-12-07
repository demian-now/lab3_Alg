#pragma once
#include "List.h"
#include "BinaryHeap.h"
#include <iostream>

bool BinaryHeap::isHeap(size_t index = 0)
{
	size_t left_child = 2 * index + 1, right_child = 2 * index + 2;
	if (left_child >= size)
		return true;
	if (right_child >= size && Heap[index] >= Heap[left_child])
		return true;
	if (Heap[index] >= Heap[left_child] && Heap[index] >= Heap[right_child])
		return (isHeap(left_child) && isHeap(right_child));
	return false;
}

void BinaryHeap::heapify(size_t index = 0)
{
	size_t root = index;
	size_t left = 2 * root + 1, right = left + 1;
	if (left<size && Heap[left]>Heap[root])
		root = left;
	if (right<size && Heap[right]>Heap[root])
		root = right;
	if (root != index)
	{
		std::swap(Heap[root], Heap[index]);
		heapify(root);
	}
}

BinaryHeap::BinaryHeap()
{
	this->size = 0;
	this->max_size = 250;
	Heap = new int[max_size];
}

BinaryHeap::~BinaryHeap()
{
	delete[]Heap;
}

void BinaryHeap::insert_ready_heap(int* ready_heap, size_t size)
{
	while (size > max_size)
		max_size += 250;
	delete[]Heap;
	Heap = new int[max_size];
	this->size = size;
	for (size_t i = 0; i < size; i++)
		Heap[i] = ready_heap[i];
	for (size_t i = 0; i < this->size; i += 2 * i + 1)
		heapify();
}

bool BinaryHeap::contains(int key)
{
	if (size == 0)
		return false;
	for (size_t i = 0; i < size; i++)
		if (Heap[i] == key)
			return true;
	return false;
}

void BinaryHeap::insert(int value)
{
	size_t size_heap = size;
	int parent = (size_heap - 1) / 2;
	if (size + 1 > max_size)
		resize_heap();
	Heap[size] = value;
	while (parent >= 0 && size_heap > 0)
	{
		if (Heap[size_heap] > Heap[parent])
			std::swap(Heap[size_heap], Heap[parent]);
		size_heap = parent;
		parent = (size_heap - 1) / 2;
	}
	size++;
}

void BinaryHeap::remove(int key)
{
	int control = 0;
	for (size_t i = 0; i < size - control; i++)
	{
		if (Heap[i] == key)
			control++;
		Heap[i] = Heap[i + control];
	}
	size -= control;
	for (size_t i = 0; i < size; i += 2 * i + 1)
		heapify();
}

void BinaryHeap::print_heap()
{
	size_t i = 0, k = 1;
	while (i < size) {
		while ((i < k) && (i < size)) {
			std::cout << Heap[i] << " ";
			i++;
		}
		std::cout << std::endl;
		k = k * 2 + 1;
	}
}

void BinaryHeap::resize_heap()
{
	max_size += 250;
	int* temp = new int[max_size];
	for (size_t i = 0; i < size; i++)
		temp[i] = Heap[i];
	delete[]Heap;
	Heap = temp;
}

BinaryHeap::bft_iterator::bft_iterator(BinaryHeap* cur)
{
	data = cur;
}

int BinaryHeap::bft_iterator::next()
{
	if (!has_next())
		throw "No more elements in heap";
	index++;
	return data->Heap[index - 1];
}

bool BinaryHeap::bft_iterator::has_next()
{

	if (data->size != index) return true;
	return false;
}

BinaryHeap::dft_iterator::dft_iterator(BinaryHeap* cur)
{
	data = cur;
}

int BinaryHeap::dft_iterator::next()
{
	if (!has_next())
		throw "No more elements in heap";
	int temp = data->Heap[index];
	size_t right_child = index * 2 + 2, left_child = index * 2 + 1;
	if (index == 0)
		stack_right.push_back(0);
	if (right_child < data->size)
	{
		stack_right.push_back(right_child);
		index = left_child;
	}
	else
	{
		if (left_child < data->size)
			index = left_child;
		else
		{
			if (stack_right.at(stack_right.get_size() - 1) == 0)
				stack_right.pop_back();
			else
			{
				index = stack_right.at(stack_right.get_size() - 1);
				stack_right.pop_back();
			}
			if (data->size == 1)
				index--;
		}
	}
	return temp;
}

bool BinaryHeap::dft_iterator::has_next()
{
	if (data->size == 0)
		return false;
	if (index == 0)
		return true;
	if (stack_right.isEmpty() && index != 0)
		return false;
	else
		return true;
}

Iterator* BinaryHeap::create_dft_iterator()
{
	return new dft_iterator(this);
}

Iterator* BinaryHeap::create_bft_iterator()
{
	return new bft_iterator(this);
}
