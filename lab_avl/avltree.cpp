/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp_ = t->right;
    t->right = temp_->left;
    temp_->left = t;
    t=temp_;
    //renew height
    t->left->height = update_height(t->left);
    t->height = update_height(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp_ = t->left;
    t->left = temp_->right;
    temp_->right = t;
    t=temp_;
    //renew height
    t->right->height = update_height(t->right);
    t->height = update_height(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    if(subtree==NULL) return;
    if(heightbalance(subtree)>=2)
    {
        if(heightbalance(subtree->right)>=0)
        {
            rotateLeft(subtree);
        }
        else rotateRightLeft(subtree);
    }
    if(heightbalance(subtree)<=-2)
    {
        if(heightbalance(subtree->left)<=0)
        {
            rotateRight(subtree);
        }
        else rotateLeftRight(subtree);
    }
    subtree->height= update_height(subtree);
}

template <class K, class V>
int AVLTree<K, V>::heightbalance(Node* subRoot)
{
    int height_right;
    int height_left;
    if(subRoot==NULL) return 0;

    if(subRoot->right==NULL)  height_right = -1;
    else  height_right = subRoot->right->height;

    if(subRoot->left==NULL)  height_left = -1;
    else  height_left = subRoot->left->height;

    return height_right-height_left;
}


template <class K, class V>
int AVLTree<K, V>::update_height(Node* node)
{
    int left_height=-1;
    int right_height=-1;
    if(node->left!=NULL) left_height = node->left->height;
    if(node->right!=NULL) right_height = node->right->height;
    return 1+max(left_height,right_height);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    //insert as leaves
    if(subtree==NULL)
    {
        subtree = new Node(key,value);
        // rebalance(subtree);
    } 
    //still finding
    else if(subtree->key > key) 
    {
        insert(subtree->left,key,value);
        rebalance(subtree);
    }
    else if(subtree->key < key) 
    {
        insert(subtree->right,key,value);
        rebalance(subtree);
    }
        //update new value
    else if(subtree->key == key)
    {
        subtree->value = value;
        return;
    }    
    // subtree->height= update_height(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}


template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) 
    {
        // in left subtree
        remove(subtree->left,key);
        rebalance(subtree);

    } else if (key > subtree->key) 
    {
        // in right subtree
        remove(subtree->right,key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree=NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
                //find IOP
                Node* temp_ = subtree->left;
                Node* iop_ = temp_;
                while(temp_!=NULL)
                {
                    //if(temp_->right==NULL) break;
                    iop_ = temp_;
                    temp_ = temp_->right;
                }
                //swap IOP and current node
                swap(iop_,subtree);
                //call remove again
                remove(subtree->left,key);
        } else {
            /* one-child remove */
                //left child remains
            if(subtree->left!=NULL)
            {
                Node* store=subtree;
                subtree = subtree->left;
                delete store;
                store = NULL;
            }
            if(subtree->right!=NULL)
            {
                Node* store=subtree;
                subtree = subtree->right;
                delete store;
                store = NULL;
            }
        }

    }

}

