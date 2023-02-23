#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: 
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: 

private:
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    
    
    Node<T>*copy = obj.head;int i=1;
    if(!copy) return;
    else if(obj.size == 1){
        head = new Node<T>(copy -> data);
        head -> next = head;
        head -> prev = head;
    }
    else{
        Node<T>*current;
        head = new Node<T>(copy -> data);
        head -> next = head;
        head -> prev = head;
        current = head;
        copy = copy -> next;
        for(i;i<obj.size;i++){
            Node<T>* newNode = new Node<T>(copy -> data);
            newNode -> prev = current;
            newNode -> next = current -> next;
            current -> next -> prev = newNode;
            current -> next = newNode;
            current = current -> next;
            copy = copy -> next;
        }
        
    }
    size = obj.size;
    

}

template<class T>
LinkedList<T>::~LinkedList()
{
    int node_num = size;
    if(!head) return;
    else if(node_num == 1){
        delete head;
        head = NULL;
        size--;
    }
    else{
        int i;
        for(i = 0; i < node_num; i++){ 
            Node<T>* current = head;
            head -> prev -> next = head -> next;
            head -> next -> prev = head -> prev;
            head = head -> next;
            delete current;
            size--;
        }
        head = NULL;
        size = 0;
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    
    if(&rhs != this){
        Node<T>*copy = rhs.head;int i=1;
        removeAllNodes();
        head = NULL;
        size = 0;
        if(!copy);
        else if(rhs.size == 1){
            head = new Node<T>(copy -> data);
            head -> next = head;
            head -> prev = head;
        }
        else{
            Node<T>*current;
            head = new Node<T>(copy -> data);
            head -> next = head;
            head -> prev = head;
            current = head;
            copy = copy -> next;
            for(i;i<rhs.size;i++){
                Node<T>* newNode = new Node<T>(copy -> data);
                newNode -> prev = current;
                newNode -> next = current -> next;
                current -> next -> prev = newNode;
                current -> next = newNode;
                current = current -> next;
                copy = copy -> next;
            }
            
        }
    }
    size = rhs.size;
    return *this;
    

}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if(size == 0) {return true;}
    else{
        return false;
    }
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const 
{
    int n = 0;
    if(!head) return false;
    else{
        Node<T>*current = head; 
        while(current != head){
            if(current == node){
                n++;
                break;
            }
            current = current -> next;
        }
        if(n) return true;
        else return false;
    }
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if(!head) return head;
    else{
        return head -> prev;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T>* current = head;Node<T>*np = NULL;int i, node_num = size;
    if(!current) return NULL;
    else{
        for(i = 0; i < node_num; i++){
            if(current -> data == data){
                np = current;
                break;
            }
            current = current -> next;
        }
        return np;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    int node_num = size;
    if(index > node_num - 1 || index < 0) return NULL;
    else if(!index && !node_num) return NULL;
    else if(index <= node_num -1){
        int counter = 0,i;
        Node<T>* current = head;
        for(i = 0; i < node_num; i++){
            if(counter == index) return current;
            else{
                counter++;
                current = current -> next;
            }
        }
    }
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    
    Node<T>*newNode = new Node<T>(data); 
    if(!head){
        newNode -> next = newNode;
        newNode -> prev = newNode;
        head = newNode;
    }
    else{
        newNode -> next = head;
        newNode -> prev = head -> prev;
        head -> prev -> next = newNode;
        head -> prev = newNode;
       
    }
    size++;
    
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    if(!head){
        head = new Node<T>(data);
        head -> next = head;
        head -> prev = head;
    }
    else{
        Node<T>*newNode = new Node<T>(data);
        newNode -> next = head;
        newNode -> prev = head -> prev;
        head -> prev -> next = newNode;
        head -> prev = newNode;
        head = newNode;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    int node_num = size;
    int n = 0,i;
    if(!head) return;
    else{
        Node<T>*current = head; 
        for(i = 0; i < node_num; i++){
            if(current == node){
                n++;
                break;
            }
            current = current -> next;
        }
        if(n) {
            Node<T>* newNode = new Node<T>(data); 
            newNode -> prev = current;
            newNode -> next = current -> next;
            newNode -> prev -> next = newNode;
            newNode -> next -> prev = newNode;
            size++;
        }
    }

}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    int node_num = size;
    if(!head) return;
    else if(index > node_num - 1 || index < 0) return;
    else if(index == 0 && node_num == 1){
        Node<T>*newNode = new Node<T>(data);
        newNode -> next = head;
        newNode -> prev = head;
        head -> prev = newNode;
        head -> next = newNode;
        head = newNode;
        size++;
    }
    else if(index == 0 && node_num > 1){
        Node<T>*newNode = new Node<T>(data);
        newNode -> next = head;
        newNode -> prev = head -> prev;
        head -> prev -> next = newNode;
        head -> prev = newNode;
        head = newNode;
        size++;
        
    }
    else if(index <= node_num -1){
        int counter = 0,i; Node<T>* current = head;
        Node<T>* newNode = new Node<T>(data);
        for(i = 0; i < node_num; i++){
            if(counter == index) break;
            else{
                counter++;
                current = current -> next;
            }
        }
        current = current -> prev; 
        newNode -> prev = current;
        newNode -> next = current -> next;
        newNode -> prev -> next = newNode;
        newNode -> next -> prev = newNode;
        size++;
    }
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    int n = 0,i,counter=0,node_num = size;
    if(!head) return -1;
    else{
        Node<T>*current = head; 
        for(i = 0; i < node_num; i++){
            if(current == node){
                n++;
                break;
            }
            counter++;
            current = current -> next;
        }
        if(n) return counter; else return -1;
    }
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    int node_num = size;
    if(currentIndex < node_num){
        if(currentIndex == newIndex );
        else if((newIndex > node_num - 1) && currentIndex == 0){
            head = head -> next;
        }
        else if((newIndex > node_num - 1 ) && currentIndex != 0){
            Node<T>*current = getNodeAtIndex(currentIndex);
            current -> prev -> next = current -> next;
            current -> next -> prev = current -> prev;
            current -> next = head;
            current -> prev = head -> prev;
            head -> prev -> next = current;
            head -> prev = current;
        }
        else if(currentIndex == 0){
            Node<T>*current = getNodeAtIndex(newIndex);
            Node<T>* move = head;
            head -> prev -> next = head -> next;
            head -> next -> prev = head -> prev;
            head = head -> next;
            current -> next -> prev = move; 
            move -> prev = current ;
            move -> next = current -> next;
            current -> next = move;
        }
        else if( newIndex == 0){
            Node<T>*current = getNodeAtIndex(currentIndex);
            current -> prev -> next = current -> next;
            current -> next -> prev = current -> prev;
            head -> prev -> next = current;
            current -> prev = head -> prev;
            head -> prev = current;
            current -> next = head;
            head = current;
        }
        else if(currentIndex > newIndex){
            Node<T>*move = getNodeAtIndex(currentIndex);
            Node<T>*current = getNodeAtIndex(newIndex);
            move -> prev -> next = move -> next;
            move -> next -> prev = move -> prev;
            current -> prev -> next = move;
            move -> prev = current -> prev;
            move -> next = current;
            current -> prev = move;
            
        }
        else{
            Node<T>*move = getNodeAtIndex(currentIndex);
            Node<T>*current = getNodeAtIndex(newIndex);
            move -> prev -> next = move -> next;
            move -> next -> prev = move -> prev;
            current -> next -> prev = move; 
            move -> prev = current ;
            move -> next = current -> next;
            current -> next = move;
            
        }
        
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{   
        int n = 0,node_num = size;
        if(!head) return;
        else if(node == head && node_num == 1){
            delete head;
            head = NULL;
            size--;
            
        }
        else if(node == head && node_num > 1){
            Node<T>*current = head;
            head -> prev -> next = head -> next;
            head -> next -> prev = head -> prev;
            head = head -> next;
            delete current;
            current = NULL;
            size--;
        }
        else{
            Node<T>*current = head; 
            for(int i = 0; i < node_num; i++){
                if(current == node){
                    n++;
                    break;
                }
                current = current -> next;
            }
            if(n){
                current -> prev -> next = current -> next;
                current -> next -> prev = current -> prev;
                delete current;
                size--;
            }
        }
        
    
    

}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    int node_num = size,i;
    if(!head) return;
    else if(data == head -> data && node_num == 1){
        delete head;
        head = NULL;
        size = 0;
    }
    else if(data == head -> data && node_num > 1){
        Node<T>* current = head;
        current -> prev -> next = current -> next;
        current -> next -> prev = current -> prev;
        head = head -> next;
        delete current;
        size--;
    }
    else{
        Node<T>* current = head;
        for(i = 0; i < node_num; i++){
            if(current -> data == data){
                Node<T>* tmp = current;
                current -> prev -> next = current -> next;
                current -> next -> prev = current -> prev;
                current = current -> next;
                delete tmp;
                size--;
                
            }
            else{
                current = current -> next;
            }
            
        }
        
        
    }
    
    
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    int node_num = size;
    if(index > node_num -1 || index < 0 ) return;
    else if(!head) return;
    else if(index == 0 && node_num == 1){
        delete head;
        head = NULL;
        size--;
    }
    else if(index == 0 && node_num > 1){
        Node<T>* tmp = head;
        head -> next -> prev = head -> prev;
        head -> prev -> next = head -> next;
        head = head -> next;
        delete tmp;
        size--;
    }
    else{
        int counter = 0,i; Node<T>* current = head;
        for(i = 0; i < node_num; i++){
            if(counter == index) break;
            else{
                counter++;
                current = current -> next;
            }
        }
        current -> next -> prev = current -> prev;
        current -> prev -> next = current -> next;
        delete current;
        size--;
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    int node_num = size;
    if(!head) return;
    else if(node_num == 1){
        delete head;
        head = NULL;
        size--;
    }
    else{
        int i;
        for(i = 0; i < node_num; i++){ 
            Node<T>* current = head;
            head -> prev -> next = head -> next;
            head -> next -> prev = head -> prev;
            head = head -> next;
            delete current;
            size--;
        }
        head = NULL;
        size = 0;
    }
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H

