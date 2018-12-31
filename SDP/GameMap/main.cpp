#include <iostream>
#include "Helper.hpp"

int main() {
    Graph m_graph;
    std::string fileName, startZone;
    std::cout << "Enter file name:" << std::endl;
    std::cin >> fileName;
    std::cin.ignore();
    std::cout << "Enter start zone: " << std::endl;
    char zone[1024];
    std::cin.getline(zone, 1024);
    startZone = zone;
    Helper::parseMap(m_graph, fileName);
    std::cout << "Analyze map...." << std::endl;
    m_graph.AnalyzeGraph(startZone);
    std::cout << "Generate DOT file for you :)" << std::endl;
    Helper::generateDOTFile(m_graph, fileName);

    return 0;
}