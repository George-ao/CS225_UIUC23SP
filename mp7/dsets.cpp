
#include "dsets.h"
using namespace std;
void DisjointSets::addelements(int num)
{
    for(int i=0; i<=num-1; i++)
    {
        uptrees_.push_back(-1);
    }
}

int DisjointSets::find(int elem)
{
    //find rep elem
    if(uptrees_[elem]<0)
        return elem;
    //not rep elem
    else
    {
        return uptrees_[elem] = find(uptrees_[elem]);
    }
}


void DisjointSets::setunion(int a, int b)
{
    //invalid input
    if(a>=uptrees_.size()||b>=uptrees_.size()||a<0||b<0||a==b)
        return;
    //find roots
    int root1 = find(a);
    int root2 = find(b);
    //same root
    if(root1==root2)
        return;
    int newSize = uptrees_[root1] + uptrees_[root2];
    // If uptrees_[root1] is less than (more negative), it is the larger set;
    // we union the smaller set, root2, with root1.
    if ( uptrees_[root1] <= uptrees_[root2] ) 
    {
        uptrees_[root2] = root1;
        uptrees_[root1] = newSize;
    }
    // Otherwise, do the opposite:
    else 
    {
        uptrees_[root1] = root2;
        uptrees_[root2] = newSize;
    }
}
int DisjointSets::size(int elem)
{
    return -uptrees_[find(elem)];
}