all: test_CO_SST test_SST

test_CO_SST: static-search-trees.h static-search-trees.cpp co_static_search_trees_tests.cpp
	g++ -O3 -flto -o test_co_sst static-search-trees.cpp co_static_search_trees_tests.cpp

test_SST: static-search-trees.h static-search-trees.cpp static_search_trees_tests.cpp
	g++ -O3 -flto -o test_sst static-search-trees.cpp static_search_trees_tests.cpp