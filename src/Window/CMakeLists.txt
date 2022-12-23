add_library(window "Canvas.cpp" "Canvas.h"  
"CanvasCallbacks.h" "CanvasCallbacks.cpp" 
"CanvasSettings.h" "CanvasSettings.cpp"

"InputDevices/Keyboard.h" "InputDevices/Keyboard.cpp" "InputDevices/Mouse.h" "InputDevices/Mouse.cpp")

target_link_libraries(window glm glfw io)
