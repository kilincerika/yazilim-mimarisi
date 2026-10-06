#ifndef LOGRECORD_H
#define LOGRECORD_H

#include <string>
#include <map>

struct LogRecord {
    std::string timestamp;
    std::string clientIp;
    std::string method;
    std::string path;
    int status;
    long bytes;
    std::string userAgent;
    std::map<std::string, std::string> attributes; // Gelecekteki geniþlemeler için kritik nokta!
    std::string raw;
};

#endif
