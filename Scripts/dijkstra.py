from PIL import Image, ImageDraw
import numpy as np
from serviceForDijkstra import *
import sys

def ReadTaskFromFile(path):
    '''
    Reads map, start/goal positions and true value of path length between given start and goal from file by path. 
    '''
    file = open(path, 'r')
    g = Graph()
    for line in (file.readlines()):
        if line[0] == 'p':
            line = line.split(' ')
            v_count = int(line[2])
            g.vtxs = [Vertex(i, []) for i in range(v_count)]
        elif line[0] == 'a':
            line = line.strip().split(' ')
            id1 = int(line[1]) - 1
            id2 = int(line[2]) - 1
            cost = int(line[3])

            g.vtxs[id1].addN(Edge(id2, cost))
    file.close()
    return g

def Dijkstra(graph, idStart, openType = Open, closedType = Closed):
    OPEN = openType()
    CLOSED = closedType()

    OPEN.AddNode(Node(idStart))
    while not OPEN.isEmpty():
        st = OPEN.GetBestNode()
        CLOSED.AddNode(st)
        
        neigh = graph.getNeighbours(st.id)
        for pos in neigh:
            new_neigh = Node(pos.to, g=(st.g + pos.cost), parent=st)
            if not CLOSED.WasExpanded(new_neigh):
                OPEN.AddNode(new_neigh)
    

    return (True, None, CLOSED, OPEN)


file_name = sys.argv[1]
file_to = sys.argv[2]
start_id = int(sys.argv[3])

g = ReadTaskFromFile(file_name)
_, _, CLOSED, _ = Dijkstra(g, start_id)
file = open(file_to, 'w')

for k in CLOSED.nodes:
    file.write(str(CLOSED.nodes[k].id) + ' ' + str(CLOSED.nodes[k].g) + '\n')
file.close()