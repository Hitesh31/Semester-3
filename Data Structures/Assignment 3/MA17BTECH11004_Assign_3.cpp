#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
using namespace std;
struct node
{
 long long int data;
  struct node *left,*right,*parent;
};
//if a node is deleted then it will be replaced by successor
struct node *root;
struct node *Addnode (long long int key)
{
  struct node *temp=new node;
  temp->data=key;
  temp->left=NULL;
  temp->right=NULL;
  temp->parent=NULL;
  return temp;
}
struct node *insert (struct node **r,long long int key)
{
  if((*r)==NULL)
    return Addnode(key);
  
  else 
  {
    if((*r)->data>key)
       {
         ((*r)->left)= insert(&(*r)->left,key);
         ((*r)->left)->parent=(*r);
       } 
  else if((*r)->data<key)
      {
       ((*r)->right)= insert(&(*r)->right,key);
       ((*r)->right)->parent=(*r);
      }
  else if((*r)->data==key)
    return (*r); 
  }
  return (*r);
}
bool search (struct node **p,long long int key)
{
  if((*p)==NULL)
      return false;
  else if((*p)->data>key)
      return search(&(*p)->left,key);
  else if((*p)->data<key)
      return search(&(*p)->right,key);
  else if((*p)->data==key)
      return true;
  return false;
}
void path (struct node **p,long long int key)
{
  if((*p)->data>key)
       {
         cout<<0;
         path(&(*p)->left,key);
       }
  if((*p)->data<key)
      {
         cout<<1;
         path(&(*p)->right,key);
      }
  if((*p)->data==key)
      cout<<"\n";
}
struct node *deletenode(struct node *p,long long int key);
struct node* successor(struct node *p,long long int key)
{
  while(p!=NULL)
  {
    if((p)->data>key)
      (p)=(p)->left;
    else if((p)->data<key)
      (p)=(p)->right;
    else if((p)->data==key)
      break;
  }
  if(p==NULL)
  {
    //if key is not present in the tree
    insert(&root,key);
    struct node *newsec=successor(root,key);
    root= deletenode(root,key);
    return newsec;
  }

  else
  {
    //if key is present
    //now,if node->right is not null
    if((p)->right!=NULL)
     {
       struct node *temp=(p)->right;
       while(temp->left!=NULL)
          temp=temp->left;
       return temp;
     }
    //if there is node->right is null then successor is in ancestors 
     if(p==root) 
          return NULL;
    struct node *n=(p);
    struct node *t = n->parent; 
    while(t!= NULL && n == t->right) 
    { 
       n = t; 
       t = t->parent; 
    } 
    return t; 
  }
  return p;
}
struct node *deletenode(struct node *p,long long int key)
{
    if (p==NULL)
       return p; 
    if (p->data>key) 
        p->left = deletenode(p->left, key);  
    else if (p->data<key) 
        p->right = deletenode(p->right, key);
      else
    { 
        // node with only one child or no child 
        if (p->left == NULL) 
        { 
            struct node *temp = p->right; 
            if(p->right!=NULL)p->right->parent=p->parent;
            free(p); 
            return temp; 
        } 
        else if (p->right == NULL) 
        { 
            struct node *temp = p->left;
            if(p->left!=NULL)
            p->left->parent=p->parent; 
            free(p); 
            return temp; 
        } 
        // node with two children: Get the inorder successor (smallest 
        // in the right subtree
        struct node* temp = p->right;
        while (temp->left != NULL) 
            temp = temp->left; 
        // Copy the inorder successor's content to this node 
        p->data = temp->data; 
        // Delete the inorder successor 
        p->right = deletenode(p->right, temp->data); 
    }
    return p; 
}
void preorder(struct node **p)
{
  if((*p)==NULL)
    return;
  cout<<(*p)->data<<" ";
  preorder(&(*p)->left);
  preorder(&(*p)->right);
}
void deletebst(struct node *p)  
{ 
    if (p == NULL) return; 
  
    /* first delete left subtree */
    deletebst(p->left);
    /*then delete right subtree*/ 
    deletebst(p->right);
    /* then delete the node */
    free(p); 
} 
int main() 
{
  char digit;
   while((digit=fgetc(stdin))!=EOF)
   {
     if(digit=='N')
     {
       deletebst(root);
       root=NULL;
       char dump;
       scanf("%c",&dump);
       string s;
       getline(cin,s);
      // cout<<s<<s.size()<<endl;
       string num;
       bool p=true;
       for(int i=0;i<s.size();i++)
       {
         if(s[i]==' ')
         {
           long long int no;
           if(num.size()>0)no=stoi(num);
           if(p==true) 
           {
             root=insert(&root,no);
             p=false;
           }
           else insert(&root,no);
           num.clear();
         }
         else
         {
           num=num+s[i];
         }
       }
       long long int no;
       if(num.size()>0)no=stoi(num);
       if(p==false) insert(&root,no);
       if(p==true && num.size()>0) 
       {
         root=insert(&root,no);
       }
       num.clear();
      // cout<<root->data;
     }
     else if(digit=='+')
     {
       long long int no;
       cin>>no;
       if(root==NULL) root=insert(&root,no);
       else insert(&root,no);
     }
     else if(digit=='S')
     {
       long long int no;
       cin>>no;
       bool y=search(&root,no);
       if(y==false)
          cout<<"-1\n";
        if(y==true)
          path(&root,no);
     }
     if(digit=='P')
     {
       preorder(&root);
       cout<<endl;
     }
     if(digit=='>')
     {
        long long int no;
         cin>>no;
         struct node *suc=successor(root,no);
         if(suc==NULL) cout<<"-1\n";
         else cout<<suc->data<<endl;
     }
     if(digit=='-')
     {
       long long int no;
       cin>>no;
       root=deletenode(root,no);
     }
   }
}