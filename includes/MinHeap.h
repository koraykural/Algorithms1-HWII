/**
 * This file contains MinHeap class and implementation.
 * 
 * MinHeap uses templates.
 * 
 * Template class must implement operator< to work with MinHeap. 
 */

#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>
#include <stdexcept>

using namespace std;

template <class T>
class MinHeap
{
private:
    vector<T> data;

    /**
     * Returns index of parent of the element in the given index.
     * 
     * O(1)
     * 
     * @param index {int} Index of the child element.
     * 
     * @return {int} Index of the parent of the given child index.
     */
    int parent(int index)
    {
        int p_index = (index - 1) / 2;

        if (p_index < 0 || p_index >= get_size())
        {
            throw out_of_range("parent");
        }

        return p_index;
    }

    /**
     * Returns index of left child of the element in the given index.
     * 
     * O(1)
     * 
     * @param index {int} Index of the parent element.
     * 
     * @return {int} Index of the left child of the given parent index.
     */
    int left_child(int index)
    {
        int c_index = (index * 2) + 1;

        if (c_index < 0 || c_index >= get_size())
        {
            throw out_of_range("left_child");
        }

        return c_index;
    }

    /**
     * Returns index of right child of the element in the given index.
     * 
     * O(1)
     * 
     * @param index {int} Index of the parent element.
     * 
     * @return {int} Index of the right child of the given parent index.
     */
    int right_child(int index)
    {
        int c_index = (index * 2) + 2;

        if (c_index < 0 || c_index >= get_size())
        {
            throw out_of_range("right_child");
        }

        return c_index;
    }

    /**
     * Returns index of the smaller child.
     * 
     * Throws error if no child exists.
     * 
     * O(1)
     * 
     * @param parent_index {int} Index of the parent element.
     * 
     * @return {int} Index of the smaller child.
     */
    int get_smaller_child_index(int parent_index)
    {
        /* ------------------- Index of child or -1 if not exists ------------------- */
        int left_child_index;
        int right_child_index;

        try
        {
            left_child_index = left_child(parent_index);
        }
        catch (const out_of_range &e)
        {
            left_child_index = -1;
        }

        try
        {
            right_child_index = right_child(parent_index);
        }
        catch (const out_of_range &e)
        {
            right_child_index = -1;
        }
        /* ------------------------------------------------------------------------- */

        // If no child exists
        if (left_child_index < 0 && right_child_index < 0)
        {
            throw out_of_range("smaller_child_index");
        }

        // If only left child exists
        else if (left_child_index >= 0 && right_child_index < 0)
        {
            return left_child_index;
        }

        // If only right child exists
        else if (right_child_index >= 0 && left_child_index < 0)
        {
            return right_child_index;
        }

        // If left child is smaller
        else if (data.at(left_child_index) < data.at(right_child_index))
        {
            return left_child_index;
        }

        // If right child is smaller
        else
        {
            return right_child_index;
        }
    }

    /**
     * Swaps position of two elements.
     * 
     * O(1)
     * 
     * @param a {int} Index of the first element to be swapped.
     * @param b {int} Index of the second element to be swapped.
     */
    void swap(int a, int b)
    {
        if (a < 0 || b < 0 || a >= get_size() || b >= get_size())
        {
            throw out_of_range("swap");
        }

        std::swap(data[a], data[b]);
    }

    /**
     * Moves an element one level up in the tree. Then makes a 
     * recursive call for the same element again.
     * 
     * O(log(n))
     * 
     * @param index {int} Index of the element to be moved up.
     */
    void move_up(int index)
    {
        try
        {
            if (data.at(index) < data.at(parent(index)))
            {
                // Shift up if needed
                swap(index, parent(index));

                // Recursive call for parent
                move_up(parent(index));
            }
        }
        catch (out_of_range)
        {
            return;
        }
    }

    /**
     * Moves an element one level down in the tree. Then makes a 
     * recursive call for the same element again.
     * 
     * O(log(n))
     * 
     * @param index {int} Index of the element to be moved down.
     */
    void move_down(int index)
    {
        try
        {
            int smaller_child_index = get_smaller_child_index(index);

            // Swap parent with smaller child, if needed
            if (data.at(index) > data.at(smaller_child_index))
            {
                // Shift down
                swap(index, smaller_child_index);

                // Recursive call for child
                move_down(smaller_child_index);
            }
        }
        catch (const out_of_range &e)
        {
            return;
        }
    }

public:
    /**
     * Default constructor.
     * 
     * Creates an empty min heap.
     */
    MinHeap()
    {
    }

    /**
     * Creates a min heap from an unordered vector.
     * 
     * O(n * log(n))
     * 
     * @param unordered_data {vector<T>} Unordered vector to construct heap from.
     */
    MinHeap(vector<T> unordered_data)
    {
        for (int i = 0; unordered_data.size(); i++)
        {
            insert(unordered_data.at(i));
        }
    }

    /**
     * Returns the element at given index.
     * 
     * Element is not removed from heap.
     * 
     * O(1)
     * 
     * @param i {int} Index of the element.
     * 
     * @return {T} Element at the given index.
     */
    T operator[](int i)
    {
        return data.at(i);
    }

    /**
     * Returns number of element in the heap.
     * 
     * O(1)
     * 
     * @return {int} Number of elements in heap.
     */
    int get_size() const
    {
        return data.size();
    }

    /**
     * Inserts a new element to the heap.
     * 
     * O(log(n))
     * 
     * @param value {T} Element to be inserted into heap.
     */
    void insert(T value)
    {
        // Append it as a leaf.
        data.push_back(value);

        // Move up to the correct position.
        move_up(get_size() - 1);
    }

    /**
     * Removes the minimum element from the heap.
     * 
     * O(log(n))
     * 
     * @return {T} Element with the smallest value.
     */
    T get_min()
    {
        if (get_size() == 0)
        {
            throw out_of_range("get_min");
        }

        // Store data to be returned in a variable
        T min_value = data[0];

        // Move latest leaf to root
        data[0] = data[get_size() - 1];

        // Remove old copy of the leaf
        data.pop_back();

        // Recursively move down leaf again
        move_down(0);

        return min_value;
    }

    /**
     * Updates the value at the given index.
     * 
     * O(log(n))
     * 
     * @param index {int} Index of the element to be updated.
     * 
     * @param new_value {double} New value of the element.
     */
    void update_value(int index, double new_value)
    {
        if (index < 0 || index >= get_size())
        {
            throw out_of_range("update_value");
        }

        T old_value = data[index];
        data[index] = new_value;

        // New value is smaller, move element upwards
        if (old_value > new_value)
        {
            move_up(index);
        }

        // New value is bigger, move element downwards
        else
        {
            move_down(index);
        }
    }
};

#endif
