add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp "Panels/MainMenu.h" "Panels/MainMenu.cpp" "Panels/Panel.h" "Panels/Panel.cpp" "Panels/SettingsMenu.h" "Panels/SettingsMenu.cpp" "Panels/AchievementsMenu.h" "Panels/AchievementsMenu.cpp" "Panels/LobbyMenu.h" "Panels/LobbyMenu.cpp" "Panels/GamePanel.h" "Panels/GamePanel.cpp")

target_link_libraries(app drawables engine)