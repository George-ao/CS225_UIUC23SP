/**
 * @file skipList.cpp
 * Doubly Linked Skip List (lab_gdb2), skip list implementation
 *
 * @author Arman Tajback - Created
 * @author Jordi Paris Ferrer & Arman Tajback - Modified
 * @date (created) Fall 2016
 * @date (modified) Spring 2017
 * @date (modified) Fall 2017
 */

#include "skipList.h"


/**
 * Default constructs the SkipList.
 * Uses two sentinel nodes, each initially of height 1
 */
SkipList::SkipList()
{
    ////3.11 10:23,previosu one is initialization rather than give it values
    // SkipNode* head = new SkipNode();
    // SkipNode* tail = new SkipNode();
    head = new SkipNode();
    tail = new SkipNode();

    head->nodePointers[0].next = tail;
    tail->nodePointers[0].prev = head;

    head->key = INT_MIN;
    head->value = HSLAPixel();

    tail->key = INT_MAX;
    tail->value = HSLAPixel();
    ////3.12 10:01
    // int listHeight = 1;
    // int length = 0;

    // int probability = 50;
    // int maxLevel = 14;  // log(128 * 128)
    listHeight = 1;
    length = 0;

    probability = 50;
    maxLevel = 14;  // log(128 * 128)
}

/**
 * The assignment= operator.
 * @param other The SkipList to copy into ourselves.
 * @return The current object
 * @see copy()
 */
const SkipList& SkipList::operator=(const SkipList & other)
{
    if(this != &other)
    {
        clear();
        copy(other);
    }

    return *this;
}



/**
 * Inserts a new node into the sorted order in the list, initialized with the provided values.
 * Will replace the value at key if it already exists
 * @param key The key to associate with the new Node
 * @param value The value to associate with the new Node
 */
void SkipList::insert(int key, HSLAPixel value)
{

    SkipNode *temp = this->find(key);
    if (temp)
    {
        temp->value = value;
        ////3.12 10:57 return after changing the value
        return;
    }   

    length++;

    int newNodeLevel = levelGenerator();

    SkipNode * traverse = head;

    int level=head->nodePointers.size()-1;

    // Set up traverse to point to the node right before where we want to insert
    ////3.12 11:05 change the judge condition
    // while ((traverse->nodePointers[0].next != tail ||(level!=0)) && level >= 0)
    while (traverse->nodePointers[0].next != tail && (level >= 0))
    {
        int nextKey = traverse->nodePointers[level].next->key;

        if (key < nextKey)
        {
            level--;
            if(level < 0 )
                break;
        }
        else 
        {
            traverse = traverse->nodePointers[level].next;
            level = traverse->nodePointers.size()-1;
        }

    }

    // expand head and tail to encompass the new height of the list, if needed
    for(int i = listHeight; i < max(this->listHeight, newNodeLevel); i++)
    {
        head->nodePointers.push_back(SkipPointer());
        tail->nodePointers.push_back(SkipPointer());

        //// no need:::3.12 12:03 initialization for new head, tail  ???
        // if(i>listHeight)
        // {
        //     head->nodePointers[i].next= tail;
        //     tail->nodePointers[i].prev = head;
        // }
    }
     
    this->listHeight = max(this->listHeight, newNodeLevel);

    SkipNode * prev = traverse;
    SkipNode * forward = traverse->nodePointers[0].next;
    SkipNode * newNode = new SkipNode(key, value, newNodeLevel);

    int forwardLevel = 0;
    int backwardLevel = 0;

    ////no change :(maybe 3.12 11:42 chaneg maxlevel)
     int maxLevel = min(newNodeLevel, this->listHeight);
    //int forward_level = forward->nodePointers.size()-1;
    //int maxLevel = min(newNodeLevel, forward_level);
    
    ////3.12 11:54 change condition
    // while (forwardLevel < maxLevel)
    while (forwardLevel < maxLevel)         ///???
    {
        if(forward == tail)
        {
            forward->nodePointers[forwardLevel].prev = newNode;
            newNode->nodePointers[forwardLevel].next = forward;
            forwardLevel++;

        }
        ////3.12 13:03
        //if(forward->nodePointers.size() > (size_t)forwardLevel)
        else if(forward->nodePointers.size() > (size_t)forwardLevel)
        {
            forward->nodePointers[forwardLevel].prev = newNode;
            newNode->nodePointers[forwardLevel].next = forward;
            forwardLevel++;
        }
        else
        {
            forward = forward->nodePointers[0].next;
        }
    }
    ////3.12 11:54 change condition
    // while (backwardLevel < maxLevel)
    while (backwardLevel < maxLevel)
    {
        if(prev == head)
        {
            prev->nodePointers[backwardLevel].next = newNode;
            newNode->nodePointers[backwardLevel].prev = prev;
            backwardLevel++;
        }
        ////3.12 13:03
        //if(prev->nodePointers.size() > (size_t)backwardLevel)
        else if(prev->nodePointers.size() > (size_t)backwardLevel)
        {
            prev->nodePointers[backwardLevel].next = newNode;
            newNode->nodePointers[backwardLevel].prev = prev;
            backwardLevel++;
        }
        else
        {
            prev = prev->nodePointers[0].prev;
        }
    }


}
/**
 * A function that searches for the given key and returns the associated HSLAPixel
 * Returns (0, 0, 0, 50) if it's not found
 * @param key The key to search for
 * @return The pixel with the specified key, or (0, 0, 0, 50) if not found
 */
HSLAPixel SkipList::search(int key)
{
    SkipNode * retval;

    retval = find(key);
    ////3.12 10:50 switch the rwo return 
    // if (retval == NULL) 
    //     return retval->value;

    // return HSLAPixel(0,0,0, 50);
    if (retval == NULL)     return HSLAPixel(0,0,0, 50);
    return retval->value;
}

/**
 * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
 * Randomly calls findR or findI
 * @param key The key to search for in the list
 * @return A pointer to the node containing key, or NULL if not found in the list
 */
SkipNode * SkipList::find(int key)
{
    SkipNode * retval;
    if ((rand() % 2) ==0)
        retval=findR(key);
    else 
        retval=findI(key);

    return retval;
}


/**
 * Finds the given key in the list if it exists, and returns a pointer to the node containing it.
 * @param key The key to search for in the list
 * @return A pointer to the node containing key, or NULL if not found in the list
 */
SkipNode * SkipList::findR(int key)
{
    return findRHelper(key, head->nodePointers.size()-1, head);
}

/**
 * Helper function for findR.
 * @param key The key to search for
 * @param level The level we're searching through
 * @param curr The current node we're searching through
 * @return A pointer to the node with the given key, or NULL if it could not be found
 */
SkipNode * SkipList::findRHelper(int key, int level, SkipNode * curr)
{

    if (curr == tail || level < 0 || level>=listHeight)  //::??
        return NULL;

    int nextKey =  curr->nodePointers[level].next->key;

    //3.12 change here
    //SkipNode* ret;

    if (nextKey == key)
        // ret = curr->nodePointers[level].next;
        return curr->nodePointers[level].next;
    ////3.12 9:54,change to else if
    // if (nextKey > key) 
    else if (nextKey > key) 
        ////3.12 9:54
        //ret = findRHelper(key, level, curr);
        // ret = findRHelper(key, level-1, curr);
        return findRHelper(key, level-1, curr);

    else
        return findRHelper(key, level, curr->nodePointers[level].next);    
    ////3.12 9:54
    return NULL;
}

/**
 * An iterative find function
 * @param key The key to search for
 * @return A pointer to the node with the given key, or NULL if it could not be found
 */
SkipNode * SkipList::findI(int key)
{

    SkipNode * traverse = head;
    SkipNode * retNode=NULL;

    int level = head->nodePointers.size()-1;
    ////3.12 change the judge condition
     while (traverse->nodePointers[0].next != tail && level >= 0)
    //while ((traverse->nodePointers[0].next != tail ||(level!=0)) && level >= 0)
    {
        int nextKey = traverse->nodePointers[level].next->key;

        if (nextKey == key)
        {
            retNode = traverse->nodePointers[level].next;
            ////3.12 10:13 return the pointer
            return retNode;
        }
        else if (key < nextKey)
        {
            level--;
        }
        else {
            traverse=traverse->nodePointers[level].next;
            //level=traverse->nodePointers.size()-1; // slightly slows down code in our sorted inserts
        }

    }
    return NULL;
}



/**
 * Removes the node with the given key from the list.
 * @param key The key to search for and remove from the list
 * @return A boolean indicating whether a node was successfully removed from the list
 */
bool SkipList::remove(int key)
{
    // don't allow the removal of sentinel nodes
    if(key == INT_MAX || key == INT_MIN)
        return false;


    SkipNode * node = find(key);
    ////3.12 10:36 delete this line
    //bool ret = true;

    // can't remove a node that doesn't exist
    if(node == NULL)
        ////3.12 10:36 add return false
        //ret = false;
        return false;

    length--;

    // pass through all the pointers on either side of us
    for(size_t i = 0; i < node->nodePointers.size(); i++)
    {
        SkipNode * next = node->nodePointers[i].next;
        SkipNode * prev = node->nodePointers[i].prev;

        prev->nodePointers[i].next = next;
        next->nodePointers[i].prev = prev;
    }

    delete node;

    return true;
}



/**
 * A function that returns the keys of the list in a vector, using only next pointers.
 * @return a vector containing the keys from head to tail, including the sentinel values
 */
vector<int> SkipList::traverse()
{
    SkipNode * listPrintingTraverser = head;

    vector<int> ret;
    ////3.12 10:45 chaneg the while judge condition
    // while (listPrintingTraverser != tail)
    while (listPrintingTraverser != NULL)
    {
        ret.push_back(listPrintingTraverser->key);

        listPrintingTraverser = listPrintingTraverser->nodePointers[0].next;
    }

    return ret;
}

