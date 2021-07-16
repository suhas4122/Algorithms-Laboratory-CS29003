/*
Suhas Jain
19CS30048
3rd september 2020
Lab-1
*/

#include <iostream>
using namespace std;

struct Node
{
  int value;
  Node* link;

  Node(int new_value)
  {
  value = new_value;
  }
};

Node* XOR (Node *a, Node *b)  //to xor any 2 node adresses
{
    return (Node*) ((uintptr_t) (a) ^ (uintptr_t) (b));
}

void reverse_list(Node* &head, Node* &tail){ //to reverse normally
    Node* temp;
    temp=head;
    head=tail;
    tail=temp;
    return;
}

void traverse_from_front_to_end(Node *head)  //print from front
{
   Node *curr = head;
   Node *prev = NULL;
   Node *next;

   cout<<"Doubly linked list traversed from front to end: ";

   while (curr != nullptr)
   {
      cout << curr->value << " ";

      next = XOR(prev, curr->link);

      prev = curr;
      curr = next;
   }

   cout<<endl;
}

void traverse_from_end_to_front(Node*tail){   //print from end
   Node *curr = tail;
   Node *prev = NULL;
   Node *next;

   cout<<"Doubly linked list traversed from end to front: ";

   while (curr != nullptr)
   {
      cout << curr->value << " ";

      next = XOR(prev, curr->link);

      prev = curr;
      curr = next;
   }

   cout<<endl;
}

void push(Node* &head, Node* &tail, int data)   //add new data at the end
{
   Node* newNode = new Node(data);

   if(head==NULL){
      head=tail=newNode;
      newNode->link = NULL;
      return;
   }

   newNode->link = XOR(tail, nullptr);

   tail->link = XOR(newNode, XOR(tail->link,  nullptr));

   tail = newNode;
}

Node* reverse_adv(Node* &start, Node* &tail, Node* previous){  //to reverse the list from a start element to tail
    Node* prev;
    Node* curr;
    Node* next;
    Node* temp;
    temp=curr=XOR(previous, start->link);
    prev=start;
    next=XOR(start, curr->link);
    start->link=XOR(previous, tail);
    curr->link=XOR(NULL, next);
    Node* second_last;
    second_last=XOR(NULL, tail->link);
    tail->link=XOR(start, second_last);
    prev=tail;
    tail=temp;
    return prev;
}

void alternate(Node* &head, Node* &tail, int n){  //to use reverse_adv and solve the 3rd part
    reverse_list(head, tail);
    Node* start;
    Node* prev;
    prev=NULL;
    start=head;
    for(int i=0; i<n-2; i++){
        Node* temp;
        temp=reverse_adv(start, tail, prev);
        prev=start;
        start=temp;
    }
    return;
}
/*
we are doing like this, suppose the list is 1 2 3 4 5
then we'll change it to 1 5 4 3 2
then 1 5 2 3 4 and so on....
*/
int main()
{
   int n;
   cout<<"Enter the number of elements you want to enter: ";
   cin>>n;

   Node* head=NULL;
   Node* tail=NULL;

   for(int i=0; i<n; i++){
      int value;
      cin>>value;
      push(head, tail, value);
   }
   cout<<endl;

   traverse_from_front_to_end(head);
   traverse_from_end_to_front(tail);

   reverse_list(head, tail);
   traverse_from_front_to_end(head);

   alternate(head, tail, n);
   traverse_from_front_to_end(head);

   return 0;
}
