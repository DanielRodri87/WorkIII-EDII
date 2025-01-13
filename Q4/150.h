#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REGISTRATION_SIZE 6
#define HASH_TABLE_SIZE 150

typedef struct Employee {
    char registration[REGISTRATION_SIZE];
    char name[REGISTRATION_SIZE];
    char role[REGISTRATION_SIZE];
    float salary;
} Employee;

typedef struct HashTable {
    int keys[HASH_TABLE_SIZE];
    Employee employees[HASH_TABLE_SIZE];
} HashTable;

void testHashFunction(int (*hashFunction)(const char[]), int (*collisionResolver)(int, const char[]));
Employee createEmployee();
int insertIntoHashTable(HashTable *table, int hash, const char registration[], Employee employee, int (*collisionResolver)(int, const char[]));

void initializeHashTable(HashTable *table);
int functionHash1(const char registration[]);
int functionHash2(const char registration[]);

int resolveCollision1(int hash, const char registration[]);
int resolveCollision2(int hash, const char registration[]);
int charToInt(char c);