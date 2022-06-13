add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp "MainMenu.h" "MainMenu.cpp")

target_link_libraries(app drawables engine)