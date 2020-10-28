file(GLOB test_sources RELATIVE "${CMAKE_CURRENT_LIST_DIR}" "*.cpp")

foreach(test_sources ${test_sources})
    string( REPLACE ".cpp" "" test_name ${test_sources})
    add_executable(${test_name} ${test_sources})
    target_link_libraries(${test_name} TFHE)
endforeach(test_sources ${test_sources})