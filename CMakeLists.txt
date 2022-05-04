cmake_minimum_required(VERSION 3.20)
project(algo)

set(CMAKE_CXX_STANDARD 17)

add_executable(algo main.cpp solutions.cpp solutions.h data_structures/Trie.cpp data_structures/Trie.h data_structures/IndexPQ.cpp data_structures/IndexPQ.h mainWithTime.cpp mainWithTime.h data_structures/SegmentTree.h)
