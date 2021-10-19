add_library(window MyWindow.cpp Camera.cpp Image.cpp Image.h MyWindow.h Camera.h Mouse.h Mouse.cpp Keyboard.h Keyboard.cpp)

target_link_libraries(window glm)
