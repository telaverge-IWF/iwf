#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <unistd.h>
#include <sys/syscall.h>
#include <linux/unistd.h>

#include "ThreadSpec.h"
#include "Logger.h" 


pid_t gettid();

// TODO make this a thread specific store, instead of making a syscall 
// everytime a trace is generated
inline pid_t gettid()
{
    return syscall(SYS_gettid);
}


namespace eAccelero
{

ThreadSpec <Logger> Logger::currLogger;
Logger* Logger::initLogger = NULL;

Logger& Logger::InitLogger(const char *name)
{
    if(initLogger == NULL && name != NULL)
    {
        initLogger = new Logger(name);
    }
    else if(initLogger == NULL)
    {
        initLogger = new Logger("INIT_LOG");
    }
    return *initLogger;
}

Logger& Logger::GetInitLogger()
{
    if(initLogger == NULL)
    {
        initLogger = new Logger("INIT_LOG");
    }
    return *initLogger;
}

Logger::Logger(const char *name,bool isTimePrefixRequired)
    : m_channel(NULL),
      m_name(name),
      m_isTimePrefixRequired(isTimePrefixRequired)
{
    // Default channel is console, can be altered later
    m_channel = ConsoleLogChannel::Instance();
    //currLogger = this; 
}


// Constants
// TODO make this mutable using Logger functions
const char* HeaderFmt = "[%s.%06d]|%d|%s|%s|%s:%d";
//syslog header format
const char* SyslogHeaderFmt = "%d|%s|%s|%s:%d";
const char* TimeFmt   = "%b%d %H:%M:%S";
const int TRACE_MAX_TSTR = 40;

static const char * TraceLevelTable[Logger::MAX_LEVELS] =
{
    "Fatal",
    "Alert",
    "Critical",
    "Error",
    "Warning",
    "Notice",
    "Info",
    "Debug"
};

int Logger::log(const Level &level, const char *srcFile, 
              int lineNo, const char *funcName,
              const char *fmt, ...)
{
    if (m_channel == NULL)
    {
        return 0;
    }

    char timeStr[TRACE_MAX_TSTR];
    char msg[MAX_STRING];
    char fmtmsg[MAX_STRING];
    char newFileName[MAX_STRING];
    int ret = 0;
    struct tm tNow;
    struct timeval tval;
    va_list vaList;


    // Strip the path from fileName
    if (srcFile)
    {
        int i;
        char* ptr = const_cast<char*>(srcFile);
        for(i = 0; *ptr; ptr++)
        {
            if (*ptr == '/')
            {
                // Dir encounter, reset the buffer index
                i = 0;
                continue;
            }
            newFileName[i++] = *ptr;
        }
        newFileName[i] = '\0';
    }


    // Form the Trace header
    if(m_isTimePrefixRequired)
    {
        gettimeofday(&tval, NULL);
        // Form the time string to be displayed in the trace
        strftime(timeStr, TRACE_MAX_TSTR, TimeFmt, localtime_r(&(tval.tv_sec), &tNow));
        snprintf(msg, MAX_STRING, HeaderFmt, timeStr, tval.tv_usec, gettid(),
                m_name.c_str(), TraceLevelTable[level], newFileName, lineNo);
    }
    else
    {
        snprintf(msg, MAX_STRING, SyslogHeaderFmt, gettid(), m_name.c_str(), 
                TraceLevelTable[level], newFileName, lineNo);
    }

    // Form the message from the variable args and the format
    va_start(vaList, fmt);
    ret = vsnprintf(fmtmsg, MAX_STRING, fmt, vaList);
    va_end(vaList);

    //strcat(msg, "\n ");
    strcat(msg, fmtmsg);

    // Level is required for utilities like syslogd
    m_channel->log(msg, level);

    return ret;
}
 
ConsoleLogChannel* ConsoleLogChannel::m_instance = NULL;

ConsoleLogChannel* ConsoleLogChannel::Instance()
{
    if (m_instance == NULL)
    {
        m_instance = new ConsoleLogChannel();
    }
    return m_instance;
}

void ConsoleLogChannel::Destroy()
{
    if (m_instance != NULL)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

FileLogChannel::FileLogChannel(const char *fileName, const char* dirName,
            std::ios_base::openmode mode)
{
    std::string filePath(dirName);
    filePath.append("/");
    filePath.append(fileName);

    m_ostr.open(filePath.c_str(), mode);
}

void FileLogChannel::log(const char *str, int level)
{
    // TODO Mutex locks
    m_ostr << str << std::endl;
}

void FileLogChannel::dump(const unsigned char *bytes, unsigned len)
{
    if (m_protoDecoder)
    {
        std::string decodedStr;

        m_protoDecoder->Decode(bytes, len, decodedStr);

        m_ostr << decodedStr << std::endl;
    }
}

SyslogChannel::SyslogChannel(const char *ident, int options, int facility)
{
    openlog(ident, options, facility);
}

SyslogChannel::~SyslogChannel()
{
    closelog();
}

void SyslogChannel::log(const char* str, int level)
{
    syslog(level, str);
}

void SyslogChannel::dump(const unsigned char *bytes, unsigned len)
{
    // not implemented
}

ScopedLogger::ScopedLogger(Logger &logger)
{
    mpOldLogger = Logger::currLogger.GetData();
    Logger::currLogger = &logger;
}

ScopedLogger::~ScopedLogger()
{
    Logger::currLogger = mpOldLogger;
}

} // namespace eAccelero
