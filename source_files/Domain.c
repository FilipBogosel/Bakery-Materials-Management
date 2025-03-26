#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Domain.h"

Material* create_material(char* name, char* supplier, int quantity, Date expiration_date)
{
    Material* material = (Material*)malloc(sizeof(Material)); // we allocate memory for the structure
	if (material == NULL) return NULL; // if the allocation failed we return NULL

    // Below we allocate memory for each char array in Material
    material->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    if (!material->name) {
        free(material);
        return NULL;
    }
    material->supplier = (char*)malloc(sizeof(char) * (strlen(supplier) + 1));
	if (!material->supplier) {
		free(material->name);
		free(material);
		return NULL;
	}
    // We copy the given strings to their respective fields in material
    strcpy_s(material->name, strlen(name) + 1, name);
    strcpy_s(material->supplier, strlen(supplier) + 1, supplier);
    // Assigning the int and struct. expiration_date directly
    material->quantity = quantity;
    material->expiration_date = expiration_date;
    return material;
}

// Function to deallocate the memory allocated in the creator for a material
// frees only the fields that memory was allocated for
void destroy_material(Material* material)
{
    free(material->name);
    free(material->supplier);
    free(material);
}

char* get_material_name(Material* material)
{
    if (material == NULL) return "\0";
    return material->name;
}

char* get_material_supplier(Material* material)
{
    if (material == NULL) return "\0";
    return material->supplier;
}

int get_material_quantity(Material* material)
{
    if (material == NULL) return 0;
    return material->quantity;
}


Date get_material_expiration_date(Material *material)
{
    return material->expiration_date;
}

void test_create_material()
{
    Date date = { 10, 10, 2025 };
    Material* material = create_material("sugar", "sugar.srl", 100, date);
    assert(material != NULL);
    assert(strcmp(material->name, "sugar") == 0);
    assert(strcmp(material->supplier, "sugar.srl") == 0);
    assert(material->quantity == 100);
    assert(material->expiration_date.day == 10 && material->expiration_date.month == 10 && material->expiration_date.year == 2025);
    destroy_material(material);
    ///printf("All tests passed!!!");
}