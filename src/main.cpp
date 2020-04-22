#include <iostream>
#include <cstddef>
#include <vector>

#include "Benchmark.h"
#include "Allocator.h"
#include "StackAllocator.h"
#include "CAllocator.h"
#include "LinearAllocator.h"
#include "PoolAllocator.h"
#include "FreeListAllocator.h"

#define DEFAULT_ALCOC_SIZE 32
#define DEFINE_ALIGNMENT 8
#define DEFAULT_OP_NUMBER 1000000

int main(int argc, char* argv[]) {
    long unsigned int alloc_size = DEFAULT_ALCOC_SIZE;
    long unsigned int alignment = DEFINE_ALIGNMENT;
    int op_number = DEFAULT_OP_NUMBER;
    
    switch(argc){
        case 1:
           std::cout << "No allocation size given, using default = " << DEFAULT_ALCOC_SIZE << std::endl;
           std::cout << "No alignment given, using default = " << DEFINE_ALIGNMENT << std::endl;
           std::cout << "No allocation size given, using default = " << DEFAULT_OP_NUMBER << std::endl;
           break;
        case 2:
           alloc_size = atoi(argv[1]);
           std::cout << "No alignment given, using default = " << DEFINE_ALIGNMENT << std::endl;
           std::cout << "No allocation size given, using default = " << DEFAULT_OP_NUMBER << std::endl;
           break;
        case 3:
           alloc_size = atoi(argv[1]);
           alignment = atoi(argv[2]);
           std::cout << "No allocation size given, using default = " << DEFAULT_OP_NUMBER << std::endl;
           break;
        case 4:            
           alloc_size = atoi(argv[1]);
           alignment = atoi(argv[2]);
           op_number = atoi(argv[3]);
        
    }
    const std::vector<std::size_t> ALLOCATION_SIZES {alloc_size};//, 64, 256, 512, 1024, 2048, 4096};
    const std::vector<std::size_t> ALIGNMENTS {alignment};//, 8, 8, 8, 8, 8, 8};

    Allocator * cAllocator = new CAllocator();
    Allocator * linearAllocator = new LinearAllocator(4096*1e4);
    Allocator * stackAllocator = new StackAllocator(4096*1e4);
    Allocator * poolAllocator = new PoolAllocator(4096*1e4, alloc_size);
    Allocator * freeListAllocator = new FreeListAllocator(4096*1e6, FreeListAllocator::PlacementPolicy::FIND_FIRST);

    Benchmark benchmark(op_number);

    std::cout << "C" << std::endl;
    benchmark.MultipleAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
   // benchmark.MultipleFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
   // benchmark.RandomAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
   // benchmark.RandomFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS); 

    std::cout << "LINEAR" << std::endl;
    benchmark.MultipleAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    //benchmark.RandomAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);

    std::cout << "STACK" << std::endl;
    benchmark.MultipleAllocation(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    //benchmark.MultipleFree(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    //benchmark.RandomAllocation(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    //benchmark.RandomFree(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);

    std::cout << "POOL" << std::endl;
    benchmark.SingleAllocation(poolAllocator, alloc_size, alignment);
//    benchmark.SingleFree(poolAllocator, 4096, 8);

    std::cout << "FREE LIST" << std::endl;
    benchmark.MultipleAllocation(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
  //  benchmark.MultipleFree(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
  //  benchmark.RandomAllocation(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
  //  benchmark.RandomFree(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    
    delete cAllocator;
    delete linearAllocator;
    delete stackAllocator;
    delete poolAllocator;
    
    return 1;
}




