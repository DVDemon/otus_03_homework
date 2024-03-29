cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
 project(03_homework VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
 project(03_homework VERSION 0.0.3)
endif()


find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(allocator main.cpp)
add_library(library lib.cpp)
add_executable(gtests tests.cpp)

set_target_properties(allocator library gtests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(allocator PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(allocator PRIVATE library)
target_link_libraries(gtests ${GTEST_LIBRARIES} library)
target_link_libraries(gtests ${CMAKE_THREAD_LIBS_INIT} library )
    
target_compile_options(allocator PRIVATE -Wall -Wextra -pedantic -Werror )
target_compile_options(library PRIVATE -Wall -Wextra -pedantic -Werror )
target_compile_options(gtests PRIVATE -Wall -Wextra -pedantic -Werror )

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ddzuba@yandex.ru)
include(CPack)

enable_testing()
add_test(gtests gtests)