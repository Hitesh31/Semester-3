#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct linknode   //linknode of a doubly linked list
{
  int data; //data stored in each linknode
  struct linknode *prev,*next; //next and prev linknodes
};
struct linknode *head=NULL,*tail=NULL; //head and tail of linked list
void insert_link (struct linknode **h,struct linknode **t,int a)
{
  //making a link list
  if(*h==NULL && a!=0)
  {
    struct linknode *x=(struct linknode*)malloc(sizeof(struct linknode));
    x->data=a;
    x->next=NULL;
    x->prev=NULL;
    *h=x;
    *t=x;
  //  printf("%d\n",head->data);
  }
  else if(*h!=NULL)
  {
    struct linknode * x=(struct linknode*)malloc(sizeof(struct linknode)),*temp;
    x->data=a;
    x->next=NULL;
    temp=*t;
    temp->next=x;
    x->prev=*t;
    *t=x;
  //  printf("%d\n",tail->data);
  }
}
int compare(struct linknode **head1,struct linknode **head2)
{  //comparing both linked lists after removing initial zeroes 
  struct linknode *temp1,*temp2;
    temp1=*head1;
    temp2=*head2;
    int p1=0,p2=0;
    while(temp1!=NULL && temp2!=NULL)
    {
      temp1=temp1->next;
      temp2=temp2->next;
      if(temp1==NULL) {p1=1;}
      if(temp2==NULL) {p2=1;}
      if(p1==1 && p2==0) return 0;
      if(p1==0 && p2==1) return 1;
    }
   if(p1==1 && p2==1) //if length of both are equal
  {
    temp1=*head1;
    temp2=*head2;
    int q=0;
    int equal=0;
    while(temp1!=NULL && temp2!=NULL) //go to most significant digit and compare
    {  
      if(temp1->data>temp2->data)
        {
          q=1;
          return 1;
          break;
        }
      else if(temp1->data<temp2->data)
        {
          q=1;
          return 0;
          break;
        }
      else if(temp1->data==temp2->data)
        {
           //if digits are equal
          temp1=temp1->next;
          temp2=temp2->next;
        }
    }
    if(q==0) //if both are equal
    return 2;
  }
}
//node for bst
 struct node 
 {
 	 struct linknode *tip;
	 struct node *left,*right;
 };
 struct node *root;
  //add new node
    struct node *Addnode(struct linknode **x)
  {
    struct node *temp=(struct node *)malloc(sizeof (struct node));
    temp->tip=*x;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
  }
  //inserting a node
  struct node *insert(struct node **r,struct linknode **p)
  {
	  if((*r)==NULL)
		  return Addnode(&(*p));
	  if(compare(&(*r)->tip,&(*p))==1)
		  ((*r)->left) = insert(&(*r)->left,&(*p));
    if(compare(&(*r)->tip,&(*p))==0)
		  ((*r)->right) = insert(&(*r)->right,&(*p));
    if(compare(&(*r)->tip,&(*p))==2)
      {
        (*r)->left=NULL;
        head=NULL;
        tail=NULL;
      }
    return *r;
  }
// check if number exits
bool search(struct node **j,struct linknode **b)
{
  if((*j)==NULL)
      return false;
  if(compare(&(*j)->tip,&(*b))==1)
		  return search(&(*j)->left,&(*b));
  if(compare(&(*j)->tip,&(*b))==0)
     {
		  return search(&(*j)->right,&(*b));
     }
  if(compare(&(*j)->tip,&(*b))==2)
      return true;
}
//print the path
void path(struct node **l,struct linknode **m)
 {
   if(compare(&(*l)->tip,&(*m))==2)
    printf("\n");
   else if(compare(&(*l)->tip,&(*m))==1)
    {
      printf("0");
	    path(&(*l)->left,&(*m));
    }
   else if(compare(&(*l)->tip,&(*m))==0)
    {
      printf("1");
		  path(&(*l)->right,&(*m));
    }
 }

void preorder(struct node **o) 
{ 
    if ((*o) == NULL) 
        return; 
    // first print data of node 
      struct linknode *y; 
      y=(*o)->tip;
      while(y!=NULL)
        {
          printf("%d",y->data);
          y=y->next;
        }
        printf(" ");
    // then recur on left sutree 
    preorder(&(*o)->left);   
    // now recur on right subtree 
    preorder(&(*o)->right); 
}  

void deletelist(struct linknode **point)
{  //free both lists
   struct linknode* tmp1;
   while (*point!= NULL)
    {
       tmp1 = *point;
       *point = (*point)->next;
       free(tmp1);
    }
}
void deletebst(struct node* del)  
{ 
    if (del == NULL) return; 
    // first delete both subtrees 
    deletebst(del->left); 
    deletebst(del->right); 
    // then delete the node 
    deletelist(&(del)->tip);
    free(del); 
}  


int main()
{
   char digit;
 while((digit=fgetc(stdin))!=EOF)
 {
   if(digit=='N')
   {
     deletebst(root); //delete bst
     root=NULL;
     char f;
     scanf("%c",&f);
     int g=0;
     char dig;
     while((dig=fgetc(stdin))!=EOF)
     {
       if(dig==' ')
       {
         g=1;
         if(root==NULL) //if root is null
         {
           root=insert(&root,&head);
           head=NULL;
           tail=NULL;
         }
         else
          {
           insert(&root,&head);
           head=NULL;
           tail=NULL;
          } 
       }
       else if(dig=='\n')
       {
          if(g==0) root=insert(&root,&head);
          if(g==1) insert(&root,&head);
           head=NULL;
           tail=NULL;
       //   printf("%d",            root->right->tip->next->next->data);
          break;
       }
       else
       {
         dig=dig-'0';
         insert_link(&head,&tail,dig);
       }
     }
   }
   else if(digit=='S')
   {
     char f;
     scanf("%c",&f);
     char take;
     while((take=fgetc(stdin))!=EOF)
     {
       if(take=='\n')
       {
         bool res=search(&root,&head);
         if(res==false)
         {
          printf("-1\n");
         // printf("%d",root->tip->data);
          head=NULL;
          tail=NULL;
         }
         else if(res==true)
         {
          path(&root,&head);
          head=NULL;
          tail=NULL;
         }
         break;
       }
       else
       {
         take=take -'0';
         insert_link(&head,&tail,take);
       }
     }
   }
   else if(digit=='P')
   {
     preorder(&root);
     printf("\n");
   }
 }
}