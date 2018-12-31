//
// Created by yasen on 12/20/18.
//

#ifndef GAMEMAP_GRAPH_HPP
#define GAMEMAP_GRAPH_HPP

#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <utility>

typedef std::string Weight;
typedef std::string Key;
typedef std::string Value;

class Graph {
public:
    class Edge {
        friend class Graph;

        Weight m_weight;

        explicit Edge(Weight weight = Weight());

    public:
        const Weight& getWeight() const;
    };

    class Vertex {
        friend class Graph;

        Value zone_name;

        bool visited;

        explicit Vertex(Value new_zone_name = Value(), const bool& new_visited = false);

    public:
        std::unordered_map<Key, Edge> adjacency;
        std::vector<Key> keysArray;

        const bool& hasVisited() const;

        void setKeyName(const Key& keyName);
        void setVisited(const bool& isVisited);
    };

    void BFS(const Value& startVertex, Key& toDoAnalyzeVertex);
    void AnalyzeGraph(const Value& startVertex);
private:
    std::unordered_set<Key> key_storage;

    void clear();

public:
    std::unordered_map<Key, Vertex> all_vertices;

    void add_vertex(const Key& key);

    void add_edge(const Key& from, const Key& to, const Weight& m_weight = Weight());


    Vertex* vertex(const Key& key);

public:
    ~Graph() {
        clear();
    }
};

void Graph::add_vertex(const Key& key) {
    if(all_vertices.find(key) != all_vertices.end()) {
        return;
    }

    all_vertices.insert(std::make_pair(key, Vertex(key)));
}

void Graph::add_edge(const Key& from, const Key& to, const Weight& m_weight) {

    auto from_iter = all_vertices.find(from);
    auto to_iter = all_vertices.find(to);

    if(from_iter != all_vertices.end() && to_iter != all_vertices.end()) {
        if(from_iter->second.adjacency.find(to) != from_iter->second.adjacency.end()) {
            return;
        }
        from_iter->second.adjacency.insert(std::make_pair(to, Edge(m_weight)));
    }
}


inline void Graph::clear() {
    all_vertices.clear();
}

Graph::Vertex* Graph::vertex(const Key &key) {
    auto it = all_vertices.find(key);

    if (it != all_vertices.end()) {
        return &it->second;
    }

    return nullptr;
}


void Graph::BFS(const Value& startVertex, Key& toDoAnalyzeVertex) {
    if(all_vertices.find(startVertex) == all_vertices.end()) {
        return;
    }

    std::unordered_set<Key> visited;
    std::queue<Key> m_queue;
    m_queue.push(startVertex);

    Key currentVertexName;
    bool hasChild = false;
    while(!m_queue.empty()) {
        currentVertexName = m_queue.front();

        Vertex& current_vert = all_vertices.find(currentVertexName)->second; //get pointer to vertex

        if(!current_vert.keysArray.empty() && !current_vert.hasVisited()) { //get keys from zone
            for(auto& key : current_vert.keysArray) {
                key_storage.insert(key);
            }
        }

        Key keyName;
        for (auto& edge : current_vert.adjacency) {
            hasChild = true;
            if(visited.find(edge.first) == visited.end()) {
                keyName = edge.second.getWeight();
                if(!keyName.empty()) {
                    if(key_storage.find(keyName) != key_storage.end()) {
                        m_queue.push(edge.first);
                    }
                } else {
                    m_queue.push(edge.first);
                }
            }
        }

        m_queue.pop();
        current_vert.setVisited(true);
        visited.insert(currentVertexName);
    }
    if(hasChild) {
        toDoAnalyzeVertex = currentVertexName;
    } else {
        toDoAnalyzeVertex = "";
    }

}

void Graph::AnalyzeGraph(const Value& startVertex) {
    if(all_vertices.find(startVertex) == all_vertices.end()) {
        std::cout << "Start zone don't exist. Sorry :/" << std::endl;
        return;
    }
    std::unordered_set<Key> visited;
    Key toDoAnalyzeVertex = startVertex;

    while(!toDoAnalyzeVertex.empty()) {
        const Key currentStartVertex = toDoAnalyzeVertex;
        if(visited.find(currentStartVertex) != visited.end()) {
            break;
        }
        // BFS from every not visited and potential vertex.
        // toDoAnalyzeVertex is that vertex which is marked as last in BFS
        BFS(currentStartVertex, toDoAnalyzeVertex);
        visited.insert(currentStartVertex);
    }
}

Graph::Vertex::Vertex(Value new_zone_name, const bool& new_visited) : zone_name(std::move(new_zone_name)), visited(new_visited) {}

inline void Graph::Vertex::setKeyName(const Key &keyName) {
    keysArray.push_back(keyName);
}

inline const bool& Graph::Vertex::hasVisited() const {
    return visited;
}

void Graph::Vertex::setVisited(const bool& isVisited) {
    visited = isVisited;
}


Graph::Edge::Edge(Weight weight) : m_weight(std::move(weight)) {}

inline const Weight& Graph::Edge::getWeight() const {
    return m_weight;
}


#endif //GAMEMAP_GRAPH_HPP
