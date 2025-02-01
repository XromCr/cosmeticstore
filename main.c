#include "cosmetic.h"
int main() {
    const char* filename = "cosmetic.dat";
    load_database(filename);
    menu(filename);
    free(database);
    return 0;
}
