#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
struct node   //node of a doubly linked list
{
  int data; //data stored in each node
  struct node *prev,*next; //next and prev nodes
};
int length1=0,length2=0; //length of each node
bool k=true; //flag for optimisation
struct node *head1,*tail1,*head2,*tail2; //head and tail for both linked lists
//head will store most significant digit
void insert1 (int a )
{
  if(head1==NULL && a!=0) //if head is null then don't add 0 to list
  {
    head1=(struct node*)malloc(sizeof(struct node));
    head1->data=a;
    head1->next=NULL;
    head1->prev=NULL;
    tail1=head1;
    if(k==true)length1++;
    else length2++;
  }
  else if(head1!=NULL)
  {
    struct node *x=(struct node*)malloc(sizeof(struct node));
    x->data=a;
    x->next=NULL;
    struct node *temp;
    temp=head1;
    while(temp->next!=NULL)
    temp=temp->next;
    temp->next=x;
    x->prev=temp;
    tail1=x;
    if(k==true)length1++;
    else length2++;
  }
}
void insert2 (int a )
{
  if(head2==NULL && a!=0)
  {
    head2=(struct node*)malloc(sizeof(struct node));
    head2->data=a;
    head2->next=NULL;
    head2->prev=NULL;
    tail2=head2;
    if(k==true)length1++;
    else length2++;
  }
  else if(head2!=NULL)
  {
    struct node *x=(struct node*)malloc(sizeof(struct node));
    x->data=a;
    x->next=NULL;
    struct node *temp;
    temp=head2;
    while(temp->next!=NULL)
    temp=temp->next;
    temp->next=x;
    x->prev=temp;
    tail2=x;
    if(k==true)length1++;
    else length2++;
  }
}
void compare()
{  //comparing both linked lists after removing initial zeroes 
  if(length1>length2) //if length of a > length of b print 1
    printf("1\n");     //here length is significant digits
  else if(length1<length2) //if length of a < length of b
    printf("0\n");
  else if(length1==length2) //if both are equal
  {
    struct node *temp1,*temp2;
    temp1=head1;
    temp2=head2;
    int equal=0;
    while(temp1!=NULL && temp2!=NULL) //go to most significant digit and compare
    {  
      if(temp1->data>temp2->data)
        {
          printf("1\n");
          break;
        }
      else if(temp1->data<temp2->data)
        {
          printf("0\n");
          break;
        }
      else if(temp1->data==temp2->data)
        {
          equal++; //if digits are equal
          temp1=temp1->next;
          temp2=temp2->next;
        }
    }
    if(equal==length1) //if both are equal
    printf("1\n");
  }
  length1=0; //reset lengths
  length2=0;
  k=true;
}
void freelist()
{  //free both lists
   struct node* tmp1;
   while (head1 != NULL)
    {
       tmp1 = head1;
       head1 = head1->next;
       free(tmp1);
    }
     struct node* tmp2;
   while (head2 != NULL)
    {
       tmp2 = head2;
       head2 = head2->next;
       free(tmp2);
    }
}
int main()
{
  char digit;
 while((digit=fgetc(stdin))!=EOF)
 {
    if(digit=='\n')
    {
      compare();
      freelist();
    }
    else if(digit==' ')
    {
      k=false;
    }
    else
    {
      digit=digit-'0';
      if(k==true)
      insert1(digit); //store a in linked list 1
      else 
      insert2(digit); //store b in linked list 2
    }
 }
  return(0);
}