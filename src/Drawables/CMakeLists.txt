add_library(drawables Drawable.h "Drawable.cpp" "Text.h" "Image.h" "Rect.h" "Rect.cpp" 
  "Text.cpp" "Image.cpp"  
 "View.h" "View.cpp"  )

target_link_libraries(drawables graphics)