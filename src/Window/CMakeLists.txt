add_library(window "Window.cpp" Camera.cpp Image.cpp Image.h 
"Window.h" Camera.h 
"Shader.h" "Shader.cpp"
AspectRatio.h AspectRatio.cpp
Framebuffer.h Framebuffer.cpp 
Text.h Text.cpp)

target_link_libraries(window glm)
