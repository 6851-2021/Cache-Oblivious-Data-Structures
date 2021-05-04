all: test_CO_SST test_CA_SST test_SST perf

ifeq ($(DEBUG),1)
  	# We want debug mode.
	CXXFLAGS += -g -DDEBUG -Og -ggdb -Wno-attributes
else
  	# We want release mode.
  	CXXFLAGS += -O3 -flto -DNDEBUG
endif


test_CO_SST: static-search-trees.h static-search-trees.cpp co_static_search_trees_tests.cpp
	g++ ${CXXFLAGS} static-search-trees.cpp co_static_search_trees_tests.cpp -o test_co_sst

test_CA_SST: static-search-trees.h static-search-trees.cpp static_search_trees_tests.cpp
	g++ ${CXXFLAGS} static-search-trees.cpp ca_static_search_trees_tests.cpp -o test_ca_sst

test_SST: static-search-trees.h static-search-trees.cpp static_search_trees_tests.cpp
	g++ ${CXXFLAGS} static-search-trees.cpp static_search_trees_tests.cpp -o test_sst

perf: static-search-trees.h static-search-trees.cpp perf_sst.cpp perf_co_sst.cpp perf_params.h perf_built_co_sst.cpp
	g++ ${CXXFLAGS} static-search-trees.cpp perf_sst.cpp -o perf_sst
	g++ ${CXXFLAGS} static-search-trees.cpp perf_co_sst.cpp -o perf_co_sst
	g++ ${CXXFLAGS} static-search-trees.cpp perf_ca_sst.cpp -o perf_ca_sst
	g++ ${CXXFLAGS} static-search-trees.cpp perf_built_co_sst.cpp -o perf_built_co_sst 

perf_co_matrix_walker: matrix_walker.h matrix_walker.cpp perf_matrix_walker.cpp
	g++ ${CXXFLAGS} -DPERF matrix_walker.cpp perf_matrix_walker.cpp -o perf_co_matrix_walker

perf_naive_matrix_walker: matrix_walker.h matrix_walker.cpp perf_matrix_walker.cpp
	g++ ${CXXFLAGS} matrix_walker.cpp perf_matrix_walker.cpp -o perf_naive_matrix_walker

test_matrix_walker: matrix_walker.h matrix_walker.cpp matrix_walker_tester.cpp
	g++ ${CXXFLAGS} matrix_walker.cpp matrix_walker_tester.cpp -o test_matrix_walker

main: static-search-trees.h static-search-trees.cpp  matrix_walker.h matrix_walker.cpp main.cpp
	g++ ${CXXFLAGS} static-search-trees.cpp matrix_walker.cpp main.cpp -o main

test_built_co_sst: static-search-trees.h static-search-trees.cpp test_built_co_sst.cpp
	g++ ${CXXFLAGS} static-search-trees.cpp test_built_co_sst.cpp -o ./test_built_co_sst

clean:
	rm -f test_co_sst test_sst perf_sst perf_co_sst test_ca_sst perf_ca_sst test_matrix_walker
