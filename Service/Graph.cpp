#include "Graph.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Graph::Graph(std::vector<Vertex> adjList) : adjList_(std::move(adjList)) {};

std::vector<Edge> Graph::getNeighbours(int id) const {
    return adjList_[id].neighs;
}

const Vertex &Graph::getVertex(int id) const {
    return adjList_[id];
}

void parseGraph(std::string data_file, std::vector<Vertex> &dest) {
    std::ifstream in(data_file);
    
    std::cout << in.good() << std::endl;

    for (std::string line; std::getline(in, line);) {
        std::istringstream line_stream(line);

        std::string type;
        line_stream >> type;

        if (type == "p") {
            std::string dummy, vtxs, edgs;

            line_stream >> dummy >> vtxs >> edgs;
            dest.resize(std::atoi(vtxs.data()));
        }
        else if (type == "v") {
            std::string vtx, x, y;
            line_stream >> vtx >> x >> y;

            int id = std::atoi(vtx.data());

            dest[id].position = {
                std::atol(x.data()),
                std::atol(y.data())
            };
            dest[id].id = id;
        }
        else if (type == "a") {
            std::string vtx1, vtx2, time, dist;
            line_stream >> vtx1 >> vtx2 >> time >> dist;

            Edge e = {
                std::atoi(vtx2.data()),
                static_cast<float>(std::atof(time.data())),
                static_cast<float>(std::atof(dist.data()))
            };
            dest[std::atoi(vtx1.data())].neighs.push_back(e);
        }
    }
}