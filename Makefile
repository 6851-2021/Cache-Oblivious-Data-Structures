all: test_sst perf_sst

ifeq ($(DEBUG),1)
  	# We want debug mode.
	CXXFLAGS += -g -DDEBUG -Og -ggdb -Wno-attributes
else
  	# We want release mode.
  	CXXFLAGS += -O3 -flto -DNDEBUG
endif




SST_DIR = static_search_trees

test_co_sst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_co_sst.cpp
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_co_sst.cpp -o test_co_sst

test_ca_sst:  ${SST_DIR}/static_search_trees.h  ${SST_DIR}/static_search_trees.cpp   ${SST_DIR}/test_ca_sst.cpp
	g++ ${CXXFLAGS}  ${SST_DIR}/static_search_trees.cpp  ${SST_DIR}/test_ca_sst.cpp -o test_ca_sst

test_simple_sst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_simple_sst.cpp
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_simple_sst.cpp -o test_simple_sst

test_built_co_sst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_built_co_sst.cpp
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_built_co_sst.cpp -o ./test_built_co_sst

test_map_rep_sst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_map_rep_sst.cpp
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/test_map_rep_sst.cpp -o ./test_map_rep_sst

test_sst: test_co_sst test_simple_sst test_ca_sst test_built_co_sst test_map_rep_sst

perf_sst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/perf_params.h ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/perf_simple_sst.cpp ${SST_DIR}/perf_co_sst.cpp ${SST_DIR}/perf_ca_sst.cpp ${SST_DIR}/perf_built_co_sst.cpp ${SST_DIR}/perf_map_rep_sst.cpp 
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/perf_simple_sst.cpp -o perf_simple_sst
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/perf_co_sst.cpp -o perf_co_sst
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/perf_ca_sst.cpp -o perf_ca_sst
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/perf_built_co_sst.cpp -o perf_built_co_sst
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${SST_DIR}/perf_map_rep_sst.cpp -o perf_map_rep_sst

clean_sst:
	rm -f test_co_sst test_ca_sst test_built_co_sst test_simple_sst test_built_co_sst test_map_rep_sst
	rm -f perf_sst perf_simple_sst perf_co_sst perf_ca_sst perf_built_co_sst perf_map_rep_sst


DST_DIR = dynamic_search_trees
OFM_DIR = ordered-file-maintenance-in-c

test_co_dst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/static_search_trees.cpp ${DST_DIR}/co_dynamic_search_tree.h ${DST_DIR}/co_dynamic_search_tree.cpp ${DST_DIR}/test_co_dst.cpp ${OFM_DIR}/OrderedFileMaintenance.h ${OFM_DIR}/OrderedFileMaintenance.cpp
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${DST_DIR}/co_dynamic_search_tree.cpp ${DST_DIR}/test_co_dst.cpp ${OFM_DIR}/OrderedFileMaintenance.cpp -o ./test_co_dst 

perf_time_dst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/static_search_trees.cpp ${DST_DIR}/co_dynamic_search_tree.h ${DST_DIR}/co_dynamic_search_tree.cpp ${DST_DIR}/perf_time_dst.cpp ${OFM_DIR}/OrderedFileMaintenance.h ${OFM_DIR}/OrderedFileMaintenance.cpp
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${DST_DIR}/co_dynamic_search_tree.cpp ${DST_DIR}/perf_time_dst.cpp ${OFM_DIR}/OrderedFileMaintenance.cpp -o ./perf_time_dst 

perf_co_dst: ${SST_DIR}/static_search_trees.h ${SST_DIR}/static_search_trees.cpp ${DST_DIR}/co_dynamic_search_tree.h ${DST_DIR}/co_dynamic_search_tree.cpp ${DST_DIR}/perf_co_dst.cpp ${OFM_DIR}/OrderedFileMaintenance.h ${OFM_DIR}/OrderedFileMaintenance.cpp
	g++ ${CXXFLAGS} ${SST_DIR}/static_search_trees.cpp ${DST_DIR}/co_dynamic_search_tree.cpp ${DST_DIR}/perf_co_dst.cpp ${OFM_DIR}/OrderedFileMaintenance.cpp -o ./perf_co_dst 

perf_std_set: ${DST_DIR}/perf_std_set.cpp
	g++ ${CXXFLAGS} ${DST_DIR}/perf_std_set.cpp -o ./perf_std_set

perf_dst: perf_co_dst perf_std_set perf_time_dst

clean_dst:
	rm -f test_co_dst
	rm -f perf_co_dst perf_std_set perf_time_dst


MW_DIR = matrix_walker


perf_matrix_walker: perf_co_matrix_walker perf_naive_matrix_walker

test_matrix_walker: ${MW_DIR}/matrix_walker.h ${MW_DIR}/matrix_walker.cpp ${MW_DIR}/test_matrix_walker.cpp
	g++ ${CXXFLAGS} ${MW_DIR}/matrix_walker.cpp ${MW_DIR}/test_matrix_walker.cpp -o test_matrix_walker

perf_co_matrix_walker: ${MW_DIR}/matrix_walker.h ${MW_DIR}/matrix_walker.cpp ${MW_DIR}/perf_matrix_walker.cpp
	g++ ${CXXFLAGS} -DCO ${MW_DIR}/matrix_walker.cpp ${MW_DIR}/perf_matrix_walker.cpp -o perf_co_matrix_walker

perf_naive_matrix_walker: ${MW_DIR}/matrix_walker.h ${MW_DIR}/matrix_walker.cpp ${MW_DIR}/perf_matrix_walker.cpp
	g++ ${CXXFLAGS} ${MW_DIR}/matrix_walker.cpp ${MW_DIR}/perf_matrix_walker.cpp -o perf_naive_matrix_walker


clean_matrix_walker:
	rm -f test_matrix_walker 
	rm -f perf_co_matrix_walker perf_naive_matrix_walker







clean: clean_sst clean_matrix_walker clean_dst
