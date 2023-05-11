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
#include <map>
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
map<int, vector<pair<int, int> > > adjacency;
// TODO. Define a constructor, a destructor, and proper methods

void AddVertice(int, int, int);
string IsAdjacent(int, int);
string Neighbors(int);
};

void Graph::AddVertice(int v1, int v2, int weight) {
  adjacency[v1].push_back(make_pair(v2, weight));
}

string Graph::IsAdjacent(int v1, int v2) {
  vector<pair<int, int> > from = adjacency[v1];
  for (vector<pair<int, int> >::iterator iter=from.begin(); iter!=from.end(); iter++) {
    if (iter->first == v2)
      return "T";
  }
  return "F";
}

string Graph::Neighbors(int v) {
  string neighbors = "";
  for (int i=0; i<adjacency[v].size(); i++)
    neighbors += to_string(adjacency[v][i].first) + " ";
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
