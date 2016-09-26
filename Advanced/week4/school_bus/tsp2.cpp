#include <stdio.h>
#include <iostream>

using namespace std; 

int queue[100], stack[100], alt[100], v[100];
int sp,head,tail,i,n,g,j,s,path,module,map[100][100];
int num_cities; 

void read_data() {
    int vertex_count, edge_count;
    
    std::cin >> vertex_count >> edge_count;
    num_cities = vertex_count; 
    // Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        map[from][to] = map[to][from] = weight;
    }

}


int main()
{
 /*  printf("Number of cities:");
  scanf( "%d",&n);
  printf("Max Segment:");
  scanf( "%d",&module);
  printf("Seed:");
  scanf( "%d",&g);
  srand(g); */
// Generating the sysmetric connection matrix randomly
 /* for (i=0   ; i<n ; i++) {
    for (j=i+1 ; j<n ; j++) {
       map[i][j]= rand() % (module+1);
       map[j][i]=map[i][j];
      } */
    read_data();
    n = num_cities; 
    for (i=0   ; i<n ; i++) {
        for (j=0 ; j<n ; j++) printf("%3d ",map[i][j]);
        printf("\n");
    }
  
//Start with an initial solution from city 1 
 for (i=0 ; i<n ; i++) {
    queue[i]=i;
  }
// Set route length to high value
   path=10000*n;
   stack[0]=queue[0];
   alt[0]=0;
   // printf("running...\n");
   sp=0;
   head=0;
   tail=n-1;
   s=0;
// Explore a branch of the factorial tree
   while(1) {    
      while(sp<n-1 && s<path)  {
          sp++;
          head++; if (head==n) head=0;
          stack[sp]=queue[head];
          s=s+map[stack[sp]][stack[sp-1]];
          alt[sp]=n-sp-1;
       }
// Save a better solution
      if (s+map[stack[sp]][stack[0]]<path) {
        path=s+map[stack[sp]][stack[0]];
        for (i=0 ; i<n ; i++) v[i]=stack[i]+1;
      }
// Leaving nodes when there is no more  branches 
      while (alt[sp]==0 && sp>=0) {
        tail++; if (tail==n) tail=0;
        queue[tail]=stack[sp];
        s=s-map[stack[sp]][stack[sp-1]];
        sp--;
      }
// If Bottom of stack is reached then stop
      if (sp<0) break;
      tail++; if (tail==n) tail=0;
      queue[tail]=stack[sp];
      s=s-map[stack[sp]][stack[sp-1]];
// Explore an alternate branch
      alt[sp]=alt[sp]-1;
      head++; if (head==n) head=0;
      stack[sp]=queue[head];
      s=s+map[stack[sp]][stack[sp-1]];
  }
  printf("%d\n",path);
  printf("%d ",stack[0]+1);
  for (i=n-1 ; i>0 ; i--) printf("%d ",v[i]);
  // printf("%d\n",stack[0]+1);
  return 0;
}