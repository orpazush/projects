/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 7.10.20									 *
 ****************************************************************************/

#include "logger.hpp"

using namespace std;

namespace ilrd
{
namespace project
{

Logger::Logger() : m_stop(false), m_thread(&Logger::WriteToFile, this), m_level(NONE)

{
    SetDefaultLevel();
    const char *filePath = getenv("ILRD_LOGGER_FILE_PATH");
    if (!filePath)
    {
        perror("ILRD_LOGGER_FILE_PATH is not set. default is /tmp/logger");
        filePath = "/tmp/logger";
    }
    m_file.open(filePath, ios::app);
}

Logger::~Logger()
{
    m_stop = true;
    Log("shutting down logger", NONE);
    m_thread.join();
    m_file.close();
}

void Logger::Log(const char *msg, Logger::level_t level)
{
    if (m_level >= level)
    {
        m_queue.Push(msg);
    }
}

void Logger::SetLevel(level_t newLevel) noexcept
{
    m_level = newLevel;
}

void Logger::SetDefaultLevel()
{
    level_t levels[5] = {NONE, ERROR, WARNING, INFO, DEBUG};
    char *envLevel = getenv("ILRD_LOGGER_LEVEL");
    if (!envLevel)
    {
        m_level = NONE;
    }
    else
    {
        int level = atoi(envLevel);
        if (level > DEBUG)
        {
            m_level = NONE;
        }
        else
        {
            m_level = levels[level];
        }
    }
}

void Logger::WriteToFile()
{
    while (!m_stop || !m_queue.IsEmpty())
    {
        string msg;
        m_queue.Pop(msg);
        m_file << msg << endl;
    }
}

namespace logger_details
{
void Log(const char *msg, Logger::level_t level, size_t line,
         const char *function)
{
    stringstream fullMsg;
    time_t timer = time(NULL);

    fullMsg << msg << " - line:" << line << " in:" << function << " at:" <<
            ctime(&timer);
    Singleton<Logger>::GetInstance()->Log(fullMsg.str().c_str(), level);
}
}//logger_details

}//project
}//ilrd

