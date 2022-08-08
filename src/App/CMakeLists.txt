add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp 
    "Panels/Main/MainMenu.h" "Panels/Main/MainMenu.cpp" "Panels/Panel.h" "Panels/Panel.cpp"     
    "DevController.h" "DevController.cpp")

target_link_libraries(app drawables engine io)