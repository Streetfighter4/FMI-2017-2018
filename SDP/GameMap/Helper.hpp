//
// Created by yasen on 12/22/18.
//

#include <fstream>
#include <cstring>
#include <iostream>
#include "Graph.hpp"

const size_t MAX_LINE_SIZE = 1024;

namespace Helper {
    void parseMap(Graph& graph, const std::string& fileName) {
        std::ifstream ifs(fileName);

        if(!ifs.is_open()) {
            return;
        }
        char line[MAX_LINE_SIZE];
        ifs.getline(line, MAX_LINE_SIZE);
        while (strcmp(line, "[zones]") != 0) {
            ifs.getline(line, MAX_LINE_SIZE);
        }

        std::string lineBuffer;
        std::string zone1, zone2, key;
        size_t spaceIndex, bracket1, bracket2;
        while (lineBuffer != "[keys]") {
            ifs.getline(line, MAX_LINE_SIZE);
            lineBuffer = line;

            if(lineBuffer.empty()) {
                break;
            }
            memset(line, 0, MAX_LINE_SIZE);

            spaceIndex = lineBuffer.find(' ');
            zone1 = lineBuffer.substr(0, spaceIndex);

            bracket1 = lineBuffer.find('[');
            if(bracket1 != -1) {
                zone2 = lineBuffer.substr(spaceIndex+4, bracket1 - (spaceIndex+5));
                bracket2 = lineBuffer.find(']');
                key = lineBuffer.substr(bracket1+1, bracket2-bracket1-1);
            } else {
                zone2 = lineBuffer.substr(spaceIndex+4);
            }

            graph.add_vertex(zone1);
            graph.add_vertex(zone2);
            graph.add_edge(zone1, zone2, key);
            key = "";
        }
        ifs.getline(line, MAX_LINE_SIZE);
        while(!ifs.eof()) {
            ifs.getline(line, MAX_LINE_SIZE);
            lineBuffer = line;

            if(lineBuffer.empty()) {
                continue;
            }
            memset(line, 0, MAX_LINE_SIZE);

            spaceIndex = lineBuffer.find('-');
            key = lineBuffer.substr(0, spaceIndex-1);
            zone1 = lineBuffer.substr(spaceIndex+3);
            graph.vertex(zone1)->setKeyName(key);
        }

        ifs.close();
    }


    std::string createEdge(const std::string& from, const std::string& to, const std::string& label) {
        std::string line = "\t" + from + " -> " + to;
        if(!label.empty()) {
            line += "[label=\"";
            line += label;
            line += "\"]\n";
        } else {
            line += '\n';
        }
        return line;
    }

    std::string createVertex(const std::string& name, const std::vector<std::string>& keysArray, const bool& hasVisited) {
        std::string line = "\t" + name + "[";
        if(hasVisited) {
            if(keysArray.empty()) {
                return "";
            } else {
                line += "label=\"";
                line += name;
                for(auto& key : keysArray) {
                    line += "\\l";
                    line += key;
                }

                line += "\"";
            }
        } else {
            if(!keysArray.empty()) {

                line += "label=\"";
                line += name;
                for(auto& key : keysArray) {
                    line += "\\l";
                    line += key;
                }

                line += "\", ";

            }
            line += "color=red,style=filled,fillcolor=\"#ffefef\"";
        }

        line += "]\n";


        return line;
    }

    void generateDOTFile(const Graph& graph, const std::string& fileName) {
        size_t indexDot = fileName.find_last_of('.');
        std::string realFileName = fileName.substr(0, indexDot);
        std::ofstream ofs(realFileName+".dot");
        if(!ofs.is_open()) {
            return;
        }
        ofs << "digraph " << realFileName << " {\n";
        for (auto& vertex : graph.all_vertices) {
            for(auto& adj : vertex.second.adjacency) {
                ofs << createEdge(vertex.first, adj.first, adj.second.getWeight());
            }
        }
        ofs << "\n";
        for (auto& vertex : graph.all_vertices) {
            /*
            std::cout << "Vertex: " << vertex.first << ", keys:";
            for(auto& key : vertex.second.keysArray) {
                std::cout << key << " ";
            }
            std::cout << ", Has visited: " << ((vertex.second.hasVisited()) ? "True" : "False") << std::endl;
             */
            ofs << createVertex(vertex.first, vertex.second.keysArray, vertex.second.hasVisited());
        }

        ofs << "\n}";
        ofs.close();
    }
}