#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

vector<vector<bool>> makeEmpty(int nodes) {
    vector<vector<bool>> connections;
    for (int i = 0; i < nodes; i++) {
        vector<bool> row;
        for (int j = 0; j < nodes; j++) {
            row.push_back(false);
        }
        connections.push_back(row);
    }
    return connections;
}

void connect(vector<vector<bool>> &connections, int a, int b) {
    connections[a][b] = true;
    connections[b][a] = true;
}

string toGraphViz(vector<vector<bool>> &connections) {
    string out = "";
    for (int i = 0; i < connections.size(); i++) {
        for (int j = i + 1; j < connections.size(); j++) {
            if (connections[i][j]) {
                out = out + to_string(i) + "->" + to_string(j) + " [dir=none]\n";
            }
        }
    }
    return "digraph g{\n" + out + "}\n";
}

vector<vector<bool>> readGraph(string path) {
    ifstream in(path);
    int n;
    in >> n;
    vector<vector<bool>> out = makeEmpty(n);
    int a, b;
    while (in >> a >> b) {
        connect(out, a, b);
    }
    return out;
}

int main(int argc, char **argv) {
    string path = "test.txt";
    if (argc == 2)path = argv[1];
    auto g = readGraph(path);
    cout << toGraphViz(g);
    return 0;
}