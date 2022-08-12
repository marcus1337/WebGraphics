add_library(ui Button.h Button.cpp UIScript.h UIScript.cpp)

target_link_libraries(ui graphics drawables engine lua dl )