#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"
#include <stdarg.h>

typedef struct Service {
	DynamicArray* materials;
}Service;

//The structure to store an operation(a function)
typedef struct Operation {
	Material material;
	Material undo_material;
	void (*function)(DynamicArray*, ...);
	void (*undo_function)(DynamicArray*, ...);
	int undo_position, redo_position;
	
}Operation;

//The structure to store the undo-redo stacks
typedef struct Undo_Redo {
	Operation* undo_stack;
	Operation* redo_stack;
	int undo_length, redo_length;
	int undo_capacity, redo_capacity;
}Undo_Redo;

//Function that adds an operation's reverse to the undo stack a
void add_operation_to_undo(Operation operation, Undo_Redo* undo);

//Function that adds an operation to the redo stack
void add_operation_to_redo(Operation operation, Undo_Redo* redo);

//Function that executes the undo
void undo_func(Undo_Redo* undo, DynamicArray*);

//Function that executes the redo
void redo_func(Undo_Redo* undo, DynamicArray*);


//Function that creates an undo-redo structure
Undo_Redo create_undo_redo();





/// <summary>
/// This function initialse the given list of materials for the bakery with 10 elements
/// </summary>
/// <param name="materials_list"></param> This parameter is the array of materials which we want to initialise
void initialise_with_10(DynamicArray* materials_list);

//Function that adds the given material to the end if option = NULL and to the given position(position-'0') otherwise
void add_material(DynamicArray* materials, int position, Material material);

//Function that deletes a material from the given position in the list
void delete_material(DynamicArray* materials, int position, Material mat);

//Function that updates a material from a given position in the list
void update_material(DynamicArray* materials, int position, Material new_value);

//Function that returns certain materials past their expiration date containing a given string(can be empty => all dysplayed)
DynamicArray* materials_past_expiration_date(DynamicArray* materials, char* given_string, Date today_date);

//Function that is like max for 2 given dates, it returns the greatest
int max_date(Date date1, Date date2);

//Creates and returns a Date structure from a given string(format dd.mm.yyyy)
Date create_date_from_string(char* given_string);

//Function that sorts the given dynamic array ascending or descending(user choise) by the quantities
void sort_by_quantity(DynamicArray* materials, char* option);


//Function that returns the suppliers that provuded the most materials(we find all the materials from them and add the quantities)
//The number_of_suppliers parameter is passed to save the total number of suppliers we'll need for printing  
char** suppliers_most_materials(DynamicArray* materials, int *no_suppliers, char** suppliers);


#endif // !SERVICE_H