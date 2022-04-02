add_library(window "Screen.cpp" Camera.cpp
"Screen.h" Camera.h 
AspectRatio.h AspectRatio.cpp)

target_link_libraries(window glm)
