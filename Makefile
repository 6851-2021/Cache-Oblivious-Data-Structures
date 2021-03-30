
test_CO_SST: static-search-trees.h static-search-trees.cpp static_search_trees_tests.cpp
	g++ -o test_co_sst static-search-trees.cpp static_search_trees_tests.cpp