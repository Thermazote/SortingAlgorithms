from plotly import graph_objects as go
import os
import json
import pandas as pd


def isfloat(num):
    try:
        float(num)
        return True
    except ValueError:
        return False


if __name__ == '__main__':
    sizes = [size for size in range(100, 1000, 100)] + \
        [size for size in range(1000, 10000, 1000)] + \
        [size for size in range(10000, 100000, 10000)] + \
        [size for size in range(100000, 1000000, 100000)]
    
    timings = dict()
    
    for filename in os.listdir():
        if filename.split('.')[-1] == 'txt':
            with open(filename, 'r') as file:
                timings[filename.split('.')[0]] = []
                for line in file.readlines():
                    if 'Elapsed time: ' in line:
                        timings[filename.split('.')[0]] += [float(s) for s in line.split() if isfloat(s)]
            
    with open('table.txt', 'w') as file:
        df = pd.concat([pd.DataFrame({'Sizes': sizes}), pd.DataFrame({k: pd.Series(v) for k, v in timings.items()})], axis=1)
        file.write(df.to_string())
    
    fig = go.Figure()

    for key, value in timings.items():
        fig.add_trace(go.Scatter(x=sizes[:len(value)], y=value, mode='lines+markers', name=key))
    
    fig.update_layout(
        title="Sorting algorithms complexity visualization",
        xaxis_title="Number of elements",
        yaxis_title="Time, sec",
        legend_title="Sorting algorithms"
    )
    
    fig.show()

    