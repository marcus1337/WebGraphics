
#ifndef GLOBAL_H
#define GLOBAL_H
#include "Engine/Engine.h"
#include "Drawables/Image.h"
#include "Drawables/View.h"
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <memory>
#include <functional>

class Global {
    static std::vector<std::string> getResourceFolderPaths();

public:

    static Engine& getEngineInstance();
    static void reload();
};

#endif // !GLOBAL_H
