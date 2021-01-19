/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 29.9.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_STORAGE_STORAGE_HPP
#define ILRD_RD8788_STORAGE_STORAGE_HPP

#include <cstddef>               // size_t
#include <boost/noncopyable.hpp> // noncopyable

namespace ilrd
{
namespace project
{

template<size_t SIZE_OF_BLOCK>
class Storage : private boost::noncopyable
{
public:
	explicit Storage(size_t num_of_blocks);
	virtual ~Storage();

	virtual void Read(void *dest, size_t index) const=0;
	virtual void Write(const void *src, size_t index)=0;
};

/* ---------------------------------Ctor & Dtor----------------------------- */
template<size_t BLOCK_SIZE>
Storage<BLOCK_SIZE>::Storage(size_t num_of_blocks)
{
    (void)num_of_blocks;
}


template<size_t BLOCK_SIZE>
Storage<BLOCK_SIZE>::~Storage()
{
    //empty
}}
}
#endif //ILRD_RD8788_STORAGE_STORAGE_HPP