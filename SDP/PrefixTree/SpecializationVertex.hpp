//
// Created by yasen on 12/30/18.
//

#ifndef PREFIXTREE_SPECIALIZATIONVERTEX_HPP
#define PREFIXTREE_SPECIALIZATIONVERTEX_HPP


#include "Graph.hpp"

namespace std {
    template <>;
    struct hash<Graph::Vertex> {
        inline size_t operator()(const Graph::Vertex* vertex) const {
            auto addr = reinterpret_cast<uintptr_t>(vertex);
#if SIZE_MAX < UINTPTR_MAX
            /* size_t is not large enough to hold the pointer’s memory address */
            addr %= SIZE_MAX;
            /* truncate the address so it is small enough to fit in a size_t */
#endif
            return addr;
        }
    };

}



#endif //PREFIXTREE_SPECIALIZATIONVERTEX_HPP
