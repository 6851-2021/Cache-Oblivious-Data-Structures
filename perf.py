import pandas as pd
import argparse
import re
import os
from subprocess import PIPE, run
from sys import argv

class PerfObj:
    def __init__(self):
        self.df = pd.DataFrame()
        self.stat_of_interest = ['cache-references', 'cache-misses', "L1-dcache-load-misses", "L1-dcache-loads", "L1-dcache-stores",\
             "LLC-load-misses", "LLC-loads", "LLC-store-misses", "LLC-stores", "cpu-clock"]

    def parse_perf_stat(self, perf_stat, name, n, q):
        data = perf_stat.split()
        parsed_data = {"name": name, "n": n, "q": q, "input": f"{n}_{q}"}
        self.extract_names = self.stat_of_interest
        for i in range(len(data)):
            if data[i] in self.stat_of_interest:
                if data[i] == "cpu-clock":
                    parsed_data[data[i]] = data[i-2].replace(",", "")
                else:
                    parsed_data[data[i]] = self.__parse_int(data[i-1])

        self.df = self.df.append(parsed_data, ignore_index=True)
        return parsed_data


    def __parse_int(self, integer):
        return int(integer.replace(",", ""))

    def __str__(self):
        col =["name"] + self.stat_of_interest
        return self.get_records()[col].to_string(index = False)

    def record_cache(self, program_name, n=None, q=None):
        command = ["perf", "stat", "-e", ",".join(self.stat_of_interest), program_name]
        
        #format input
        inputstr = ""
        if n and q:
            inputstr = f"{n} {q}\n"
        result = run(command, stdout=PIPE, universal_newlines=True, input=inputstr, stderr=PIPE)
        parsed_data = self.parse_perf_stat(result.stderr, program_name, n, q)
        return parsed_data

    # returns a data frame
    def get_records(self):
        self.df["cache-references"] = self.df["cache-references"].astype(int)
        self.df["cache-misses"] = self.df["cache-misses"].astype(int)
        self.df["L1-dcache-load-misses"] = self.df["L1-dcache-load-misses"].astype(int)
        self.df["LLC-load-misses"] = self.df["LLC-load-misses"].astype(int)
        self.df["cpu-clock"] = self.df["cpu-clock"].astype(float)

        return self.df

if __name__ == '__main__':
    # perf = PerfObj()
    # perf.record_cache("./perf_co_sst")
    # perf.record_cache("./perf_sst")
    # perf.record_cache("./perf_ca_sst")
    # perf.record_cache("./perf_built_co_sst")
    # print(perf)
    if len(argv) > 3:
        perf = PerfObj()
        program_name = argv[1]
        n = int(argv[2])
        q = int(argv[3])
        perf.record_cache(program_name, n, q)
        print(perf) 
    else:
        print("Usage python perf.py <program> <n> <q>")
    