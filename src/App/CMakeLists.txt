add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp "MainMenu.h" "MainMenu.cpp" "Panel.h" "Panel.cpp" "SettingsMenu.h" "SettingsMenu.cpp")

target_link_libraries(app drawables engine)