//
// Created by yasen on 12/20/18.
//

#ifndef GAMEMAP_GRAPH_HPP
#define GAMEMAP_GRAPH_HPP

#include <string>
#include <unordered_map>

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
        Weight& weight();
        const Weight& weight() const;
    };

    class Vertex {
        friend class Graph;

        Value m_value;

        std::unordered_map<Key, Edge> adjacency;

        explicit Vertex(const Value& value = Value());

    public:
        Value& value();
        const Value& value() const;
    };

private:
    std::unordered_map<Key, Vertex> all_vertices;

public:
    void add_vertex(const Key& key, const Value& value);

    void add_edge(const Key& from, const Key& to, const Weight& m_weight = Weight());

    bool has_edge(const Key& from, const Key& to) const;
    bool has_vertex(const Key& key) const;


    Vertex* vertex(const Key& key);
    const Vertex* vertex(const Key& key) const;

    Edge* edge(const Key& from, const Key& to);
    const Edge* edge(const Key& from, const Key& to) const;

    std::size_t size_vertex() const;

    void clear();
};

void Graph::add_vertex(const Key &key, const Value &value) {
    if(all_vertices.find(key) != all_vertices.end()) {
        return;
    }

    all_vertices.insert(std::make_pair(key, Vertex(value)));
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

Graph::Vertex::Vertex(const Value &value) : m_value(value) {}

inline Value &Graph::Vertex::value() {
    return m_value;
}

inline const Value& Graph::Vertex::value() const {
    return m_value;
}

Graph::Edge::Edge(const Weight &weight) : m_weight(weight) {}

inline Weight& Graph::Edge::weight() {
    return m_weight;
}

inline const Weight& Graph::Edge::weight() const {
    return m_weight;
}


#endif //GAMEMAP_GRAPH_HPP
