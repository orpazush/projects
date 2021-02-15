/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review :      						         *
 * 					Last update : 11.10.20									 *
 ****************************************************************************/
#ifndef ILRD_RD8788_SERIALIZER_HPP
#define ILRD_RD8788_SERIALIZER_HPP

#include <cstddef>							// size_t
#include <string>							// std::string
#include <boost/noncopyable.hpp>        	// boost::noncopyable
#include <boost/smart_ptr/shared_ptr.hpp> 	// boost::shared_ptr

#include "factory.hpp"

namespace ilrd
{
namespace project
{

template <typename BASE>
class Serializer : private boost::noncopyable
{
public:

    void Serialize(std::ostream& out, const BASE &obj) const;
    boost::shared_ptr<BASE> Deserialize(std::istream& in) const;

    template <typename DERIVED>
    void Add();

private:
	Factory<BASE, std::string, std::istream&> m_factory;
};

template<typename BASE>
void Serializer<BASE>::Serialize(std::ostream& out, const BASE &obj) const
{
    out << typeid(obj).name() << " ";//handle mangling TODO
    obj.Serialize(out);
    out << " ";
}

template<typename BASE>
boost::shared_ptr<BASE> Serializer<BASE>::Deserialize(std::istream& in) const
{
    std::string type;
    in >> type;
    BASE *base = m_factory.Create(type, in);

    return boost::shared_ptr<BASE>(base);
}

template<typename BASE>
template<typename DERIVED>
void Serializer<BASE>::Add()
{
    m_factory.Add(typeid(DERIVED).name(), &DERIVED::Deserialize);//handle mangling TODO
}

} // namespace project
} // namespace ilrd

#endif // ifndef ILRD_RD8788_SERIALIZER_HPP
