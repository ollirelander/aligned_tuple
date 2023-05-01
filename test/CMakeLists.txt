include(CheckCXXCompilerFlag)

if((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    set(OPTIONS -Wall -Wextra -pedantic-errors -Werror)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(OPTIONS /W4 /WX)
    if(HAS_PERMISSIVE_FLAG)
        set(OPTIONS ${OPTIONS} /permissive-)
    endif()
endif()

add_executable(test "test.cpp")

set_target_properties(${test} PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(${test} PRIVATE cxx_std_14)
target_compile_options(${test} PRIVATE ${OPTIONS})
target_link_libraries(${test} PRIVATE ${CMAKE_PROJECT_NAME})
