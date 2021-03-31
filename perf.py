import pandas as pd
import argparse
import re
import os
from subprocess import PIPE, run
from sys import argv

class PerfObj:
    def __init__(self):
        self.df = pd.DataFrame()
        self.stat_of_interest = ['cache-references', 'cache-misses']

    def parse_perf_stat(self, perf_stat):
        data = perf_stat.split()
        parsed_data = {}
        for i in range(len(data)):
            if data[i] in self.stat_of_interest:
                parsed_data[data[i]] = self.__parse_int(data[i-1])
        self.df = self.df.append(parsed_data, ignore_index=True)


    def __parse_int(self, integer):
        return int(integer.replace(",", ""))

    def __str__(self):
        return self.get_records()[self.stat_of_interest].to_string(index = False)

    def record_cache(self, program_name):
        command = ["perf", "stat", "-e", ",".join(self.stat_of_interest), program_name]
        result = run(command, stdout=PIPE, universal_newlines=True, stdin=None, stderr=PIPE)
        self.parse_perf_stat(result.stderr)

    # returns a data frame
    def get_records(self):
        self.df["cache-references"] = self.df["cache-references"].astype(int)
        self.df["cache-misses"] = self.df["cache-misses"].astype(int)

        return self.df

if __name__ == '__main__':
    #can pass folder name in first argument
    if len(argv) > 1:
        perf = PerfObj()
        perf.record_cache(argv[1])
        perf.record_cache(argv[1])
        # get_cache_misses(perf_stat)
        print(perf)
        
    else:
        print("Usage python perf.py <program>")
    