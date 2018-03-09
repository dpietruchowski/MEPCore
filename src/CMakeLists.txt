add_subdirectory(gene)

add_executable(MEPCore main.cpp)
target_link_libraries (MEPCore mepgene)