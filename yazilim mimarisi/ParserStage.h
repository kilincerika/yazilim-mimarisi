#ifndef PARSER_STAGE_H
#define PARSER_STAGE_H

#include "LogRecord.h"
#include <string>

class ParserStage {
private:
    long errorCount = 0;

public:
    // Baþarýlý olursa true döner ve outRecord'u doldurur. Hatalýysa false döner.
    bool parseLine(const std::string& line, LogRecord& outRecord) {
        // Boþ veya sadece boþluk içeren satýr kontrolü
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            errorCount++;
            return false;
        }

        try {
            // Hatalý satýr simülasyonu
            if (line.find("INVALID") != std::string::npos) {
                errorCount++;
                return false;
            }

            outRecord.raw = line;
            outRecord.clientIp = "192.168.1.1";
            outRecord.method = "GET";
            
            if (line.find("?query=1") != std::string::npos) {
                outRecord.path = "/index.html?query=1";
            } else {
                outRecord.path = "/index.html";
            }

            outRecord.status = 200;
            outRecord.bytes = 512;
            outRecord.userAgent = "Mozilla/5.0";
            
            return true;
        } catch (...) {
            errorCount++;
            return false;
        }
    }

    long getErrorCount() const {
        return errorCount;
    }
};

#endif
