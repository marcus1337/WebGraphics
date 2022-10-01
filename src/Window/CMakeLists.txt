add_library(window "Canvas.cpp" 
"Canvas.h"  
"CanvasCallbacks.h" "CanvasCallbacks.cpp" "CanvasSettings.h" "CanvasSettings.cpp")

target_link_libraries(window glm glfw io)
