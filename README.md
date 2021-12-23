# Bi-criteria-Search-Algorithms
A software project at the SPbU.

## Description 
This project contains algorithms implementations that solves Bi-criteria pathfinding problem.

<img src="/Images/nyc3.gif"/>


## Getting started
For project build you should have compiler on C++17 standart.
For example, you can install it with 
```
sudo apt install build-essential 
```
This project should be built with CMake.
For example, you can install it with
```
sudo apt install cmake
```
Also you will need Boost library.
For example, you can install it with
```
sudo apt install libboost-all-dev   
```

Also you will need Python3.8

For Python you will need `tqdm` and `Pil`. You can install all dependencies from `requirements.txt` with
```
pip install -r requirements.txt
```


## Installing

To download current repository to your local machine use
```
git clone https://github.com/bagrorg/Bi-criteria-Search-Algorithms
```

To build the project follow the guide
```cmd
cd Bi-criteria-Search-Algorithms/
mkdir build
cd build
cmake ..
make -j nproc
```

## Arguments
You can manage settings of execution using arguments.

+ `algo` - wich algorithm to use. Now supported - BOA*, BOA*-epsilon and PP-A* (to use BOA*-epsilon just use BOA* and pass epsilons)
+ `report_path` - where to save execution description
+ `graph_path` - path to graph description file
+ `iterations` - how much executions to provide
+ `eps_dist`, `eps_time` - epsilons for PP-A* and BOA*-epsilon algorithms for distance cost and time cost
+ `start_id`, `goal_id` - indexes of start and goal vertexes
+ `history_path` - where to save history of OPEN and CLOSEd
+ `h_time_path`, `h_dist_path` - path to heuristic files (e.g. dijkstra results)

Also you can run explanation with 
```
./main --help
```

## Input and output
### 3 sepparate input graph files
For input there must be 3 files:
+ file with time cost
+ file with distance cost
+ file with coordinates

Indexing of vertices must starts from 1!
Format:
+ file with time/distance cost
Lines must be like
```
c {comments}
p sp {count of vertices} {count of edges}

a {vertex from} {vertex to} {time/distance cost}
```

+ file with coordinates
Lines must be like
```
c {comments}

v {vertex index} {x} {y}
```

After this, you can merge this files to one with script `mergeGraphFiles.py`. To check how to use this script see [Scripts](#scripts). This file you will need for execution

### 1 input graph file
+ file with time, distance and coordinates
Lines must be
```
c {comments}
p sp {count of vertices} {count of edges}
v {vertex index} {x} {y}
a {vertex from} {vertex to} {time cost} {distance cost}
```
Indexing of vertices must starts from 0!

You can find examples [here](https://github.com/bagrorg/Bi-criteria-Search-Algorithms/tree/master/Examples/Graphs). Also you can find `.gr/.co` files on 9th DIMACS Implementation Challenge: ShortestPath. Check [Sources](#sources) for more information.

### Output files

+ history file - contains all OPEN or solutions updates while an execution
Format:
```
e {num of epoch (iteration)}

n {nodes that was added on this iteration}

s {solution that was added on this iteration}
```
+ gif - gif file of working process

+ solutions - Paretto-optimal frontier
Format
```
s {dist} {time}
p {path}
```
Examples [here](https://github.com/bagrorg/Bi-criteria-Search-Algorithms/tree/master/Examples/Output)

### Misc
+ heuristics (from `dijkstra.py`)
Format
```
{vertex id} {heuristic}
```

## Scripts
+ `mergeGraphFiles.py {time path} {dist path} {coord path} {output path}` - merging 3 graph files at `{time path}`, `{dist path}` and `{coord path}` to one at `{output path}`. Indexing must starts from 1.


+ `dijkstra.py {input graph path} {output path} {vertex id}` - counting dijkstra results (for heuristics) using graph at `{input graph path}` for `{vertex id}` vertex and saving it at `{output path}` in format
```
{vertex id} {result}
```
Indexing must starts from 0.
+ `renderHistory.py {history path} {graph path} {output path} {start id} {goal id} {duration} {max frames} {width} {height}` - making a gif from hastory file at `{history path}` using graph at `{graph path}` and saving it at `{output path}`. History is for path starting at `{start id}` and ending at `{goal id}`. `{duration}`, `{max frames}`, `{height}` and `{width}` - settings for gif output. Can be `-1` for default. Indexing must starts from 0.

+ `serviceForDijkstra.py` - contains interfaces for `dijkstra.py`

+ `run.py` - main script that runs program on input graph
  + `{--time_graph_path}`, `{--dist_graph_path}`, `{--coords_graph_path}` - paths to input files
  + `{--output_graph_path}`, `{--output_graph_path}`, `{--dist_heuristic_path}` - paths to output files
  + `{--start_id}`, `{--goal_id}` - vertexes indexes
  + `{--app_path}` - path to c++ built program
  + `{--algo_name}` - algorithm (e.g. `BOA*`)
  + `{--history_path}` - path to history output (optional)
  + `{--eps_time}`, `{--eps_dist}` - epsilons (optional)
  + `{--report_path}` -- report path (optional)
Example
```
python3.9 run.py --time_graph_path ../Data/USA-road-t.NY.gr --dist_graph_path ../Data/USA-road-d.NY.gr --coords_graph_path ../Data/USA-road-d.NY.co --output_graph_path ../Data/Res.gr --output_graph_path ../Data/timeHeur.txt --dist_heuristic_path ../Data/distHeur.txt --start_id 31231 --goal_id 0 --app_path ../build/main --algo_name BOA* --eps_time 0 --eps_dist 0 --report_path ../Data/report.csv
```

## Sources
+ Hernández Ulloa, C., Yeoh, W., Baier, J. A., Zhang, H., Suazo, L., & Koenig, S. (2020). A Simple and Fast Bi-Objective Search Algorithm. [URL](https://ojs.aaai.org//index.php/ICAPS/article/view/6655)
+ Goldin, B., & Salzman, O. (2021). Approximate Bi-Criteria Search by Efficient Representation of Subsets of the Pareto-Optimal Frontier. [URL](https://ojs.aaai.org/index.php/ICAPS/article/view/15957)
+ 9th DIMACS Implementation Challenge: ShortestPath. [URL](http://users.diag.uniroma1.it/challenge9/download.shtml)
## Participants
### Mentor
Yakovlev Konstantin Sergeevich
### Students
Kulikov Daniil

Sadykov Rustam
