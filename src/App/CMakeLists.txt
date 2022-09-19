add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp 
    "Panels/Main/MainMenuPanel.h" "Panels/Main/MainMenuPanel.cpp" "Panels/Panel.h" "Panels/Panel.cpp"     
    "DevController.h" "DevController.cpp" "Panels/Main/SettingsPanel.h" "Panels/Main/SettingsPanel.cpp" "Panels/Main/LobbyPanel.h" "Panels/Main/LobbyPanel.cpp" "Panels/Main/GamePanel.h" "Panels/Main/GamePanel.cpp" "Panels/Main/LobbySearchPanel.h" "Panels/Main/LobbySearchPanel.cpp" "Panels/Main/GameView.h" "Panels/Main/GameView.cpp" "Panels/Main/InstructionsPanel.h" "Panels/Main/InstructionsPanel.cpp")

target_link_libraries(app drawables engine io ui)