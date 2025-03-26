#include "Domain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Repository.h"

DynamicArray* create_dynamic_array(int capacity)
{
	DynamicArray* dynamic_array = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (dynamic_array == NULL) {
		printf("Memory allocation failed for dynamic array!");
		return NULL;
	}

	dynamic_array->elements = (TElement*)malloc(capacity * sizeof(TElement));
	if (dynamic_array->elements == NULL)
	{
		free(dynamic_array);
		printf("Memory allocation failed for dynamic array elements!");
		return NULL;
	}
	dynamic_array->size = 0;
	dynamic_array->capacity = capacity;
	return dynamic_array;
}

void destroy_dynamic_array(DynamicArray* dynamic_array)
{
	if (dynamic_array) {
		free(dynamic_array->elements);
		free(dynamic_array);
	}
}

int sizeof_dynamic_array(DynamicArray* dynamic_array)
{
	if (dynamic_array) {
		return dynamic_array->size;
	}
	return 0;
}

TElement get_element_at_position_dynamic_array(DynamicArray* dynamic_array, int position)
{
	if (position >= 0 && position < sizeof_dynamic_array(dynamic_array))
	{
		return dynamic_array->elements[position];
	}
	//TODO: raise error in the future for wrong position given
}


void update_element_at_position_dynamic_array(DynamicArray* dynamic_array, int position, TElement new_value)
{
	if (position >= 0 && position < sizeof_dynamic_array(dynamic_array))
	{
		dynamic_array->elements[position] = new_value;
	}
	//TODO: raise error in the future for wrong position given
}

//Reallocates more memory if the current capacity is not enough
void resize_dynamic_array_bigger(DynamicArray* dynamic_array)
{
	int new_capacity = dynamic_array->size * 2;
	TElement* new_elements = (TElement*)realloc(dynamic_array->elements, new_capacity*sizeof(TElement));
	if (new_elements == NULL) {
		printf("Memory reallocation failed for dynamic array!");
		return;
	}
	dynamic_array->capacity = new_capacity;
	dynamic_array->elements = new_elements;
	return;
}

void append_dynamic_array(DynamicArray* dynamic_array, TElement element)
{
	if (dynamic_array->size >= dynamic_array->capacity) {
		resize_dynamic_array_bigger(dynamic_array);
	}
	dynamic_array->elements[dynamic_array->size++] = element;
}

void add_to_position_dynamic_array(DynamicArray* dynamic_array, int position, TElement element)
{
	if (position >= 0 && position < sizeof_dynamic_array(dynamic_array)) {
		if (dynamic_array->size >= dynamic_array->capacity) {
			resize_dynamic_array_bigger(dynamic_array);
		}
		for (int i = dynamic_array->size; i > position; i--) {
			dynamic_array->elements[i] = dynamic_array->elements[i - 1];
		}

		dynamic_array->size++;
		dynamic_array->elements[position] = element;
		return;
	}
	//TODO: raise error in the future for wrong position given
}


void deletes_from_position_dynamic_array(DynamicArray* dynamic_array, int position)
{
	
	if (position >= 0 && position < sizeof_dynamic_array(dynamic_array)) {
		for (int i = position; i < dynamic_array->size; i++) {
			dynamic_array->elements[i] = dynamic_array->elements[i + 1];
			
		}
		dynamic_array->size--;
	}
	
	//TODO: raise error in the future for wrong position given
}

//get the elements in the array
TElement* get_elements_dynamic_array(DynamicArray* dynamic_array)
{
	return dynamic_array->elements;
}


//typedef struct MaterialsRepository {
//	Material materials_list[10000];
//}MaterialsRepository;

