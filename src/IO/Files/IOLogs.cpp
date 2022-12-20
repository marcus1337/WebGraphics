#include "IOLogs.h"
#include <iostream>
#include <fstream>

IOLogs::IOLogs() {
 
}

void IOLogs::redirectCout(std::string logsFilePath, std::string errorLogsFilePath) {
    outCout.open(logsFilePath);
    outCerr.open(errorLogsFilePath);
    std::cout.rdbuf(outCout.rdbuf());
    std::cerr.rdbuf(outCerr.rdbuf());
}