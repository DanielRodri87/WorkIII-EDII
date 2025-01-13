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

typedef struct hashTable
{
    int hash[AVAILABLE_HASH_SIZE];
    Employee employee[AVAILABLE_HASH_SIZE];
} HashTable;

void display_menu();
void testHashFunction(int hashFunction(char[]), int resolveCollision(int, char[]));
Employee generateEmployee();

void initializeHashTable(HashTable *hashTable);
int insertIntoHashTable(HashTable *hashTable, int hash, char registration[], Employee employee, int resolveCollision(int, char[]));
int functionHash1(char registration[]);
int functionHash2(char registration[]);

int resolveCollision1(int hash, char registration[]);
int resolveCollision2(int hash, char registration[]);
int charToInt(char c);