#ifndef DOMAIN_H
#define DOMAIN_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#pragma once

typedef struct Date {
    int day, month, year;
} Date;

typedef struct Material {
    char* name, *supplier;
    int quantity;
    Date expiration_date;
} Material;

// Constructor function for an element of type Material
// As parameters we have the fields that need to be initialized
Material* create_material(char* name, char* supplier, int quantity, Date expiration_date);

// Destructor function to deallocate the memory allocated in the constructor for a Material
// Frees only the fields that memory was allocated for
void destroy_material(Material* material);

void test_create_material();

// Getter function for the name of a Material
char* get_material_name(Material* material);

// Getter function for the supplier of a Material
char* get_material_supplier(Material* material);

// Getter function for the quantity of a Material
int get_material_quantity(Material* material);

// Getter function for the expiration date of a Material
Date get_material_expiration_date(Material* material);

#endif // DOMAIN_H