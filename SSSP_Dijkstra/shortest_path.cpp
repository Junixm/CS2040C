#include "graph.h"
#include "shortest_path.h"
#include "heap.hpp"
using namespace std;

#define INF 1000

class Vertice{
private:
  int _from;
  int _totalDist;

public:
  Vertice(int from): _from(from), _totalDist(INF) {}

  int from() const { return _from; }
  int totalDistance() const { return _totalDist; }

  void changeFrom(const int from) { _from = from; }
  void changeTotalDistance(const int totalDist) {_totalDist = totalDist; }
};

class Node{
private:
  int _vertex;
  int _distance;

public:
  Node(): _vertex(-1), _distance(-1) {} 
  Node(int vertex, int dist): _vertex(vertex), _distance(dist) {}

  int vertex() const { return _vertex; }
  int distance() const { return _distance; }

  bool operator>(const Node& other) const {
    return _distance < other._distance;
  }
  bool operator==(const Node& other) const {
    return _vertex == other._vertex;
  }
};

Path shortestPath(const Graph& g, int source, int dest) {
  
  // initial queue
  Heap<Node> queue;
  vector<Vertice> array;
  array.reserve(g.num_vertices());
  for(int i = 0; i < g.num_vertices(); i++){
    Vertice vertex(i);
    if(i == source){
      vertex.changeTotalDistance(0);
    }
    array[i] = vertex;
    Node node(i, vertex.totalDistance());
    queue.insert(node);
  }

  //dequeue source
  Node dequeued = queue.extractMax();
  int curr = source;

  while(curr != dest){
    // relax neighbors vertices
    const forward_list<GraphEdge>& adjList = g.edges_from(curr);
    for(const GraphEdge& edge: adjList){
      int oldDist = array[edge.dest()].totalDistance();
      int newDist = dequeued.distance() + edge.weight();

      if(newDist < oldDist){
        array[edge.dest()].changeFrom(curr);
        array[edge.dest()].changeTotalDistance(newDist);
        Node larger(edge.dest(), oldDist);
        Node smaller(edge.dest(), newDist);
        queue.changeKey(larger, smaller);
      }
    }

    if(queue.empty()){
      throw std::out_of_range("path does not exist");
    }
    dequeued = queue.extractMax();
    curr = dequeued.vertex();
  }

  if (array[dest].totalDistance() == INF) {
    throw std::out_of_range("path does not exist");
  }

  //dest to source
  vector<int> direction;
  curr = dest;
  int shortest = array[curr].from();
  while(curr != shortest){ //shortest way not itself
    direction.push_back(curr);
    curr = shortest;
    shortest = array[curr].from();
  }
  direction.push_back(curr);

  //reverse it so it passes
  int size = direction.size();
  for(int i = 0; i < size / 2; i++){
    int temp = direction[i];
    direction[i] = direction[size - i - 1];
    direction[size - i - 1] = temp;
  }

  return Path(array[dest].totalDistance(), direction);
}