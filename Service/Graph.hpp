#pragma once

#include <vector>
#include <string>

using Position = std::pair<long, long>;

struct Edge {
    int to_id;

    float time_cost;
    float dist_cost;
};

struct Vertex {
    Position position;
    int id;

    std::vector<Edge> neighs;
};

class Graph {
public:
    Graph(std::vector<Vertex> adjList);

    std::vector<Edge> getNeighbours(int id) const;
    const Vertex& getVertex(int id) const;
private:
    std::vector<Vertex> adjList_;
};

void parseGraph(std::string data_file, std::vector<Vertex> &dest);