#include "Service.h"
#include <stdlib.h>


void initialise_with_10(DynamicArray* materials_list)
{
    materials_list->elements[0] = (Material){ "sugar", "sugar.srl", 100, {10, 10, 2025} };
    materials_list->elements[1] = (Material){ "flour", "flour.inc", 200, {15, 12, 2024} };
    materials_list->elements[2] = (Material){ "butter", "butter.co", 150, {20, 11, 2023} };
    materials_list->elements[3] = (Material){ "eggs", "eggs.ltd", 300, {25, 10, 2022} };
    materials_list->elements[4] = (Material){ "milk", "milk.farm", 250, {30, 9, 2021} };
    materials_list->elements[5] = (Material){ "yeast", "yeast.pro", 50, {5, 8, 2020} };
    materials_list->elements[6] = (Material){ "salt", "salt.mines", 400, {10, 7, 2025} };
    materials_list->elements[7] = (Material){ "chocolate", "choco.factory", 120, {15, 6, 2024} };
    materials_list->elements[8] = (Material){ "vanilla", "vanilla.extr", 80, {20, 5, 2023} };
    materials_list->elements[9] = (Material){ "baking powder", "baking.inc", 60, {25, 4, 2022} };
	materials_list->size = 10;
}

void add_material(DynamicArray* materials, int position, Material material)
{
    if (position == -1) {
        append_dynamic_array(materials, material);
        return;
    }
    //int int_position = atoi(position);
    add_to_position_dynamic_array(materials, position, material);
    return;
}

void delete_material(DynamicArray* materials, int position,Material mat)
{
    deletes_from_position_dynamic_array(materials, position);
    return;
}

void update_material(DynamicArray* materials, int position, Material new_value)
{
    update_element_at_position_dynamic_array(materials, position, new_value);
    return;
}

int max_date(Date date1, Date date2) {
    if (date1.year > date2.year) return 1;
    else if (date1.year < date2.year) return 0;
    else {
        if (date1.month > date2.month) return 1;
        else if (date1.month < date2.month) return 0;
        else {
            if (date1.day > date2.day) return 1;
            else return 0;
        }
    }
}


Date create_date_from_string(char* given_string)
{
    char day[3] = { given_string[0], given_string[1], '\0' };
    char month[3] = { given_string[3], given_string[4], '\0' };
    char year[5] = { given_string[6], given_string[7], given_string[8], given_string[9], '\0' };

    int day_int = atoi(day);
    if (!day_int) {
		return (Date) { 0, 0, 0 };
    }
    int month_int = atoi(month);
	if (!month_int) {
		return (Date) { 0, 0, 0 };
	}
    int year_int = atoi(year);
	if (!year_int) {
		return (Date) { 0, 0, 0 };
	}
    Date date = { day_int, month_int, year_int };
    return date;
}

void sort_by_quantity(DynamicArray* materials, char* option)
{
	if (strcmp(option, "asc")) {
		Material* elements = get_elements_dynamic_array(materials);
		int length = sizeof_dynamic_array(materials);
		for (int i = 0; i < length - 1; i++)
		{
            for (int j = i + 1; j < length; j++)
            {
                if (get_material_quantity(&elements[i]) < get_material_quantity(&elements[j])) {
                    Material aux = elements[i];
                    elements[i] = elements[j];
                    elements[j] = aux;
                }
            }
		}
	}
	else {
		Material* elements = get_elements_dynamic_array(materials);
		int length = sizeof_dynamic_array(materials);
		for (int i = 0; i < length - 1; i++)
		{
            for (int j = i + 1; j < length; j++)
            {
                if (get_material_quantity(&elements[i]) > get_material_quantity(&elements[j])) {
                    Material aux = elements[i];
                    elements[i] = elements[j];
                    elements[j] = aux;
                }
            }
		}
	}
}




DynamicArray* materials_past_expiration_date(DynamicArray* materials, char* given_string, Date today_date)
{
    DynamicArray* result = create_dynamic_array(sizeof_dynamic_array(materials));
    int length = sizeof_dynamic_array(materials);
    if (strcmp(given_string, "-") == 0) {
        Material *elements = get_elements_dynamic_array(materials);
        for (int i = 0; i < length; i++)
        {
            Date exp_date = get_material_expiration_date(&elements[i]);
            if (max_date(today_date,exp_date)) {
                add_material(result,-1, elements[i]);
            }
        }
    }
    else {
        Material* elements = get_elements_dynamic_array(materials);
        for (int i = 0; i < length; i++)
        {
            Date exp_date = get_material_expiration_date(&elements[i]);
            if (max_date(today_date, exp_date) && strstr(get_material_name(&elements[i]),given_string)) {
                add_material(result,-1,  elements[i]);
            }
        }
    }
    return result;
}



char** suppliers_most_materials(DynamicArray* materials, int* no_suppliers, char ** suppliers)
{
    int length = sizeof_dynamic_array(materials);
    int number = 100;
	Material* elements = get_elements_dynamic_array(materials);
    
	int* quantities = (int*)malloc(length * sizeof(int));
	int no_suppliers_aux = 0;
	for (int i = 0; i < length; i++)
	{
		int found = 0;
		for (int j = 0; j < no_suppliers_aux; j++)
		{
			if (strcmp(suppliers[j], get_material_supplier(&elements[i])) == 0) {
				quantities[j] += get_material_quantity(&elements[i]);
				found = 1;
			}
		}
		if (found == 0) {
			strcpy(suppliers[no_suppliers_aux], get_material_supplier(&elements[i]));
			quantities[no_suppliers_aux] = get_material_quantity(&elements[i]);
			no_suppliers_aux++;
		}
	}
	for (int i = 0; i < no_suppliers_aux - 1; i++)
	{
		for (int j = i + 1; j < no_suppliers_aux; j++)
		{
			if (quantities[i] < quantities[j]) {
				int aux = quantities[i];
				quantities[i] = quantities[j];
				quantities[j] = aux;
				char aux_string[100];
				strcpy(aux_string, suppliers[i]);
				strcpy(suppliers[i], suppliers[j]);
				strcpy(suppliers[j], aux_string);
			}
		}
	}
	free(quantities);
	*no_suppliers = no_suppliers_aux;
	return suppliers;
    
}

void add_operation_to_undo(Operation operation, Undo_Redo* undo)
{
    if (undo->undo_length == undo->undo_capacity)
    {
        undo->undo_stack = (Operation*)realloc(undo->undo_stack, (undo->undo_capacity * 2) * sizeof(Operation));
        undo->undo_capacity *= 2;
    }
    undo->undo_stack[undo->undo_length] = operation;
    undo->undo_length++;
}

void add_operation_to_redo(Operation operation, Undo_Redo* redo)
{
    if (redo->redo_length == redo->redo_capacity)
    {
        redo->redo_stack = (Operation*)realloc(redo->redo_stack, (redo->redo_capacity * 2) * sizeof(Operation));
        redo->redo_capacity *= 2;
    }
    redo->redo_stack[redo->redo_length] = operation;
    redo->redo_length++;
}



void undo_func(Undo_Redo* undo, DynamicArray* materials)
{
	if (undo->undo_length == 0) return;
	Operation operation = undo->undo_stack[undo->undo_length - 1];
	operation.undo_function(materials, operation.undo_position, operation.undo_material);
	undo->undo_length--;
	return;
}

void redo_func(Undo_Redo* undo, DynamicArray* materials)
{
	if (undo->redo_length == 0) return;
	Operation operation = undo->redo_stack[undo->redo_length - 1];
	operation.function(materials, operation.redo_position, operation.material);
	undo->redo_length--;
	return;
}

Undo_Redo create_undo_redo()
{
	Undo_Redo undo_redo;
	undo_redo.undo_stack = (Operation*)malloc(10 * sizeof(Operation));
	undo_redo.redo_stack = (Operation*)malloc(10 * sizeof(Operation));
	undo_redo.undo_length = 0;
	undo_redo.redo_length = 0;
	undo_redo.undo_capacity = 10;
	undo_redo.redo_capacity = 10;
	return undo_redo;
}







