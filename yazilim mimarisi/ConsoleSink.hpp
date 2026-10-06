#ifndef CONSOLE_SINK_HPP
#define CONSOLE_SINK_HPP

#include "LogRecord.h"
#include <iostream>

class ConsoleSink {
public:
    void write(const LogRecord& record) {
        std::cout << "[" << (record.timestamp.empty() ? "N/A" : record.timestamp) << "] "
                  << record.clientIp << " - "
                  << record.method << " "
                  << record.path << " -> Status: "
                  << record.status << " (" << record.bytes << " bytes)" << std::endl;
    }
};

#endif
