add_library(window "Window.cpp" Camera.cpp
"Window.h" Camera.h 
AspectRatio.h AspectRatio.cpp)

target_link_libraries(window glm)
