set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tokenizer tokenizer.cpp)
target_include_directories(tokenizer PUBLIC ..)

add_executable(diverter diverter.cpp)
target_include_directories(diverter PUBLIC ..)

