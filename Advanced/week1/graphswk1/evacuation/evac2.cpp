/*
 * C++ Program to Implement The Edmonds-Karp Algorithm
 */
#include<cstdio>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include<iostream>

 
using namespace std; 
 
int capacities[10000][10000];
int flowPassed[10000][10000];
vector<int> graph[10000];
int parentsList[10000];       
int currentPathCapacity[10000];  
 
int bfs(int startNode, int endNode)
{
    memset(parentsList, -1, sizeof(parentsList));
    memset(currentPathCapacity, 0, sizeof(currentPathCapacity));
 
    queue<int> q;
    q.push(startNode);
 
    parentsList[startNode] = -2;
    currentPathCapacity[startNode] = 9999;
 
    while(!q.empty())
    {
        int currentNode = q.front();
        q.pop();
 
        for(int i=0; i<graph[currentNode].size(); i++)
        {
            int to = graph[currentNode][i];
            cout << " to " << to << " i " << i <<  " curr n " << currentNode << endl;
            if(parentsList[to] == -1)
            {
                cout << " cap " << capacities[currentNode][to] << " flow " << flowPassed[currentNode][to] << endl; 
                if(capacities[currentNode][to] - flowPassed[currentNode][to] > 0)
                { 
                    cout << " curr path cap " << currentPathCapacity[currentNode] << endl; 
                    parentsList[to] = currentNode;
                    currentPathCapacity[to] = min(currentPathCapacity[currentNode], 
                    capacities[currentNode][to] - flowPassed[currentNode][to]);
                    if(to == endNode)
                    {
                        cout <<  currentPathCapacity[endNode]  << " endNode " << endNode << endl;
                        return currentPathCapacity[endNode];
                    }
                    q.push(to);
                }
            }
        }
    }
    return 0;
}
 
int edmondsKarp(int startNode, int endNode)
{
    int maxFlow = 0;
      while(true)
    {
        int flow = bfs(startNode, endNode);
        if (flow == 0) 
        {
            break;
        }
        maxFlow += flow;
        int currentNode = endNode;
        while(currentNode != startNode)
        {
            cout << " curr node ek " << currentNode << endl; 
            int previousNode = parentsList[currentNode];
            flowPassed[previousNode][currentNode] += flow;
            flowPassed[currentNode][previousNode] -= flow;
            currentNode = previousNode;
        }
    }
    return maxFlow;
}



int main()
{
    
     std::ios_base::sync_with_stdio(false);

    
    int nodesCount, edgesCount;
    // cout<<"enter the number of nodes and edges\n";
    cin>>nodesCount>>edgesCount;
 
    int source = 1, sink = nodesCount;
    // cout<<"enter the source and sink\n";
    // cin>>source>>sink;
 
    for(int edge = 0; edge < edgesCount; edge++)
    {
        // cout<<"enter the start and end vertex alongwith capacity\n";
        int from, to, capacity;
        cin>>from>>to>>capacity;
 
        capacities[from][to] = capacity;
        graph[from].push_back(to);
 
        graph[to].push_back(from);
    }
 
    int maxFlow = edmondsKarp(source, sink);
 
    cout<<maxFlow<<endl;
 
}