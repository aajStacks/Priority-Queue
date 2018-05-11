	// FILE: pqueue2.cpp
// IMPLEMENTS: PriorityQueue (See pqueue2.h for documentation.)
//-- IMPLEMENTED BY: (Mohammed Hossain, EMAIL: mhossai007@citymail.cuny.edu)

// INVARIANT for the PriorityQueue Class:
//   1. The member variable many_items is the number of items in the
//      PriorityQueue.
//   2. The items themselves are stored in the member variable heap,
//      which is a partially filled array organized to follow the usual
//      heap storage rules from Chapter 11 of the class notes.
// NOTE: Private helper functions are implemented at the bottom of this
// file along with their precondition/postcondition contracts.

#include <cassert>    // Provides assert function
#include <iomanip>   // Provides setw
#include <iostream>  // Provides cin, cout
#include <math.h>      // Provides log2
#include "pqueue2.h"
using namespace std;

PriorityQueue::PriorityQueue( )
{
	heap[CAPACITY];
	many_items = 0;
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
    if(many_items == 0)
    {
        heap[many_items].data = entry;
        heap[many_items].priority = priority;
        ++many_items;
    }

    else
    {
        heap[many_items].data = entry;
        heap[many_items].priority = priority;
        unsigned int i = many_items;
        ++many_items;
        while(parent_priority(i)< priority)
        {
            swap_with_parent(i);
            i = parent_index(i);
        }
    }

}

PriorityQueue::Item PriorityQueue::get_front( )
{
	assert(many_items>0);
	if(many_items == 1)
    {
        Item front_value = heap[0].data;
        --many_items;
        return front_value;
    }
    else
    {
        Item front_value = heap[0].data;
        heap[0] = heap[many_items-1];
        unsigned int priority = heap[many_items].priority;
        unsigned int k=0;
        while((k<many_items)&& !is_leaf(k)&&big_child_priority(k)>priority)
        {
            unsigned int j = big_child_index(k);
            swap_with_parent(big_child_index(k));
            k=j;
        }
        --many_items;
        return front_value;
    }
}

bool PriorityQueue::is_leaf(size_t i) const
// Precondition: (i < many_items)
// Postcondition: If heap[i] has no children in the heap, then the function
// returns true. Otherwise the function returns false.
{
	if(2*i+1>=many_items)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

size_t PriorityQueue::parent_index(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the index of the parent of heap[i].
{
    assert((i>0) && (i<many_items));
	return (i-1)/2;
}

unsigned int PriorityQueue::parent_priority(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the priority of the parent of heap[i].
{
    return heap[(i-1)/2].priority;
}

size_t PriorityQueue::big_child_index(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value is the index of one of heap[i]'s children.
// This is the child with the larger priority.
{
	assert(!is_leaf(i));
	if((2*i)+2<many_items)
    {
        if(heap[(2*i)+1].priority>heap[(2*i)+2].priority)
        {
            return (2*i)+1;
        }
        else
        {
            return (2*i)+2;
        }
    }
    else
    {
        return (2*i)+1;
    }
}

unsigned int PriorityQueue::big_child_priority(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value heap[big_child_index(i)].priority
{
	return heap[big_child_index(i)].priority;
}

void PriorityQueue::swap_with_parent(size_t i)
// Precondition: (i > 0) && (i < many_items)
// Postcondition: heap[i] has been swapped with heap[parent_index(i)]
{
        assert(i>0 && i< many_items);
        OneItemInfo temp_parent = heap[parent_index(i)];
        OneItemInfo temp_child = heap[i];
        heap[i]= temp_parent;
        heap[parent_index(i)]= temp_child;
}

void PriorityQueue::print_tree(const char message[ ], size_t i) const
// Postcondition: If the message is non-empty, then that has been written
// to cout. After the message, the portion of the heap with root at node
// node i has been written to the screen. Each node's data is indented
// 4*d, where d is the depth of the node.
// NOTE: The default argument for message is the empty string, and the
// default argument for i is zero. For example, to print the entire
// tree of a PriorityQueue p, with a message of "The tree:", you can call:
//     p.print_tree("The tree:");
// This call uses i=0, which prints the whole tree.
{
	const char NO_MESSAGE[] = "";
	size_t depth;

	if(message[0] != '\0')
    {
        cout<<message<<endl;
    }
    if(i>many_items)
    {
        cout<<"NO NODES"<<endl;
    }
    else
    {
        depth = int(log(double(i+1))/log(2.0));
        cout<<setw(depth*4)<< "";
        cout<<heap[i].data;
        cout << " (priority " << heap[i].priority << ")" << endl;
        if(2*i + 1 < many_items)
        {
            print_tree(NO_MESSAGE, 2*i +1);
        }
        if(2*i+2<many_items)
        {
            print_tree(NO_MESSAGE, 2*i+2);
        }
    }
}