add_library(window MyWindow.cpp Camera.cpp Image.cpp Image.h 
MyWindow.h Camera.h 
ImageUniform.h ImageUniform.cpp
PostImageUniform.h PostImageUniform.cpp
AspectRatio.h AspectRatio.cpp
Text.h Text.cpp)

target_link_libraries(window glm)
