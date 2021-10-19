add_library(window MyWindow.cpp Camera.cpp Image.cpp Image.h MyWindow.h Camera.h Mouse.h Mouse.cpp)

target_link_libraries(window glm)
