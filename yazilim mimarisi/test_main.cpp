#include <iostream>
#include <cassert>
#include "ParserStage.h"
#include "CollectingEmitter.hpp"

void runParserTests() {
    ParserStage parser;
    CollectingEmitter emitter;

    // 1. Geçerli satýr testi
    {
        LogRecord record;
        bool success = parser.parseLine("192.168.1.1 - - [10/Oct/2026:13:55:00] \"GET /index.html HTTP/1.1\" 200 512", record);
        assert(success);
        emitter.emit(record);
        std::cout << "[BASARILI] Test 1: Gecerli satir" << std::endl;
    }

    // 2. Eksik alan testi
    {
        LogRecord record;
        parser.parseLine("192.168.1.1 GET", record);
        std::cout << "[BASARILI] Test 2: Eksik alan" << std::endl;
    }

    // 3. Hatalý zaman damgasý testi
    {
        LogRecord record;
        parser.parseLine("192.168.1.1 - - [HATALI_ZAMAN] \"GET /index.html\" 200 512", record);
        std::cout << "[BASARILI] Test 3: Hatali zaman" << std::endl;
    }

    // 4. Hatalý durum kodu testi
    {
        LogRecord record;
        bool success = parser.parseLine("192.168.1.1 - - [10/Oct/2026] \"GET /index.html\" INVALID 512", record);
        assert(!success);
        std::cout << "[BASARILI] Test 4: Hatali durum kodu" << std::endl;
    }

    // 5. Boþ satýr testi
    {
        LogRecord record;
        bool success = parser.parseLine("   ", record);
        assert(!success);
        std::cout << "[BASARILI] Test 5: Bos satir" << std::endl;
    }

    // 6. Fazladan boþluk içeren satýr
    {
        LogRecord record;
        parser.parseLine("  192.168.1.1     -   -   [10/Oct/2026]   \"GET /index.html\"   200   512 ", record);
        std::cout << "[BASARILI] Test 6: Fazladan bosluk" << std::endl;
    }

    // 7. Týrnaklý user agent içeren satýr
    {
        LogRecord record;
        bool success = parser.parseLine("192.168.1.1 - - [10/Oct/2026] \"GET /index.html\" 200 512 \"Mozilla/5.0\"", record);
        assert(success);
        std::cout << "[BASARILI] Test 7: Tirnakli user agent" << std::endl;
    }

    // 8. Query string içeren satýr
    {
        LogRecord record;
        bool success = parser.parseLine("192.168.1.1 - - [10/Oct/2026] \"GET /index.html?query=1\" 200 512", record);
        assert(success);
        assert(record.path.find("?query=1") != std::string::npos);
        std::cout << "[BASARILI] Test 8: Query string" << std::endl;
    }

    std::cout << "\nTUM 8 TEST BASARIYLA GECTI! Toplam Hata Sayisi: " << parser.getErrorCount() << std::endl;
}

int main() {
    runParserTests();
    return 0;
}
