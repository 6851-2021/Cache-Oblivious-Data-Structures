from subprocess import PIPE, run
import pandas as pd
import uuid
import numpy as np
import matplotlib.pyplot as plt
from perf import PerfObj
from sys import argv

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
    fig, ax = plt.subplots(figsize=(20,10))
    for i in range(len(dfs)):
        label = ""
        df_name, df = dfs[i]
        df.plot(x=x_axis, y=y_axis, ax=ax, label=df_name)

    # Add some text for labels, title and custom x-axis tick labels, etc.
    ax.set_ylabel(y_axis)
    # ax.set_title('')
    ax.legend()
    
    fig.savefig(save_file)

def record_program(program_name, log_folder=None):
    Ns = range(1000, 10000, 1000)
    Qs = [100000]
    perf = PerfObj()
    for n in Ns:
        for q in Qs:
            perf.record_cache(program_name, n, q)
    return perf.get_records()

def main(programs_to_record):
    dfs = []
    for program in programs_to_record:
        df = record_program(program)
        dfs.append((program, df))
    # plot_barchart_against(dfs, y_axis="L1-dcache-load-misses")
    plot_lines_against(dfs, x_axis="n", y_axis="L1-dcache-load-misses")
if __name__ == '__main__':
    if len(argv) > 1:
        main(argv[1:])
    else:
        print("Error :| replace this code or pass arguments")


