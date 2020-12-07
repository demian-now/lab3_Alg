#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3/BinaryHeap.cpp"
#include "../Lab3/List.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SuperTestMachine
{
	TEST_CLASS(SuperTestMachine)
	{
	public:
		BinaryHeap Test;
		TEST_METHOD(isHeap_test)
		{
			int test[5] = { 10,5,4,3,2 };
			Test.insert_ready_heap(test, 5);
			Assert::AreEqual(Test.isHeap(), true);
		}
		TEST_METHOD(correct_insert)
		{
			for (size_t i = 0; i < 5; i++)
				Test.insert(i);
			for (size_t i = 0; i < 5; i++)
				Assert::AreEqual(Test.contains(i), true);
		}
		TEST_METHOD(correct_heap_after_insert)
		{
			Test.insert(123);
			Assert::AreEqual(Test.isHeap(), true);
		}
		TEST_METHOD(correct_insert_ready_heap)
		{
			int test[5] = { 10,5,4,3,2 };
			Test.insert_ready_heap(test, 5);
			for (size_t i = 0; i < 5; i++)
				Assert::AreEqual(Test.contains(test[i]), true);
		}
		TEST_METHOD(correct_remove)
		{
			int test[5] = { 10,5,4,3,2 };
			Test.insert_ready_heap(test, 5);
			Test.remove(10);
			Assert::AreEqual(Test.contains(10), false);
		}
		TEST_METHOD(correct_heap_after_remove)
		{
			int test[5] = { 10,5,4,3,2 };
			Test.insert_ready_heap(test, 5);
			Test.remove(10);
			Assert::AreEqual(Test.isHeap(), true);
		}
		TEST_METHOD(test_bft_iterator)
		{
			int test[5] = { 10,5,4,3,2 };
			Test.insert_ready_heap(test, 5);
			Iterator* Iter = Test.create_bft_iterator();
			for (size_t i = 0; i < 5; i++)
				Assert::AreEqual(Iter->next(), test[i]);
			Assert::AreEqual(Iter->has_next(), false);
		}
		TEST_METHOD(test_dft_iterator)
		{
			int test[5] = { 10,5,4,3,2 };
			Test.insert_ready_heap(test, 5);
			int result[5] = { 10,5,3,2,4 };
			Iterator* Iter = Test.create_dft_iterator();
			for (size_t i = 0; i < 5; i++)
				Assert::AreEqual(Iter->next(), result[i]);
			Assert::AreEqual(Iter->has_next(), false);
		}
	};
}