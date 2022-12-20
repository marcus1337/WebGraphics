#include <iostream>
#include <fstream>

#ifndef IOLOGS_H
#define IOLOGS_H

class IOLogs {

    std::ofstream outCout;
    std::ofstream outCerr;

public:

    IOLogs();
    void redirectCout(std::string logsFilePath, std::string errorLogsFilePath);

};

#endif