//
// Created by yasen on 12/25/18.
//

#ifndef PREFIXTREE_GRAPH_HPP
#define PREFIXTREE_GRAPH_HPP

#include <unordered_set>
#include <vector>
#include <iostream>
#include <map>


class Graph {
public:

    class Vertex {
        friend class Graph;
        bool isFinal;
        typedef std::pair<size_t , Vertex*> value;
        std::map<wchar_t, value> adjacency;

        explicit Vertex(const bool& new_isFinal = false) : isFinal(new_isFinal) {};
    };

    typedef std::pair<wchar_t, int> DeltaTransition;
    typedef std::pair<Vertex*, std::vector<DeltaTransition>> VectorDeltaTransitions;
    typedef std::vector<std::vector<Vertex*>> EquivalentClasses;
private:
    Vertex* m_root;
    std::vector<Vertex*> all_vertices;

private:
    void add_word_recursive(const wchar_t* word, Vertex* ver);
    void minimized_recursive(EquivalentClasses& equivalent_classes);
    int find(const Vertex* adj, const EquivalentClasses& equivalent_classes);
    std::vector<Vertex*> collectFullClass(std::vector<VectorDeltaTransitions>&);
    void redirectVertices(EquivalentClasses& equivalent_classes);
    void findEveryPhraseFromVertex(wchar_t* prefix, Vertex* currentVertex, size_t size);
public:
    Graph();

    void add_word(const wchar_t* word);
    void minimized();
    void print() const;
    void findEveryPhraseWithPrefix(const wchar_t* prefix);
};

Graph::Graph() : m_root(new Vertex) {
    all_vertices.push_back(m_root);
}

void Graph::add_word(const wchar_t* word) {

    add_word_recursive(word, m_root);
}

void Graph::add_word_recursive(const wchar_t* word, Graph::Vertex* ver) {
    if(!word) {
        return;
    }
    auto it = ver->adjacency.find(*word);

    if (it != ver->adjacency.end()) {
        add_word_recursive(++word, it->second.second);
        return;
    }

    if (*word == '\0') {
        ver->isFinal = true;

    } else {
        Vertex* new_vertex = new Vertex;
        ver->adjacency.insert(std::make_pair(*word, std::make_pair(0, new_vertex)));
        all_vertices.push_back(new_vertex);

        add_word_recursive(++word, new_vertex);
    }
}

void Graph::print() const {
    std::cout << "sizeof prefix tree: " << sizeof(*this) + sizeof(all_vertices) << " bytes" << std::endl;
    std::cout << "Number of vertices: " << all_vertices.size() << std::endl;
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
            for(auto& letter : ver->adjacency) {

                int indexOfEquivalentClass = find(letter.second.second, equivalent_classes);
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
                index = find(adj.second.second, equivalent_classes);
                adj.second.second = equivalent_classes[index][0];
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

void Graph::findEveryPhraseWithPrefix(const wchar_t* prefix) {
    Vertex* currentVertex = m_root;

    auto* word = new wchar_t[64];
    wcscpy(word, prefix);


    while(*prefix != '\0') {
        auto it = currentVertex->adjacency.find(*prefix);
        if(it != currentVertex->adjacency.end()) {

            it->second.first++;
            currentVertex = it->second.second;
            ++prefix;
        } else {
            std::cout << "No such phrase :/" << std::endl;
            return;
        }
    }

    findEveryPhraseFromVertex(word, currentVertex, wcslen(word));
    delete[] word;

}

void Graph::findEveryPhraseFromVertex(wchar_t* prefix, Graph::Vertex *currentVertex, size_t size) {
    if(currentVertex->isFinal) {
        std::wcout << prefix << std::endl;
    }
    for(auto& ver : currentVertex->adjacency) {
        prefix[size] = ver.first;
        prefix[size+1] = '\0';
        findEveryPhraseFromVertex(prefix, ver.second.second, size+1);
    }
}


#endif //PREFIXTREE_GRAPH_HPP
