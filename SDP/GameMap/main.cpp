#include <iostream>
#include "Helper.hpp"

int main(int argc, char* argv[]) {
    Graph m_graph;
    Helper::parseMap(m_graph, argv[1]);

    m_graph.AnalyzeGraph(argv[2]);

    std::cout << "Start point: " << argv[2] << std::endl;
    std::cout << std::endl;

    std::cout << "Has been visited: " << std::endl;
    std::cout << "Castle_black: " << ((m_graph.vertex("Castle_black")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "Moromont: " << ((m_graph.vertex("Mormont")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "Karstark: " << ((m_graph.vertex("Karstark")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Stark: " << ((m_graph.vertex("House_Stark")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "Bolton: " << ((m_graph.vertex("Bolton")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Greyjoy: " << ((m_graph.vertex("House_Greyjoy")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "Frey: " << ((m_graph.vertex("Frey")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Arryn: " << ((m_graph.vertex("House_Arryn")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Tully: " << ((m_graph.vertex("House_Tully")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Lannister: " << ((m_graph.vertex("House_Lannister")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Targaryen: " << ((m_graph.vertex("House_Targaryen")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "King's_Landing: " << ((m_graph.vertex("King's_Landing")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Tyrell: " << ((m_graph.vertex("House_Tyrell")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "Tarly: " << ((m_graph.vertex("Tarly")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Martell: " << ((m_graph.vertex("House_Martell")->hasVisited()) ? "True" : "False") << std::endl;
    std::cout << "House_Baratheon: " << ((m_graph.vertex("House_Baratheon")->hasVisited()) ? "True" : "False") << std::endl;

    Helper::


    return 0;
}