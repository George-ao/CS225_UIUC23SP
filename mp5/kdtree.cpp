/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

//this function is to judge which point has smaller value in curDim
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim])
      return true;
    if(first[curDim] > second[curDim])
      return false;
    //use operator if there is a tie
    return first<second;
}

//this function is used to check if we shoudl repalce currentbest point with potential point
template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double cur_dist=0;
    double potential_dist=0;
    //cur_dist
    for(int i=0; i<= Dim-1;i++)
    {
      cur_dist += (currentBest[i]-target[i])*(currentBest[i]-target[i]);
    }
    //potential_dist
    for(int i=0; i<= Dim-1;i++)
    {
      potential_dist += (potential[i]-target[i])*(potential[i]-target[i]);
    }
    if(cur_dist < potential_dist)
      return false;
    if(cur_dist > potential_dist)
      return true;
    //if there is a tie
    return potential < currentBest;
}
//a constructor for our kD-tree build the tree with given point vector
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    
    //case that vevtor has no point
    if(newPoints.empty())
    {
      root = new KDTreeNode();
      size = 0;
      return;
    }
    //case that vector has point
      //copy the vector
    KDTree_vector = newPoints;
      //cur_dim start from 0, use helper function to realize our goal
    root=NULL;
    help_KDTree(KDTree_vector,0,0,newPoints.size()-1,root);
    size = KDTree_vector.size();
}
//helper function for the constructor, build the KD-tree recursively
template <int Dim>
void KDTree<Dim>::help_KDTree(vector<Point<Dim>>& KDTree_vector, int cur_dim, int left, int right, KDTreeNode* & subroot)
{
  //base case
  if(left>right) 
  {
    subroot=NULL;
    return;
  }
  int nodes_num = right - left + 1;
  int k = (nodes_num-1)/2+1;
  int index = kthSmallest(KDTree_vector,left,right,k,cur_dim);

  //deal with cur
  subroot = new KDTreeNode(KDTree_vector[index]);
  //add size?
  size++;
  //left and right by recursion
  help_KDTree(KDTree_vector, (cur_dim+1)%Dim,left,index-1,subroot->left);
  help_KDTree(KDTree_vector, (cur_dim+1)%Dim,index+1,right,subroot->right);
  return;

}

// Implementation of partition of QuickSelect
// I take the last element as pivot
// In this process, smaller elem are moved to left,greater elements to right
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& KDTree_vector, int left, int right,int cur_dim)
{
    Point<Dim> flag = KDTree_vector[right];
    int i = left;
    for (int j = left; j <= right - 1; j++) {
      if(smallerDimVal(KDTree_vector[j],flag,cur_dim))
      {
        swap(KDTree_vector[i], KDTree_vector[j]);
        i++;
      }
    }
    swap(KDTree_vector[i], KDTree_vector[right]);
    return i;
}
// This function returns kth smallest 
// element in vector
template <int Dim>
int KDTree<Dim>::kthSmallest(vector<Point<Dim>>& KDTree_vector, int left, int right, int k,int cur_dim)
{
    //k starts from 0 !!!
    // If k is the smallest 
    if (k > 0 && k <= right - left+ 1) {
  
      // Partition the array divide the array with pivot and return pivot correct index
      int index = partition(KDTree_vector, left, right,cur_dim);
  
      // If position is same as k
      if (index - left == k - 1)
          return index;
  
      // pivot is larger
      if (index - left > k - 1) 
          return kthSmallest(KDTree_vector, left, index - 1, k,cur_dim);
  
      // Else recur for right subarray
      return kthSmallest(KDTree_vector, index + 1, right, k - index + left - 1,cur_dim);
    }
    return -1;
}


/** helper function for clear **/
template <int Dim>
void KDTree<Dim>::clear(KDTreeNode* subroot)
{
  if(subroot==NULL) return;
  clear(subroot->left);
  clear(subroot->right);
  delete subroot;
}

/** helper function for copy **/
template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::copy(KDTreeNode* &root_1,const KDTreeNode* root_2)
{
  if(root_2==NULL) return NULL;

  root_1 = new KDTreeNode(root_2->point);
  root_1->left = copy(root_1->left,root_2->left);
  root_1->right = copy(root_1->right,root_2->right);
  return root_1;
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
  this->root = copy(root,other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
  if(this==&rhs) return *this;
  clear(root);
  this->root = copy(root,rhs.root);
  return *this;
}
template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  clear(root);
}
/** fucntion to find the nearest neighbor of the given point **/
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    
    if(root==NULL) return Point<Dim>();
    //initialize cloest by root
    Point<Dim> closest = Point<Dim>(root->point);
    double cur_rad = 0;
    for(int i=0; i<= Dim-1;i++)
    {
      cur_rad += (closest[i]-query[i])*(closest[i]-query[i]);
    }

    help_find(query,root,0,closest,cur_rad);
    return closest;
    // return Point<Dim>();
}

/** fucntion to find the nearest neighbor of the given point **/
template <int Dim>
void KDTree<Dim>::help_find(const Point<Dim>& query,KDTreeNode* node,int cur_dim, Point<Dim>& closest, double& cur_rad) const
{
    /**
     * @todo Implement this function!
     */

    if(node==NULL) return;
    //look in subtree containing target
      //if the node has samller value in that dimension, we search right
    if(smallerDimVal(node->point,query,cur_dim))
    {
      //if no more node in right direction
        //update closest and radius then return
      if(node->right==NULL&&node->left==NULL) 
      {
        if(shouldReplace(query,closest,node->point))
        {
          closest = node->point;
          cur_rad=0;
          for(int i=0; i<= Dim-1;i++)
          {
            cur_rad += (closest[i]-query[i])*(closest[i]-query[i]);
          }
        }
        return ;
      }
      help_find(query,node->right,(cur_dim+1)%Dim,closest,cur_rad);

      //check current
        if(shouldReplace(query,closest,node->point))
        {
          closest = node->point;
          cur_rad=0;
          for(int i=0; i<= Dim-1;i++)
          {
            cur_rad += (closest[i]-query[i])*(closest[i]-query[i]);
          }
        }


      //come to here. we already go to the bottom and we go up now, we need to check other subtree if needed
      //could there be a closer point in the other subtree
        //yes and look there
      if((query[cur_dim]-node->point[cur_dim])*(query[cur_dim]-node->point[cur_dim])<=cur_rad)
      {
        help_find(query,node->left,(cur_dim+1)%Dim,closest,cur_rad);
      }
        //no and we are done 
      else return ;
    }
      //if the node has bigger value in that dimension, we search left 
    else
    {
      //if no more node in left direction
        //update closest and radius then return
      if(node->left==NULL&&node->right==NULL)
      {
        if(shouldReplace(query,closest,node->point))
        {
          closest = node->point;
          cur_rad=0;
          for(int i=0; i<= Dim-1;i++)
          {
            cur_rad += (closest[i]-query[i])*(closest[i]-query[i]);
          }
        }
        return ;
      }
      help_find(query,node->left,(cur_dim+1)%Dim,closest,cur_rad);
      
      //check current
        if(shouldReplace(query,closest,node->point))
        {
          closest = node->point;
          cur_rad=0;
          for(int i=0; i<= Dim-1;i++)
          {
            cur_rad += (closest[i]-query[i])*(closest[i]-query[i]);
          }
        }

      //come to here. we already go to the bottom and we go up now, we need to check other subtree if needed
      //could there be a closer point in the other subtree
        //yes and look there
      if((query[cur_dim]-node->point[cur_dim])*(query[cur_dim]-node->point[cur_dim])<=cur_rad)
      {
        help_find(query,node->right,(cur_dim+1)%Dim,closest,cur_rad);
      }
        //no and we are done 
      else return ;
    }
}