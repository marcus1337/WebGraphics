
add_library(utility GLData.cpp  GLData.h   "ShaderCompiler.h" "ShaderCompiler.cpp")

target_link_libraries(utility glm io)

