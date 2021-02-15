/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 11.10.20									 *
 ****************************************************************************/

#ifndef __ILRD_RD8788_FACTORY_H__
#define __ILRD_RD8788_FACTORY_H__

#include <map>                    //map
#include <boost/noncopyable.hpp>  // boost::noncopyable

#include "logger.hpp"             //LOG_..

namespace ilrd
{
namespace project
{

/*-----------------------------Factory With Param----------------------------*/
//KEY must be copyable and comparable
template <typename BASE, typename KEY , typename PARAM = void >
class Factory : private boost::noncopyable
{
public:
    void Add(const KEY &key, BASE*(*creator)(PARAM) );
    BASE *Create(const KEY &key, PARAM param) const;

private:
    std::map<KEY, BASE*(*)(PARAM)> m_map;
};

/*---------------------------Factory Without Param---------------------------*/
template <typename BASE, typename KEY>
class Factory<BASE, KEY, void> : private boost::noncopyable
{
public:
    void Add(const KEY &key, BASE*(*creator)());
    BASE *Create(const KEY &key) const;

private:
    std::map<KEY, BASE*(*)()> m_map;
};

/*----------------------Methods of Factory With Param------------------------*/
template<typename BASE, typename KEY, typename PARAM>
void Factory<BASE, KEY, PARAM>::Add(const KEY &key, BASE *(*creator)(PARAM))
{
    if (!m_map.insert(std::make_pair(key, creator)).second)
    {
        LOG_WARNING("creator wasn't inserted because key already exists");
        throw std::runtime_error("key is already exist");
    }
}

template<typename BASE, typename KEY, typename PARAM>
BASE *Factory<BASE, KEY, PARAM>::Create(const KEY &key, PARAM param) const
{
    if (m_map.end() != m_map.find(key))
    {
        return m_map.find(key)->second(param);
    }
    else
    {
        LOG_ERROR("inserted invalid key");
        throw std::runtime_error("invalid key");
    }
}

/*--------------------Methods of Factory Without Param-----------------------*/

template<typename BASE, typename KEY>
void Factory<BASE, KEY, void>::Add(const KEY &key, BASE *(*creator)())
{
    if (!m_map.insert(std::make_pair(key, creator)).second)
    {
        LOG_WARNING("creator wasn't inserted because key is already exist");
        throw std::runtime_error("key is already exist");
    }
}

template<typename BASE, typename KEY>
BASE *Factory<BASE, KEY, void>::Create(const KEY &key) const
{
    if (m_map.end() != m_map.find(key))
    {
        return m_map.find(key)->second();
    }
    else
    {
        LOG_ERROR("inserted invalid key");
        throw std::runtime_error("invalid key");
    }
}
/*---------------------------------------------------------------------------*/

} // namespace project
} // namespace ilrd

#endif // __ILRD_RD8788_FACTORY_H__