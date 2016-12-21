#
# Main executable for TaDIgA
#

set(Tadiga_HEADERS
    tadiga.h
    tadiga_IGES_geometry.h
    tadiga_factory.h
    tadiga_geometry.h
    tadiga_geometry_factory.h
)

set(Tadiga_SOURCES
    tadiga.cc
    tadiga_IGES_geometry.cc
    tadiga_factory.cc
    tadiga_geometry.cc
    tadiga_geometry_factory.cc
)

add_library(tadigaLib ${Tadiga_SOURCES})
set(Tadiga_LIBRARY tadigaLib)

set(Tadiga_LINK_LIBRARIES
    ${Tadiga_LIBRARY}
    ${Trilinos_LIBRARIES}
    ${REQUIRED_LIBS}
)

add_executable(tadiga tadiga_main.cc)
target_link_libraries(tadiga ${Tadiga_LINK_LIBRARIES})

#
# Install target for Tadiga main executable
#
install(TARGETS tadiga 
    RUNTIME DESTINATION bin
)

add_subdirectory(test)
