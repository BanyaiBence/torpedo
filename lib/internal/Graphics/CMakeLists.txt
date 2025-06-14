# Declare your library target
add_library(Graphics
        Graphics.c
        Graphics.h
)

# If you want to build as static/shared optionally, add:
# option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Link SDL3 (static)
target_link_libraries(Graphics PRIVATE SDL3::SDL3)

# Include directories (optional, but good for future extensions)
# If you have headers in this directory:
target_include_directories(Graphics
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # So others can include "mylib.h"
)

# (Optional) If your library has a version
set_target_properties(Graphics PROPERTIES
        VERSION 1.0.0
        SOVERSION 1
)

# If you want to install the library (optional)
# install(TARGETS mylib DESTINATION lib)
# install(FILES mylib.h DESTINATION include)
