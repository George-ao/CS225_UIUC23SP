/**
 * @file dsets.h
 *
 * Defintion for a class the represent a family of a disjoint sets.
 * Each DisjointSets object represents a family of disjoint sets, where each element has an integer index.
 * It is implemented with the optimizations discussed in class, as up-trees stored in a single vector of ints. 
 * Specifically, path compression and union-by-size are used. Each place in the vector represents a node. 
 * (Note that this means that the elements in our universe are indexed starting at 0.) 
 * A nonnegative number is the index of the parent of the current node; 
 * a negative number in a root node is the negative of the set size.
 * @author Yuyi Ao
 * @date Spring 2023
 */
#ifndef DSETS_H
#define DSETS_H
#include <vector>
using namespace std;
class DisjointSets
{
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        
    private:
        vector<int> uptrees_;
};
// #include "dsets.h"
#endif