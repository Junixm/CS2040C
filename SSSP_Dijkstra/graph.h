#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <forward_list>
#include <iostream>
#include <string>
#include <vector>

using std::forward_list;
using std::ostream;
using std::string;
using std::vector;

/**
 * @brief Representation of an edge in the graph.
 * Contains the destination vertex and the weight of the edge.
 * The source vertex is implicit in the index of the forward_list, and thus not
 * stored in the edge.
 */
class GraphEdge {
 private:
  int _dest;
  int _weight;

 public:
  // Public constructor creates an invalid edge. Needed for use in vector.
  GraphEdge() : _dest(-1), _weight(-1) {}
  GraphEdge(int index, int weight) : _dest(index), _weight(weight) {}
  GraphEdge(const GraphEdge& e) : _dest(e._dest), _weight(e._weight) {}
  int dest() const { return _dest; }
  int weight() const { return _weight; }
  bool operator>(const GraphEdge& e) const { return _weight > e._weight; }
  bool operator==(const GraphEdge& e) const { return _dest == e._dest; }
};

/**
 * @brief Representation of a graph.
 * The graph is represented as an adjacency list.
 * The vertices are numbered from 0 to n-1.
 */
class Graph {
 private:
  // This vector has a slot for each vertex in the graph.
  // The forward_list (a singly-linked list) for each vertex
  // contains all of the edges from that vertex.
  vector<forward_list<GraphEdge>> _vertices;

 public:
  // Create an empty graph with n vertices
  Graph(int n) : _vertices(n) {}

  int num_vertices() const { return _vertices.size(); }

  // Get edges of vertex i
  const forward_list<GraphEdge>& edges_from(int i) const {
    return _vertices[i];
  }

  // Add an edge from source vertex to dest vertex with weight weight
  void addEdge(int source, int dest, int weight);

  // Utility function to print graph to stdout
  void print() const;
};

ostream& operator<<(ostream&, const GraphEdge&);
ostream& operator<<(ostream&, const Graph&);

#endif /* __GRAPH_H__ */
