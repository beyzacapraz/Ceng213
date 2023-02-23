#include "BinaryHeap.h"

BinaryHeap::BinaryHeap()
{
    item = 0;
}

bool BinaryHeap::contains(int uniqueId){
    if(item == 0) return false;
    else{
        for(int i = 1; i <= item; i++){
            if(elements[i].uniqueId == uniqueId) return true;
        }
        return false;
    }
}
void BinaryHeap::b_up(int hole, double weight,HeapElement initial)
{
    int parent;
    for(;hole/2 > 0 && weight < elements[hole/2].weight; hole = parent){
        parent = hole/2;
        elements[hole] = elements[parent];
        
    }
    elements[hole] = initial;
    
}


bool BinaryHeap::Add(int uniqueId, double weight)
{
    
    HeapElement initial;int size = elements.size(); 
    initial.uniqueId = uniqueId; initial.weight = weight;
    if(item == 0){ 
        if(size<2) elements.resize(2);
        elements[1]=initial;
        item++;
        return true;
    }
    else if(item && contains(uniqueId)) return false;
    else{
        if((item + 1) == size){ elements.resize(size*2 + 1);}
        elements[0] = initial;
        int hole = ++item;
        b_up(hole,weight,initial);
        return true;
    }

    

}
void BinaryHeap::b_down(int hole)
{
    int child;
    HeapElement tmp = elements[hole];

    for( ; hole*2 <= item; hole = child) {
        child = hole * 2;
        if(child != item && elements[child + 1].weight < elements[child].weight) child++;
        if(elements[child].weight < tmp.weight) elements[hole] = elements[child];
        else break;
    }
    elements[hole] = tmp;
    
}

bool BinaryHeap::PopHeap(int& outUniqueId, double& outWeight)
{
    if(item){
        outUniqueId = elements[1].uniqueId;outWeight = elements[1].weight;
        elements[1] = elements[item];
        item--;
        b_down(1);
        return true;
        
    }
    else return false;

}
int BinaryHeap::find_index(int uniqueId) // Id gerekli mi ?
{
    for(int i = 1; i < item; i++){
        if(elements[i].uniqueId == uniqueId) return i;
    }
}

bool BinaryHeap::ChangePriority(int uniqueId, double newWeight)
{
    if(contains(uniqueId)){
        int index = find_index(uniqueId);
        elements[index].weight = newWeight;
        if (index != 1 && elements[index].weight < elements[index/2].weight){// parenttan  küçükse yukarý
            HeapElement tmp;tmp = elements[index];
            b_up(index,newWeight,tmp);
        }
        else {
            if((index*2 <= item && elements[index].weight > elements[index/2].weight)|| //child daha küçükse aþaðý
            (index*2+1 <= item && elements[index].weight > elements[index*2+1].weight))
                b_down(index); 
        }
        return true;
    }
    else return false;
}

int BinaryHeap::HeapSize() const
{
    return item;
}
