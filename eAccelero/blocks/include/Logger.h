#ifndef __EACC_Logger_h__
#define __EACC_Logger_h__

#include <iostream>
#include <string>
#include <bitset>
#include <fstream>
#include <stdexcept>

#include <syslog.h>

#include "EAcc.h"
#include "Logger_Defs.h"

namespace eAccelero
{

/* Forward Declaration for Logging*/
template<typename TSType>
class ThreadSpec;

class LogProtoDecoder
{
 public:
    virtual ~LogProtoDecoder();
    virtual void Decode(const uint8_t *bytes, uint32_t len, std::string &out) = 0;
};

// Abstract class to redirect to needed output
// Possible Channels are stdout or file or syslogd 
//          or ipc(mess) or a splitter or NullChannel
//
class LogChannel
{
 public:
    LogChannel()
        : m_protoDecoder(NULL)
    {
    }
    virtual ~LogChannel() {}
    virtual void log(const char *str, int level = 0) = 0;

    // Dumps in a hex format, TODO should get Src and Dest
    virtual void dump(const unsigned char *bytes, unsigned len) = 0;

    void RegisterProtoDecoder(LogProtoDecoder *decoder)
    {
        m_protoDecoder = decoder;
    }
 protected:
    LogProtoDecoder *m_protoDecoder;
};

// Should have a means to get config property
// Mutex locks, probably at the channel level 
// Mechanism for enabling log per subscriber etc... 
class Logger
{
 public:

    enum Level
    {
        EACC_LOG_FATAL,
        EACC_LOG_ALERT,
        EACC_LOG_CRITICAL,
        EACC_LOG_ERROR,
        EACC_LOG_WARNING,
        EACC_LOG_NOTICE,
        EACC_LOG_INFO,
        EACC_LOG_DEBUG,

        MAX_LEVELS
    };

    enum Channel
    {
        EACC_CHANNEL_SYSLOG,
        EACC_CHANNEL_FILE,
        EACC_CHANNEL_CONSOLE,
        EACC_MAX_CHANNELS
    };

    enum
    {
        MAX_STRING = 8192
    };

    Logger(const char *name,bool isTimePrefixRequired= false);
    ~Logger() {}

    // @throw std::out_of_range if level is > MAX_LEVELS
    Logger& SetLevel(const Level &level, bool val = true);

    Level GetLevel();

    Logger& SetLogChannel(LogChannel *channel,bool isTimePrefixRequired= false);

    bool IsEnabled(const Level &level);

    // Formats the message and logs using the channel
    // Use the macros for actual logging
    int log(const Level &level, const char *srcFile, 
              int lineNo, const char *funcName,
              const char *fmt, ...);

    static ThreadSpec <Logger> currLogger;
    static Logger *initLogger;
    static Logger& InitLogger(const char *name);
    static Logger& GetInitLogger();
 
 protected:
    
    std::bitset<MAX_LEVELS> m_level;
    LogChannel  *m_channel;
    std::string m_name;
    bool m_isTimePrefixRequired;
};

class ScopedLogger
{
public:
    ScopedLogger(Logger &logger);
    ~ScopedLogger();
private:
    Logger *mpOldLogger;
};

class NullLogChannel: public LogChannel
{
 public:
    void log(const char* str, int level = 0)
    {
        (void)str;
    }
    void dump(const unsigned char *bytes, unsigned len)
    {
        (void)bytes;
        (void)len;
    }
};

class ConsoleLogChannel: public LogChannel
{
 public:
    void log(const char* str, int level = 0);
    void dump(const unsigned char *bytes, unsigned len);

    static ConsoleLogChannel* Instance();
    static void Destroy();

 private:
    static ConsoleLogChannel *m_instance;
};

class FileLogChannel: public LogChannel
{
 public:
    FileLogChannel(const char *fileName, const char* dirName,
            std::ios_base::openmode mode = std::ios_base::app);

    void log(const char* str, int level = 0);
    void dump(const unsigned char *bytes, unsigned len);

 private:
    std::ofstream m_ostr;
};

class SyslogChannel: public LogChannel
{
 public:
    SyslogChannel(const char *ident = NULL, int options = 0, int facility = LOG_USER);
    ~SyslogChannel();

    void log(const char* str, int level = 0);
    void dump(const unsigned char *bytes, unsigned len);
};

template <int N>
class DemuxLogChannel: public LogChannel
{
 public:
    // TODO have a static check to limit the number of channels
    // probably to 4
    enum { MAX_CHANNELS = N };

    DemuxLogChannel()
    {
        for(int i = 0; i < MAX_CHANNELS; i++)
            m_channels[i] = NULL;
    }

    void addChannel(LogChannel *channel)
    {
        for(int i = 0; i < MAX_CHANNELS; i++)
        {
            if (m_channels[i] == NULL)
            {
                m_channels[i] = channel;
                return;
            }
        }
        throw std::out_of_range("Cannot add anymore channel");
    }

    void removeChannel(LogChannel *channel)
    {
        for(int i = 0; i < MAX_CHANNELS; i++)
        {
            if (m_channels[i] == channel)
            {
                m_channels[i] = NULL;
                return;
            }
        }
    }

    void log(const char* str, int level = 0)
    {
        for(int i = 0; i < MAX_CHANNELS; i++)
        {
            if (m_channels[i])
                m_channels[i]->log(str, level);
        }
    }

    void dump(const unsigned char *bytes, unsigned len)
    {
        for(int i = 0; i < MAX_CHANNELS; i++)
        {
            if (m_channels[i])
                m_channels[i]->dump(bytes, len);
        }
    }
    
 private:
    LogChannel *m_channels[N];    
};


inline Logger& Logger::SetLevel(const Level &level, bool val)
{
    m_level.reset();
    m_level.set(level, val);
    return *this;
}

inline Logger::Level Logger::GetLevel()
{
    return (Logger::Level)m_level._Find_first();
}

inline Logger& Logger::SetLogChannel(LogChannel *channel,bool isTimePrefixRequired)
{
    m_channel = channel;
    m_isTimePrefixRequired = isTimePrefixRequired;
    return *this;
}

inline bool Logger::IsEnabled(const Level &level)
{
    // NOTE: this may not be portable
    unsigned bitPos = m_level._Find_first();
    return (bitPos != MAX_LEVELS) && (bitPos >= (unsigned)level);
}

inline void ConsoleLogChannel::log(const char *str, int level)
{
    std::cout << str << std::endl;
}

inline void ConsoleLogChannel::dump(const unsigned char *bytes, unsigned len)
{
}

} // namespace eAccelero

#define EACC_LOG(_logger, _level, ...) \
    _logger.IsEnabled(_level) ? \
        _logger.log(_level, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__) :\
        0

#endif // __EACC_Logger_h__
