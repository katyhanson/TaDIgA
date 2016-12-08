#
# Main executable for Tadiga
#

# Glob header files in subdirectories
file (GLOB srcHEADERS 
  "*.h"
)

set(Tadiga_HEADERS
    ${srcHEADERS}
)

# Glob source files in subdirectories
file (GLOB srcSOURCES 
  "*.cc"
)

set(Tadiga_SOURCES
    ${srcSOURCES}
)


set(Tadiga_LINK_LIBRARIES
    ${Trilinos_LIBRARIES}
    ${REQUIRED_LIBS}
)

add_executable(Tadiga ${Tadiga_SOURCES})
target_link_libraries(Tadiga ${Tadiga_LINK_LIBRARIES})

#
# Install target for Tadiga main executable
#
install(TARGETS Tadiga 
    RUNTIME DESTINATION bin
)
