#include <iostream>
#include <chrono>
#include <vector>
#include "RMAllocator.h"
#include "N2Allocator.h"


using namespace std;

int main()
{

	RMAllocator a1;
	vector<void *> pointer(10);

	std::chrono::steady_clock::time_point alloc_start1 = std::chrono::steady_clock::now();
	for(int i = 0; i < 10; i++) {
		pointer[i] = a1.malloc(10);
	}
	std::chrono::steady_clock::time_point alloc_end1 = std::chrono::steady_clock::now();

	for(int i = 0; i < 10; i++) {
		a1.free(pointer[i], 10);
	}
	a1.defragment();
	std::chrono::steady_clock::time_point test_end1 = std::chrono::steady_clock::now();
	cerr << "RMAllocator first test:\n"
                  << "Allocation :" << duration_cast<std::chrono::microseconds>(alloc_end1 - alloc_start1).count() << " microseconds" << "\n"
                  << "Deallocation :" << duration_cast<std::chrono::microseconds>(test_end1 - alloc_end1).count() << " microseconds" << "\n\n";


	N2Allocator allocator({.block_16 = 2, .block_32 = 800, .block_64 = 800});
        vector<char *> pointers(10, 0);
        std::chrono::steady_clock::time_point alloc_start = std::chrono::steady_clock::now();
        for (int i = 0; i < 10; ++i) {
            pointers[i] = (char *) allocator.allocate(10);
        }
        std::chrono::steady_clock::time_point alloc_end = std::chrono::steady_clock::now();
        for (int i = 0; i < 10; ++i) {
            allocator.deallocate(pointers[i]);
        }
        std::chrono::steady_clock::time_point test_end = std::chrono::steady_clock::now();
        cout << "N2 allocator first test:" << endl;
                  cout << "Allocation :" << duration_cast<std::chrono::microseconds>(alloc_end - alloc_start).count() << " microseconds" << endl;
                  cout << "Deallocation :" << duration_cast<std::chrono::microseconds>(test_end - alloc_end).count() << " microseconds" << endl << endl;



RMAllocator a2;
	vector<void *> pointer2(30);

	std::chrono::steady_clock::time_point alloc_start2 = std::chrono::steady_clock::now();
	for(int i = 0; i < 30; i++) {
		pointer2[i] = a2.malloc(10);
	}
	std::chrono::steady_clock::time_point alloc_end2 = std::chrono::steady_clock::now();

	for(int i = 0; i < 30; i++) {
		a2.free(pointer2[i], 10);
	}
	a2.defragment();
	std::chrono::steady_clock::time_point test_end2 = std::chrono::steady_clock::now();
	cerr << "RMAllocator second test:\n"
                  << "Allocation :" << duration_cast<std::chrono::microseconds>(alloc_end2 - alloc_start2).count() << " microseconds" << "\n"
                  << "Deallocation :" << duration_cast<std::chrono::microseconds>(test_end2 - alloc_end2).count() << " microseconds" << "\n\n";


	N2Allocator allocator2({.block_16 = 100, .block_32 = 800, .block_64 = 800});
        vector<char *> pointers2(30, 0);
        std::chrono::steady_clock::time_point alloc_start3 = std::chrono::steady_clock::now();
        for (int i = 0; i < 30; ++i) {
            pointers2[i] = (char *) allocator2.allocate(10);
        }
        std::chrono::steady_clock::time_point alloc_end3 = std::chrono::steady_clock::now();
        for (int i = 0; i < 30; ++i) {
            allocator2.deallocate(pointers2[i]);
        }
        std::chrono::steady_clock::time_point test_end3 = std::chrono::steady_clock::now();
        cout << "N2 allocator second test:" << endl;
                  cout << "Allocation :" << duration_cast<std::chrono::microseconds>(alloc_end3 - alloc_start3).count() << " microseconds" << endl;
                  cout << "Deallocation :" << duration_cast<std::chrono::microseconds>(test_end3 - alloc_end3).count() << " microseconds" << endl << endl;

RMAllocator a3;
	vector<void *> pointer3(60);

	std::chrono::steady_clock::time_point alloc_start5 = std::chrono::steady_clock::now();
	for(int i = 0; i < 60; i++) {
		pointer3[i] = a3.malloc(10);
	}
	std::chrono::steady_clock::time_point alloc_end5 = std::chrono::steady_clock::now();

	for(int i = 0; i < 60; i++) {
		a3.free(pointer3[i], 10);
	}
	a3.defragment();
	std::chrono::steady_clock::time_point test_end5 = std::chrono::steady_clock::now();
	cerr << "RMAllocator third test:\n"
                  << "Allocation :" << duration_cast<std::chrono::microseconds>(alloc_end5 - alloc_start5).count() << " microseconds" << "\n"
                  << "Deallocation :" << duration_cast<std::chrono::microseconds>(test_end5 - alloc_end5).count() << " microseconds" << "\n\n";


	N2Allocator allocator3({.block_16 = 100, .block_32 = 800, .block_64 = 800});
        vector<char *> pointers3(60, 0);
        std::chrono::steady_clock::time_point alloc_start6 = std::chrono::steady_clock::now();
        for (int i = 0; i < 60; ++i) {
            pointers3[i] = (char *) allocator3.allocate(10);
        }
        std::chrono::steady_clock::time_point alloc_end6 = std::chrono::steady_clock::now();
        for (int i = 0; i < 60; ++i) {
            allocator3.deallocate(pointers3[i]);
        }
        std::chrono::steady_clock::time_point test_end6 = std::chrono::steady_clock::now();
        cout << "N2 allocator third test:" << endl;
                  cout << "Allocation :" << duration_cast<std::chrono::microseconds>(alloc_end6 - alloc_start6).count() << " microseconds" << endl;
                  cout << "Deallocation :" << duration_cast<std::chrono::microseconds>(test_end6 - alloc_end6).count() << " microseconds" << endl << endl;

}


