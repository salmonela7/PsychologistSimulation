#include "Queue.h"
#include <stdlib.h>
#include <iostream>
#include <new>
#include <exception>
#include <string>
#define POP_ERROR_EMPTY_QUEUE "Queue is empty, cannot pop element!"
#define EMPTY_QUEUE "Queue is empty!"
using namespace std;
Queue::Queue()
{
    this->size = 0;
    this->rear = NULL;
    this->front = NULL;
}
Queue::~Queue() {}
bool Queue::isEmpty()
{
    return this->size == 0;
}
bool Queue::isFull()
{
    Node * temp = new Node;

    if(temp != NULL)
    {
        delete temp;
        return false;
    }
    return true;
}
void Queue::addElement(Queue_type x)
{
    if(this->size == 0)
    {
        this->rear = new Node;
        this->rear->el = x;
        this->front = this->rear;
        this->front->next=this->rear->next=NULL;
    }
    {
        this->rear->next = new Node;
        this->rear->next->next = NULL;
        this->rear->el = x;
        this->rear=this->rear->next;
    }
    this->size++;
}

Queue_type Queue::remove()
{
    if (this->size == 0)
        throw range_error(POP_ERROR_EMPTY_QUEUE);
    Queue_type x = this->front->el;
    Node *temp = this->front;
    if(size > 1)
        this->front = this->front->next;
    else
    {
        this->front = NULL;
        this->rear = NULL;
    }
    this->size--;
    delete temp;
    return x;
}
Queue_type Queue::first()
{
    if (this->size == 0)
        throw range_error(EMPTY_QUEUE);
    else
        return this->front->el;
}
int Queue::length()
{
    return this->size;
}
//void Queue::display()
//{
//    if(this->size == 0)
//        throw range_error(EMPTY_QUEUE);
//    else
//    {
//        Node*temp=this->front;
//        while(temp->next!=NULL)
//        {
//            cout<<temp->el<<"\t";
//            temp=temp->next;
//        }
//    }
//    cout<<endl<<endl;
//}
/*void Queue::emptyQ(string x)
{
    cout<< x;
}*/
