set(LIBRARY_SOURCES
	binary_tree.cpp
)
set(LIBRARY_HEADERS
    binary_tree.h
)
set(LIBRARY_INCLUDES
    "./"
    "${CMAKE_BINARY_DIR}/configured_files/include")

add_library(${LIBRARY_NAME} STATIC
    ${LIBRARY_SOURCES}
    ${LIBRARY_HEADERS}
)
target_include_directories(${LIBRARY_NAME} PUBLIC
    ${LIBRARY_INCLUDES}) #where to fined .h files
