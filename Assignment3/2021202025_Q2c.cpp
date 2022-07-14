#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

template <typename T>
void pop_front(std::vector<T> &vec)
{
    if (!vec.empty())
    {
        vec.erase(vec.begin());
    }
}

class PriorityHeap
{
public:
    vector<pair<int, int>> nodes;
    int leaf;

    PriorityHeap()
    {
        leaf = 1;
        nodes.push_back({0, 0});
    }

    void push(int weight, int dest)
    {
        int temp = leaf;
        if (nodes.size() > temp)
        {
            nodes[temp] = make_pair(weight, dest);
        }
        else
        {
            nodes.push_back({weight, dest});
        }

        while (temp > 1)
        {
            if (nodes[temp / 2].first > nodes[temp].first)
            {
                swap(nodes[temp / 2], nodes[temp]);
                temp = temp / 2;
            }
            else
            {
                break;
            }
        }

        leaf += 1;
    }

    void heapify()
    {

        nodes[1] = nodes[leaf - 1];
        int parentValue = nodes[1].first;

        int it = 1;
        while ((it * 2) + 1 <= leaf - 1)
        {

            if (parentValue > nodes[it * 2].first || parentValue > nodes[it * 2 + 1].first)
            {

                if (nodes[it * 2].first > nodes[it * 2 + 1].first)
                {

                    swap(nodes[it], nodes[it * 2 + 1]);
                    it = it * 2 + 1;
                    continue;
                }

                else
                {
                    swap(nodes[it], nodes[it * 2]);
                    it = it * 2;
                    continue;
                }
            }

            break;
        }

        if (leaf - 1 >= it * 2)
        {
            if (nodes[it * 2].first < nodes[it].first)
            {
                swap(nodes[it], nodes[it * 2]);
            }
        }

        leaf--;
    }

    int pop()
    {
        int smallest = nodes[1].second;
        //taking the last leaf, replacing with root
        heapify();

        return smallest;
    }

    bool isempty()
    {
        if (leaf <= 1)
            return true;
        return false;
    }
};

void addEdge(vector<vector<pair<int, int>>> &adj, int u, int v, int wt)
{
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
    // cout << adj[u][0].second << endl;
    // cout << adj[v][0].second << endl;
}

// Print adjacency list representation ot graph
void printGraph(vector<vector<pair<int, int>>> adj, int V)
{
    int v, w;
    for (int u = 0; u < V; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it != adj[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
        cout << "\n";
        // cout << adj[u].size() << endl;

        // for(int i = 0; i<adj[u].size())
    }
}

class dijkstra
{
public:
    vector<int> visited;
    vector<int> nodeWeight;
    vector<int> parent;
    vector<int> distance;

    PriorityHeap heap;
    bool calculated;
    int vertices;
    //public:
    dijkstra(int v)
    {

        visited.resize(v + 1, 0);
        nodeWeight.resize(v + 1, INT_MAX);
        parent.resize(v + 1, INT_MAX);
        distance.resize(v + 1, INT_MAX);

        vertices = v;
    }

    int dijkstraPath(vector<vector<pair<int, int>>> graph, int first_node, vector<pair<int, int>> &kShortest, vector<pair<int, string>> &paths)
    {
        nodeWeight[first_node] = 0;
        heap.push(first_node, first_node);

        distance[first_node] = 0;

        while (heap.isempty() == false)
        {
            int currentVertex = heap.pop();
            int disSoFar = nodeWeight[currentVertex];

            // cout << currentVertex << endl;

            for (auto it = graph[currentVertex].begin(); it != graph[currentVertex].end(); it++)
            {
                int new_vertex = it->first;
                int new_weight = it->second;

                // cout << new_vertex << " " << new_weight << endl;

                if (visited[new_vertex] == 0)
                {
                    heap.push(new_weight, new_vertex);

                    if ((new_weight + disSoFar) == nodeWeight[new_vertex])
                    {
                        string s1 = to_string(parent[new_vertex]);
                        string s2 = to_string(currentVertex);

                        //find current parent of 2
                        //find parent of 2 after updation
                        //string compare which is shorter current parent or existing parent (lexico)
                        //whichever is shorter will be the parent

                        if (s1 > s2)
                        {
                            // cout << "******************" << endl;
                            // cout << new_vertex << " " << currentVertex << endl;
                            // cout << "******************" << endl;
                            parent[new_vertex] = currentVertex;
                            nodeWeight[new_vertex] = new_weight + disSoFar;
                        }
                    }

                    else if ((new_weight + disSoFar) < nodeWeight[new_vertex])
                    {
                        parent[new_vertex] = currentVertex;
                        nodeWeight[new_vertex] = new_weight + disSoFar;
                    }

                    // weight[new_vertex] = min(weight[new_vertex], new_weight + disSoFar);
                }
            }

            visited[currentVertex] = 1;
            // if (currentVertex == end_node) {
            //     calculated = true;
            //     return weight[end_node];
            // }
        }

        for (int i = 0; i < vertices; i++)
        {
            if (i != first_node)
            {
                kShortest.push_back(make_pair(i, nodeWeight[i]));
                // cout << "Node " << i << " Distance from source is: " << nodeWeight[i] << endl;
            }
        }

        return INT_MAX;
    }
    //to return the actual shortest path taken in reverse
    void reversePath(vector<int> &act_path, int source, int destination)
    {

        // cout << "------------------------------------" << endl;
        // for (auto p : parent) {
        //     cout << p << " ";
        // }
        // cout << endl;
        // cout << "------------------------------------" << endl;

        act_path.push_back(destination);
        while (destination != source)
        {
            act_path.push_back(parent[destination]);
            destination = parent[destination];
        }
    }

    void stringreversePath(vector<string> &act_path, int source, int destination)
    {
        act_path.push_back(to_string(destination));
        while (destination != source)
        {
            act_path.push_back(to_string(parent[destination]));
            destination = parent[destination];
        }
    }
};

bool comparefn(pair<int, string> a, pair<int, string> b)
{
    if (a.first < b.first)
        return 1;
    else if (a.first == b.first)
    {
        return a.second < b.second;
    }
    else
    {
        return 0;
    }
}

class gridNode
{
public:
    int r;
    int c;
    int distance;
    gridNode(int a, int b, int d)
    {
        r = a;
        c = b;
        distance = d;
    }
};

int shortestPathBFS(vector<vector<char>> &grid, vector<vector<bool>> &visited, gridNode src, vector<vector<int>> &bfsGrid)
{
    vector<gridNode> que;

    que.push_back(src);

    while (!que.empty())
    {
        gridNode temp = que.front();
        pop_front(que);

        if (grid[temp.r][temp.c] == 'd')
        {
            return temp.distance;
        }

        int currRow = temp.r;
        int currCol = temp.c;
        int nextRow = temp.r + 1;
        int nextCol = temp.c + 1;
        int prevRow = temp.r - 1;
        int prevCol = temp.c - 1;
        int m = grid.size();
        int n = grid[0].size();

        if (nextCol < n - 1)
        {
            if (!visited[currRow][nextCol])
            {
                gridNode newNode = gridNode(currRow, nextCol, temp.distance + 1);
                que.push_back(newNode);
                bfsGrid[currRow][nextCol] = temp.distance + 1;
                visited[currRow][nextCol] = true;
            }
        }

        if (prevCol >= 0)
        {
            if (!visited[currRow][prevCol])
            {
                gridNode newNode = gridNode(currRow, prevCol, temp.distance + 1);
                que.push_back(newNode);
                bfsGrid[currRow][prevCol] = temp.distance + 1;
                visited[currRow][prevCol] = true;
            }
        }

        if (nextRow < m - 1)
        {
            if (!visited[nextRow][currCol])
            {
                gridNode newNode = gridNode(nextRow, currCol, temp.distance + 1);
                que.push_back(newNode);
                bfsGrid[nextRow][currCol] = temp.distance + 1;
                visited[nextRow][currCol] = true;
            }
        }

        if (prevRow >= 0)
        {
            if (!visited[prevRow][currCol])
            {
                gridNode newNode = gridNode(prevRow, currCol, temp.distance + 1);
                que.push_back(newNode);
                bfsGrid[prevRow][currCol] = temp.distance + 1;
                visited[prevRow][currCol] = true;
            }
        }
    }

    return -1;
}

void shortestPathGrid()
{
    // vector<vector<char>> grid = {
    //     { '#', '#', '#', '#', '#', '#', '#', '#' },
    //     { '.', '.', '.', '.', '.', '.', '.', '#' },
    //     { '#', '#', '#', '#', '#', '.', '.', '#' },
    //     { '#', '.', '#', '.', '#', '.', '.', '#' },
    //     { '#', 'R', '#', '.', '.', '.', '.', '#' },
    //     { '#', '.', '.', '.', '.', 'R', '.', '#' },
    //     { '#', '.', '.', '.', 'R', '.', 'A', '#' },
    //     { '#', '#', '#', '#', '#', '#', '#', '#' }
    // };

    // vector<vector<char>> grid = {
    //     {'#', '#', '#', '#'},
    //     {'.', '.', '.', '#'},
    //     {'#', '.', 'A', '#'},
    //     {'#', '#', '#', '#'}
    // };

    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m, '.'));
    vector<string> tempGrid(n);

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        tempGrid[i] = s;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            grid[i][j] = tempGrid[i][j];
        }
    }

    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size()));
    vector<vector<int>> bfsGrid(grid.size(), vector<int>(grid[0].size(), 0));

    gridNode src(1, 0, 0);
    // grid[1][0] = 0;

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {

            // if (grid[i][j] == 'A')
            // {
            //     src.r = i;
            //     src.c = j;
            // }

            if (grid[i][j] == '#')
                visited[i][j] = true;
            else
                visited[i][j] = false;
        }
    }

    visited[1][0] = true;
    shortestPathBFS(grid, visited, src, bfsGrid);

    int minDistanceRider = INT_MAX;
    for (int i = 0; i < bfsGrid.size(); i++)
    {
        for (int j = 0; j < bfsGrid[0].size(); j++)
        {
            if (grid[i][j] == 'R')
            {
                if (bfsGrid[i][j] == 0)
                {
                    continue;
                }
                minDistanceRider = min(minDistanceRider, bfsGrid[i][j]);
            }
        }
    }

    // cout << bfsGrid[grid.size() - 2][grid[0].size() - 2] << " " << minDistanceRider << endl;
    if (bfsGrid[grid.size() - 2][grid[0].size() - 2] == 0)
    {
        cout << "No" << endl;
        return;
    }

    if (bfsGrid[grid.size() - 2][grid[0].size() - 2] <= minDistanceRider)
    {
        cout << "Yes" << endl;
        cout << bfsGrid[grid.size() - 2][grid[0].size() - 2] << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    // for (int i = 0; i < bfsGrid.size(); i++) {
    //     for (int j = 0; j < bfsGrid[0].size(); j++) {
    //         cout << bfsGrid[i][j] << "\t";
    //     }
    //     cout << endl;
    // }
}

void dfs(vector<vector<pair<int, int>>> &graph, vector<vector<int>> &result, vector<int> &path, int u, int v, vector<bool> &visited, vector<int> &distances, int &distance)
{
    path.push_back(u);
    int toRemove = 0;
    visited[u] = true;
    if (u == v)
    {
        result.push_back(path);
        distances.push_back(distance);
        // distance = 0;
    }
    else
        // for (auto v : graph[u]) {
        //     cout << "-----" << endl;
        //     cout << v.first << endl;
        //     dfs(graph, result, path, v.first);
        // }
        for (auto it = graph[u].begin(); it != graph[u].end(); it++)
        {
            // cout << it->first << endl;
            if (!visited[it->first])
            {
                distance += it->second;
                toRemove = it->second;
                // cout << "-------" << endl;
                // cout << u << " " << it->first << " " << it->second << " | " << distance << endl;
                dfs(graph, result, path, it->first, v, visited, distances, distance);
                distance -= toRemove;

                // distance -= it->second;
            }
        }

    path.pop_back();
    visited[u] = false;
}

vector<vector<int>> allPathsSourceTarget(vector<vector<pair<int, int>>> &graph, vector<int> &distances, int src, int dest)
{
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> visited(graph.size(), false);

    int distance = 0;

    dfs(graph, result, path, src, dest, visited, distances, distance);

    // vector<vector<pair<int, int>>> ans;

    return result;
}

// Driver code
int main()
{
    // int V = 9;
    // // vector<pair<int, int> > adj[V];
    // vector <vector<pair<int, int>>> adj(V);
    // for (int i = 0; i < V; i++)
    // {
    //     vector<pair<int, int>> v;
    //     adj.push_back(v);
    // }
    // adj[0].push_back(make_pair(1, 10));
    // cout << adj[0][0].second << endl;

    // addEdge(adj, 0, 1, 10);
    // addEdge(adj, 0, 4, 20);
    // addEdge(adj, 0, 2, 40);
    // addEdge(adj, 1, 2, 30);
    // addEdge(adj, 1, 3, 40);
    // addEdge(adj, 1, 4, 50);
    // addEdge(adj, 2, 3, 60);
    // addEdge(adj, 3, 4, 70);
    // printGraph(adj, V);

    // int V, M;
    // cin >> V >> M;

    // vector <vector<pair<int, int>>> adj(V);

    // for (int i = 0; i < M; i++) {
    //     int a, b, c;
    //     cin >> a >> b >> c;
    //     addEdge(adj, a, b, c);
    // }

    // addEdge(adj, 0, 1, 4);
    // addEdge(adj, 0, 7, 8);
    // addEdge(adj, 1, 2, 8);
    // addEdge(adj, 1, 7, 11);
    // addEdge(adj, 2, 3, 7);
    // addEdge(adj, 2, 8, 2);
    // addEdge(adj, 2, 5, 4);
    // addEdge(adj, 3, 4, 9);
    // addEdge(adj, 3, 5, 14);
    // addEdge(adj, 4, 5, 12);
    // addEdge(adj, 5, 6, 2);
    // addEdge(adj, 6, 7, 8);
    // addEdge(adj, 6, 8, 6);
    // addEdge(adj, 7, 8, 2);
    // printGraph(adj, V);

    // vector <pair<int, string>> paths(V);

    // // cout << "---------------------------------------------------" << endl;
    // // for (auto p : paths) {
    // //     cout << p.second << endl;
    // // }

    // int source;
    // cin >> source;

    // dijkstra d(V);

    // vector<pair<int, int>> kShortest;

    // d.dijkstraPath(adj, source, kShortest, paths);

    // // for (auto i : kShortest) {
    // //     cout << i.first << " " << i.second << endl;
    // // }
    // // cout << endl;

    // // cout << "------------------------" << endl;
    // // cout << .kShortestsize() << endl;

    // // vector<pair<int, string>> kShortestPaths;
    // // d.shortest_path(path, 2, 2);
    // // for (int i = 0; i < path.size(); i++)
    // //     cout << path[i] << " ";
    // vector<string> shortestPaths;

    // for (int i = 0; i < V; i++) {
    //     if (i == source) continue;
    //     vector<int> path;
    //     d.reversePath(path, source, i);
    //     string sPath = "";
    //     for (int i = 0; i < path.size(); i++) {
    //         cout << path[i] << " ";
    //         sPath += to_string(path[i]);
    //     }
    //     shortestPaths.push_back(sPath);
    //     cout << endl;
    // }

    // vector<pair<int, string>> finalShortestPaths;

    // for (int i = 0; i < kShortest.size(); i++) {
    //     finalShortestPaths.push_back(make_pair(kShortest[i].second, shortestPaths[i]));
    // }

    // cout << endl;
    // for (auto p : finalShortestPaths) {
    //     cout << p.first << " " << p.second << endl;
    // }

    // sort(finalShortestPaths.begin(), finalShortestPaths.end(), comparefn);

    // cout << endl;
    // int k = 2;
    // for (int i = 0; i < k; i++) {
    //     auto p = finalShortestPaths[i];
    //     for (int i = 0; i < p.second.size(); i++) {
    //         cout << p.second[i] << " ";
    //     }
    //     cout << endl;
    //     // cout << p.first << " " << p.second << endl;
    // }

    // cout << "shortest distance =" << d.shortest_path(adj, 1, 2);
    // cout << endl << endl;
    // vector<vector<int>> graph = { {1, 2}, {3}, {3}, {} };
    // auto ans = allPathsSourceTarget(graph);

    // for ()
    // int src = 2;
    // int dest = 3;

    // vector<int> distances;
    // auto ans = allPathsSourceTarget(adj, distances, src, dest);

    // int distancePrint = 0;
    // for (auto a : ans) {
    //     for (auto b : a) {
    //         // cout << b << " " << distances[distancePrint] << endl;
    //         cout << b << " ";
    //     }
    //     cout << distances[distancePrint];
    //     cout << endl;
    //     distancePrint++;
    // }
    // int k;
    // cin >> k;

    // vector<pair<int, string>> finalKShortestPaths;

    // for (int i = 0; i < V; i++) {
    //     for (int j = i + 1; j < V; j++) {
    //         if (i != j) {

    //             vector<int> distances;
    //             auto ans = allPathsSourceTarget(adj, distances, i, j);

    //             int distancePrint = 0;
    //             for (auto a : ans) {
    //                 string s = "";
    //                 for (auto b : a) {
    //                     // cout << b << " " << distances[distancePrint] << endl;
    //                     // cout << b << " ";
    //                     s += to_string(b);
    //                 }
    //                 // cout << distances[distancePrint];
    //                 finalKShortestPaths.push_back(make_pair(distances[distancePrint], s));
    //                 // cout << endl;
    //                 distancePrint++;
    //             }
    //         }
    //     }
    // }

    // sort(finalKShortestPaths.begin(), finalKShortestPaths.end(), comparefn);

    // // for (auto pk : finalKShortestPaths) {
    // // cout << pk.first << " " << pk.second << endl;
    // for (int i = 0; i < k; i ++) {
    //     for (int j = 0; j < finalKShortestPaths[i].second.size(); j++) {
    //         cout << finalKShortestPaths[i].second[j] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << endl << endl;

    shortestPathGrid();

    // min_heap heap;
    // heap.push(10, 1);
    // heap.push(20, 4);
    // heap.push(30, 2);
    // heap.push(40, 3);

    // cout << heap.pop() << endl;
    // cout << heap.pop() << endl;

    return 0;
}