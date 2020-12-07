#pragma once
#include <cstddef>

struct Node
{
	int data;
	Node* prev;
	Node* next;
};

class BiList
{
public:
	BiList();
	~BiList();
	void push_back(int);
	void push_front(int);
	void pop_back();
	void pop_front();
	void insert(int, size_t);
	int at(size_t);
	void remove(size_t);
	size_t get_size();
	void print_to_console();
	void clear();
	void set(size_t, int);
	bool isEmpty();
	void reverse();
private:
	Node* head; 
	Node* last;
	size_t size;
};