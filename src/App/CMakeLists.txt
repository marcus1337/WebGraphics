add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp 
    "Panels/Main/MainMenuPanel.h" "Panels/Main/MainMenuPanel.cpp" "Panels/Panel.h" "Panels/Panel.cpp"     
    "DevController.h" "DevController.cpp" "Panels/Main/SettingsPanel.h" "Panels/Main/SettingsPanel.cpp" "Panels/Lobby/LobbyPanel.h" "Panels/Lobby/LobbyPanel.cpp" "Panels/Game/GamePanel.h" "Panels/Game/GamePanel.cpp" "Panels/Lobby/LobbySearchPanel.h" "Panels/Lobby/LobbySearchPanel.cpp" "Panels/Game/GameView.h" "Panels/Game/GameView.cpp" "Panels/Main/InstructionsPanel.h" "Panels/Main/InstructionsPanel.cpp" "Panels/Game/GameController.h" "Panels/Game/GameController.cpp" "Panels/Game/GameCamera.h" "Panels/Game/GameCamera.cpp")

target_link_libraries(app drawables engine io ui)