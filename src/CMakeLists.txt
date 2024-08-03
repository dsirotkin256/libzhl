add_library(sat STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/constants.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gas_exchange.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pressure.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/zhl-16c.cpp
)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
    target_compile_definitions(sat PUBLIC SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE)
else ()
    target_compile_definitions(sat PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO)
endif ()

target_include_directories(sat
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set_target_properties(sat PROPERTIES LINKER_LANGUAGE CXX)

include(FetchContent)
include(ExternalProject)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog
        GIT_TAG        v1.14.1
)
FetchContent_MakeAvailable(spdlog)

# FetchContent_Declare(
#         fmt
#         GIT_REPOSITORY https://github.com/fmtlib/fmt
#         GIT_TAG        10.1.1
# )
# FetchContent_MakeAvailable(fmt)

# FetchContent_Declare(
#         yaml-cpp
#         GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
#         GIT_TAG        0.8.0
# )
# FetchContent_MakeAvailable(yaml-cpp)


set(MI_USE_CXX ON CACHE INTERNAL "Enable CXX")
set(MI_BUILD_SHARED OFF CACHE INTERNAL "Disable shared mimalloc")
set(MI_BUILD_TESTS OFF CACHE INTERNAL "Disable mimalloc tests")
set(MI_USE_LIBATOMIC OFF CACHE INTERNAL "Disable libatomic")

FetchContent_Declare(
        mimalloc
        GIT_REPOSITORY https://github.com/microsoft/mimalloc
        GIT_TAG        v1.7.9
)
FetchContent_MakeAvailable(mimalloc)

IF(NOT DEFINED ENV{CROSS_CXX})
        set(ENV{CROSS_CXX} $ENV{CXX})
ENDIF()
IF(NOT DEFINED ENV{CROSS_CC})
        set(ENV{CROSS_CC} $ENV{CC})
ENDIF()

target_link_libraries(sat
        PUBLIC
        mimalloc-static
        spdlog
        )

add_executable(partial partial_pressure.cpp)
add_executable(desat buhlmann.cpp)

target_link_libraries(partial sat)
target_link_libraries(desat sat)

set_target_properties(partial
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)

set_target_properties(desat
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)