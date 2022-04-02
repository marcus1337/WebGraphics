add_library(window "Canvas.cpp" Camera.cpp
"Canvas.h" Camera.h 
AspectRatio.h AspectRatio.cpp)

target_link_libraries(window glm glfw)
