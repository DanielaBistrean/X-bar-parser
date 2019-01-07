# Project's name
project (x-bar)

set (SOURCES
	x-bar.cpp
	struct.cc
	texcaller.c
	grammar.cc
	nodeList.cc
)



add_executable(x-bar ${SOURCES})


target_link_libraries(x-bar wordnet)
