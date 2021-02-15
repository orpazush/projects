/******************************************************************************
 *                          code by : Orpaz Hout                              *
 ******************************************************************************/

#include "ilrd_details.hpp"

namespace ilrd
{

#ifdef HAVE_CXA_DEMANGLE //TODO
const char* demangle(const char* name)
{
   char buf[1024];
    unsigned int size=1024;
    int status;
    char* res = abi::__cxa_demangle (name,
                                 buf,
                                 &size,
                                 &status);
    return res;
  }
#else

const char* demangle(const char* name)
{
  return name;
}
#endif

}//ilrd

