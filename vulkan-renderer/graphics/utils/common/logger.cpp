//
//  Logger.cpp
//  KEGE
//
//  Created by Kenneth Esdaile on 1/29/23.
//

#include <string.h>
#include <stdarg.h>
//#include "Message.hpp"
//#include "Channel.hpp"
#include "logger.hpp"

namespace kege
{
    void Log( kege::LogLevel level, const char* message, ... )
    {
        static const char* str_log_levels[6] = {
            "[ FATAL ]: ",
            "[ ERROR ]: ",
            "[ WARN  ]: ",
            "[ INFO  ]: ",
            "[ DEBUG ]: ",
            "[ TRACE ]: "
        };

        const int length = 4096;
        //bool is_error = level < 2;
        char out_message[ 2 ][ length ];
        memset( out_message, 0x0, length );

        va_list args;
        va_start( args, message );
        vsnprintf( out_message[0], length, message, args );
        va_end( args );

        //sprintf( out_message, "%s%s\n", str_log_levels[ level ], out_message );
        snprintf( out_message[1], length, "%s%s\n", str_log_levels[ level ], out_message[0] );
        printf( "%s", out_message[1] );

//        if ( level == LOG_LEVEL_FATAL )
//        {
//            kege::Channel::broadcast< kege::Ref< Message > >( new MsgSysExit() );
//        }
    }

    bool initalizeLogging()
    {
        // TODO: create log file
        return true;
    }

    void shutdownLogging()
    {
        // clean up logging
    }

    void report_assertion_failure(const char* expression, const char* message, const char* file, int line)
    {
        Log( kege::LOG_LEVEL_FATAL, "assertion failure: ( %s ), message: %s file: $s line: %i", expression, file, message, line );
    }
}
