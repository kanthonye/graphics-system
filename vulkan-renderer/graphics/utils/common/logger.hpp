//
//  Logger.hpp
//  KEGE
//
//  Created by Kenneth Esdaile on 1/29/23.
//

#ifndef Logger_hpp
#define Logger_hpp
#include <stdio.h>
#include <vector>

#define KEGE_LOG_WARN_ENABLED  1
#define KEGE_LOG_INFO_ENABLED  1
#define KEGE_LOG_DEBUG_ENABLED 1
#define KEGE_LOG_TRACE_ENABLED 1

#if KEGE_RELEASE_MODE == 1
#define KEGE_LOG_DEBUG_ENABLED 0
#define KEGE_LOG_TRACE_ENABLED 0
#endif

namespace kege
{

    typedef enum LogLevel{
        /**
        FATAL logs are the most important and very serious log types. Fatal logs will cause the application to
        terminate because these logs are generated when a necessary requirement is not available for the
        application to run properly.
        **/
        LOG_LEVEL_FATAL,

        /**
        ERROR are the second most important log type and is a serious log level type. The error log level will not
        cause the application to terminate, but will cause the application to not function properly. These types of
        error should be taken care of immediatly.
        **/
        LOG_LEVEL_ERROR,

        /**
        WARN logs are the third most important log level type. The warn log level will not cause the application to terminate,
        and will not cause the application to not function properly. These types of error are not serious but should be taken care of..
        **/
        LOG_LEVEL_WARN,

        /**
        INFO logs detail information about the application state.
        **/
        LOG_LEVEL_INFO,
        LOG_LEVEL_DEBUG,

        /**
        Trace logs are the least important.
        **/
        LOG_LEVEL_TRACE
    } LogLevel;

    void Log( kege::LogLevel level, const char* message, ... );
    bool initalizeLogging();
    void shutdownLogging();

#define KEGE_FATAL( message, ...) Log( kege::LOG_LEVEL_FATAL, message, ##__VA_ARGS__ );
#define KEGE_ERROR( message, ...) Log( kege::LOG_LEVEL_ERROR, message, ##__VA_ARGS__ );


#if KEGE_LOG_WARN_ENABLED == 1
#define KEGE_WARN( message, ...) Log( kege::LOG_LEVEL_WARN, message, ##__VA_ARGS__ );
#else
#define KEGE_WARN( message, ...)
#endif

#if KEGE_LOG_INFO_ENABLED == 1
#define KEGE_INFO( message, ...) Log( kege::LOG_LEVEL_INFO, message, ##__VA_ARGS__ );
#else
#define KEGE_INFO( message, ...)
#endif

#if KEGE_LOG_DEBUG_ENABLED == 1
#define KEGE_DEBUG( message, ...) Log( kege::LOG_LEVEL_DEBUG, message, ##__VA_ARGS__ );
#else
#define KEGE_DEBUG( message, ...)
#endif

#if KEGE_LOG_TRACE_ENABLED == 1
#define KEGE_TRACE( message, ...) Log( kege::LOG_LEVEL_TRACE, message, ##__VA_ARGS__ );
#else
#define KEGE_TRACE( message, ...)
#endif
}

#endif /* Logger_hpp */
