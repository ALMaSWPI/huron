set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

list(APPEND SOURCE_FILES
        "${dir}/src/rotation.cc")
FILE(GLOB_RECURSE HEADER_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

list(APPEND TEST_SOURCE_FILES
        "${dir}/test/test_rotation.cc")

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

target_sources(mumei
        PRIVATE
        ${SOURCE_FILES}
        # PUBLIC
        # ${HEADER_FILES}
)
target_include_directories(mumei
        PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:include>
)

target_sources(mumei_tests
  PRIVATE
  ${TEST_SOURCE_FILES}
)
target_include_directories(mumei_tests
        PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIRS}>
        $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${INCLUDE_DIRS} DESTINATION include)
