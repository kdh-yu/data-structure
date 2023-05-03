// Practice 10. Graph Representation
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <queue> // BFS
#include <sstream>
#include <stack> // DFS
#include <tuple>
#include <vector>
using namespace std;
const char CONSTRUCT = 'C';
const char IS_ADJACENT = 'I';
const char GET_NEIGHBORS = 'N';
const char BFS = 'B';
const char DFS = 'D';
const char REACHABLITY = 'R';
const char TOPOLOGICAL_SORT = 'T';
const char SHORTEST_PATH = 'S';

class Graph {
public:
int nodes;
vector<vector<int> > adjacency;
// TODO. Define a constructor, a destructor, and proper methods

void Construct(int);
void AddVertice(int, int, int);
string IsAdjacent(int, int);
string Neighbors(int);
void printGraph();
};

void Graph::Construct(int v) {
  adjacency.resize(v);
  for (int i=0; i<v; i++) {
    adjacency[i].resize(v);
    for (int j=0; j<v; j++)
      adjacency[i][j] = 0;
  }
  nodes = v;
}

void Graph::AddVertice(int v1, int v2, int weight) {
  adjacency[v1][v2] = weight;
}

string Graph::IsAdjacent(int v1, int v2) {
  if (adjacency[v1][v2] != 0)
    return "T";
  else
    return "F";
}

string Graph::Neighbors(int v) {
  string neighbors = "";
  for(int i=0; i<nodes; i++) {
    if (adjacency[v][i] != 0)
      neighbors += to_string(i) + " ";
  }
  return neighbors;
}

 
int main() {
  Graph g;
  ifstream inFile("input.txt");
  ofstream outFile("output.txt");
  string line;

  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int u, v, wgt, nVertices, nEdges, cnt;
    //vector<tuple<int, int, int>> data;
    vector<int> p, nbrs;
    switch(op)
    {
      case CONSTRUCT:
        if (!(iss >> nVertices >> nEdges)) {
          cerr<<"CONSTRUCT: invalid input"<<endl;
          exit(1);
        }
        // TODO. Construct a graph
        g.Construct(nEdges);
        for (int i=0; i<nEdges; i++) {
          getline(inFile, line);
          istringstream is_(line);
          is_ >> u >> v >> wgt;
          g.AddVertice(u, v, wgt);
        }
        break;

      case IS_ADJACENT:
        if (!(iss >> u >> v)) {
          cerr<<"isAdjacent: invalid input"<<endl;
          exit(1);
        }
        // TODO. Check if edge (u, v) exists in the graph
        outFile << u << " " << v << " " << g.IsAdjacent(u, v) << endl;
        break;

      case GET_NEIGHBORS:
        if (!(iss >> u)) {
          cerr<<"getNeighbors: invalid input"<<endl;
          exit(1);
        }
        // TODO. Get all the neighbors of u
        outFile << g.Neighbors(u) << endl;
        break;
        
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
