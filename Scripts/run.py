import sys
import os

import dijkstra
import mergeGraphFiles

time_graph_path = None
dist_graph_path = None
coords_graph_path = None
output_graph_path = None

time_heuristic_path = None
dist_heuristic_path = None

start_id = None
goal_id = None

app_path = None

algo_name = None

eps_time = None
eps_dist = None

history_path = None
report_path = None

i = 1
while True:
    if i >= len(sys.argv):
        break

    key = sys.argv[i]
    value = sys.argv[i + 1]

    if key == '--time_graph_path':
        time_graph_path = value
    if key == '--dist_graph_path':
        dist_graph_path = value
    if key == '--coords_graph_path':
        coords_graph_path = value
    if key == '--output_graph_path':
        output_graph_path = value
    if key == '--time_heuristic_path':
        time_heuristic_path = value
    if key == '--dist_heuristic_path':
        dist_heuristic_path = value
    if key == '--start_id':
        start_id = value
    if key == '--goal_id':
        goal_id = value
    if key == '--app_path':
        app_path = value
    if key == '--algo_name':
        algo_name = value
    if key == '--eps_time':
        eps_time = value
    if key == '--eps_dist':
        eps_dist = value
    if key == '--history_path':
        history_path = value
    if key == '--report_path':
        report_path = value
    i += 2

mergeGraphFiles.main(time_graph_path, dist_graph_path, coords_graph_path, output_graph_path)
dijkstra.main(time_graph_path, time_heuristic_path, goal_id)
dijkstra.main(dist_graph_path, dist_heuristic_path, goal_id)

query_string = f'./{app_path} --algo {algo_name} --graph_path {output_graph_path} --start_id {start_id} --goal_id {goal_id}'

if history_path is not None:
    query_string += f' --history_path {history_path}'
if eps_time is not None and eps_dist is not None:
    query_string += f' --eps_time {eps_time} --eps_dist {eps_dist}'
if time_heuristic_path is not None and dist_heuristic_path is not None:
    query_string += f' --h_time_path {time_heuristic_path} --h_dist_path {dist_heuristic_path}'
if report_path is not None:
    query_string += f' --report_path {report_path}'

os.system(query_string)