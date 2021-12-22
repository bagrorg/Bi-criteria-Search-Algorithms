import heapq

class Node:
    def __init__(self, id, g = 0, h = 0, F = None, parent = None):
        self.id = id
        self.g = g
        self.h = h
        if F is None:
            self.F = self.g + h
        else:
            self.F = F        
        self.parent = parent
    
    
    def __eq__(self, other):
        return (self.id == other.id)

    def __hash__(self) -> int:
        return hash(self.id)

    def __lt__(self, other):
        return self.g < other.g

class Open:
    def __init__(self):
        self.heap = []
        self.nodes = {}

    def __iter__(self):
        return iter(self.nodes.values())

    def __len__(self):
        return len(self.nodes)

    def isEmpty(self):
        return len(self) == 0

    def AddNode(self, node: Node, *args):
        pos = node.id
        if pos in self.nodes:
            if self.nodes[pos].g <= node.g:
                return
        self.nodes[pos] = node
        heapq.heappush(self.heap, node)

    def GetBestNode(self, *args):
        while True:
            best = self.heap[0]
            heapq.heappop(self.heap)
            pos = best.id
            if pos in self.nodes:
                break
        del self.nodes[pos]
        return best

class Closed:
    def __init__(self):
        self.nodes = {}

    def __iter__(self):
        return iter(self.nodes.values())

    def __len__(self):
        return len(self.nodes)

    def AddNode(self, item):
        self.nodes[(item.id)] = item

    def WasExpanded(self, item):
        return (item.id) in self.nodes

class Edge:
    def __init__(self, to, cost):
        self.cost = cost
        self.to = to

class Vertex:
    def __init__(self, id, neighs):
        self.id = id
        self.neighs = neighs

    def addN(self, neigh):
        self.neighs.append(neigh)

class Graph:
    def __init__(self):
        self.vtxs = []
    
    def getNeighbours(self, id):
        return self.vtxs[id].neighs