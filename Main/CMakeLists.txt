cmake_minimum_required(VERSION 2.8...3.5)

include_directories( ${MODULETEMPLATE_SOURCE_DIR}/ModuleInterface )

add_executable( ModuleTemplate Main.cpp )

# Link the executable to the libraries. The order of the libraries is important.
target_link_libraries( ModuleTemplate ModuleInterface -pthread )

