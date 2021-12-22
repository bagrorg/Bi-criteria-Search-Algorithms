#pragma once

#include <vector>
#include <string>

struct Edge {
    int to_id;

    float time_cost;
    float dist_cost;
};

struct Vertex {
    long x, y;
    int id;

    std::vector<Edge> neighs;
};

class Graph {
public:
    Graph(std::vector<Vertex> adjList);

    std::vector<Edge> getNeighbours(int id) const;
private:
    std::vector<Vertex> adjList_;
};

void parseGraph(std::string data_file, std::vector<Vertex> &dest);