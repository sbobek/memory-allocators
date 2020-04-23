#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef> // size_t
#include <string>


class Allocator {
protected:
    std::size_t m_totalSize;
    std::size_t m_used;   
    std::size_t m_peak;
public:
    Allocator(const std::size_t totalSize);

    virtual ~Allocator();

    virtual void* Allocate(const std::size_t size, const std::size_t alignment = 0) = 0;

    virtual void Free(void* ptr) = 0;

    virtual void Init() = 0;

    friend class Benchmark;
    
    virtual std::string GetName() = 0;
};

#endif /* ALLOCATOR_H */

