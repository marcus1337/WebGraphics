#include "IOLogs.h"
#include "FolderPaths.h"
#include <iostream>
#include <fstream>

IOLogs::IOLogs() {
 
}

void IOLogs::redirectCoutToFile() {
    std::string logsPath = FolderPaths::getLogsPath() + "logs.txt";
    std::string logsErrPath = FolderPaths::getLogsPath() + "logs_error.txt";

    outCout.open(logsPath);
    outCerr.open(logsErrPath);
    std::cout.rdbuf(outCout.rdbuf());
    std::cerr.rdbuf(outCerr.rdbuf());

}