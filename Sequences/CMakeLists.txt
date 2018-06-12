project(sequences VERSION 0.1.0 LANGUAGES CXX)

add_library(sequences SHARED MianChowla.cpp)
install(TARGETS sequences DESTINATION lib)
install(FILES MianChowla.h DESTINATION include)
