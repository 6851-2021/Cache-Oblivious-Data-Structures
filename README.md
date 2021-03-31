# Cache-Oblivious-Btrees

Contains implementation of static search trees and cache-oblivious static search trees.

To compile the code simply run:

```make all```


For this to work you need to have perf installed. 
If you are you using ubuntu you should be able to get it by running the following command

```sudo apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r` ```

To count the number of cache misses run:

For normal static search trees:

```python3 perf.py ./perf_sst  ```

For cache-oblivious static search trees:

```python3 perf.py ./perf_co_sst  ```

You can also configure the number of iteration and elements by
modifying the numbers in perf_params.h and recompiling.
