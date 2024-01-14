/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() 
{
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() 
{
  /// @todo Graded in MP3.1

  //two node pointer
  ListNode* curr_ptr = head_;
  ListNode* next_ptr = NULL;

  //return right now if the list is empty
  if(head_==NULL) return;
  if(empty()) return;

  //if have not cleared all the nodes
  while(curr_ptr->next!=NULL)
  {
    next_ptr = curr_ptr->next;
    delete curr_ptr;
    curr_ptr = next_ptr;
  }
  //idelete last node
  if(curr_ptr->next==NULL) 
  {
    delete curr_ptr;
    length_ = 0;
    head_ =NULL; tail_ = NULL;
    return;
  }
  //set length to 0
  length_ =0;
  head_ =NULL; tail_ = NULL;
  return;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1

  //create a new node on heap
  ListNode* insert_node = new ListNode(ndata);
  //if the list is empty
  if(empty())
  {
    head_ = insert_node;
    tail_ = insert_node;
    length_++;
    return;
  }
  head_->prev = insert_node;
  insert_node->next = head_;
  head_ = insert_node;
  length_++;
  return;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  //create a new node on heap
  ListNode* insert_node = new ListNode(ndata);
  //if the list is empty
  if(empty())
  {
    head_ = insert_node;
    tail_ = insert_node;
    length_++;
    return;
  }
  tail_->next=insert_node;
  insert_node->prev = tail_;
  tail_ = insert_node;
  length_++;
  return;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
  //reverse(head_->next->next,tail_->prev->prev);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) 
{
  /// @todo Graded in MP3.1

  //store the address of the startPoint and endPoint to prepare for  boudary condition
  ListNode* addr_start = startPoint;  
  ListNode* addr_end = endPoint;
  //if only one element, no reverse
  if(startPoint==NULL || endPoint==NULL) return;
  if(startPoint->next==NULL) return;
  if(endPoint->prev==NULL) return;
  //if point to same location, no reverse
  if(startPoint == endPoint) return;

  //use two node pointer to store node before startnode and after endnode
  ListNode* store_before = startPoint->prev;
  ListNode* store_after = endPoint->next;

  //previous judgement make sure that there are at least two nodes in the list
  ListNode* cur_ptr=startPoint->next;
  ListNode* prev_ptr=startPoint;
  ListNode* next_ptr = cur_ptr->next; //may be null!

  //notice that cur_ptr start one node after startpoint
    //break the loop only when the cur_ptr at the end
  //this loop deal with all the nodes except two endpoints
  while(cur_ptr != endPoint)
  {
    cur_ptr->next = prev_ptr;
    cur_ptr->prev = next_ptr;
    prev_ptr = cur_ptr;
    cur_ptr = next_ptr;
    next_ptr = next_ptr->next;
  }
  //deal with two endpoints here
  startPoint->prev = startPoint->next;
  startPoint->next = store_after; 
  endPoint->next = endPoint->prev;
  endPoint->prev = store_before;  
    //if endpoint is tail
  if(store_after!=NULL) 
  {
    //store_after->prev=startPoint;
    store_after->prev=addr_start;
  }
  else {tail_ = addr_start;}
    //if startpoint is head
  if(store_before!=NULL) 
  {
    //store_before->next = endPoint;
    store_before->next = addr_end;
  }
  else {head_ = addr_end;}

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1

  //get the length of the list
  int length = size();
  //if the list is less than n, reverse and return
  if(length<=n) 
  {
    reverse();
    return;
  }

  //count move times and add times
  int move = length / n;
  int add = length%n;

  ListNode* front_node=head_;
  ListNode* back_node =front_node;
  //deal with "move"
  for(int i =1;i<=move;i++)
  {
    for(int j =1; j<n; j++)
    {
      back_node =back_node->next; 
    }
    //reverse the block
    reverse(front_node,back_node); //return;
    //renew the front node 
    front_node = front_node->next;
    back_node = front_node;
  }
  //deal wiht "add"
  if(add!=0) reverse(front_node,tail_);

  

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() 
{
  if(length_==0 || head_->next==NULL || head_==NULL) return;

  /// @todo Graded in MP3.1
  ListNode* cur_ptr=head_;
  ListNode* next_ptr=NULL;

  //terminate this loop only when the next node is tail
  while(cur_ptr->next!=tail_)
  {
    //if next is not tail, remove 
    next_ptr = cur_ptr->next;
    cur_ptr->next = next_ptr->next;
    next_ptr->next->prev = cur_ptr;
    //insert it as tail
    tail_->next = next_ptr;
    next_ptr->next=NULL;
    next_ptr->prev = tail_;
    tail_ = next_ptr;
    //renew the cur_ptr
    cur_ptr = cur_ptr->next;
  }

}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2

    //find the position of the split node 
    ListNode* find_before_ptr = start;
        //loop, so get the pointer of the node before the second head
    for(int counter=1;counter<splitPoint;counter++)
    {
        find_before_ptr = find_before_ptr->next;
    }
    //disconnect them
    ListNode* target = find_before_ptr->next;
    find_before_ptr->next=NULL;
    target->prev = NULL;
    //return the pointer
    return target;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2

  //input judge, so after that both list must be not empty 
  if(second==NULL) return first;
  if(first==NULL) return second;
  
  //head
  ListNode* head = first;
  //merge 
  ListNode* move_first=first;
  ListNode* move_second=second;
    //if not iterate through both lists
//   while( !(move_first==NULL && move_second==NULL) )
  while( move_first!=NULL)
  {
    //if the data in the second list is bigger, then move the second node one forward 
    if(move_first->data<move_second->data)
    {
        if(move_first->next==NULL) break;
        move_first = move_first->next;

        continue;
    }
    //need to insert
    else
    {
        //insert as the first, change head to second
        if(move_first->prev==NULL)
        {
            //store the node in the second list
            head = second;
            ListNode* store = move_second->next;
            move_second->next = move_first;
            move_first->prev = move_second;
            move_second = store;
            if(store==NULL) return head;
            move_second->prev = NULL;
            
            if(move_second!=NULL) move_second->prev = NULL;
            else {return head;}
            //continue;
        }
        //not insert as front
        else
        {
            ListNode* before_move_first = move_first->prev;
            ListNode* store = move_second->next;
            before_move_first->next = move_second;
            move_second->prev = before_move_first;
            move_first->prev = move_second;
            move_second->next = move_first;
            move_second = store;
            //move_second->prev=NULL;
            //continue;

        }        
        //if the second list is empty, we are done
        if(move_second==NULL) return head;
        continue;
    }
  }

  //move first ==null insert the rest of second list directly
  move_first->next = move_second;
  move_second->prev = move_first;

  //return
  return head;
}

template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2

    //base
    if(chainLength==0) return start;
    if(chainLength==1) return start; 

    //recurse   
    ListNode* divide;

    //divide into two 
    divide= split(start,chainLength/2);
    //mergesort each
    start = mergesort(start,chainLength/2);
    divide = mergesort(divide,chainLength%2+chainLength/2);
    //return merge together
    return merge(start,divide);
    //return start;
    // List<T> newlist;
    // newlist =  split(chainLength/2);
    // sort();
    // newlist.sort();
    // mergeWith(newlist);
    // return start;
}
