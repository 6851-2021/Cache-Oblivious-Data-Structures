# Cache-Oblivious-Btrees

Contains cache oblivious and conventional implementations of static search trees, dynamic search trees and matrix walker.

To compile the code simply run:

```make all```

## Performace benchmarking tools

For this to work you need to have perf installed. 
If you are you using ubuntu you should be able to get it by running the following command

```sudo apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r` ```

To count the number of cache misses run scripts prefixed with perf. Each script takes two inputs N the size of the data structure and Q the number of queries.

For example to run n = 10000, q = 100000 on normal static search trees:

```python3 perf.py ./perf_sst 10000 100000```

For cache-oblivious static search trees:

```python3 perf.py ./perf_co_sst 10000 100000```


