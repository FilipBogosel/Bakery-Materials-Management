#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "Domain.h"
#include "Repository.h"
#include "Service.h"
#include <crtdbg.h>


void test_get_material_name() {
    Date date = { 10, 10, 2025 };
    Material* material = create_material("sugar", "sugar.srl", 100, date);
    assert(strcmp(get_material_name(material), "sugar") == 0);
    destroy_material(material);
}

void test_get_material_supplier() {
    Date date = { 10, 10, 2025 };
    Material* material = create_material("sugar", "sugar.srl", 100, date);
    assert(strcmp(get_material_supplier(material), "sugar.srl") == 0);
    destroy_material(material);
}

void test_get_material_quantity() {
    Date date = { 10, 10, 2025 };
    Material* material = create_material("sugar", "sugar.srl", 100, date);
    assert(get_material_quantity(material) == 100);
    destroy_material(material);
}

void test_get_material_expiration_date() {
    Date date = { 10, 10, 2025 };
    Material* material = create_material("sugar", "sugar.srl", 100, date);
    Date exp_date = get_material_expiration_date(material);
    assert(exp_date.day == 10 && exp_date.month == 10 && exp_date.year == 2025);
    destroy_material(material);
}

void test_create_dynamic_array() {
    DynamicArray* array = create_dynamic_array(10);
    assert(array != NULL);
    assert(array->size == 0);
    assert(array->capacity == 10);
    destroy_dynamic_array(array);
}

void test_append_dynamic_array() {
    DynamicArray* array = create_dynamic_array(2);
    Date date = { 10, 10, 2025 };
    Material* material = create_material("sugar", "sugar.srl", 100, date); // Use create_material
    append_dynamic_array(array, *material); // Store by value
    assert(array->size == 1);
    assert(strcmp(array->elements[0].name, "sugar") == 0);
    destroy_material(material); // Free the material
    destroy_dynamic_array(array);
}

void test_add_to_position_dynamic_array() {
    DynamicArray* array = create_dynamic_array(2);
    Material material1 = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    Material material2 = { "flour", "flour.inc", 200, {15, 12, 2024} };
    append_dynamic_array(array, material1);
    add_to_position_dynamic_array(array, 0, material2);
    assert(array->size == 2);
    assert(strcmp(array->elements[0].name, "flour") == 0);
    destroy_dynamic_array(array);
}

void test_deletes_from_position_dynamic_array() {
    DynamicArray* array = create_dynamic_array(2);
    Material material = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    append_dynamic_array(array, material);
    deletes_from_position_dynamic_array(array, 0);
    assert(array->size == 0);
    destroy_dynamic_array(array);
}

void test_update_element_at_position_dynamic_array() {
    DynamicArray* array = create_dynamic_array(2);
    Material material1 = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    Material material2 = { "flour", "flour.inc", 200, {15, 12, 2024} };
    append_dynamic_array(array, material1);
    update_element_at_position_dynamic_array(array, 0, material2);
    assert(strcmp(array->elements[0].name, "flour") == 0);
    destroy_dynamic_array(array);
}

void test_initialise_with_10() {
    DynamicArray* array = create_dynamic_array(10);
    initialise_with_10(array);
    assert(array->size == 10);
    assert(strcmp(array->elements[0].name, "sugar") == 0);
    destroy_dynamic_array(array);
}

void test_add_material() {
    DynamicArray* array = create_dynamic_array(2);
    Material material = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    add_material(array, -1, material);
    assert(array->size == 1);
    assert(strcmp(array->elements[0].name, "sugar") == 0);
    destroy_dynamic_array(array);
}

void test_delete_material() {
    DynamicArray* array = create_dynamic_array(2);
    Material material = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    append_dynamic_array(array, material);
    delete_material(array, 0, material);
    assert(array->size == 0);
    destroy_dynamic_array(array);
}

void test_update_material() {
    DynamicArray* array = create_dynamic_array(2);
    Material material1 = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    Material material2 = { "flour", "flour.inc", 200, {15, 12, 2024} };
    append_dynamic_array(array, material1);
    update_material(array, 0, material2);
    assert(strcmp(array->elements[0].name, "flour") == 0);
    destroy_dynamic_array(array);
}

void test_max_date() {
    Date date1 = { 10, 10, 2025 };
    Date date2 = { 15, 12, 2024 };
    assert(max_date(date1, date2) == 1);
    assert(max_date(date2, date1) == 0);
}

void test_create_date_from_string() {
    Date date = create_date_from_string("10.10.2025");
    assert(date.day == 10);
    assert(date.month == 10);
    assert(date.year == 2025);
}

void test_sort_by_quantity() {
    DynamicArray* array = create_dynamic_array(3);
    Material material1 = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    Material material2 = { "flour", "flour.inc", 200, {15, 12, 2024} };
    Material material3 = { "butter", "butter.co", 150, {20, 11, 2023} };
    append_dynamic_array(array, material1);
    append_dynamic_array(array, material2);
    append_dynamic_array(array, material3);
    sort_by_quantity(array, "asc");
    assert(array->elements[0].quantity == 100);
    assert(array->elements[1].quantity == 150);
    assert(array->elements[2].quantity == 200);
    sort_by_quantity(array, "desc");
    assert(array->elements[0].quantity == 200);
    assert(array->elements[1].quantity == 150);
    assert(array->elements[2].quantity == 100);
    destroy_dynamic_array(array);
}

void test_materials_past_expiration_date() {
    DynamicArray* array = create_dynamic_array(3);
    Material material1 = { "sugar", "sugar.srl", 100, {10, 10, 2020} };
    Material material2 = { "flour", "flour.inc", 200, {15, 12, 2024} };
    Material material3 = { "butter", "butter.co", 150, {20, 11, 2019} };
    append_dynamic_array(array, material1);
    append_dynamic_array(array, material2);
    append_dynamic_array(array, material3);
    Date today_date = { 1, 1, 2021 };
    DynamicArray* result = materials_past_expiration_date(array, "-", today_date);
    assert(result->size == 2);
    destroy_dynamic_array(result);
    destroy_dynamic_array(array);
}

void test_suppliers_most_materials() {
    DynamicArray* array = create_dynamic_array(3);
    Material material1 = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    Material material2 = { "flour", "flour.inc", 200, {15, 12, 2024} };
    Material material3 = { "butter", "butter.co", 150, {20, 11, 2023} };
    append_dynamic_array(array, material1);
    append_dynamic_array(array, material2);
    append_dynamic_array(array, material3);
    int no_suppliers;
    char* suppliers[3];
    for (int i = 0; i < 3; i++) {
        suppliers[i] = (char*)malloc(50 * sizeof(char));
    }
    char** result = suppliers_most_materials(array, &no_suppliers, suppliers);
    assert(no_suppliers == 3);
    for (int i = 0; i < 3; i++) {
        free(suppliers[i]);
    }
    destroy_dynamic_array(array);
}

void test_undo_redo() {
    Undo_Redo undo_redo = create_undo_redo();
    DynamicArray* array = create_dynamic_array(2);
    Material material = { "sugar", "sugar.srl", 100, {10, 10, 2025} };
    add_material(array, -1, material);
    Operation operation = { material, material, add_material, delete_material, 0, 0 };
    add_operation_to_undo(operation, &undo_redo);
    undo_func(&undo_redo, array);
    assert(array->size == 0);
    redo_func(&undo_redo, array);
    destroy_dynamic_array(array);
    free(undo_redo.undo_stack);
    free(undo_redo.redo_stack);
}

/*int main() {
    test_create_material();
    test_get_material_name();
    test_get_material_supplier();
    test_get_material_quantity();
    test_get_material_expiration_date();
    test_create_dynamic_array();
    test_append_dynamic_array();
    test_add_to_position_dynamic_array();
    test_deletes_from_position_dynamic_array();
    test_update_element_at_position_dynamic_array();
    test_initialise_with_10();
    test_add_material();
    test_delete_material();
    test_update_material();
    test_max_date();
    test_create_date_from_string();
    test_sort_by_quantity();
    test_materials_past_expiration_date();
    test_suppliers_most_materials();
    test_undo_redo();

    printf("All tests passed!\n");
    _CrtDumpMemoryLeaks();
    return 0;
}*/
