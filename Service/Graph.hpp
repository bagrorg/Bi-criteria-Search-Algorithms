#pragma once

#include <vector>
#include <string>

struct Edge {
    int to_id;

    float time_cost;
    float dist_cost;
};

struct Vertex {
    float x, y;
    int id;

    std::vector<Edge> neighs;
};

class Graph {
public:
    Graph(const std::vector<Vertex> &adjList);

    std::vector<Edge> getNeighbours(int id);
private:
    std::vector<Vertex> adjList_;
};

void parseGraph(std::string data_file, std::vector<Vertex> &dest);