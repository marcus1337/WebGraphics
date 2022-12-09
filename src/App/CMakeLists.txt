add_library(app App.h App.cpp UpdateTimer.h UpdateTimer.cpp 
      "Panels/Panel.h" "Panels/Panel.cpp"     
      
      
    "Panels/Game/GamePanel.h" "Panels/Game/GamePanel.cpp" 
          
    "Panels/PanelHandler.h" "Panels/PanelHandler.cpp" 
    "Panels/PanelFactory.h" "Panels/PanelFactory.cpp" 
    "Panels/PanelContext.cpp" "Panels/PanelContext.h"   "Panels/Game/BoardButton.h" "Panels/Game/BoardButton.cpp")

target_link_libraries(app drawables engine io ui game)