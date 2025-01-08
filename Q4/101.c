#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REGISTRATION_SIZE 6
#define AVAILABLE_HASH_SIZE 101

typedef struct Employee
{
    char registration[REGISTRATION_SIZE];
    char name[REGISTRATION_SIZE];
    char role[REGISTRATION_SIZE];
    float salary;
} Employee;

Employee generateEmployee()
{
    int number = rand() % 100000;
    Employee employee;
    employee.salary = (float)number;

    for (int i = 0; i < REGISTRATION_SIZE; i++, number /= 10)
    {
        int currentDigit = number % 10;
        employee.registration[i] = (char)currentDigit + '0';
        employee.name[i] = (char)currentDigit + '0';
        employee.role[i] = (char)currentDigit + '0';
    }

    employee.registration[REGISTRATION_SIZE - 1] = '\0';
    employee.name[REGISTRATION_SIZE - 1] = '\0';
    employee.role[REGISTRATION_SIZE - 1] = '\0';

    if (employee.registration[0] == '0')
        employee.registration[0] = '1';

    return (employee);
}

typedef struct hashTable
{
    int hash[AVAILABLE_HASH_SIZE];
    Employee employee[AVAILABLE_HASH_SIZE];
} HashTable;

void initializeHashTable(HashTable *hashTable)
{
    for (int i = 0; i < AVAILABLE_HASH_SIZE; i++)
        hashTable->hash[i] = -1;
}

int charToInt(char c)
{
    return ((int)c - '0');
}

int functionHash1(char registration[])
{
    char rearranged[REGISTRATION_SIZE];

    rearranged[0] = registration[REGISTRATION_SIZE - 2];
    rearranged[1] = registration[REGISTRATION_SIZE - 1];
    for (int i = 0, j = 2; i < REGISTRATION_SIZE - 2; i++, j++)
        rearranged[j] = registration[i];

    int integerValue = atoi((char[]){rearranged[1], rearranged[3], rearranged[5]});

    return (integerValue % AVAILABLE_HASH_SIZE);
}

int functionHash2(char registration[])
{
    int part1 = (charToInt(registration[0]) * 100) + (charToInt(registration[2]) * 10) + charToInt(registration[5]);
    int part2 = (charToInt(registration[1]) * 100) + (charToInt(registration[3]) * 10) + charToInt(registration[4]);

    int sumParts = part1 + part2;

    return (sumParts % AVAILABLE_HASH_SIZE);
}

int resolveCollision1(int hash, char registration[])
{
    char firstCharactere[2] = {registration[0], '\0'};
    return (hash + atoi(firstCharactere));
}

int resolveCollision2(int hash, char registration[])
{
    (void)registration;
    return (hash + 7);
}

int insertIntoHashTable(HashTable *hashTable, int hash, char registration[], Employee employee,
                           int resolveCollision(int, char[]))
{
    int collisions = 0, inserted = 0;
    int newHash = hash;

    while (newHash < AVAILABLE_HASH_SIZE && !inserted)
    {
        if (hashTable->hash[newHash] == -1)
        {
            hashTable->hash[newHash] = newHash;
            hashTable->employee[newHash] = employee;
            inserted = 1;
        }
        else
        {
            collisions++;
            newHash = resolveCollision(newHash, registration);
        }
    }

    if (!inserted)
    {
        hashTable->hash[hash] = hash;
        hashTable->employee[hash] = employee;
    }

    return (collisions);
}

void testHashFunction(int hashFunction(char[]), int resolveCollision(int, char[]))
{
    HashTable hashTable;
    initializeHashTable(&hashTable);

    int totalCollisions = 0;
    clock_t total_time = 0;

    for (int i = 0; i < 1000; i++)
    {
        Employee employee = generateEmployee();

        clock_t start_time = clock();
        int hash = hashFunction(employee.registration);
        totalCollisions += insertIntoHashTable(&hashTable, hash, employee.registration, employee, resolveCollision);
        clock_t end_time = clock();

        total_time += (end_time - start_time);
    }

    printf("\n==============================\n");
    printf("         RESULTADOS           \n");
    printf("==============================\n");
    printf(" Tempo de Execução:   %.6f segundos\n", (double)total_time / CLOCKS_PER_SEC);
    printf(" Total de Colisões:   %d colisões\n", totalCollisions);
    printf("==============================\n");
}

void display_menu()
{
    printf("\n==============================\n");
    printf("       HASH FUNCTION MENU     \n");
    printf("==============================\n");
    printf(" 1. Testar Função Hash 1\n");
    printf(" 2. Testar Função Hash 2\n");
    printf(" 3. Sair\n");
    printf("==============================\n");
    printf(" Escolha uma opção: ");
}

int main()
{
    srand((unsigned)time(NULL));
    int option;

    do
    {
        display_menu();
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("\nTestando Função Hash 1:\n");
            testHashFunction(functionHash1, resolveCollision1);
            break;

        case 2:
            printf("\nTestando Função Hash 2:\n");
            testHashFunction(functionHash2, resolveCollision2);
            break;

        case 3:
            printf("\nSaindo do programa. Até logo!\n");
            break;

        default:
            printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (option != 3);

    return 0;
}
