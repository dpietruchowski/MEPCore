include_directories("${MEPCORE_INCLUDE_DIR}/utils")

list(APPEND MEPCORE_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/color.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/log.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/random.cpp"
)