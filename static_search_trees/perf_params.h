const int Q = (1 << 27);
const int n = (1 << 26);
const int num_runs = 1;
// When we've done rand_reset_const queries/iterations, re-seed the rand()
// function.
const int rand_reset_const = 10000;
bool sst_recursive_falg = false;