add_library(window Image.cpp MyWindow.cpp Camera.cpp Image.h MyWindow.h Camera.h)

target_link_libraries(window glm)
