set(dir "${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB_RECURSE HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

set(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# target_sources(mumei
#     PUBLIC
#     ${HEADER_FILES}
# )
target_include_directories(mumei
    PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include> 
)

install(DIRECTORY ${INCLUDE_DIRS} DESTINATION include)
