#ifndef	COSMETIC_H
#define	COSMETIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 50

typedef struct {
    char name[MAX_LEN];
    int price;
    char breed[MAX_LEN];
} Cosmetic;

extern Cosmetic* database;
extern size_t database_size;

void menu(const char* filename);
void search_cosmetic();
void edit_cosmetic();
void delete_cosmetic();
void add_cosmetic();
void display_database();
void save_database(const char* filename);
void load_database(const char* filename);

#endif
