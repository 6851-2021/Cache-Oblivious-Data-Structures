all: test_CO_SST test_CA_SST test_SST perf perf_dynamic_search_tree

ifeq ($(DEBUG),1)
  	# We want debug mode.
	CXXFLAGS += -g -DDEBUG -Og -ggdb -Wno-attributes
else
  	# We want release mode.
  	CXXFLAGS += -O3 -flto -DNDEBUG
endif


test_co_sst: static_search_trees.h static_search_trees.cpp co_static_search_trees_tests.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp co_static_search_trees_tests.cpp -o test_co_sst

test_CA_SST: static_search_trees.h static_search_trees.cpp static_search_trees_tests.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp ca_static_search_trees_tests.cpp -o test_ca_sst

test_SST: static_search_trees.h static_search_trees.cpp static_search_trees_tests.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp static_search_trees_tests.cpp -o test_sst

perf: static_search_trees.h static_search_trees.cpp perf_sst.cpp perf_co_sst.cpp perf_params.h perf_built_co_sst.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp perf_sst.cpp -o perf_sst
	g++ ${CXXFLAGS} static_search_trees.cpp perf_co_sst.cpp -o perf_co_sst
	g++ ${CXXFLAGS} static_search_trees.cpp perf_ca_sst.cpp -o perf_ca_sst
	g++ ${CXXFLAGS} static_search_trees.cpp perf_built_co_sst.cpp -o perf_built_co_sst 



main: static_search_trees.h static_search_trees.cpp  matrix_walker.h matrix_walker.cpp main.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp matrix_walker.cpp main.cpp -o main

test_built_co_sst: static_search_trees.h static_search_trees.cpp test_built_co_sst.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp test_built_co_sst.cpp -o ./test_built_co_sst

test_dynamic_search_tree: static_search_trees.h static_search_trees.cpp dynamic_search_tree.h dynamic_search_tree.cpp test_dynamic_search_tree.cpp ordered-file-maintenance-in-c/OrderedFileMaintenance.h ordered-file-maintenance-in-c/OrderedFileMaintenance.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp dynamic_search_tree.cpp test_dynamic_search_tree.cpp ordered-file-maintenance-in-c/OrderedFileMaintenance.cpp -o ./test_dynamic_search_tree 

perf_time_dynamic_search_tree: static_search_trees.h static_search_trees.cpp dynamic_search_tree.h dynamic_search_tree.cpp perf_time_dynamic_st.cpp ordered-file-maintenance-in-c/OrderedFileMaintenance.h ordered-file-maintenance-in-c/OrderedFileMaintenance.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp dynamic_search_tree.cpp perf_time_dynamic_st.cpp ordered-file-maintenance-in-c/OrderedFileMaintenance.cpp -o ./perf_time_dynamic_st

perf_dynamic_search_tree: static_search_trees.h static_search_trees.cpp dynamic_search_tree.h dynamic_search_tree.cpp perf_dynamic_st.cpp ordered-file-maintenance-in-c/OrderedFileMaintenance.h ordered-file-maintenance-in-c/OrderedFileMaintenance.cpp
	g++ ${CXXFLAGS} static_search_trees.cpp dynamic_search_tree.cpp perf_dynamic_st.cpp ordered-file-maintenance-in-c/OrderedFileMaintenance.cpp -o ./perf_dynamic_st	

perf_std_set: perf_std_set.cpp
	g++ ${CXXFLAGS} perf_std_set.cpp -o ./perf_std_set






MWDIR = matrix_walker

perf_co_matrix_walker: ${MWDIR}/matrix_walker.h ${MWDIR}/matrix_walker.cpp ${MWDIR}/perf_matrix_walker.cpp
	g++ ${CXXFLAGS} -DCO ${MWDIR}/matrix_walker.cpp ${MWDIR}/perf_matrix_walker.cpp -o perf_co_matrix_walker

perf_naive_matrix_walker: ${MWDIR}/matrix_walker.h ${MWDIR}/matrix_walker.cpp ${MWDIR}/perf_matrix_walker.cpp
	g++ ${CXXFLAGS} ${MWDIR}/matrix_walker.cpp ${MWDIR}/perf_matrix_walker.cpp -o perf_naive_matrix_walker

test_matrix_walker: ${MWDIR}/matrix_walker.h ${MWDIR}/matrix_walker.cpp ${MWDIR}/test_matrix_walker.cpp
	g++ ${CXXFLAGS} ${MWDIR}/matrix_walker.cpp ${MWDIR}/test_matrix_walker.cpp -o test_matrix_walker






clean_matrix_walker:
	rm -f test_matrix_walker perf_matrix_walker perf_naive_matrix_walker


clean:
	rm -f test_co_sst test_sst perf_sst perf_co_sst test_ca_sst perf_ca_sst test_matrix_walker test_dynamic_search_tree
