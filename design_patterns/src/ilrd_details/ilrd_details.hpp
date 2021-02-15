/******************************************************************************
 *                          code by : Orpaz Hout                              *
 ******************************************************************************/

#ifndef ILRD_RD8788_ILRD_DETAILS_HPP
#define ILRD_RD8788_ILRD_DETAILS_HPP

#include <cstdio>
#include <stdexcept>
#include "logger.hpp"

namespace ilrd
{

namespace ilrd_details
{

#if __cplusplus<201103L
#define noexcept throw()
#endif

enum status {ERROR = -1, SUCCESS, FAILURE};

using namespace project;

inline void IfErrorPerror(int to_check, const char *msg)
{
    if (ERROR == to_check)
    {
        LOG_ERROR(msg);
        perror(msg);
        throw(std::runtime_error(msg));
    }
}

inline void LogErrorAndThrowIf(bool condition, const char *msg) //throw
{
    if (condition)
    {
        LOG_ERROR(msg);
        throw(std::runtime_error(msg));
    }
}

inline void LogWarningIf(bool condition, const char *msg)
{
    if (condition)
    {
        LOG_WARNING(msg);
    }
}

inline void LogInfoIf(bool condition, const char *msg)
{
    if (condition)
    {
        LOG_INFO(msg);
    }
}

inline void LogDebugIf(bool condition, const char *msg)
{
    if (condition)
    {
        LOG_DEBUG(msg);
    }
}

#ifdef HAVE_CXA_DEMANGLE //TODO
const char* demangle(const char* name);

#else

const char* demangle(const char* name);
#endif

}//ilrd_details
}//ilrd

#endif//ILRD_RD8788_ILRD_DETAILS_HPP
