/////////////////////////////////////////////////////////
//
//    CPPUtils @ logger.cpp
//   Author: Eryk Dwornicki
//
/////////////////////////////////////////////////////////

#include "Logger.h"

FILE * Logger::s_pLogFile = 0;

void Logger::Init(const char *szFile)
{
    if(!s_pLogFile)
    {
        if(s_pLogFile = fopen(szFile,"w+"))
        {
            Info("Logger started!");
        }
        else
            printf("[FATAL ERROR] Cannot initialize logger (%s)\n", szFile);
    } else
        Error("Cannot initialize logger two times!");
}

void Logger::Shutdown()
{
    Info("Logger is shutting down.");

    if(s_pLogFile)
        fclose(s_pLogFile);
}

void Logger::Log(ELogType type, const char *msg, ...)
{
    if(!s_pLogFile)
    {
        printf("[FATAL ERROR] Cannot use Logger::Log - no log file set!\n");
        return;
    }

    va_list args;
    va_start(args,msg);

    time_t timeraw = time(NULL);
    struct tm * pTimeinfo = localtime(&timeraw);

    fprintf(s_pLogFile, "[%02d:%02d:%02d] ", pTimeinfo->tm_hour, pTimeinfo->tm_min, pTimeinfo->tm_sec);

    printf("[%02d:%02d:%02d] ", pTimeinfo->tm_hour, pTimeinfo->tm_min, pTimeinfo->tm_sec);
    switch(type)
    {
    case LogType_Error:
        {
            fputs("<error> ",s_pLogFile);
            printf("<error> ");
            break;
        }
    case LogType_Warning:
        {
            fputs("<warning> ",s_pLogFile);
            printf("<warning> ");
            break;
        }
    case LogType_Debug:
        {
            fputs("<debug> ",s_pLogFile);
            printf("<debug> ");
            break;
        }
    default:
        {
            fputs("<info> ",s_pLogFile);
            printf("<info> ");
            break;
        }
    }
    vfprintf(s_pLogFile, msg, args);
    fputc('\n', s_pLogFile);
    vprintf(msg, args);
    printf("\n");
    va_end(args);
    fflush(s_pLogFile);
}

FILE * Logger::GetFile()
{
    return s_pLogFile;
}