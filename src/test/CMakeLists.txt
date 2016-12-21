#
# Unit tests for TaDIgA
#

add_executable(tadiga_factory_test 
    ./tadiga_standard_test_main.cc
    ./tadiga_factory_test.cc)
target_link_libraries(tadiga_factory_test ${Tadiga_LINK_LIBRARIES})
add_test(tadiga_factory ./tadiga_factory_test)



