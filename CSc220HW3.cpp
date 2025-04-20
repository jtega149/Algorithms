#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>

#define TEMP_MAX 2000000000 

using namespace std;

class Points{
public:
    Points(int x_coord, int y_coord) {
        this->x_coord = x_coord;
        this->y_coord = y_coord;
    }
    void printCoords() const{
        cout << "(" << x_coord << ", " << y_coord << ")";
    }
    int x_coord;
    int y_coord;
};

double euclidean(const Points& a, const Points& b){
    return sqrt(pow(a.x_coord - b.x_coord, 2) + pow(a.y_coord - b.y_coord, 2));
}

void heldKarp(const vector<Points>& vertices){
    int N = vertices.size();
    if (N == 0) return;

    size_t end_set = (1 << N) - 1;
    vector<vector<double>> dist(N, vector<double>(N));

    // Build distance matrix
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++) {
            dist[i][j] = euclidean(vertices[i], vertices[j]);
        }
    }

    //dpTable to track costs and parent to track point from before
    unordered_map<int, vector<double>> dpTable;
    unordered_map<int, vector<int>> parent;

    dpTable[1] = vector<double>(N, TEMP_MAX);
    dpTable[1][0] = 0;

    for(int visitedSet = 1; visitedSet <= end_set; visitedSet++){
        if(!(visitedSet & 1)) continue; //visitedSet needs to include starting bit 1

        if(!dpTable.count(visitedSet)) dpTable[visitedSet] = vector<double>(N, TEMP_MAX);
        if(!parent.count(visitedSet)) parent[visitedSet] = vector<int>(N, -1);

        for(int u = 0; u < N; u++){
            if(!(visitedSet & (1 << u))) continue;

            for(int v = 0; v < N; v++){
                if(u == v || !(visitedSet & (1 << v))) continue;

                int prev_visitedSet = visitedSet ^ (1 << u); //Checking for previous visitedSet

                if(!dpTable.count(prev_visitedSet)) continue;

                double cost = dpTable[prev_visitedSet][v] + dist[v][u];
                if(cost < dpTable[visitedSet][u]){ //Setting the minimum cost
                    dpTable[visitedSet][u] = cost;
                    parent[visitedSet][u] = v;
                }
            }
        }
    }

    double min_cost = TEMP_MAX;
    int last = -1;
    for(int i = 1; i < N; i++){
        if(!dpTable.count(end_set)) break; //If not solution was found beforehand
        double cost = dpTable[end_set][i] + dist[i][0]; //Total cost of ending at a point i and returning to starting point 
        if(cost < min_cost){
            min_cost = cost;
            last = i;
        }
    }

    //Should not execute
    if(last == -1) {
        cout << "No valid path found!" << endl;
        return;
    }

    vector<int> shortestPath;
    int visitedSet = end_set;
    int current = last; //Backtracking from last point
    while(current != 0){ //Reconstruct the route
        shortestPath.push_back(current); 
        int prev = parent[visitedSet][current]; //Looking up point we came from to reach current
        visitedSet = visitedSet ^ (1 << current); //Removes current from the set
        current = prev;
    }
    shortestPath.push_back(0);
    reverse(shortestPath.begin(), shortestPath.end()); //Reversing the backwards list
    shortestPath.push_back(0);

    int pathSize = shortestPath.size();
    cout << "Optimal Path: ";
    for(size_t i = 0; i < pathSize; i++){
        vertices[shortestPath[i]].printCoords();
        if (i != pathSize - 1){
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Total optimal cost: " << min_cost << endl;
}


vector<Points> parseFile(char* filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        cout << "ERROR: Can't open file: " << filename << endl;
        exit(1);
    }
    vector<Points> pointsList;
    string line;
    while(getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        int x;
        int y;
        if(sscanf(line.c_str(), "(%d,%d)", &x, &y) == 2) {
            pointsList.push_back(Points(x, y));
            cout << "Read point: (" << x << "," << y << ")" << endl;
        }
    }
    if (pointsList.empty()) {
        cout << "WARNING: No valid points found in file." << endl;
    }
    return pointsList;
}


int main(int argc, char* argv[]){
    if(argc < 2){
        cout << "Enter file name as command-line argument as well." << endl;
        return 1;
    }
    else if(argc > 2){
        cout << "No need for extra arguments" << endl;
        return 1;
    }
    
    vector<Points> vertices = parseFile(argv[1]);
    if(vertices.empty()){
        cout << "No valid points." << endl;
        return 1;
    }
    heldKarp(vertices);
    return 0;
}