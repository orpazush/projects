/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 3.8.20									 *
 ****************************************************************************/
#include <cstring>      //strlen, strcpy
#include <iostream>     //operator <<
#include <cstddef>      //offsetof
#include <cassert>      //assert

#include "rc_string.hpp"

namespace ilrd
{
// -----------------------------Ctors & Dtor-----------------------------------

RCString::RCString(const char *str)
{
    InitRc(str);
}

RCString::~RCString()
{
    if (1 == m_rc->counter)
    {
        delete (m_rc);
        m_rc = 0;
    }

    else
    {
        --m_rc->counter;
    }
}

RCString::RCString(const RCString &other)
{
    CopyRc(other);
}

RCString &RCString::operator=(const RCString &str)
{
    this->~RCString();
    CopyRc(str);

    return (*this);
}
// ----------------------------------------------------------------------------

// ----------------------------Methods Of RCString-----------------------------
char RCString::operator[](size_t index) const
{
    assert(index <= GetLength());

    return (m_rc->str[index]);
}

char &RCString::operator[](size_t index)
{
    assert(index <= GetLength());

    if (1 < m_rc->counter)
    {
        /* GHS - suggestion
        * this = m_rc->str;
        */
        RC *oldRc = m_rc;
        InitRc(oldRc->str);

        //if InitRc threw nothing will change
        --oldRc->counter;
    }

    return (m_rc->str[index]);
}

size_t RCString::GetLength() const
{
    return (strlen(m_rc->str));
}

const char *RCString::GetStr() const
{
    return (m_rc->str);
}

// -----------------------------Methods Of RC---------------------------------
void RCString::InitRc(const char *str)
{
    // calculate the size of RC is needed due to the use in flexible array
    size_t size_rc = offsetof(RC, str) + (strlen(str) + 1);
    m_rc = static_cast<RC *>(operator new(size_rc));
    strcpy(m_rc->str, str);
    m_rc->counter = 1;
}

void RCString::CopyRc(const RCString &to_copy)
{
    m_rc = to_copy.m_rc;
    ++m_rc->counter;
}

// ----------------------------------------------------------------------------

// ---------------------------Global Operators---------------------------------
std::ostream &operator<<(std::ostream &out, const RCString &str)
{
    return (out << str.GetStr());
}

bool operator==(const RCString &str1, const RCString &str2)
{
    return (!strcmp(str1.GetStr(), str2.GetStr()));
}

bool operator!=(const RCString &str1, const RCString &str2)
{
    return (!(str1 == str2));
}

bool operator<(const RCString &str1, const RCString &str2)
{
    return (0 > strcmp(str1.GetStr(), str2.GetStr()));
}

bool operator>(const RCString &str1, const RCString &str2)
{
    return (0 < strcmp(str1.GetStr(), str2.GetStr()));
}
// ----------------------------------------------------------------------------
} // namespace ilrd
