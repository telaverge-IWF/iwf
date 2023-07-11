#include "Exception.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace eAccelero;

void ThrowSysExp(Logger &logger)
{
    int ret = open("somefile",  O_RDONLY);
    if (ret < 0)
    {
        throw SystemExceptionLog("File open failed", &logger, Logger::EACC_LOG_WARNING);
    }
}
void ThrowExp(Logger &logger)
{
    throw GenericExceptionLog("Test application", &logger, Logger::EACC_LOG_ERROR, RET_FAILURE);
}

int main()
{
    Logger logger("TestApp");
    logger.SetLevel(Logger::EACC_LOG_FATAL);

    EACC_LOG(logger, Logger::EACC_LOG_INFO, "Test application started");
    try
    {
        ThrowSysExp(logger);
    }
    catch (SystemException &sys)
    {
        EACC_LOG(logger, Logger::EACC_LOG_CRITICAL, sys.what());
    }
    catch(Exception &e)
    {
        EACC_LOG(logger, Logger::EACC_LOG_FATAL, e.what());
    }

    try
    {
        ThrowExp(logger);
    }
    catch (SystemException &sys)
    {
        EACC_LOG(logger, Logger::EACC_LOG_CRITICAL, sys.what());
    }
    catch(Exception &e)
    {
        EACC_LOG(logger, Logger::EACC_LOG_FATAL, e.what());
    }

    EACC_LOG(logger, Logger::EACC_LOG_NOTICE, "Test application completed");

    return 0;
}

