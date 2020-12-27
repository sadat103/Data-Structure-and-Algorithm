#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#define NULL_VALUE 0
#define SUCCESS_VALUE 99999
class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        if(length==1) {
            tail = list;
        }
        //printf("Current TAil item is: %d",tail->item);
        return SUCCESS_VALUE;
    }

    //add required codes to set up tail pointer
    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        ListNode * n1=list,*n2=0;
        while(n1!=0) {
            n2=n1;
            n1 = n1->next;
        }
        tail=n2;
        //printf("Current TAil item is: %d",tail->item);
        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        if(length==0)
        {
            printf("List Empty !!\n");
            return;
        }
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        printf("Length: %d\n",getLength());
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        //write your codes here
        ListNode * nodeNew=new ListNode();
        nodeNew->item=item;
        tail->next=nodeNew;
        tail=nodeNew;
        length++;
        // printf("Current TAil item is: %d\n",tail->item);
    }

    ListNode * getItemAt(int pos)
    {
        //write your codes here
        ListNode * n1=list,*n2=list;
        if(pos>length || length==0)
        {
            printf("Invalid Index\n");
            return NULL_VALUE;
        }
        for(int i=1;i<=pos;i++)
        {
            n2=n1;
            n1=n1->next;
            if(n1==NULL_VALUE)break;
        }
        return n2;

    }
    int deleteLast()
    {
        //write your codes here
        if(length==0)return NULL_VALUE;

        ListNode * temp=list,*temp2=list;
        while(temp->next!= NULL_VALUE)
        {
            temp2=temp;
            temp=temp->next;

            // printf("x");
        }
        length--;
        int t=tail->item;
        delete tail;
        temp2->next=0;
        tail=temp2;
        if(length==0)
        {
            list=0;
            tail=0;
        }
        // printf("Current TAil item is: %d\n",tail->item);
        return t;
    }

};

class Queue
{

public:
    LinkedListWithTail ll;
    Queue(){}
    void enqueue(int item)
    {
       ll.insertItem(item);
        ll.printList();
    }
    int dequeue()
    {
      return ll.deleteLast();
    }
};

int main(void)
{
    Queue qu;
    while(1)
    {
        printf("1. Enqueue. 2. Dequeue. 3. Exit. \n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);

        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            qu.ll.printList();
            if(item!=NULL_VALUE)printf("Dequeued :%d\n",item);
            else printf("Queue Empty !\n");
        }
        else if(ch==3)
        {
            break;
        }
    }

}

