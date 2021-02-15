/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 29.9.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_STORAGE_HEAP_HPP
#define ILRD_RD8788_STORAGE_HEAP_HPP

#include <cassert>                 //assert

#include "storage.hpp"

namespace ilrd
{
namespace project
{

template<size_t BLOCK_SIZE>
class StorageHeap : public Storage<BLOCK_SIZE>
{
public:
    explicit StorageHeap(size_t num_of_blocks);
    virtual ~StorageHeap();

    virtual void Read(void *dest, size_t index) const;
    virtual void Write(const void *src, size_t index);
private:
    char *m_storage;
    size_t m_num_of_blocks;
};

/* ---------------------------------Ctor & Dtor----------------------------- */

template<size_t BLOCK_SIZE>
StorageHeap<BLOCK_SIZE>::StorageHeap(size_t num_of_blocks) :
        Storage<BLOCK_SIZE>(num_of_blocks),
        m_storage(new char[num_of_blocks * BLOCK_SIZE]), m_num_of_blocks(num_of_blocks)
{
//empty
}

template<size_t BLOCK_SIZE>
StorageHeap<BLOCK_SIZE>::~StorageHeap()
{
    delete[] m_storage;
    m_storage = 0;
}

/* -------------------------------Public Methods---------------------------- */

template<size_t BLOCK_SIZE>
void StorageHeap<BLOCK_SIZE>::Read(void *buffer, size_t index) const
{
    assert(index <= m_num_of_blocks);

    std::copy(m_storage + (index * BLOCK_SIZE),
              (m_storage + (index * BLOCK_SIZE) + BLOCK_SIZE),
              static_cast<char *>(buffer));
}

template<size_t BLOCK_SIZE>
void StorageHeap<BLOCK_SIZE>::Write(const void *buffer, size_t index)
{
    assert(index <= m_num_of_blocks);

    std::copy(static_cast<const char *>(buffer),
              static_cast<const char *>(buffer) + BLOCK_SIZE,
              m_storage + (index * BLOCK_SIZE));
}

}//project
}//ilrd

#endif //ILRD_RD8788_STORAGE_HEAP_HPP
