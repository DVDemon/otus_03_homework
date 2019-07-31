cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
 project(03_homework VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
 project(03_homework VERSION 0.0.3)
endif()


find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(main main.cpp)
add_library(library lib.cpp)
add_executable(gtests tests.cpp)

set_target_properties(main library gtests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(main PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(main PRIVATE library)
target_link_libraries(gtests ${GTEST_LIBRARIES} library)
target_link_libraries(gtests ${CMAKE_THREAD_LIBS_INIT} library )
    
target_compile_options(main PRIVATE -Wall -Wextra -pedantic -Werror )
target_compile_options(library PRIVATE -Wall -Wextra -pedantic -Werror )
target_compile_options(gtests PRIVATE -Wall -Wextra -pedantic -Werror )

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ddzuba@yandex.ru)
include(CPack)

enable_testing()
add_test(gtests gtests)