#ifndef __LOGGER_DEFS_h__
#define __LOGGER_DEFS_h__

namespace eAccelero
{
#define SUB_COMP_LOG(_level, ...) \
    EACC_LOG((*(eAccelero::Logger::currLogger.GetData())), _level,__VA_ARGS__)

#define DLOG_FATAL(...) \
    SUB_COMP_LOG(eAccelero::Logger::EACC_LOG_FATAL, __VA_ARGS__)

#define DLOG_CRITICAL(...) \
    SUB_COMP_LOG(eAccelero::Logger::EACC_LOG_CRITICAL, __VA_ARGS__)

#define DLOG_ERROR(...) \
    SUB_COMP_LOG(eAccelero::Logger::EACC_LOG_ERROR, __VA_ARGS__)

#define DLOG_WARNING(...) \
    SUB_COMP_LOG(eAccelero::Logger::EACC_LOG_WARNING, __VA_ARGS__)

#define DLOG_NOTICE(...) \
    SUB_COMP_LOG(eAccelero::Logger::EACC_LOG_NOTICE, __VA_ARGS__)

#define DLOG_INFO(...) \
    SUB_COMP_LOG(eAccelero::Logger::EACC_LOG_INFO, __VA_ARGS__)

#define DLOG_DEBUG(...) \
    SUB_COMP_LOG(eAccelero::Logger::EACC_LOG_DEBUG, __VA_ARGS__)

#define INIT_LOG(...) \
    (((eAccelero::Logger::GetInitLogger())).log(eAccelero::Logger::EACC_LOG_DEBUG, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)) 

}

#endif

