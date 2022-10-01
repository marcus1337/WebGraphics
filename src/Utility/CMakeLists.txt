
add_library(utility      "ShaderCompiler.h" "ShaderCompiler.cpp" "ShaderPrograms.h" "ShaderPrograms.cpp")

target_link_libraries(utility glm io)

