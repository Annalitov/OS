#include <iostream>
#include <cinttypes>
#include "RMAllocator.h"

using namespace std;

RMAllocator::RMAllocator()
{

	mem_page_ptr = (uint8_t*)::malloc(mem_page_size);

	if (mem_page_ptr == nullptr)
		throw runtime_error("Error: Cannot allocate a memory page");

	first_block_ptr = (RMNode*)mem_page_ptr;
	first_block_ptr->next_block_ptr = nullptr;
	first_block_ptr->current_block_size = mem_page_size;
}

RMAllocator::~RMAllocator()
{
	if (mem_page_ptr != nullptr)
		::free(mem_page_ptr);
}

void* RMAllocator::malloc(const size_t size)
{

	if (size == 0)
		return nullptr;

	const size_t requested_size = max(size, sizeof(RMNode));


	RMNode* block_ptr = first_block_ptr;


	while (block_ptr != nullptr)
	{

		if (block_ptr->current_block_size >= requested_size + sizeof(RMNode))
		{
		
			uint8_t* busy_block_ptr = (uint8_t*)block_ptr + block_ptr->current_block_size - requested_size;
			
			block_ptr->current_block_size -= requested_size;
			return busy_block_ptr;
		}

		block_ptr = block_ptr->next_block_ptr;
	}


	throw runtime_error("Error: Cannot allocate memory of requested size");
}

void RMAllocator::free(const void* ptr, const size_t size)
{
	if (ptr == nullptr)
		return;


	const size_t freed_size = max(size, sizeof(RMNode));


	RMNode* freed_block_ptr = (RMNode*)ptr;
	freed_block_ptr->next_block_ptr = nullptr;
	freed_block_ptr->current_block_size = size;

	
	RMNode** previous_ptr_ptr = &first_block_ptr;
	RMNode* block_ptr = first_block_ptr;
	
	while (block_ptr != nullptr)
	{
		
		if (ptr < block_ptr)
		{
			freed_block_ptr->next_block_ptr = block_ptr;
			break;
		}

	
		previous_ptr_ptr = &block_ptr->next_block_ptr;
		block_ptr = block_ptr->next_block_ptr;
	}
	*previous_ptr_ptr = freed_block_ptr;

    defragment();
}

void RMAllocator::print()
{
	cout << "RMAllocator statistics:" << endl;
	cout << "memory page pointer = " << (void*)mem_page_ptr << endl;
	cout << "memory page size = " << mem_page_size << endl;

	int num = 0;
	RMNode* block_ptr = first_block_ptr;
	while (block_ptr != nullptr)
	{
		cout << "free block #" << num << " pointer = " << (void*)block_ptr << endl;
		cout << "free block #" << num << " size = " << block_ptr->current_block_size << endl;
		num++;
		block_ptr = block_ptr->next_block_ptr;
	}
	cout << "free blocks total = " << num << endl;
	cout << endl;
}

void RMAllocator::defragment()
{
	
	RMNode* block_ptr = first_block_ptr;

	while (block_ptr != nullptr)
	{
		while (block_ptr != nullptr)
		{
			uint8_t* end_of_block_ptr = (uint8_t*)block_ptr + block_ptr->current_block_size;
			if (end_of_block_ptr != (uint8_t*)block_ptr->next_block_ptr)
				break;

			block_ptr->current_block_size += block_ptr->next_block_ptr->current_block_size;
			block_ptr->next_block_ptr = block_ptr->next_block_ptr->next_block_ptr;
		}

		block_ptr = block_ptr->next_block_ptr;
	}
}