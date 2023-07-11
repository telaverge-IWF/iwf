#ifndef __EACC_Exception_h__
#define __EACC_Exception_h__

#include <errno.h>
#include <exception>
#include "Logger.h"
#include <string.h>
#include <typeinfo>

namespace eAccelero
{

// Aborts if the condition is not satisfied
#define EACC_ASSERT(_cond)  \
    if (BRANCH_EXPECT((_cond) == 0, 0))\
    {\
        std::cerr << "Asserion: " << #_cond << " at "\
                  << __FILE__ << ":" << __LINE__ <<std::endl;\
        abort();\
    }

// Add corresponding entry in Exception.cpp m_errorStringTable
enum RetVal
{
    RET_FAILURE = -10000, // Failed to execute operation

    RET_VAL_MAX // Should be the last enum
};

class Exception: public std::exception
{
 public:
    enum
    {
        ERR_STR_SZ = 512,
    };

    Exception(const char *desc, int errNum = 0) throw();    
    virtual ~Exception() throw();

    virtual const char *what() const throw();

    Exception& Log(Logger *m_logger, Logger::Level level = Logger::EACC_LOG_ERROR,
                   const char *srcFile = "", int lineNo = 0,
                   const char *funcName = "");

    const char* className();

    // Not to be confused with what(), this gets an error val for string
    static const char *GetErrorString(RetVal val)
    {
        return m_errorStringTable[val - RET_FAILURE];
    }

 protected:
    void AddMessage(const char *msg);
 
 private:
    char m_errStr[ERR_STR_SZ];

    static const char *m_errorStringTable[RET_VAL_MAX - RET_FAILURE];
};

inline Exception& Exception::Log(Logger *m_logger, Logger::Level level,
                             const char *srcFile, int lineNo, const char *funcName)
{
    if (m_logger && m_logger->IsEnabled(level))
    {
        m_logger->log(level, srcFile, lineNo, funcName, m_errStr);
    }

    return *this;
}

inline void Exception::AddMessage(const char *msg)
{
    strcat(m_errStr, " | ");
    strncat(m_errStr, msg, ERR_STR_SZ);
    m_errStr[ERR_STR_SZ-1] = '\0';
}

inline const char* Exception::className()
{
    // In g++ it retuns the classname prefixed with a number
    return typeid(*this).name();
}

// Accepts one more arg, which is the error code
#define GEN_EXCEPTION_LOG(_exceptionClass, _descr, _logger, _level, ...) \
            _exceptionClass(_descr, ##__VA_ARGS__)\
                .Log(_logger, _level, __FILE__, __LINE__, __FUNCTION__)

// Acceped params _descr, _logger, _level, _code
#define GenericExceptionLog(...) \
            GEN_EXCEPTION_LOG(Exception, ##__VA_ARGS__)

#define EACC_DEFINE_EXCEPTION_CLASS(_NewException, _Base, _exStr)   \
    class _NewException: public _Base                               \
    {                                                               \
     public:                                                        \
        _NewException(const char *descr, int errCode = 0) throw()   \
            : _Base(descr, errCode)                                 \
        {                                                           \
            this->AddMessage(#_exStr);                              \
        }                                                           \
        ~_NewException() throw(){}                                   \
    };


EACC_DEFINE_EXCEPTION_CLASS(SystemException, Exception, "System Exception")
#define SystemExceptionLog(...) GEN_EXCEPTION_LOG(eAccelero::SystemException, ##__VA_ARGS__)

EACC_DEFINE_EXCEPTION_CLASS(RuntimeException, Exception, "Runtime Exception")
#define RuntimeExceptionLog(...) GEN_EXCEPTION_LOG(eAccelero::RuntimeException, ##__VA_ARGS__)

} // namespace eAccelero

#endif // __EACC_Exception_h__
