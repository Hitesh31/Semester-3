#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
struct node 
{
  int vertex;
  struct list *headlist,*taillist;
};
struct list
{
  int edge;
  int weight;
  struct list *next,*prev;
};
struct heapnode
{
  int edge;
  int weight;
};
int n;
int heapsize;
void insertlist(struct list **h,struct list **t,int k,int w) //function that makes adjacency list using linked list
{
  if((*h)==NULL) //if head is null
  {
    struct list *x=(struct list*)malloc(sizeof(struct list));
    x->edge=k; //allocate memory and make edge
    x->weight=w;
    x->next=NULL;
    x->prev=NULL;
    (*h)=x;
    (*t)=x;
  }
  else 
  {
    struct list *x=(struct list*)malloc(sizeof(struct list));
    x->edge=k;
    x->weight=w;
    x->next=NULL;
    (*t)->next=x;
    x->prev=(*t);
    (*t)=x;
  }
}
void makelist(struct list **h,struct list **t) 
{
  char m;
  while((m=fgetc(stdin))!='\n')
  {
    int neighbour; //take edge input
    int weight;
    scanf("%d",&neighbour);
    scanf("%d",&weight); 
    insertlist(&(*h),&(*t),neighbour,weight); //make list of that vertex
  } 
}
int search(int p,int q,int n,struct node **a)
{
  for(int i=0;i<n;i++)
  {
    if(a[i]->vertex==p) //search if vertex is there or not
      {
        struct list *t=a[i]->headlist;
        while(t!=NULL)
        {
          if(t->edge==q) //search if edge exist and true if exist
          return t->weight;
          t=t->next;
        }
      }
  }
  return -1; //return false if edge is not present
}
void heapify(struct heapnode **heap,int i)
{
  int left=2*i;
  int right=2*i+1;
  int smallest;
  if(left<=heapsize && heap[left]->weight < heap[i]->weight)
    smallest=left;
  else smallest=i;
  if(right<=heapsize && heap[right]->weight<heap[smallest]->weight)
    smallest=right;
  if(smallest!=i)
  {
    struct heapnode *temp;
    temp=heap[i];
    heap[i]=heap[smallest];
    heap[smallest]=temp;
    heapify (heap,smallest);
  }
}
int extractmin(struct heapnode **heap)
{
  struct heapnode *temp;
  int min=heap[1]->edge;
  temp=heap[1];
  heap[1]=heap[heapsize];
  heap[heapsize]=temp;
  free(heap[heapsize]);
  heapsize--;
  heapify(heap,1);
  return min;
}
void decreasekey(struct heapnode **heap,int i,int weight)
{
  for(int j=1;j<=heapsize;j++) 
    { 
      if(heap[j]->edge==i)
      {
        i=j;
        break;
      }
    }
  heap[i]->weight=weight;
  while(i>1 && heap[i/2]->weight>heap[i]->weight)
  {
    struct heapnode *temp;
    temp=heap[i];
    heap[i]=heap[i/2];
    heap[i/2]=temp;
    i=i/2;
  }
}
void dijkstra(struct node **a,int u,int n,struct node *arr[][n+1],int dis[][n+1],int vert[][n+1])
{
  heapsize=n;
  int k=1;
  bool b[n+1];
  int dist[n+1];
  struct node *parent[n+1];
  struct heapnode *heap[n+1];
  dist[u]=0;
  dist[0]=INT_MAX;
  for(int i=1;i<=n;i++)
  {
    b[i]=false;
    if(i!=u) dist[i]=INT_MAX;
    heap[i]=(struct heapnode*)malloc(sizeof(struct heapnode));
    heap[i]->edge=i;
    heap[i]->weight=dist[i];
    parent[i]=NULL;
  }
  decreasekey(heap,u,dist[u]);
  while(heapsize!=0)
  {
    int m=extractmin(heap);
    b[m]=true;
    struct list *t;
    t=a[m-1]->headlist;
    while(t!=NULL)
    {
      if(dist[m]+t->weight < dist[t->edge] && dist[m]!=INT_MAX)
      {
        dist[t->edge]=dist[m]+t->weight;
        parent[t->edge]=parent[m];
        decreasekey(heap,t->edge,dist[t->edge]);
        parent[t->edge]=a[m-1];
      }
      t=t->next;
    }
    vert[k][u]=m;
    dis[k][u]=dist[m];
    arr[k][u]=parent[m];
    k++;
  }
}
void printdijkstra(int n,int u,struct node *arr[][n+1],int dis[][n+1],int vert[][n+1])
{
  for(int i=1;i<=n;i++)
  {
    if(dis[i][u]!=INT_MAX)
    printf("%d %d\n",vert[i][u],dis[i][u]);
    else
    printf("%d -1\n",vert[i][u]);
  }
}
void freelist(struct node **a,int n) //free the adjacency list
{
  for(int i=0;i<n;i++)
    {
      struct list *t;
      while(a[i]->headlist!=NULL)
      {
        t=a[i]->headlist;
        a[i]->headlist=a[i]->headlist->next;
        free(t);
      }
      if(a[i]!=NULL)free(a[i]);
    }
}
int main()
{
  char digit;
  while((digit=fgetc(stdin))!=EOF)
  {
    if(digit=='N')
    {
      repeat:
      scanf("%d",&n);
      struct node *a[n];
      bool computed[n+1];
      struct node *arr[n+1][n+1];
      int vert[n+1][n+1];
      int dis[n+1][n+1];
      for(int i=1;i<=n;i++) 
        computed[i]=false;
      for(int i=0;i<n;i++)
      {
        a[i]=(struct node*)malloc(sizeof(struct node));
        a[i]->vertex=i+1;
        a[i]->headlist=NULL;
        a[i]->taillist=NULL;
      }
      char t;
      while((t=fgetc(stdin))!='N')
      {
        if(t=='E')
        {
          int vertex;
          scanf("%d",&vertex);
          if(vertex<=n);
          {
            //printf("%d",a[vertex-1]->vertex);
            makelist(&a[vertex-1]->headlist,&a[vertex-1]->taillist);
          }
        }
        if(t=='?')
        {
          int u,v;
          scanf("%d",&u);
          scanf("%d",&v);
          int k=search(u,v,n,a);
          if(k!=-1) printf("%d\n",k);
          else 
          printf("-1\n");
        }
        if(t=='D')
        {
          int u;
          scanf("%d",&u);
          if(computed[u]==false)
          {
            dijkstra(a,u,n,arr,dis,vert);
            computed[u]=true;
          }
          printdijkstra(n,u,arr,dis,vert);
        }
        if(t=='P')
        {
          int u,v;
          scanf("%d",&u);
          scanf("%d",&v);
          int pathdist;
          int b[n+1];
          for(int i=1;i<=n;i++) b[i]=0;
          bool ans=false;
          if(computed[u]==false)
          {
            dijkstra(a,u,n,arr,dis,vert);
            computed[u]=true;
          }
          for(int i=n;i>=1;i--)
          {
            if(vert[i][u]==v)
            {
              if(ans==false && dis[i][u]!=INT_MAX) 
              {
                pathdist=dis[i][u];
                ans=true;
              }
              b[i]=v;
              if(arr[i][u]!=NULL)v=arr[i][u]->vertex;
            }
          }
          if(ans==true)
          {
            printf("%d ",pathdist);
            for(int i=1;i<=n;i++)
            if(b[i]!=0) printf("%d ",b[i]);
          }
          else printf("-1");
          printf("\n");
        }
        if(t=='M')
        {
          for(int i=0;i<n;i++)
          {
            printf("%d->",a[i]->vertex);
            struct list *t=a[i]->headlist;
            while(t!=NULL)
            {
              printf("%d %d ",t->edge,t->weight);
              t=t->next;
            }
            printf("\n");
          }
        }
        if(t==EOF)
        {
          freelist(a,n);
          return 0;
        }
      }
      freelist(a,n);
      goto repeat;
    }
  }
}