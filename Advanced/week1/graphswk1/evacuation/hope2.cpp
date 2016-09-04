//Name: Hy Truong Son
//School: Informatics, ELTE
//Date: Saturday, 2nd November, 2013

#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iterator>
#include <algorithm>

#define MaxN 1001
#define INF 1000000000

using namespace std;

int n, m, s, t, TotalFlow;
int c[MaxN][MaxN];
int f[MaxN][MaxN];
int trace[MaxN];

void input(){
	int i, u, v, w;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	memset(c, 0, sizeof(c));
	for (i = 1; i <= m; i++){
		scanf("%d%d%d", &u, &v, &w);
		c[u][v] = w;
		c[v][u] = w;
	}
}

void BFS(){
	int i, j;
	queue<int> q;
	memset(trace, 0, sizeof(trace));
	q.push(s);
	trace[s] = -1;
	while (!q.empty()){
		i = q.front();
		q.pop();
		for (j = 1; j <= n; j++)
			if ((trace[j] == 0) && (c[i][j] > f[i][j])){
				q.push(j);
				trace[j] = i;
				if (j == t) return;
			}
	}
}

void IncFlow(){
	int u, v, delta;
	delta = INF;
	v = t;
	while (v != s){
		u = trace[v];
		delta = min(delta, c[u][v] - f[u][v]);
		v = u;
	}
	v = t;
	while (v != s){
		u = trace[v];
		f[u][v] += delta;
		f[v][u] -= delta;
		v = u;
	}
	TotalFlow += delta;
}

void Ford_Fulkerson_Edmond_Karp(){
	memset(f, 0, sizeof(f));
	TotalFlow = 0;
	while (true){
		BFS();
		if (trace[t] == 0) break;
		IncFlow();
	}
	cout << TotalFlow << endl;
}

int main(){
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	input();
	Ford_Fulkerson_Edmond_Karp();
}