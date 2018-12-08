include_directories("${MEPCORE_INCLUDE_DIR}/core")

list(APPEND MEPCORE_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/operation.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/terminal.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/function.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/object.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/gene.cpp"
)