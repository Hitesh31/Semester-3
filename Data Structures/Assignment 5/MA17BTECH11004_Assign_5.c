#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
struct node 
{
  int vertex; //it stores vertex value
  struct list *head_list,*tail_list; //head and tail of adjacency list
};
struct list 
{
  int data; //value for edge
  struct list *next,*prev; 
};
struct indexnode //index list for vertices
{
  struct node *index;
};
struct queue //queue for bfs
{
  int value;
  struct queue *next,*prev;
};
struct store //node for 2D array that stores bfs once done
{
  int value;
  struct node *parent;
};
struct queue *front,*back;
int queuesize=0;
void enqueue(struct queue **f,struct queue **b,int a) //implementing queue using link list
{
  if((*f)==NULL)
  {
    struct queue *x=(struct queue*)malloc(sizeof(struct queue));
    x->value=a;
    x->next=NULL;
    x->prev=NULL;
    (*f)=x;
    (*b)=x;
    queuesize++;
  }
  else
  {
   struct queue *x=(struct queue*)malloc(sizeof(struct queue));
   x->value=a;
   x->next=NULL;
   x->prev=(*b);
   (*b)->next=x;
   (*b)=x;
   queuesize++;
  }
}
int dequeue() //dequeue function
{
  queuesize--;
  struct queue *x=front;
  int k=front->value;
  front=front->next;
  if(front!=NULL)front->prev=NULL;
  free(x);
  return k;
}
void insertlist(struct list **h,struct list **t,int k) //function that makes adjacency list using linked list
{
  if((*h)==NULL) //if head is null
  {
    struct list *x=(struct list*)malloc(sizeof(struct list));
    x->data=k; //allocate memory and make edge
    x->next=NULL;
    x->prev=NULL;
    (*h)=x;
    (*t)=x;
  }
  else 
  {
    struct list *x=(struct list*)malloc(sizeof(struct list));
    x->data=k;
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
    scanf("%d",&neighbour); 
    insertlist(&(*h),&(*t),neighbour); //make list of that vertex
  } 
}
bool search(int p,int q,int n,struct node **a)
{
  for(int i=0;i<n;i++)
  {
    if(a[i]->vertex==p) //search if vertex is there or not
      {
        struct list *t=a[i]->head_list;
        while(t!=NULL)
        {
          if(t->data==q) //search if edge exist and true if exist
          return true;
          t=t->next;
        }
      }
  }
  return false; //return false if edge is not present
}
void bfs(struct node **a,struct indexnode **index,int n,int s,struct store *arr[][n])
{
  bool b[n+1]; //assign boolean value for each vertex so,only 1 bit required
  for(int i=0;i<n+1;i++)
    {
      b[i]=false; //set all vertices unvisited
    }
  enqueue(&front,&back,s); //enqueue the vertex
  struct list *t;
  int m=1;
  while(queuesize!=0)
  {
    int k=dequeue(); //dequeue front
    b[k]=true; //set it visited
    if(index[k]!=NULL) t=index[k]->index->head_list; //enqueue all non visited reachable vertices 
    while(t!=NULL)
    {
      if(b[t->data]==false) 
      {
        b[t->data]=true;
        arr[m][s-1]->value=t->data;
        arr[m][s-1]->parent=index[k]->index;
        m++;
        enqueue(&front,&back,t->data);
      }
      t=t->next;
    }
  }
}
void path(struct node **a,struct indexnode **index,int n,int u,struct store *arr[][n],int v)
{
  bool ans=false;
  int b[n];
  for(int i=0;i<n;i++) b[i]=0;
       if(arr[1][u-1]->value==0)
        bfs(a,index,n,u,arr);
        for(int i=n-1;i>=0;i--)
        {
          if(arr[i][u-1]->value==v)
            {
              ans=true;
              b[i]=v;
              if(arr[i][u-1]->parent!=NULL)v=arr[i][u-1]->parent->vertex;
            }
        }
        if(ans==true)
        {
        for(int i=0;i<n;i++)
        if(b[i]!=0) printf("%d ",b[i]);
        }
        else printf("-1");
        printf("\n");
}
void freelist(struct node **a,int n) //free the adjacency list
{
  for(int i=0;i<n;i++)
    {
      struct list *t;
      while(a[i]->head_list!=NULL)
      {
        t=a[i]->head_list;
        a[i]->head_list=a[i]->head_list->next;
        free(t);
      }
      if(a[i]!=NULL)free(a[i]);
    }
}
void freeindexnode(struct indexnode **index,int n) //free index array for list
{
  for(int i=1;i<n+1;i++)
    if(index[i]!=NULL)free(index[i]);
}
void freestore(int n,struct store *arr[][n]) //free 2D array of stored bfs
{
  for(int i=0;i<n;i++)
  for(int j=0;j<n;j++)
  if(arr[i][j]!=NULL)free(arr[i][j]);
}
int n;
int main() 
{
 char digit;
 while((digit=fgetc(stdin))!=EOF)
 {
  if(digit=='N')
  {
    repeat:
    scanf("%d",&n);
    struct node *a[n]; //array of nodes or vertices
    struct indexnode *index[n+1];
    struct store *arr[n][n];
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
      {
        arr[i][j]=(struct store*)malloc(sizeof(struct store));
        arr[i][j]->value=0;
        arr[i][j]->parent=NULL;
      }
      for (int i=1;i<n+1;i++)
      {
        index[i]=(struct indexnode*)malloc(sizeof(struct indexnode));
        index[i]=NULL;
      }
    int l=0;
    char t;
    while((t=fgetc(stdin))!='N')
    {
     if(t=='E')
     {
       int vert;
       scanf("%d",&vert);
       if(l<n) 
       {
         arr[0][vert-1]->value=vert;
         struct node *x=(struct node*)malloc(sizeof(struct node));
         x->vertex=vert;
         a[l]=x;
         struct indexnode *y=(struct indexnode*)malloc(sizeof(struct indexnode));
         y->index=a[l];
         index[vert]=y;
         makelist(&a[l]->head_list,&a[l]->tail_list);
       }
       l++;
     }
     if(t=='?')
     {
      int u,v;
      scanf("%d",&u);
      scanf("%d",&v);
      bool k=search(u,v,n,a);
      if(k==true) printf("1\n");
      else printf("0\n");
     }
     if(t=='B')
     {
       int s;
       scanf("%d",&s);
       if(arr[1][s-1]->value==0) bfs(a,index,n,s,arr);
       for(int j=0;j<n;j++)
        if(arr[j][s-1]->value!=0)
          printf("%d ",arr[j][s-1]->value);
       printf("\n");
     }
     if(t=='P')
     {
       int u,v;
       scanf("%d",&u);
       scanf("%d",&v);
       path(a,index,n,u,arr,v);
     }
     if(t=='M')
     {
      for(int i=0;i<n;i++)
      {
        printf("%d\n",a[i]->vertex);
        struct list *t=a[i]->head_list;
        while(t!=NULL)
        {
          printf("%d ",t->data);
          t=t->next;
        }
        printf("\n");
      }
     }
     if(t=='I')
     {
       for(int i=1;i<n+1;i++)
       printf("%d ",index[i]->index->vertex);
       printf("\n");
     }
     if(t==EOF)
     {
      freelist(a,n);
      freeindexnode(index,n);
      freestore(n,arr);
      return 0;
     }
    }
    freelist(a,n);
    freeindexnode(index,n);
    freestore(n,arr);
    goto repeat;
   }
  }
}