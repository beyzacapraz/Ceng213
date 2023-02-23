#pragma once

#include <vector>

struct HeapElement
{
    int     uniqueId;
    double  weight;
};

class BinaryHeap
{
    private:
    std::vector<HeapElement> elements;
    int item;
    bool contains(int uniqueId);
    void b_down(int hole);
    void b_up(int hole, double weight, HeapElement initial);
    int find_index(int uniqueId);
    // Do not remove this the tester will utilize this
    // to access the private parts.
    friend class HW3Tester;
    

    protected:
    public:
        // Constructors & Destructor
                            BinaryHeap();
        //
        bool                Add(int uniqueId, double weight);
        bool                PopHeap(int& outUniqueId, double& outWeight);
        bool                ChangePriority(int uniqueId, double newWeight);
        int                 HeapSize() const;
};