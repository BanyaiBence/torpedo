# Declare your library target
add_library(SDL3Wrapper
        SDL3Wrapper.c
        SDL3Wrapper.h
)

# If you want to build as static/shared optionally, add:
# option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Link SDL3 (static)
target_link_libraries(SDL3Wrapper PRIVATE SDL3::SDL3-static)

# Include directories (optional, but good for future extensions)
# If you have headers in this directory:
target_include_directories(SDL3Wrapper
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # So others can include "mylib.h"
)

# (Optional) If your library has a version
set_target_properties(SDL3Wrapper PROPERTIES
        VERSION 1.0.0
        SOVERSION 1
)

# If you want to install the library (optional)
# install(TARGETS mylib DESTINATION lib)
# install(FILES mylib.h DESTINATION include)
