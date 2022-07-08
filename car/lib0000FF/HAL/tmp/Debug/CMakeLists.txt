cmake_minimum_required(VERSION 3.0)

project(shell)

aux_source_directory(. SRC)

add_executable(shell ${SRC})
