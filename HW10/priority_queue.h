#ifndef priority_queue_h_
#define priority_queue_h_

#include <cassert>
#include <iostream>
#include <vector>
#include <map>

// The DistancePixel_PriorityQueue is a customized, non-templated
// priority queue that stores DistancePixel pointers in a heap.  The 
// elements in the heap can be looked up in a map, to quickly find out
// the current index of the element within the heap.

// ASSIGNMENT: The class implementation is incomplete.  Finish the
//   implementation of this class, and add any functions you need.

// =========================================================================

class DistancePixel_PriorityQueue {

 public:
  
  // --------------------------
  // CONSTRUCTORS
  // default constructor
  DistancePixel_PriorityQueue() {}
  // construct a heap from a vector of data
  DistancePixel_PriorityQueue(const std::vector<DistancePixel*> &values) {
    //loop through values and push each index, which calls percolate up so it will go
    //to the correct position
    for(unsigned int i = 0; i<values.size(); i++){
      push(values[i]);
    }
  }

  // ------------------------
  // ACCESSORS
  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }
  int last_non_leaf() { return (size()-1) / 2; }
  int get_parent(int i) { assert (i > 0 && i < size()); return (i-1) / 2; }
  bool has_left_child(int i) { return (2*i)+1 < size(); }
  bool has_right_child(int i) { return (2*i)+2 < size(); }
  int get_left_child(int i) { assert (i >= 0 && has_left_child(i)); return 2*i + 1; }
  int get_right_child(int i) { assert (i >= 0 && has_right_child(i)); return 2*i + 2; }

  // read the top element
  const DistancePixel* top() const  {
    assert(!m_heap.empty());
    return m_heap[0]; 
  }

  // is this element in the heap?
  bool in_heap(DistancePixel* element) const {
    std::map<DistancePixel*,int>::const_iterator itr = backpointers.find(element);
    return (itr != backpointers.end());
  }

  // add an element to the heap
  void push(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr == backpointers.end());
    m_heap.push_back(element);
    backpointers[element] = m_heap.size()-1;
    this->percolate_up(int(m_heap.size()-1));
  }

  // the value of this element has been edited, move the element up or down
  void update_position(DistancePixel* element) {
    std::map<DistancePixel*,int>::iterator itr = backpointers.find(element);
    assert (itr != backpointers.end());
    this->percolate_up(itr->second);
    this->percolate_down(itr->second);
  }
  
  // remove the top (minimum) element
  void pop() {
    assert(!m_heap.empty());
    int success = backpointers.erase(m_heap[0]);
    assert (success == 1);
    m_heap[0] = m_heap.back();
    m_heap.pop_back();
    this->percolate_down(0);
  }
  
 private:

  // REPRESENTATION
  // the heap is stored in a vector representation (the binary tree
  // structure "unrolled" one row at a time)
  std::vector<DistancePixel*> m_heap;
  // the map stores a correpondence between elements & indices in the heap
  std::map<DistancePixel*,int> backpointers;

  // private helper functions
  void percolate_up(int i) {
    //check that the given index is not out of bounds and that the size is more than 1
    if(i>=int(m_heap.size()) || i<0 || m_heap.size() ==1){
      return;
    }
    int parent = (i-1) / 2;
    //loop until parent is the root
    while(parent>=0){
      //swap the parent and the current index if the index has a smaller value
      if(m_heap[parent]->getValue()>m_heap[i]->getValue()){
        DistancePixel* temp = m_heap[parent];
        m_heap[parent] = m_heap[i];
        m_heap[i] = temp;
        //move index up, move parent up
        i = parent;
        parent = (i-1) / 2;
      }
      else{
        break;
      }
    }
  }
  
  void percolate_down(int i) {
    //check that the given index is not out of bounds and that the size is more than 1
    if(i>=int(m_heap.size()) || i<0 || m_heap.size() ==1){
      return;
    }
    int left = 2*i + 1;
    int right = 2*i + 2;
    int size = m_heap.size();
    int child;
    //loop until we have reached bottom, or the left child is out of bounds
    while(left<size){
      //find smaller of left and right child
      if(right<size && m_heap[right]->getValue()<m_heap[left]->getValue()){
        child = right;
      }
      else{
        child = left;
      }
      //swap child and current index if the child if index is greater value
      if(m_heap[i]->getValue()>=m_heap[child]->getValue()){
        DistancePixel* temp = m_heap[i];
        m_heap[i] = m_heap[child];
        m_heap[child] = temp;
        //move current index, left and right child down
        i = child;
        left = 2*i + 1;
        right = 2*i + 2;
      }
      else{
        break;
      }
    }
  }
};

#endif
