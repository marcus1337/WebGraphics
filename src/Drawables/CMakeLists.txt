add_library(drawables Drawable.h "Drawable.cpp" "View.h" "Text.h" "Image.h" "Rectangle.h" "Button.h" "Button.cpp")

target_link_libraries(drawables graphics)