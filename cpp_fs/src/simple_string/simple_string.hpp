/******************************************************************************
*						CREATED BY:	Orpaz Houta                     	      *
*						CREATED ON: 26/07/2020               			      *
*				   		REVIEWER: Gil Mazliah (Gilio:)         				  *
******************************************************************************/
#ifndef ILRD_RD8788_SIMPLE_STRING_HPP
#define ILRD_RD8788_SIMPLE_STRING_HPP

#include <iosfwd>   // ostream

namespace ilrd
{

class String
{
public:
    String(const char *str = ""); // non explicit by intention 
    String(const String &other);
    String &operator=(const String &str);
    ~String();

    bool operator==(const String &other) const;

    size_t Length() const;
    const char *CStr() const;

private:
    char *m_cstr;
};

std::ostream &operator<<(std::ostream &out, const String &str);

// comparison between objects of class Strings
bool operator==(const char *const str, const String &other);    
bool operator<(const String &str1, const String &str2);
bool operator>(const String &str1, const String &str2);

} // namespace ilrd

#endif // ILRD_RD8788_SIMPLE_STRING_HPP__