//
// Created by yasen on 12/25/18.
//

#ifndef PREFIXTREE_GRAPH_HPP
#define PREFIXTREE_GRAPH_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>


class Graph {
public:

    class Vertex {
        friend class Graph;
        bool isFinal;

        explicit Vertex(const bool& new_isFinal = false) : isFinal(new_isFinal) {};
    };

    typedef std::pair<char, int> DeltaTransition;
    typedef std::pair<Vertex*, std::vector<DeltaTransition>> VectorDeltaTransitions;
    typedef std::vector<std::vector<Vertex*>> EquivalentClasses;
private:
    Vertex* m_root;
    std::unordered_map<Vertex*, std::unordered_map<char, Vertex*>> all_vertices;

private:
    void add_word_recursive(const char* word, Vertex* ver);
    void minimized_recursive(EquivalentClasses& equivalent_classes);
    int find(const Vertex* adj, const EquivalentClasses& equivalent_classes);
    std::vector<Vertex*> collectFullClass(std::vector<VectorDeltaTransitions>&);
    void redirectVertices(EquivalentClasses& equivalent_classes);
public:
    Graph();

    void mergerWith(Graph& other);
    void add_word(const char* word);
    void minimized();
    void print() const;
};

Graph::Graph() : m_root(new Vertex) {
    std::unordered_map<char, Vertex*> adjacency;
    all_vertices.insert(std::make_pair(m_root, adjacency));
}

void Graph::add_word(const char* word) {

    std::cout << "add_word()" << std::endl;
    add_word_recursive(word, m_root);
}

void Graph::add_word_recursive(const char* word, Graph::Vertex* ver) {

    std::cout << "add_word_recursive1()" << std::endl;
    if(!word) {
        return;
    }

    std::cout << "add_word_recursive2()" << std::endl;
    auto it = all_vertices.find(ver);

    if (it->first != nullptr) {

        std::cout << "add_word_recursive3()" << std::endl;
        auto it2 = it->second.find(*word);
        if(it2->first != '\0') {

            std::cout << "add_word_recursive4()" << std::endl;
            add_word_recursive(++word, it2->second);
            return;
        }
    }

    std::cout << "add_word_recursive5()" << std::endl;
    std::unordered_map<char, Vertex*> adjacency;
    if (*word == '\0') {
        ver->isFinal = true;

        std::cout << "add_word_recursive6()" << std::endl;
        if(it->first != all_vertices.end()->first) {
            return;
        }

        all_vertices.insert(std::make_pair(ver, adjacency));
    } else {
        Vertex* new_vertex = new Vertex;

        it->second.insert(std::make_pair(*word, new_vertex));
        all_vertices.insert(std::make_pair(ver, adjacency));

        add_word_recursive(++word, new_vertex);
    }


}

void Graph::print() const {
    std::cout << "sizeof prefix tree: " << sizeof(*this) << " bytes" << std::endl;
    std::cout << "Number of vertices: " << all_vertices.size() << std::endl;
  /*
    int i = 0;
    for(auto& ver : all_vertices) {
        std::cout << i++ << ": ";
        for(auto& elem : ver->adjacency) {
            std::cout << elem.first << ", ";
        }
        std::cout << std::endl;
    }
    */
}

void Graph::minimized() {
    EquivalentClasses equivalent_classes(2);

    for(auto& ver : all_vertices) {
        if(ver.first->isFinal) {
            equivalent_classes[1].push_back(ver.first);
        } else {
            equivalent_classes[0].push_back(ver.first);
        }
    }

    minimized_recursive(equivalent_classes);

    redirectVertices(equivalent_classes);
}

int Graph::find(const Graph::Vertex* adj, const EquivalentClasses& equivalent_classes) {
    int index = 0;
    for(auto& single_class : equivalent_classes) {
        for(auto& ver : single_class) {
            if(ver == adj) {
                return index;
            }
        }
        ++index;
    }
    return -1;
}

void Graph::minimized_recursive(EquivalentClasses& equivalent_classes) {
    std::cout << "Equivalent classes size: " << equivalent_classes.size() << std::endl;
    size_t sizeOfEquivalentClasses = equivalent_classes.size();
    EquivalentClasses new_equivalent_classes;
    for(auto& single_class : equivalent_classes) {
        if(single_class.size() == 1) { //don't touch singleton classes
            new_equivalent_classes.push_back(single_class);
            continue;
        }
        std::vector<VectorDeltaTransitions> singleClassVectorTransitions;

        for(auto& ver : single_class) {
            VectorDeltaTransitions array;
            array.first = ver;
            auto it = all_vertices.find(ver);
            for(auto& letter : it->second) {
                int indexOfEquivalentClass = find(letter.second, equivalent_classes);
                DeltaTransition DT = std::make_pair(letter.first, indexOfEquivalentClass);
                array.second.push_back(DT);
            }

            singleClassVectorTransitions.push_back(array);
        }
        while(!singleClassVectorTransitions.empty()) {

            std::vector<Vertex*> new_equivalent_class = collectFullClass(singleClassVectorTransitions);
            new_equivalent_classes.push_back(new_equivalent_class);
        }

    }
    if(sizeOfEquivalentClasses != new_equivalent_classes.size()) {
        equivalent_classes = new_equivalent_classes;
        minimized_recursive(equivalent_classes);
    }
}

std::vector<Graph::Vertex*> Graph::collectFullClass(std::vector<Graph::VectorDeltaTransitions>& singleClassVectorTransitions) {
    std::vector<Graph::Vertex*> new_equivalent_class;
    VectorDeltaTransitions firstClass = singleClassVectorTransitions[0];
    new_equivalent_class.push_back(firstClass.first);
    singleClassVectorTransitions.erase(singleClassVectorTransitions.begin());

    for(auto it = singleClassVectorTransitions.begin(); it != singleClassVectorTransitions.end(); ++it) {
        if(it->second == firstClass.second) {
            new_equivalent_class.push_back(it->first);
            singleClassVectorTransitions.erase(it);
            --it;
        }
    }
    return new_equivalent_class;
}

void Graph::redirectVertices(Graph::EquivalentClasses &equivalent_classes) {
    int index;

    for(auto& single_class : equivalent_classes) {
        for(auto& ver : single_class) {
            auto it = all_vertices.find(ver);
            for(auto& adj : it->second) {
                index = find(adj.second, equivalent_classes);
                adj.second = equivalent_classes[index][0];
            }
        }
    }

    for(auto& single_class : equivalent_classes) {
        single_class.erase(single_class.begin());
        for(Vertex* ver : single_class) {
            delete ver;
        }
        single_class.clear();
    }
    equivalent_classes.clear();
}

void Graph::mergerWith(Graph& other) {
    auto it1 = all_vertices.find(m_root);
    auto it2 = other.all_vertices.find(other.m_root);
    for(auto& ver : it2->second) {
        it1->second.insert(ver);
    }
    for(auto& ver : other.all_vertices) {
        if(ver.first == other.m_root) {
            continue;
        }
        all_vertices.insert(ver);
    }
    delete other.m_root;

    other.all_vertices.clear();
}


#endif //PREFIXTREE_GRAPH_HPP
