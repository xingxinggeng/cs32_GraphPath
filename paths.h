// paths.h - shortest distances/paths function for CS 32 PA2
//
// CONSTANT to represent infinity:
// const size_t INF = ULONG_MAX;
//
// FUNCTION:
// void shortest(wtdgraph<string> &g,
//               size_t start,
//               vector<size_t> &distances,
//               vector<list<size_t> > &paths);
// Preconditions: distances and paths vectors are large
// enough to contain g.size() elements, and start is less
// than g.size().
// Postconditions: distances filled with shortest distances
// from start vertex of g to all other vertices. If no path
// exists to vertex i, then distances[i] is set to INF. Also
// paths[i] is a list of vertex numbers showing the path
// from start  to vertex i (empty list means no path exists).

#ifndef PATHS_H
#define PATHS_H

#include <climits> // provides ULONG_MAX, maximum size_t
#include <list>
#include <vector>
#include "wtdgraph.h"
using main_savitch_15::wtdgraph;
using std::size_t;
using std::vector;
using std::list;
using std::string;

const size_t INF = ULONG_MAX;

void shortest(wtdgraph<string> &g,
              size_t start,
              vector<size_t> &distances,
              vector<list<size_t> > &paths);

#endif
