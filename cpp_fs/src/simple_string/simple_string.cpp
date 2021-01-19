/******************************************************************************
*						CREATED BY:	Orpaz Houta                     	      *
*						CREATED ON: 26/07/2020               			      *
*				   		REVIEWER: Gil Mazliah (Gilio:)         				  *
******************************************************************************/
#include <cstring>             //strlen, strcpy..
#include <iostream>

#include "simple_string.hpp"   

namespace ilrd
{
String::String(const char *str)
{
    size_t len = strlen(str) + 1;

    m_cstr = new char[len]; //add try & catch.. 
    strcpy(m_cstr, str);
}

String::~String()
{
    delete[] m_cstr;
    m_cstr = 0;
}

String::String(const String& other)
{
    size_t len = other.Length() + 1;

    m_cstr = new char[len]; //add try & catch.. 
    strcpy(m_cstr, other.m_cstr); 
}

String& String::operator=(const String& str)
{
    if (m_cstr != str.CStr())
    {
        delete[] m_cstr;
        size_t len = str.Length() + 1;

        m_cstr = new char[len]; //add try & catch.. 
        strcpy(m_cstr, str.m_cstr); 
    }

    return (*this);
}


bool String::operator==(const String &other) const
{
    return (!strcmp(m_cstr, other.m_cstr));
}

size_t String::Length() const
{
    return (strlen(m_cstr));
}

const char *String::CStr() const
{
    return (m_cstr);
}


std::ostream& operator<<(std::ostream &out, const String &str)
{
    return (out << str.CStr());
}

bool operator==(const char *const str, const String &other)
{
    return (!strcmp(str, other.CStr()));
}   

bool operator<(const String &str1, const String &str2)
{
    return (0 > strcmp(str1.CStr(), str2.CStr()));
}

bool operator>(const String &str1, const String &str2)
{
    return (0 < strcmp(str1.CStr(), str2.CStr()));
}

}// namespace ilrd

