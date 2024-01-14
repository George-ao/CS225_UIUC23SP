/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirror(root);
}
/**
 * Private helper function for the public mirror function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::mirror(Node* subroot)
{
    //base case
    if(subroot==NULL) return;

    //recursive case
        //exchange left and right
    Node* intermediate = subroot->left;
    subroot->left = subroot->right;
    subroot->right = intermediate;
        //go furthur 
    mirror(subroot->left);
    mirror(subroot->right);
    return;
}


/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // bool return_val = true;
    // T prev=INT32_MIN;
    // isOrdered(this->root,return_val,prev);
    // return return_val;
    vector<T> path_store;
    isOrdered(root,path_store);
    int bound = path_store.size()-1;
    for(int i =0;i<bound;i++)
    {
        if(path_store[i]>=path_store[i+1])
        {
            return false;
        }
    }
    return true;

}

/**
 * Private helper function for the public mirror function.
 * @param subRoot
 */
// template <typename T>
// void BinaryTree<T>::isOrdered(Node* subroot, bool& return_val, T& prev) const
// {
//     //base case
//     if(subroot==NULL) return ;
//     //recursive case
//     isOrdered(subroot->left,return_val,prev);
//         //if not bigger, change bool value to false
//     if(subroot->elem <= prev)
//     {
//         return_val = false;
//     }
//         //if current bigger, iterate prev and recurse 
//     prev = subroot->elem;
//     isOrdered(subroot->right,return_val,prev);
//     return;
// }
template <typename T>
void BinaryTree<T>::isOrdered(Node* subroot, vector<T> &v_) const
{
    //base case
    if(subroot==NULL) return ;
    //recursive case
    isOrdered(subroot->left,v_);
        //if not bigger, change bool value to false
    v_.push_back(subroot->elem);
        //if current bigger, iterate prev and recurse 
    isOrdered(subroot->right,v_);
    return;
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
        //count which path
    //int path_count = 0;
        //count each node
    //int node_count = 0; 
    paths.clear();
    vector<T> single_paths;
    printPaths(paths,single_paths,root);
    return;
}

/**
 * Private helper function for the public printPaths function.
 * @param paths
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths,vector<T> single_paths,Node* subroot) const
{
    //base case
    if(subroot==NULL) return;
    if(subroot->left==NULL && subroot->right==NULL) 
    {
        //add path and clear single path
        single_paths.push_back(subroot->elem);
        paths.push_back(single_paths);
        //single_paths.clear();
        return;
    }
    //current node
    single_paths.push_back(subroot->elem);
    printPaths(paths,single_paths,subroot->left);
    printPaths(paths,single_paths,subroot->right);
    return;
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
        //sum to current node
    int sum = -1;
        //count the number of node
    int count = 0;
    vector<T> store_sum;
    sumDistances(root,sum,store_sum,count);
    int total_size=store_sum.size();
    sum=0;
    for(int i =0;i<total_size;i++)
    {
        sum = sum +store_sum[i];
    }
    return sum;
}
template <typename T>
void BinaryTree<T>::sumDistances(Node*subroot, int sum,vector<T> &store_sum,int& count) const
{
    //base case
    if(subroot==NULL) return;

    //recursive
        //deal with current node
    sum = sum +1 ;// subroot->elem;
    store_sum.push_back(sum);
    sumDistances(subroot->left,sum,store_sum,count);
    sumDistances(subroot->right,sum,store_sum,count);   
    return;

}
