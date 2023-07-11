#include "Exception.h"
#include <string.h>

namespace eAccelero
{

const char* Exception::m_errorStringTable[RET_VAL_MAX - RET_FAILURE] =
{
    "Failed to execue operation",
};

Exception::Exception(const char *descr, int errNum) throw()
{
    if (errNum != 0 || errno != 0)
    {
        if (errNum == 0 && errno != 0)
        {
            errNum = errno;
        }
        if (errNum < RET_VAL_MAX)
        {
            // Internal error, lookup the table
            snprintf(m_errStr, ERR_STR_SZ, 
                "%s <%s:%d>", descr, 
                m_errorStringTable[errNum - RET_FAILURE], errNum);
        }
        else
        {
            // System error
            snprintf(m_errStr, ERR_STR_SZ, 
                "%s <%s:%d>", descr, strerror(errNum), errNum);
        }
    }
    else
    {
        snprintf(m_errStr, ERR_STR_SZ, 
                "%s", descr);
    }    
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
    return m_errStr;
}

};

