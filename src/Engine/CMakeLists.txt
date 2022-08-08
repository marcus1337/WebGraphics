add_library(engine Engine.h Engine.cpp "Graphics.h" "Graphics.cpp"  )

target_link_libraries(engine io window utility graphics)