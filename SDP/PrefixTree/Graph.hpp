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

        std::unordered_map<char, Vertex*> adjacency;

        explicit Vertex(const bool& new_isFinal = false) : isFinal(new_isFinal) {};
    };

    typedef std::pair<char, int> DeltaTransition;
    typedef std::pair<Vertex*, std::vector<DeltaTransition>> VectorDeltaTransitions;
    typedef std::vector<std::vector<Vertex*>> EquivalentClasses;
private:
    Vertex* m_root;
    std::vector<Vertex*> all_vertices;

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
    all_vertices.push_back(m_root);
}

void Graph::add_word(const char* word) {

    add_word_recursive(word, m_root);
}

void Graph::add_word_recursive(const char* word, Graph::Vertex* ver) {
    if(!word) {
        return;
    }
    auto it = ver->adjacency.find(*word);

    if (it != ver->adjacency.end()) {
        add_word_recursive(++word, it->second);
        return;
    }

    if (*word == '\0') {
        ver->isFinal = true;

    } else {
        Vertex* new_vertex = new Vertex;
        ver->adjacency.insert(std::make_pair(*word, new_vertex));
        all_vertices.push_back(new_vertex);

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
        if(ver->isFinal) {
            equivalent_classes[1].push_back(ver);
        } else {
            equivalent_classes[0].push_back(ver);
        }
    }
    all_vertices.clear();
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
    //std::cout << "Equivalent classes size: " << equivalent_classes.size() << std::endl;
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
            for(auto& letter : ver->adjacency) {

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
            for(auto& adj : ver->adjacency) {
                index = find(adj.second, equivalent_classes);
                adj.second = equivalent_classes[index][0];
            }
        }
    }
    all_vertices.clear();
    for(auto& single_class : equivalent_classes) {

        all_vertices.push_back(single_class[0]);
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

    for(auto& ver : other.m_root->adjacency) {
        m_root->adjacency.insert(ver);
    }
    for(auto& ver = ++other.all_vertices.begin(); ver != other.all_vertices.end(); ++ver) {
        all_vertices.push_back(*ver);
    }
    delete other.m_root;

    other.all_vertices.clear();
}


#endif //PREFIXTREE_GRAPH_HPP
