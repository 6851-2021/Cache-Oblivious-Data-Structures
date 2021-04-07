all: test_CO_SST test_CA_SST test_SST perf

test_CO_SST: static-search-trees.h static-search-trees.cpp co_static_search_trees_tests.cpp
	g++ -O3 -flto -o test_co_sst static-search-trees.cpp co_static_search_trees_tests.cpp

test_CA_SST: static-search-trees.h static-search-trees.cpp static_search_trees_tests.cpp
	g++ -O3 -flto -o test_ca_sst static-search-trees.cpp ca_static_search_trees_tests.cpp

test_SST: static-search-trees.h static-search-trees.cpp static_search_trees_tests.cpp
	g++ -O3 -flto -o test_sst static-search-trees.cpp static_search_trees_tests.cpp

perf: static-search-trees.h static-search-trees.cpp perf_sst.cpp perf_co_sst.cpp perf_params.h
	g++ -O3 -flto -o perf_sst static-search-trees.cpp perf_sst.cpp
	g++ -O3 -flto -o perf_co_sst static-search-trees.cpp perf_co_sst.cpp
	g++ -O3 -flto -o perf_ca_sst static-search-trees.cpp perf_ca_sst.cpp

clean:
	rm -f test_co_sst test_sst perf_sst perf_co_sst
