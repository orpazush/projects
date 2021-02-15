/*****************************************************************************
 * 					written by : Orpaz Houta								 *
 * 					review : Gil Steinberg     						         *
 * 					Last update : 7.10.20									 *
 ****************************************************************************/

#ifndef ILRD_RD8788_LOGGER_HPP
#define ILRD_RD8788_LOGGER_HPP

#include <fstream>                      //std::fstream
#include <boost/core/noncopyable.hpp>   //noncopyable
#include <boost/thread.hpp>             //boost::thread

#include "waitable_queue.hpp"           //WaitableQueue
#include "singleton.hpp"                //Singleton<Logger>

#if __cplusplus<201103L
#define noexcept throw()
#endif

namespace ilrd
{
namespace project
{

class Logger : private boost::noncopyable
{
public:
    enum level_t
    {
        NONE,
        ERROR,
        WARNING,
        INFO,
        DEBUG
    };

    ~Logger();

    void Log(const char *msg, level_t level);
    void SetLevel(level_t newLevel) noexcept;

private:
    friend class Singleton<Logger>;
    explicit Logger();
    void SetDefaultLevel();
    void WriteToFile();

    WaitableQueue<std::string> m_queue;
    std::fstream m_file;
    bool m_stop;
    boost::thread m_thread;
    level_t m_level;
};

#define LOG(msg, level) (ilrd::project::logger_details::Log(msg, \
                        level, __LINE__, __FUNCTION__))
#define LOG_ERROR(msg) (LOG(msg, Logger::ERROR))
#define LOG_WARNING(msg) (LOG(msg, Logger::WARNING))
#define LOG_INFO(msg) (LOG(msg, Logger::INFO))
#define LOG_DEBUG(msg) (LOG(msg, Logger::DEBUG))

namespace logger_details
{
//env level "ILRD_LOGGER_LEVEL"
//env log file "ILRD_LOGGER_FILE_PATH"

void Log(const char *msg, Logger::level_t level, size_t line, const char *function);

}//logger_details

}//project
}//ilrd
#endif //ILRD_RD8788_LOGGER_HPP
