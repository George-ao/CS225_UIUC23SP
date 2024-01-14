
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    //1-base
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    // if(currentIdx*2<=last_position)
    //     return true;
    // else return false;
    if(currentIdx*2>_elems.size()-1)
        return false;
    return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    // if(rightChild(currentIdx)>last_position)
    //     return leftChild(currentIdx);
    // if(higherPriority(_elems[leftChild(currentIdx)],_elems[rightChild(currentIdx)]))
    //     return leftChild(currentIdx);
    // else    
    //     return rightChild(currentIdx);
    if(rightChild(currentIdx)>_elems.size()-1)
        return leftChild(currentIdx);
    if(higherPriority(_elems[leftChild(currentIdx)],_elems[rightChild(currentIdx)]))
        return leftChild(currentIdx);
    else    
        return rightChild(currentIdx);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.

    //no need to heapify down
        //out of capacity
    if (currentIdx > _elems.size()-1)
        return;
        //no child
    if(!hasAChild(currentIdx))
        return;
    //need to heapify down

    size_t to_comapre = maxPriorityChild(currentIdx);
    
    if(!higherPriority(_elems[currentIdx], _elems[to_comapre]))
    {
        std::swap(_elems[currentIdx], _elems[to_comapre]);
        heapifyDown(to_comapre);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    std::vector<T>vc(1);
    vc[0] = T();
    _elems = vc;
    // _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    std::vector<T>vc(1);
    vc[0] = T();
    _elems = vc;

    // _elems.push_back(T());
    // for(size_t i=0;i<=elems.size()-1;i++)
    // {
    //     push(elems[i]);
    // }
    for(size_t i=0;i<=elems.size()-1;i++)
    {
        _elems.push_back(elems[i]);
    }
    for(size_t i=_elems.size()-1;i>0;i--)
    {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority

    //swap with last element
    T highest_priority = _elems[1];
    _elems[1] = _elems[_elems.size()-1];
    _elems.pop_back();

    //restore heap property
    heapifyDown(1);

    //return pop value
    return highest_priority;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap

    _elems.push_back(elem);
    //restore heap property
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    if(_elems.size()<=1)
        return true;
    else 
        return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}