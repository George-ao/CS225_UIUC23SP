/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    // Your code here
    //base case: if the stack is empty
    if(s.empty()) return T(); 
    //recurse step
    T cur_value = s.top();
    T store = s.top();
    s.pop();
    cur_value=cur_value+sum(s);
    s.push(store);
    return cur_value;

    //return T(); // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    // optional: queue<T> q2;
    //return if it is empty
    if(q.empty()) return; 

    //int block_count=0;
    int tol_elem = q.size();
    int elem_count = 1;
    for(int i=1;elem_count<=tol_elem; i++)
    {
        //do not need to be reverse if i is odd number
        if(i%2!=0)
        {
            //move the elem in current block to the end

            //chekc if the block is not "complete"
            int judge_point;
            if(elem_count+i>tol_elem) judge_point = tol_elem-elem_count+1;
            else judge_point = i;
            for(int j=1;j<=judge_point;j++)
            {
            T store = q.front();
            q.pop();
            q.push(store);
            }
            elem_count += i;
        }   
        //needed to be reverse
        else
        {   
            //chekc if the block is not "complete"
            int judge_point;
            if(elem_count+i>tol_elem) judge_point = tol_elem-elem_count+1;
            else judge_point = i;
            //push to stack
            for(int j=1;j<=judge_point;j++)
            {
            T store = q.front();
            q.pop();
            s.push(store);
            }
            //push to queue
            for(int j=1;j<=judge_point;j++)
            {
            T store = s.top();
            s.pop();
            q.push(store);
            }          
            elem_count += i;  
        }
    //block_count++;
    }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional 
    //T temp1; // rename me
    //T temp2; // rename :)

    //base case: if the stack is empty
    if(s.empty()) return true; 

    //use recurse to reach the stack bottom first
    T cur_s_value = s.top();
    s.pop();
    retval= verifySame(s,q)&&retval;

    //check if the queue front equal to stack top
    retval = (q.front()==s.top())&&retval;
    //recover the stack and change front element of the stack
    T cur_q_value = q.front();
    q.pop();
    q.push(cur_q_value);
    s.push(cur_s_value);


    return retval;
}

}