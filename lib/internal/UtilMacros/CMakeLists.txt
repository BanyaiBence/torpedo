# Declare your library target
add_library(UtilMacros STATIC
        UtilMacros.h
)
set_target_properties(UtilMacros PROPERTIES LINKER_LANGUAGE C)

# If you want to build as static/shared optionally, add:
# option(BUILD_SHARED_LIBS "Build shared libraries" ON)


# Include directories (optional, but good for future extensions)
# If you have headers in this directory:
target_include_directories(UtilMacros
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # So others can include "mylib.h"
)

# (Optional) If your library has a version
set_target_properties(UtilMacros PROPERTIES
        VERSION 1.0.0
        SOVERSION 1
)

# If you want to install the library (optional)
# install(TARGETS mylib DESTINATION lib)
# install(FILES mylib.h DESTINATION include)
