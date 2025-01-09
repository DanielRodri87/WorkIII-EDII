#include "150.h"

int main() {
    srand((unsigned)time(NULL));
    int option;

    do {
        printf("\n===========================\n");
        printf("       Hash Tester         \n");
        printf("===========================\n");
        printf("1. Testar Fun\u00e7\u00e3o de Hash 1\n");
        printf("2. Testar Fun\u00e7\u00e3o de Hash 2\n");
        printf("3. Sair\n");
        printf("===========================\n");
        printf("Escolha uma op\u00e7\u00e3o: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("\nTestando Fun\u00e7\u00e3o de Hash 1:\n");
                testHashFunction(functionHash1, resolveCollision1);
                break;
            case 2:
                printf("\nTestando Fun\u00e7\u00e3o de Hash 2:\n");
                testHashFunction(functionHash2, resolveCollision2);
                break;
            case 3:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOp\u00e7\u00e3o inv\u00e1lida! Tente novamente.\n");
        }
    } while (option != 3);

    return 0;
}

void testHashFunction(int (*hashFunction)(const char[]), int (*collisionResolver)(int, const char[])) {
    HashTable table;
    initializeHashTable(&table);

    int totalCollisions = 0;
    clock_t totalTime = 0;

    for (int i = 0; i < 1000; i++) {
        Employee employee = createEmployee();

        clock_t startTime = clock();
        int hash = hashFunction(employee.registration);
        totalCollisions += insertIntoHashTable(&table, hash, employee.registration, employee, collisionResolver);
        clock_t endTime = clock();

        totalTime += (endTime - startTime);
    }

    printf("\n==============================\n");
    printf("         RESULTADOS           \n");
    printf("==============================\n");
    printf(" Tempo de Execu\u00e7\u00e3o:   %f segundos\n", (double)totalTime / CLOCKS_PER_SEC);
    printf(" Total de Colis\u00f5es:   %d colis\u00f5es\n", totalCollisions);
    printf("==============================\n");
}

Employee createEmployee() {
    int number = rand() % 100000;
    Employee employee;
    employee.salary = (float)number;

    for (int i = 0; i < REGISTRATION_SIZE; i++, number /= 10) {
        int currentDigit = number % 10;
        employee.registration[i] = (char)(currentDigit + '0');
        employee.name[i] = (char)(currentDigit + '0');
        employee.role[i] = (char)(currentDigit + '0');
    }

    employee.registration[REGISTRATION_SIZE - 1] = '\0';
    employee.name[REGISTRATION_SIZE - 1] = '\0';
    employee.role[REGISTRATION_SIZE - 1] = '\0';

    if (employee.registration[0] == '0')
        employee.registration[0] = '1';

    return employee;
}

int insertIntoHashTable(HashTable *table, int hash, const char registration[], Employee employee, int (*collisionResolver)(int, const char[])) {
    int collisions = 0, insered = 0;
    int newHash = hash;

    while (newHash < HASH_TABLE_SIZE && insered == 0) {
        if (table->keys[newHash] == -1) {
            table->keys[newHash] = newHash;
            table->employees[newHash] = employee;
            insered = 1;
        } else {
            collisions++;
            newHash = collisionResolver(newHash, registration);
        }
    }

    if (insered == 0) {
        table->keys[hash] = hash;
        table->employees[hash] = employee;
    }

    return collisions;
}

void initializeHashTable(HashTable *table) {
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
        table->keys[i] = -1;
}

int functionHash1(const char registration[]) {
    char rearranged[REGISTRATION_SIZE];

    rearranged[0] = registration[REGISTRATION_SIZE - 2];
    rearranged[1] = registration[REGISTRATION_SIZE - 1];

    for (int i = 0, j = 2; i < REGISTRATION_SIZE - 2; i++, j++)
        rearranged[j] = registration[i];

    int combinedValue = atoi((char[]){rearranged[1], rearranged[3], rearranged[5]});

    return (combinedValue % HASH_TABLE_SIZE);
}

int functionHash2(const char registration[]) {
    int part1 = charToInt(registration[0]) * 100 + charToInt(registration[2]) * 10 + charToInt(registration[5]);
    int part2 = charToInt(registration[1]) * 100 + charToInt(registration[3]) * 10 + charToInt(registration[4]);

    return ((part1 + part2) % HASH_TABLE_SIZE);
}

int resolveCollision1(int hash, const char registration[]) {
    char firstDigit[2] = {registration[0], '\0'};
    return (hash + atoi(firstDigit));
}

int resolveCollision2(int hash, const char registration[]) {
    (void)registration;
    return (hash + 5);
}

int charToInt(char c) {
    return (int)(c - '0');
}
