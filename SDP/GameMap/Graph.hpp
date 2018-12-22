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

typedef std::string Weight;
typedef std::string Key;
typedef std::string Value;

class Graph {
public:
    class Edge {
        friend class Graph;

        Weight m_weight;

        explicit Edge(const Weight& weight = Weight());

    public:
        Weight& getWeight();
    };

    class Vertex {
        friend class Graph;

        Value zone_name;
        Value key_name;

        bool visited;

        std::unordered_map<Key, Edge> adjacency;

        explicit Vertex(const Value& new_zone_name = Value(), const bool& visited = false);

    public:
        Value& getZoneName();
        Value& getKeyName();
        bool& hasVisited();

        void setKeyName(const Key& keyName);
        void setVisited(const bool& isVisited);
    };

    void BFS(const Value& startVertex, Key& analyze_vertex);
    void AnalyzeGraph(const Value& startVertex);
private:
    std::unordered_map<Key, Vertex> all_vertices;
    std::unordered_set<Key> key_storage;

    void clear();

public:
    void add_vertex(const Key& key);

    void add_edge(const Key& from, const Key& to, const Weight& m_weight = Weight());

    bool has_edge(const Key& from, const Key& to) const;
    bool has_vertex(const Key& key) const;


    Vertex* vertex(const Key& key);

    Edge* edge(const Key& from, const Key& to);

    std::size_t size_vertex() const;


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

bool Graph::has_edge(const Key &from, const Key &to) const {
    auto from_iter = all_vertices.find(from);

    if (from_iter != all_vertices.end())
    {
        return from_iter->second.adjacency.find(to) != from_iter->second.adjacency.end();
    }

    return false;

}

inline bool Graph::has_vertex(const Key &key) const {
    return all_vertices.find(key) != all_vertices.end();
}

inline std::size_t Graph::size_vertex() const {
    return all_vertices.size();
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

Graph::Edge* Graph::edge(const Key& from, const Key& to) {
    auto from_it = all_vertices.find(from);

    if(from_it != all_vertices.end()) {
        auto to_it = from_it->second.adjacency.find(to);

        if(to_it != from_it->second.adjacency.end()) {
            return &to_it->second;
        }
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

        if(!current_vert.getKeyName().empty()) { //get key from zone
            key_storage.insert(current_vert.getKeyName());
            current_vert.setKeyName("");
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
        return;
    }
    std::unordered_set<Key> visited;
    Key toDoAnalyzeVertex = startVertex;

    while(!toDoAnalyzeVertex.empty()) {
        const Key currentStartVertex = toDoAnalyzeVertex;
        if(visited.find(currentStartVertex) != visited.end()) {
            break;
        }
        std::cout << "BFS with vertex: " << currentStartVertex << std::endl;
        BFS(currentStartVertex, toDoAnalyzeVertex);
        visited.insert(currentStartVertex);
    }
}

Graph::Vertex::Vertex(const Value& new_zone_name, const bool& new_visited) : zone_name(new_zone_name), visited(new_visited) {}

inline Value& Graph::Vertex::getZoneName() {
    return zone_name;
}

inline Value& Graph::Vertex::getKeyName() {
    return key_name;
}

inline void Graph::Vertex::setKeyName(const Key &keyName) {
    key_name = keyName;
}

inline bool& Graph::Vertex::hasVisited() {
    return visited;
}

void Graph::Vertex::setVisited(const bool& isVisited) {
    visited = isVisited;
}


Graph::Edge::Edge(const Weight &weight) : m_weight(weight) {}

inline Weight& Graph::Edge::getWeight() {
    return m_weight;
}


#endif //GAMEMAP_GRAPH_HPP