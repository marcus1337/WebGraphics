
add_library(model Mesh.cpp Model.cpp MatrixData.h Mesh.h Model.h ModelManager.cpp ModelManager.h)


target_link_libraries(model glm io )
