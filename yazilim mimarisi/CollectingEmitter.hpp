#ifndef COLLECTING_EMITTER_HPP
#define COLLECTING_EMITTER_HPP

#include "LogRecord.h"
#include <vector>

class CollectingEmitter {
private:
    std::vector<LogRecord> collectedRecords;

public:
    void emit(const LogRecord& record) {
        collectedRecords.push_back(record);
    }

    const std::vector<LogRecord>& getCollectedRecords() const {
        return collectedRecords;
    }

    void clear() {
        collectedRecords.clear();
    }
};

#endif
