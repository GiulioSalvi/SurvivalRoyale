#ifndef _LOGS_CONFIGURATION_H_
    #define _LOGS_CONFIGURATION_H_
    /// @brief The length of the string "logs/dd-MM-yyyy_hh,mm,ss.log", that is the pattern of the filename of every log file generated by this program.
    #define fileNameBufferSize 29
    
    typedef struct LogsConfiguration {
        char fileName[fileNameBufferSize];
        bool useConsole;
    } LogsConfiguration;
#endif