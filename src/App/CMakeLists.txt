add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp 
    "Panels/Main/MainMenuPanel.h" "Panels/Main/MainMenuPanel.cpp" "Panels/Panel.h" "Panels/Panel.cpp"     
    "ShaderUpdater.h" "ShaderUpdater.cpp" 
    "Panels/Main/SettingsPanel.h" "Panels/Main/SettingsPanel.cpp" 
    "Panels/Game/GamePanel.h" "Panels/Game/GamePanel.cpp" 
    "Panels/Main/InstructionsPanel.h" "Panels/Main/InstructionsPanel.cpp"     
    "Panels/PanelHandler.h" "Panels/PanelHandler.cpp" 
    "Panels/PanelFactory.h" "Panels/PanelFactory.cpp" 
    "Panels/PanelContext.cpp" "Panels/PanelContext.h" "Panels/Game/ChessScript.h" "Panels/Game/ChessScript.cpp")

target_link_libraries(app drawables engine io ui game)