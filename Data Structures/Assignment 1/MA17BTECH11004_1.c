#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 struct node     //node of a doubly linked list
  {
    int data;     
    struct node *prev;    //pointer to prev node of doubly linked list
     struct node *next;   // pointer to next node of doubly linked list
  };
  struct node *head=NULL,*tail=NULL,*head1=NULL,*tail1=NULL,*head2,*tail2;
  /*
  head/head1 will contain MSB of their respected input numbers
  tail/tail1 will contain LSB of their respected input numbers
  only head2 will contain LSB of linked list 3
  tail of linked list = last node
  head of linked list = 1st node
  head is head for 1st linked list
  head1 is head for 2nd
  */
  void insert(int a)
  {
    if(head==NULL)
    {
      head = (struct node*)malloc(sizeof(struct node)); //new node
      head->data=a; //store data on address
      head->next=NULL; //next node of head is null if head was initially null
      head->prev=NULL; //prev node of head i null if head was initially null
      tail=head; //head and tail are same if there is one node
    }
    else 
    {
      struct node *x=(struct node*)malloc(sizeof(struct node)); //head is not null so make new node
      x->data=a; //store data in that node
      x->next=NULL; //since it is new node its next node is null
      struct node* temp;  //for traversing and to link new node to linked list
      temp=head;
      while(temp->next!=NULL)
      temp=temp->next; 
      temp->next=x; //new node is now next node to last node (that was previously last)
      x->prev=temp; //the last node is now prev node to recently added node
      tail=x; //tail is now new node
    }
  }
  void insert1(int a)
  {
    if(head1==NULL)
    {
      head1 = (struct node*)malloc(sizeof(struct node));
      head1->data=a;
      head1->next=NULL;
      head1->prev=NULL;
      tail1=head1;
    }
    else 
    {
      struct node *x=(struct node*)malloc(sizeof(struct node));
      x->data=a;
      x->next=NULL;
      struct node* temp;
      temp=head1;
      while(temp->next!=NULL)
      temp=temp->next;
      temp->next=x;
      x->prev=temp;
      tail1=x;
    }
  }
  void insert2(int a)
  {
    if(head2==NULL)
    {
      head2 = (struct node*)malloc(sizeof(struct node));
      head2->data=a;
      head2->next=NULL;
      head2->prev=NULL;
      tail2=head2;
    }
    else 
    {
      struct node *x=(struct node*)malloc(sizeof(struct node));
      x->data=a;
      x->next=NULL;
      struct node* temp;
      temp=head2;
      while(temp->next!=NULL)
      temp=temp->next;
      temp->next=x;
      x->prev=temp;
      tail2=x;
    }
  }
 
  int main()
{  
  bool k=true;
  char digit;
  while((digit=fgetc(stdin))!=EOF)
  {
    if(digit=='\n')
    { bool o=0; //optimisation
      struct node *p,*p1; //pointers for both linked list traversels
      p=tail; //start traversel from tail to add
      p1=tail1; //start traversal from tail to add
      while(p!=NULL && p1!=NULL)
      {
        int g; //data to store in final linked list
        g=p->data + p1->data;
        if(g>=10) //if data is greater than 10
        {
          g=g-10;
          if(p!=NULL && p->prev!=NULL) p->prev->data=p->prev->data +1;
          else
            { if(p1->prev!=NULL)
              p1->prev->data=p1->prev->data +1; //add carry if its prev node exist
              else o=1;  //optimisation if prev is not null
            }
        }
        p=p->prev; //p point to prev
        p1=p1->prev; //p1 point to prev
        insert2(g); //data store in new link list
      }
      while(p!=NULL && p1==NULL)
      {
        int g; //same as prev loop
        g=p->data;
        if(g>=10)
        {
          if(p->prev!=NULL)
          {
            g=g-10;
            p->prev->data=p->prev->data+1;
          }
        }
        p=p->prev;
        insert2(g);
      }
       while(p1!=NULL && p==NULL)
      {
        int g;  //same as prev loop
        g=p1->data;
        if(g>=10)
        {
          if(p1->prev!=NULL)
          {
            g=g-10;
            p1->prev->data=p1->prev->data+1;
          }
        }
        p1=p1->prev;
        insert2(g);
      } 
       if(o==1){printf("1");} //optimisation 
      struct node* r;
      r=tail2;
      while(r!=NULL)
      {
        printf("%d",r->data); //printing the addition
        r=r->prev;  
      }
     head=NULL;
     tail=NULL;
     head1=NULL;
     head2=NULL;
     tail1=NULL;
     tail2=NULL;
     k=true; //input now for 1st link list
      printf("\n");
    }
    else if(digit==' ')
    {
      k=false; //optimisation so now input is for link list 2
    }
    else
    {
     if(k)   //if k is true make link list 1
      {digit=digit-'0';
      insert(digit);}
      else  //else make link list 2
      {
        digit=digit-'0';
        insert1(digit);
      }
    }
  }
  return 0;
}
/*98172397 891729837498097
8128347 8172398047098123748979
9088909347878 129885789
87213 18

*/
 