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
#define DEFAULT_OP_NUMBER 1000

int main(int argc, char* argv[]) {
    long unsigned int alloc_size = DEFAULT_ALCOC_SIZE;
    long unsigned int alignment = DEFINE_ALIGNMENT;
    int op_number = DEFAULT_OP_NUMBER;
    
    switch(argc){
        case 1:
           std::cerr << "No allocation size given, using default = " << DEFAULT_ALCOC_SIZE << std::endl;
           std::cerr << "No alignment given, using default = " << DEFINE_ALIGNMENT << std::endl;
           std::cerr << "No allocation size given, using default = " << DEFAULT_OP_NUMBER << std::endl;
           break;
        case 2:
           alloc_size = atoi(argv[1]);
           std::cerr << "No alignment given, using default = " << DEFINE_ALIGNMENT << std::endl;
           std::cerr << "No allocation size given, using default = " << DEFAULT_OP_NUMBER << std::endl;
           break;
        case 3:
           alloc_size = atoi(argv[1]);
           alignment = atoi(argv[2]);
           std::cerr << "No allocation size given, using default = " << DEFAULT_OP_NUMBER << std::endl;
           break;
        case 4:            
           alloc_size = atoi(argv[1]);
           alignment = atoi(argv[2]);
           op_number = atoi(argv[3]);
        
    }
    const std::vector<std::size_t> ALLOCATION_SIZES {alloc_size};//, 64, 256, 512, 1024, 2048, 4096};
    const std::vector<std::size_t> ALIGNMENTS {alignment};//, 8, 8, 8, 8, 8, 8};

    
 
    std::cout << "nOperations,elapsedTim,operationsPerSec,timePerOperation,memoryPeak,allocatorName,allocationSize, alignment" << std::endl;
    
    for(int on = 10; on <= op_number; on+=10){

        
   

        Benchmark benchmark(on);

        //std::cout << "C" << std::endl;
        Allocator * cAllocator = new CAllocator();
        benchmark.MultipleAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        delete cAllocator;
        //benchmark.MultipleFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.RandomAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.RandomFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS); 
        
        Allocator * linearAllocator = new LinearAllocator(1e9);
        //std::cout << "LINEAR" << std::endl;
        benchmark.MultipleAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.RandomAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        delete linearAllocator;

        Allocator * stackAllocator = new StackAllocator(1e9);
        //std::cout << "STACK" << std::endl;
        benchmark.MultipleAllocation(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.MultipleFree(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.RandomAllocation(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.RandomFree(stackAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        delete stackAllocator;

        Allocator * poolAllocator = new PoolAllocator(16777216, alloc_size);
        //std::cout << "POOL" << std::endl;
        benchmark.SingleAllocation(poolAllocator, alloc_size, alignment);
        //benchmark.SingleFree(poolAllocator, 4096, 8);
        delete poolAllocator;

        Allocator * freeListAllocator = new FreeListAllocator(1e8, FreeListAllocator::PlacementPolicy::FIND_FIRST);
        //std::cout << "FREE LIST" << std::endl;
        benchmark.MultipleAllocation(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.MultipleFree(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.RandomAllocation(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        //benchmark.RandomFree(freeListAllocator, ALLOCATION_SIZES, ALIGNMENTS);
        delete poolAllocator;
    }
    

    
    return 1;
}




