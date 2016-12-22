#
# Unit tests for TaDIgA
#

add_executable(tadiga_parser_test 
    ./tadiga_standard_test_main.cc
    ./tadiga_parser_test.cc)
target_link_libraries(tadiga_parser_test ${Tadiga_LINK_LIBRARIES})
add_test(tadiga_parser ./tadiga_parser_test)



