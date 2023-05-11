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
string BreadthFirstSearch(int);
string DepthFirstSearch(int);
string TopologicalSort();
int InDegree(int);
void PrintGraph();
};

void Graph::AddVertice(int v1, int v2, int weight) {
  adjacency[v1];
  adjacency[v2];
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

string Graph::DepthFirstSearch(int st) {
  vector<int> visited;
  stack<int> s;
  string r = "";
  s.push(st);
  while (!s.empty()) {
    int u = s.top();
    s.pop();
    if (find(visited.begin(), visited.end(), u) == visited.end()) {
      visited.push_back(u);
      for (int i=0; i<adjacency[u].size(); i++) {
        if (find(visited.begin(), visited.end(), adjacency[u][i].first) == visited.end())
          s.push(adjacency[u][i].first);
      }
    }
  }

  for (int i=0; i<visited.size(); i++)
    r += to_string(visited[i]) + " ";
  return r;
}

string Graph::BreadthFirstSearch(int st) {
  vector<int> visited;
  queue<int> q;
  string r = "";
  visited.push_back(st);
  q.push(st);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i=0; i<adjacency[u].size(); i++) {
      if (find(visited.begin(), visited.end(), adjacency[u][i].first) == visited.end()) {
        visited.push_back(adjacency[u][i].first);
        q.push(adjacency[u][i].first);
      }
    }
  }
  for (int i=0; i<visited.size(); i++)
    r += to_string(visited[i]) + " ";
  return r;
}

int Graph::InDegree(int u) {
  int cnt = 0;
  vector<int> temp;
  for (map<int, vector<pair<int, int> > >::iterator iter=adjacency.begin(); iter!=adjacency.end(); iter++) {
    for (int i=0; i<adjacency[iter->first].size(); i++) {
      temp.push_back(adjacency[iter->first][i].first);
    }
  }
  cnt += count(temp.begin(), temp.end(), u);
  return cnt;
}

string Graph::TopologicalSort() {
  map<int, int> indegree;
  for (map<int, vector<pair<int, int> > >::iterator iter=adjacency.begin(); iter!=adjacency.end(); iter++) {
    indegree[iter->first] = Graph::InDegree(iter->first);
  }
  vector<int> t;
  queue<int> q;
  for (map<int, vector<pair<int, int> > >::iterator iter=adjacency.begin(); iter!=adjacency.end(); iter++) {
    if (indegree[iter->first] == 0)
      q.push(iter->first);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    t.push_back(u);
    for (vector<pair<int, int> >::iterator iter=adjacency[u].begin(); iter!=adjacency[u].end(); iter++) {
      indegree[iter->first]--;
      if (indegree[iter->first] == 0)
        q.push(iter->first);
    }
  }
  string r = "";
  for (int i=0; i<t.size(); i++)
    r += to_string(t[i]) + " ";
  return r;
}

void Graph::PrintGraph() {
  for (map<int, vector<pair<int, int> > >::iterator iter=adjacency.begin(); iter!=adjacency.end(); iter++) {
    string r = to_string(iter->first) + " -> ";
    for (vector<pair<int, int> >::iterator it=iter->second.begin(); it!=iter->second.end(); it++)
      r += "(" + to_string(it->first) + ", " + to_string(it->second) + ") -> ";
    r += "|";
    cout << r << endl;
  }
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

      case DFS:
        if (!(iss >> u)) {
          cerr<<"DFS: invalid input"<<endl;
          exit(1);
        }
        outFile << g.DepthFirstSearch(u) << endl;
        break;

      case BFS:
        if (!(iss >> u)) {
          cerr<<"BFS: invalid input"<<endl;
          exit(1);
        }
        outFile << g.BreadthFirstSearch(u) << endl;
        break;
      
      case TOPOLOGICAL_SORT:
        outFile << g.TopologicalSort() << endl;
        break;
      
      default:
        cerr<<"Undefined operator"<<endl;
        exit(1);
    }
  }
  g.PrintGraph();
  outFile.close();
  inFile.close();
}
