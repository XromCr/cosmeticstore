#include "cosmetic.h"

Cosmetic* database = NULL;
size_t database_size = 0;

void load_database(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Не удалось открыть файл для чтения\nНачинаем с пустой базы данных\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    database_size = file_size / sizeof(Cosmetic);
    database = malloc(database_size * sizeof(Cosmetic));
    if (!database) {
        printf("Ошибка выделения памяти\n");
        fclose(file);
        exit(1);
    }

    fread(database, sizeof(Cosmetic), database_size, file);
    fclose(file);
}

void save_database(const char* filename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Не удалось открыть файл для записи\n");
        return;
    }

    fwrite(database, sizeof(Cosmetic), database_size, file);
    fclose(file);
}

void display_database() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    printf("\nБаза данных магазина косметики:\n");
    for (size_t i = 0; i < database_size; i++) {
        printf("%zu. Название: %s, Артикул: %d, Бренд: %s\n", i + 1, database[i].name, database[i].age, database[i].breed);
    }
}

void add_cosmetic() {
    Сosmetic new_cosmetic;

    printf("Введите название: ");
    scanf("%s", new_cosmetic.name);
    printf("Введите цену: ");
    scanf("%d", &new_cosmetic.price);
    printf("Введите бренд: ");
    scanf("%s", new_cosmetic.brand);

    Сosmetic* new_database = realloc(database, (database_size + 1) * sizeof(Сosmetic));
    if (!new_database) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    database = new_database;
    database[database_size++] = new_cosmetic;

    printf("Товар успешно добавлен\n");
}

void delete_cosmetic() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    size_t index;
    printf("Введите номер товара для удаления: ");
    scanf("%zu", &index);

    if (index < 1 || index > database_size) {
        printf("Неверный номер\n");
        return;
    }

    for (size_t i = index - 1; i < database_size - 1; i++) {
        database[i] = database[i + 1];
    }

    Сosmetic* new_database = realloc(database, (database_size - 1) * sizeof(Сosmetic));
    if (!new_database && database_size - 1 > 0) {
        printf("Ошибка выделения памяти\n");
        return;
    }

    database = new_database;
    database_size--;

    printf("Товар удален\n");
}

void edit_dog() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    size_t index;
    printf("Введите номер товара для редактирования: ");
    scanf("%zu", &index);

    if (index < 1 || index > database_size) {
        printf("Неверный номер\n");
        return;
    }

    Сosmetic* cosmetic = &database[index - 1];

    printf("Редактирование Товара: %s\n", cosmetic->name);
    printf("Введите новое название: ");
    scanf("%s", cosmetic->name);
    printf("Введите новую цену: ");
	int new_price;
    scanf("%d", &new_price);
	cosmetic->price = new_price;
    printf("Введите новый бренд: ");
    scanf("%s", cosmetic->brand);

    printf("Товар обновлен\n");
}

void search_cosmetic() {
    if (database_size == 0) {
        printf("База данных пуста\n");
        return;
    }

    char query[MAX_LEN];
    printf("Введите название или бренд для поиска: ");
    scanf("%s", query);

    printf("\nРезультаты поиска:\n");
    for (size_t i = 0; i < database_size; i++) {
        if (strstr(database[i].name, query) || strstr(database[i].brand, query)) {
            printf("%zu. Название: %s, Цена: %d, Бренд: %s\n", i + 1, database[i].name, database[i].price, database[i].brand);
        }
    }
}

void menu(const char* filename) {
    int choice;

    do {
        printf("\nМеню:\n");
        printf("1. Показать все товары\n");
        printf("2. Добавить новый товар \n");
        printf("3. Удалить товар\n");
        printf("4. Редактировать товар\n");
        printf("5. Искать товар\n");
        printf("6. Выйти\n");
        printf("Введите ваш выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_database();
                break;
            case 2:
                add_cosmetic();
                break;
            case 3:
                delete_cosmetic();
                break;
            case 4:
                edit_cosmetic();
                break;
            case 5:
                search_cosmetic();
                break;
            case 6:
                save_database(filename);
                printf("Выход из программы\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 6);
}
