#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#pragma once
#include "Domain.h"
#include <string.h>
typedef Material TElement;//We denote the data type we want to use with TElement->we can reuse the array in the future for other data types

typedef struct DynamicArray{
	TElement* elements;
	int size;
	int capacity;
}DynamicArray;


//Function that creates a new, empty dynamic array of materials with initial size "capacity"
DynamicArray* create_dynamic_array(int capacity);

//Function that destroys a dynamic array(the memory location is beeing freed)
void destroy_dynamic_array(DynamicArray* dynamic_array);

//Function that gives the number of elements in the array(0 if the array doesn't exist)
int sizeof_dynamic_array(DynamicArray* dynamic_array);

//Function that returns the element at a certain position in the dynamic array
TElement get_element_at_position_dynamic_array(DynamicArray* dynamic_array, int position);

//Function that updates(change value) the element at a certain position in the dynamic array
void update_element_at_position_dynamic_array(DynamicArray* dynamic_array, int position, TElement new_value);

//Function that adds an element to the end of the dynamic array
void append_dynamic_array(DynamicArray* dynamic_array, TElement element);

//Function that inserts an element in a certain position in the dynamic array
void add_to_position_dynamic_array(DynamicArray* dynamic_array, int position, TElement element);

// Function that deletes the element form the given position
void deletes_from_position_dynamic_array(DynamicArray* dynamic_array, int position);

//get the elements in the array
TElement* get_elements_dynamic_array(DynamicArray* dynamic_array);


#endif