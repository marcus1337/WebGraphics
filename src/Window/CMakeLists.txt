add_library(window "Canvas.cpp" "../Graphics/Camera.cpp"
"Canvas.h" "../Graphics/Camera.h" 
AspectRatio.h AspectRatio.cpp)

target_link_libraries(window glm glfw)
