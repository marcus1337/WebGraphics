add_library(drawables Drawable.h "Drawable.cpp" "View.h" "Text.h" "Image.h")

target_link_libraries(drawables graphics)