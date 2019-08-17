#include <stdio.h>
#include <stdlib.h>
struct node 
{
  long int data;
  struct node *left,*right,*parent;
  char color;
};
struct node *root;
struct node *NIL;
struct node *getnode(struct node *p,long int key)
{
  //iterative search to get node
 while(p!=NULL && p!=NIL )
  {
    if((p)->data>key)
      (p)=(p)->left;
    else if((p)->data<key)
      (p)=(p)->right;
    else if((p)->data==key)
      break;
  }
  return p; 
}
void preorder(struct node **p)
{
  if((*p)==NIL)
    return;
  printf("%ld ",(*p)->data);
  preorder(&(*p)->left);
  preorder(&(*p)->right);
}
void path (struct node **p,long int key)
{
  //if key exist print path recursively
  if((*p)->data>key)
       {
         printf("0");
         path(&(*p)->left,key);
       }
  if((*p)->data<key)
      {
         printf("1");
         path(&(*p)->right,key);
      }
  if((*p)->data==key)
      return;
}
void leftrotate(struct node **r,struct node **p)
{
  struct node *y=((*p)->right); //y=right of ptr
  if(y!=NULL && y!=NIL)
  {
    (*p)->right=y->left; //y's left subtree is now p's right subtree
    if(y->left!=NIL)
      y->left->parent=(*p);
    y->parent=(*p)->parent; //p's parent is now of y
    if ((*p)->parent == NIL) 
        (*r) = y; 
    else if ((*p)==(*p)->parent->left) 
        (*p)->parent->left = y; 
    else
        (*p)->parent->right = y;
    y->left = (*p); //x is y's left
    (*p)->parent = y;
  }
}
void rightrotate(struct node **r,struct node **p)
{
  struct node *y=((*p)->left); //y=left of ptr
  //rest same as leftrotate only pointers changed
  if(y!=NULL && y!=NIL)
  {
    (*p)->left=y->right;
    if(y->right!=NIL)
      y->right->parent=(*p);
    y->parent=(*p)->parent;
    if ((*p)->parent == NIL) 
        (*r) = y; 
    else if ((*p)==(*p)->parent->right) 
        (*p)->parent->right = y; 
    else
        (*p)->parent->left = y; 
    y->right = (*p); 
    (*p)->parent = y;
  }  
}
struct node *predecessor(struct node *k)
{
  struct node *temp=k->left;
  while(temp->right!=NIL)
  {
    temp=temp->right;
  }
  return temp;
}
void deletefix(struct node *x)
{
  while(x!=root && x->color=='B')
  {
    if(x==x->parent->left)
    {
      struct node *w=x->parent->right;
      if(w->color=='R')
      {
        w->color='B';
        x->parent->color='R';
        struct node *joint=x->parent;
        leftrotate(&root,&joint);
        w=x->parent->right;
      }
      if(w->left->color=='B' && w->right->color=='B')
      {
        w->color='R';
        x=x->parent;
      }
      else 
      {
        if(w->right->color=='B')
        {
          w->left->color='B';
          w->color='R';
          struct node *joint=w;
          rightrotate(&root, &joint);
          w=x->parent->right;
        }
        w->color=x->parent->color;
        x->parent->color='B';
        w->right->color='B';
        struct node *joint=x->parent;
        leftrotate(&root,&joint);
        x=root;
      }
    }
    else
    {
      struct node *w=x->parent->left;
      if(w->color=='R')
      {
        w->color='B';
        x->parent->color='R';
        struct node *joint=x->parent;
        rightrotate(&root,&joint);
        w=x->parent->left;
      }
      if(w->right->color=='B' && w->left->color=='B')
      {
        w->color='R';
        x=x->parent;
      }
      else 
      {
        if(w->left->color=='B')
        {
          w->right->color='B';
          w->color='R';
          struct node *joint=w;
          leftrotate(&root,&joint);
          w=x->parent->left;
        }
        w->color=x->parent->color;
        x->parent->color='B';
        w->left->color='B';
        struct node *joint=x->parent;
        rightrotate(&root,&joint);
        x=root;
      }
    }
  }
  x->color='B';
}
void transplant(struct node *u,struct node *v)
{
  if(u->parent==NIL)
  root=v;
  else if(u==u->parent->left)
  u->parent->left=v;
  else u->parent->right=v;
  v->parent=u->parent;
}
void deletenode(struct node *z)
{
  struct node *y=z;
  char ogy=y->color;
  struct node *x=NIL;
  if(z->left==NIL)
  {
    x=z->right;
    transplant(z,z->right);
  }
  else if(z->right==NIL)
  {
    x=z->left;
    transplant(z,z->left);
  }
  else 
  {
    y=predecessor(z);
    ogy=y->color;
    x=y->left;
    if(y->parent==z)
      x->parent=y;
    else 
    {
      transplant(y,y->left);
      y->left=z->left;
      y->left->parent=y;
    }
    transplant(z,y);
    y->right=z->right;
    y->right->parent=y;
    y->color=z->color;
  }
  free(z);
  if(ogy=='B')
  deletefix(x);
}
void fixinsert(struct node *b)
{
  struct node *x=b;
  while(x!=root && x->parent->color=='R')
  {
    if(x->parent==x->parent->parent->left)
    {
      struct node *y=x->parent->parent->right;
      if(y!=NIL && (y)->color=='R')
      { 
        x->parent->color='B';
        (y)->color='B';
        x->parent->parent->color='R';
        x=x->parent->parent;
      }
      else 
      {
        if(x==x->parent->right)
        {
          x=x->parent;
          struct node *joint=x;
          leftrotate(&root,&joint);
        }
        x->parent->color='B';
        x->parent->parent->color='R';
        struct node *joint=x->parent->parent;
        rightrotate(&root,&joint);
      }
    }
    else 
    {
      struct node *y=x->parent->parent->left;
      if(y!=NIL && (y)->color=='R')
      { 
        x->parent->color='B';
        (y)->color='B';
        x->parent->parent->color='R';
        x=x->parent->parent;
      }
      else 
      { 
        if(x==x->parent->left)
        {
          x=x->parent;
          struct node *joint=x;
          rightrotate(&root,&joint);
        }
        x->parent->color='B';
        x->parent->parent->color='R';
        struct node *joint=x->parent->parent;
        leftrotate(&root,&joint);
      }
    }
  }
  root->color='B';
}
void insert (long int key)
{
  struct node *p=root;
  struct node *y=NIL;
  while(p!=NULL && p!=NIL)
  {
    y=p;
    if((p)->data>key)
      (p)=(p)->left;
    else if((p)->data<key)
      (p)=(p)->right;
  }
  struct node *o;
  struct node *k=y;
  o=(struct node*)malloc(sizeof(struct node));
  o->data=key;
  o->left=NIL;
  o->right=NIL;
  o->color='R';
  o->parent=NIL;
  if(root==NIL) 
  {
    root=o;
  }
  else if(key<y->data)
  {
    k->left=o;
    o->parent=k;
  }
  else 
  {
    k->right=o;
    o->parent=k;
  }
  struct node *g=o;
  fixinsert(g);
}
struct node* successor(struct node *p,long int key)
{
  struct node *y;
  while(p!=NIL)
  {
    y=p;
    if((p)->data>key)
      (p)=(p)->left;
    else if((p)->data<key)
      (p)=(p)->right;
    else if((p)->data==key)
      break;
  }
  if(p==NIL)
  {
    //if key is not present in the tree
    if(y->data>key) return y;
    else
    return successor(root,y->data);
  }

  else
  {
    //if key is present
    //now,if node->right is not null
    if((p)->right!=NIL)
     {
       struct node *temp=(p)->right;
       while(temp->left!=NIL)
          temp=temp->left;
       return temp;
     }
    //if there is node->right is null then successor is in ancestors 
     if(p==root) 
          return NIL;
    struct node *n=(p);
    struct node *t = n->parent; 
    while(t!= NIL && n == t->right) 
    { 
       n = t; 
       t = t->parent; 
    } 
    return t; 
  }
  return p;
}
void deleterbtree(struct node *p)  
{ 
    if (p==NULL || p == NIL) return; 
    // first delete left subtree 
    deleterbtree(p->left);
    //then delete right subtree 
    deleterbtree(p->right);
    // then delete the node 
    free(p); 
}
int main() 
{
  char t;
  while((t=fgetc(stdin))!=EOF)
  {
    if(t=='N')
    {
      NIL=(struct node *)malloc(sizeof(struct node));
      NIL->parent=NULL;
      NIL->data=-1;
      NIL->color='B';
      NIL->left=NULL;
      NIL->right=NULL;
      deleterbtree(root);
      root=NIL; 
      char m;
      long int num;
      while((m=fgetc(stdin))!='\n')
      {
        scanf("%ld",&num);
        struct node *z=getnode(root,num);
        if(z==NIL || z==NULL)
        insert(num);
      }
    }
    if(t=='+')
    {
      long int num;
      scanf("%ld",&num);
      struct node *z=getnode(root,num);
      if(z==NIL || z==NULL)
      insert(num);
    }
    if(t=='P')
    {
      preorder(&root);
      printf("\n");
    }
    if(t=='C')
    {
      long int num;
      scanf("%ld",&num);
      struct node *child_parent=getnode(root,num);
      if(child_parent==NIL) printf("-1\n");
      else 
      {
        if(child_parent->left==NIL) printf("L B");
        else printf("%ld %c",child_parent->left->data,child_parent->left->color);
        if(child_parent->right==NIL) printf(" L B\n");
        else printf(" %ld %c\n",child_parent->right->data,child_parent->right->color);
      }
    }
    if(t=='M')
    { //prints parent of a node
      long int no;
      scanf("%ld",&no);
      struct node *ch=getnode(root,no);
      if(ch!=NIL && ch->parent!=NIL) printf("%ld\n",ch->parent->data);
      else printf("-1\n");
    }
    if(t=='-')
    {
      long int num;
      scanf("%ld",&num);
      struct node *del=getnode(root,num);
      if(del!=NIL)
      deletenode(del);
    }
    if(t=='S')
    {
      long int no;
      scanf("%ld",&no);
      struct node *joint=getnode(root,no);
      if(joint==NIL)
        printf("-1\n");
      else
      {
        path(&root,no);
        printf(" %c\n",joint->color);
      }
    }
    if(t=='>')
    {
      long int no;
      scanf("%ld",&no);
      struct node *suc=successor(root,no);
      if(suc==NIL) printf("-1\n");
      else printf("%ld\n",suc->data);
    }
    if(t=='Q')
    {
      if(NIL->parent!=NIL) 
        {
          printf("-1 %ld\n",NIL->parent->data);
        }
    }
  }
  deleterbtree(root);
  free(NIL);
  return 0;
}