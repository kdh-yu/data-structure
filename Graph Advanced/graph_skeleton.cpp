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
// TODO. Define a constructor, a destructor, and proper methods

};
 
int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr<<"Correct usage: [exe] [input] [output]"<<endl;
    exit(1);
  }
  Graph g;
  ifstream inFile(argv[1]);
  ofstream outFile(argv[2]);
  string line;
  while (getline(inFile, line))
  {
    char op = line[0];
    istringstream iss(line.substr(1));
    int u, v, wgt, nVertices, nEdges, cnt;
    vector<tuple<int, int, int>> data;
    vector<int> p, nbrs;
    switch(op)
    {
      case CONSTRUCT:
        if (!(iss >> nVertices >> nEdges)) {
          cerr<<"CONSTRUCT: invalid input"<<endl;
          exit(1);
        }
        // TODO. Construct a graph
        break;
      case IS_ADJACENT:
        if (!(iss >> u >> v)) {
          cerr<<"isAdjacent: invalid input"<<endl;
          exit(1);
        }
        // TODO. Check if edge (u, v) exists in the graph
        break;
      case GET_NEIGHBORS:
        if (!(iss >> u)) {
          cerr<<"getNeighbors: invalid input"<<endl;
          exit(1);
        }
        // TODO. Get all the neighbors of u
        break;
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  outFile.close();
  inFile.close();
}
