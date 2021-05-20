from subprocess import PIPE, run
import pandas as pd
import uuid
import numpy as np
import matplotlib.pyplot as plt
from perf import PerfObj
from sys import argv
import os

def plot_barchart_against(dfs: list, y_axis="L1-dcache-load-misses", test_names=None, save_file="bars.png"):
    df1 = dfs[0][1]
    if test_names is not None:
        df1 = df1[df1["input"].isin(test_names)]
        labels = sorted(test_names)
    else:
        labels = []
        for name, df in dfs:
            labels.extend(df["input"].unique())
        labels = sorted(labels)

    x = np.arange(len(labels))  # the label locations
    width = 1/(len(dfs))*4/5  # the width of the bars

    rects = []
    for df_name, df in dfs:
        rects.append(df)

    bar_height = [[] for i in range(len(rects))]
    error_height = [[] for i in range(len(rects))]

    for label in labels:
        for i, rect in enumerate(rects):
            try:
                bar_height[i].append(rect.loc[rect["input"] == label][y_axis].mean())
                error_height[i].append(rect.loc[rect["input"] == label][y_axis].std())
            except:
                print("plot_shart_against: failed: ", label)

    fig, ax = plt.subplots(figsize=(20,10))
    for i in range(len(dfs)):
        label = ""
        df_name = dfs[i][0]
        offset = (i -  int(len(dfs)/2))
        if len(dfs)%2 == 0:
            offset += 1/2
        ax.bar(x + offset*width, bar_height[i], width, yerr=error_height[i], label=label+df_name)

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel(y_axis)
    # ax.set_title('')
    ax.set_xticks(x)
    ax.set_xticklabels(labels)
    plt.xticks(rotation=90)
    ax.legend()
    
    fig.savefig(save_file)

def plot_lines_against(dfs: list, x_axis="n", y_axis="L1-dcache-load-misses", test_names=None, save_file="lines.png"):
    ys = [[] for i in range(len(dfs))]
    fig, ax = plt.subplots()
    for i in range(len(dfs)):
        label = ""
        df_name, df = dfs[i]
        df = df.groupby([x_axis], as_index=False).mean()
        df.plot(x=x_axis, y=y_axis, ax=ax, label=df_name)

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel(y_axis)
    # ax.set_title('')
    ax.legend()
    
    fig.savefig(save_file)

def record_program(program_name, log_folder=None):
    Ns = list(range(100000, 1000000, 100000)) + list(range(1000000, 10000000, 1000000))
    Qs = [100000000]
    perf = PerfObj()
    for n in Ns:
        for q in Qs:
            parsed_data = perf.record_cache(program_name, n, q)
    if log_folder:
        perf.get_records().to_pickle(f"{log_folder}/{uuid.uuid4()}.log")

    return perf.get_records()

def mkdir(path):
    try:
        os.makedirs(path)
    except FileExistsError:
        # directory already exists
        pass

def record(programs_to_record):
    dfs = []
    for program in programs_to_record:
        log_folder = "logs/" + program.replace("./", "")
        mkdir(log_folder)
        df = record_program(program, log_folder)
        dfs.append((program, df))
    # plot_barchart_against(dfs, y_axis="L1-dcache-load-misses")
    plot_lines_against(dfs, x_axis="n", y_axis="L1-dcache-load-misses")


def get_log_df(path):
    log_files = [os.path.join(path, f) for f in os.listdir(path) if f.endswith(".log")]
    ret_df = pd.DataFrame()
    for log_file in log_files:
        df = pd.read_pickle(log_file)
        ret_df = ret_df.append(df, ignore_index=True)
            
    return ret_df

def plot(programs):
    names = [name for name in programs]
    folders = [f"logs/{name}/" for name in names]
    dfs = []
    for name, folder in zip(names, folders):
        df = get_log_df(folder)
        dfs.append((name.replace('./perf_', ''), df))
    plot_lines_against(dfs, x_axis="n", y_axis="L1-dcache-load-misses")

if __name__ == '__main__':
    if len(argv) > 1:
        record(argv[1:])
    else:
        
        programs = ["./perf_std_set", "./perf_co_dst"]
        # programs = ["./perf_co_sst", "./perf_ca_sst", "./perf_built_co_sst", "./perf_simple_sst_recursive", "./perf_simple_sst_iterative"]
        # programs = ["./co_matrix_walker", "./naive_matrix_walker"]
        record(programs)
        plot(programs)

