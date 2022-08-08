add_library(drawables Drawable.h "Drawable.cpp" "Text.h" "Image.h" "Rect.h" "Rect.cpp" 
  "Text.cpp" "Image.cpp"  
      
   
"ShaderTimer.h" "ShaderTimer.cpp"
)

target_link_libraries(drawables graphics)