#ifndef PAGE_A_H
#define PAGE_A_H
#include "Engine/Engine.h"
#include "Drawables/Image.h"
#include "Drawables/View.h"

#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <memory>
#include <functional>

#include "Global.h"

class Page {

    Engine& engine;
    std::shared_ptr<Image> background;

    void setBackground();
    void renderNetwork();

public:
    Page();
    void processUserInput();
    void loop();

};

#endif // !PAGE_A_H