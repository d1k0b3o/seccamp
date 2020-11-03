file(GLOB myTFHE_souces "*.cpp")

if(USE_80BIT_SECURITY)
    add_definitions(-DENABLE_80BIT_SECURITY)
endif()

add_library(TFHE
    ${myTFHE_souces}
)

target_include_directories(TFHE
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/RANDEN
    ${PROJECT_SOURCE_DIR}/SPQLIOS
)

target_link_libraries(TFHE INTERFACE SPQLIOS RANDEN)