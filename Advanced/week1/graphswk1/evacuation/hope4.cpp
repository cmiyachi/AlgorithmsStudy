#include <iostream>
#include <queue>
#include <algorithm>
#include<cstdio>
#include<queue>
#include<cstring>
#include<vector>
#include <climits>

using namespace std;
const int msize = 10000;

int N, M; // 
int r[msize][msize]; //
int pre[msize]; // 
bool vis[msize]; // 


bool BFS(int s, int t)
{
    queue<int> que;
    memset(pre, -1, sizeof(pre));
    memset(vis, false, sizeof(vis));

    pre[s] = s;
    vis[s] = true;
    que.push(s);

    int p;
    while(!que.empty())
    {
        p = que.front();
        que.pop();
        for(int i=1; i<=M; ++i)
        {
            if(r[p][i]>0 && !vis[i])
            {
            pre[i] = p;
                vis[i] = true;
                if(i == t) 
                    return true;
                que.push(i);
            }
        }
    }
    return false;
}

int EK(int s, int t)
{
    int maxflow = 0, d;
    while(BFS(s, t))
    {
        d= INT_MAX;
      
        for(int i=t; i!=s; i=pre[i])
        d = min(d, r[pre[i]][i]);
     
        for(int i=t; i!=s; i=pre[i])
        {
            r[pre[i]][i] -= d;
            r[i][pre[i]] += d;
        }
        maxflow += d;
    }
    return maxflow;
}

int main()
{
    cin >> N >> M; 
    {
        memset(r, 0, sizeof(r));
        int s, e, c;
        
            
        for(int i=0; i<M; ++i)
        {
            cin >> s >> e >> c;
            r[s][e] += c; 
        }

        if (M == 1)
            cout << c; 
        else 
            cout << EK(1, N) << endl;
    }
    return 0;
}