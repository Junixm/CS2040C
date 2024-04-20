#ifndef __SHORTESTPATH_H__
#define __SHORTESTPATH_H__

#include <vector>
#include "graph.h"
// We should include graph.h here, but that causes problems with coursemology.
// So instead, please make sure to include it before this file.

using std::vector;

class Path {
 private:
  const int _total_distance;
  const vector<int> _path;

 public:
  Path(int total_distance, vector<int> path)
      : _total_distance(total_distance), _path(path) {}
  int total_distance() const { return _total_distance; }
  const vector<int>& path() const { return _path; }
};

Path shortestPath(const Graph& g, int source, int dest);

#endif /* __SHORTESTPATH_H__ */
