cmake_minimum_required(VERSION 3.6)
project(Janus)

set(CMAKE_CXX_STANDARD 11)


FIND_PACKAGE(BISON)
FIND_PACKAGE(FLEX)

BISON_TARGET(
        Parser
        parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
)

FLEX_TARGET(
        Lexer
        lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} automata/ activity/)


set(SOURCE_FILES main.cpp graph/graph.cpp graph/graph.h graph/vertex.cpp graph/vertex.h graph/edgeinfo.cpp graph/edgeinfo.h automata/logistics.cpp automata/logistics.h activity/activity.cpp activity/activity.h maxplus/maxplus.cpp maxplus/maxplus.h maxplus/statespace.cpp maxplus/statespace.h)
add_executable(Janus ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS} ${SOURCE_FILES} graph/graph.cpp graph/graph.h )







