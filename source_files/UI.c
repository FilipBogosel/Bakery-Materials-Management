#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Service.h"
#include <crtdbg.h>

//Function that prints the list of materials
void  print_materials(DynamicArray* materials)
{
	printf("We have %d materials:\n", sizeof_dynamic_array(materials));
	for (int i = 0; i < sizeof_dynamic_array(materials); i++) {
		Material material = get_element_at_position_dynamic_array(materials, i);
		printf("Element %d:\n", i);
		printf("Name: %s\n", get_material_name(&material));
		printf("Supplier: %s\n", get_material_supplier(&material));
		printf("Quantity: %d\n", get_material_quantity(&material));
		printf("Expiration date: %d.%d.%d\n\n", get_material_expiration_date(&material).day, get_material_expiration_date(&material).month, get_material_expiration_date(&material).year);

	}
	return;
}

//Function that reads a material from the console, because we need this more than once
Material* read_material_console() {
	char expiration_date[11];
	char name[50];
	char supplier[50];
	int quantity;
	Date date;
	printf("Name: ");
	int i = scanf("%49s", name);//we read at most 49 characters
	if (i != 1) {
		while (getchar() != '\n');
		printf("Invalid input for name!\n");
		return NULL;
	}
	printf("Supplier: ");
	int j = scanf("%49s", supplier);
	if (j != 1) {
		while (getchar() != '\n');
		printf("Invalid input for supplier!\n");
		return NULL;
	}
	printf("Quantity: ");
	int l = scanf("%d", &quantity);
	if (l != 1) {
		while (getchar() != '\n');
		printf("Invalid input for quantity!\n");
		return NULL;
	}
	printf("Expiration date(dd.mm.yyyy): ");
	int k = scanf("%10s", expiration_date);
	if (k != 1) {
		while (getchar() != '\n');
		printf("Invalid input for expiration date!\n");
		return NULL;
	}
	date = create_date_from_string(expiration_date);
	if (date.day == 0 && date.month == 0 && date.year == 0) {
		printf("Invalid date!\n");
		return NULL;
	}
	Material* material = create_material(name, supplier, quantity, date);
	return material;
}

//Function that print the sorted list of materials by quantity from the given supplier
//We'll be given a string for the supplier and a value for the maximum quantity
void print_sorted_materials_from_supplier(DynamicArray* materials, char* supplier, int max_quantity, char* sort_option)
{
	DynamicArray *result_array = create_dynamic_array(sizeof_dynamic_array(materials));
	Material* material_elements = get_elements_dynamic_array(materials);
	for (int i = 0; i < sizeof_dynamic_array(materials); i++) {
		Material material = material_elements[i];
		if (strcmp(get_material_supplier(&material), supplier) == 0 && get_material_quantity(&material)<=max_quantity) {
			add_material(result_array,-1 , material);
		}
	}
	if (sizeof_dynamic_array(result_array) == 0)
	{
		printf("No such elements found!\n");
		destroy_dynamic_array(result_array);
		return;
	}
	sort_by_quantity(result_array, sort_option);
	print_materials(result_array);
	destroy_dynamic_array(result_array);
	
}

void print_suppliers(char** suppliers_list, int number_of_suppliers) {
	for (int i = 0; i < number_of_suppliers; i++) {
		printf("Supplier1 %d: %s\n",i,suppliers_list[i]);
	}
}




void print_menu() {
	printf("1. Add a new material\n");
	printf("2. Update a material\n");
	printf("3. Delete a material\n");
	printf("4. List all materials\n");
	printf("5. List materials past expiration date(you can provide a string for searching specific materials)\n");
	printf("6. List suppliers by the most materials delivered\n");
	printf("7. Display all materials from a given supplier which have the quantity less than a given value\n");
	printf("8. Undo\n");
	printf("9. Redo\n");
	printf("10. Exit\n");

}
int main()
{
	//test_create_material();
	DynamicArray* materials = create_dynamic_array(100);
	initialise_with_10(materials);
	Undo_Redo undo = create_undo_redo();
	while (1) {
		print_menu();
		printf("Your choice: ");
		int option;
		int i = scanf("%d",&option);
		if (i != 1) {
			while (getchar() != '\n');
			printf("Invalid option!\n");
			continue;
		}
		if (option == 1) {
			Material* material = read_material_console();
			if (!material) {
				printf("Failed to create material. Invalid input/memory error.\n");
				continue;
			}
			add_material(materials,-1 , *material);
			printf("Material added successfully!\n");
			Operation operation = { *material, *material, add_material, delete_material, sizeof_dynamic_array(materials) - 1, - 1 };
			add_operation_to_undo(operation, &undo);
			undo.redo_length = 0;
			destroy_material(material);
			
		}
		if (option == 2) {
			Material* material = read_material_console();
			int position;
			printf("Position: ");
			scanf("%d", &position);
			Material* old_material = (Material*)malloc(sizeof(Material));
			*old_material = get_element_at_position_dynamic_array(materials, position);
			update_material(materials, position, *material);
			printf("Material updated successfully!\n");
			Operation operation = { *material, *old_material, update_material, update_material, position, position };
			add_operation_to_undo(operation, &undo);
			undo.redo_length = 0;
			destroy_material(material);
			destroy_material(old_material);
		}
		if (option == 3) {
			int position;
			printf("Position: ");
			scanf("%d", &position);
			Material material = get_element_at_position_dynamic_array(materials, position);
			Material* null_material = create_material("", "", 0, create_date_from_string("01.01.0001"));
			delete_material(materials, position, *null_material);
			printf("Material deleted successfully!\n");
			Operation operation = {*null_material, material,delete_material,add_material, position, position };
			add_operation_to_undo(operation, &undo);
			undo.redo_length = 0;
			destroy_material(null_material);

		}
		if (option == 4) {
			print_materials(materials);
		}
		if (option == 5) {
			char given_string[50];
			printf("String to search in name(write \"-\" if you don't want any specific name): ");
			scanf("%49s", given_string);
			char today_date[11];
			printf("Today's date(dd.mm.yyyy): ");
			scanf("%10s", today_date);
			Date date = create_date_from_string(today_date);
			DynamicArray* result = materials_past_expiration_date(materials, given_string, date);
			if (sizeof_dynamic_array(result) == 0) printf("No materials found!\n");
			print_materials(result);
			destroy_dynamic_array(result);
		}
		if (option == 6) {
			int no_suppliers = 0;
			char** suppliers;
			int length = sizeof_dynamic_array(materials);
			suppliers = (char**)malloc(length * sizeof(char*));
			if (suppliers == NULL) {
				printf("Unsucceed!");
				continue;
			}
			for (int i = 0; i < length; i++)
			{
				suppliers[i] = (char*)malloc(100 * sizeof(char)); 
			}
			suppliers = suppliers_most_materials(materials, &no_suppliers, suppliers);
			if (suppliers == NULL) {
				printf("Didn't work!");
				free(materials);
			}
			print_suppliers(suppliers, no_suppliers);
			for (int i = 0; i < length; i++) {
				free(suppliers[i]);
			}
			free(suppliers);
		}
		if (option == 7) {
			char sort_option[5];
			printf("Choose how you want to sort(asc-> ascending, desc-> descending) :");
			scanf("%s", sort_option);
			printf("The supplier: ");
			char supplier[50];
			scanf("%49s", supplier);
			int max_quantity;
			printf("The maximum quantity: ");
			scanf("%d", &max_quantity);
			print_sorted_materials_from_supplier(materials, supplier, max_quantity, sort_option);


		}
		if (option == 8) {
			if (undo.undo_length == 0) printf("No more undos!\n");
			else {
				undo_func(&undo, materials);
				add_operation_to_redo(undo.undo_stack[undo.undo_length], &undo);
			}

		}
		if (option == 9) {
			if (undo.redo_length == 0) printf("No more redos!\n");
			else {
				redo_func(&undo, materials);
			}
			
		}
		if (option == 10) break;

	}
	if (undo.undo_stack != NULL) free(undo.undo_stack);
	if (undo.redo_stack != NULL) free(undo.redo_stack);
	if (materials != NULL) {
		destroy_dynamic_array(materials);
	}

	

	_CrtDumpMemoryLeaks();

	return 0;
}

