#include "101.h"

/**
 * @brief Função principal do programa. Exibe o menu, processa a escolha do usuário e testa as funções hash.
 * @return Retorna 0 ao finalizar o programa.
 */

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

/**
 * @brief Exibe o menu de opções para o usuário.
 */

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

/**
 * @brief Testa uma função hash e exibe os resultados de desempenho.
 * @param hashFunction Ponteiro para a função hash a ser testada.
 * @param resolveCollision Ponteiro para a função de resolução de colisões.
 */

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
    printf(" Tempo de Execução:   %f segundos\n", (double)total_time / CLOCKS_PER_SEC);
    printf(" Total de Colisões:   %d colisões\n", totalCollisions);
    printf("==============================\n");
}

/**
 * @brief Gera um funcionário com valores aleatórios para os campos.
 * @return Employee Estrutura de funcionário gerada.
 */

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

    return employee;
}

/**
 * @brief Inicializa a tabela hash, preenchendo com valores padrão.
 * @param hashTable Ponteiro para a tabela hash a ser inicializada.
 */

void initializeHashTable(HashTable *hashTable)
{
    for (int i = 0; i < AVAILABLE_HASH_SIZE; i++)
        hashTable->hash[i] = -1;
}

/**
 * @brief Insere um funcionário na tabela hash.
 * @param hashTable Ponteiro para a tabela hash.
 * @param hash Valor hash gerado.
 * @param registration Registro do funcionário.
 * @param employee Estrutura do funcionário a ser inserida.
 * @param resolveCollision Função para resolver colisões.
 * @return int Número de colisões ocorridas durante a inserção.
 */

int insertIntoHashTable(HashTable *hashTable, int hash, char registration[], Employee employee, int resolveCollision(int, char[]))
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

    return collisions;
}

/**
 * @brief Função hash que reorganiza os caracteres do registro.
 * @param registration Registro do funcionário.
 * @return int Valor hash gerado.
 */

int functionHash1(char registration[])
{
    char aux[REGISTRATION_SIZE];

    aux[0] = registration[REGISTRATION_SIZE - 2];
    aux[1] = registration[REGISTRATION_SIZE - 1];
    for (int i = 0, j = 2; i < REGISTRATION_SIZE - 2; i++, j++)
        aux[j] = registration[i];

    char temp[4] = {aux[1], aux[3], aux[5], '\0'};
    int valorInteiro = atoi(temp);
    return valorInteiro % AVAILABLE_HASH_SIZE;
}

/**
 * @brief Função hash que utiliza somas específicas do registro.
 * @param registration Registro do funcionário.
 * @return int Valor hash gerado.
 */

int functionHash2(char registration[])
{
    int part1 = (charToInt(registration[1 - 1]) * 100) + (charToInt(registration[3 - 1]) * 10) + (charToInt(registration[6 - 1]));
    int part2 = (charToInt(registration[2 - 1]) * 100) + (charToInt(registration[4 - 1]) * 10) + (charToInt(registration[5 - 1]));

    int mudance = part1 + part2;
    return mudance % AVAILABLE_HASH_SIZE;
}

/**
 * @brief Resolve colisões somando o valor do primeiro caractere.
 * @param hash Valor hash atual.
 * @param registration Registro do funcionário.
 * @return int Novo valor hash.
 */

int resolveCollision1(int hash, char registration[])
{
    char firstCharactere[2] = {registration[0], '\0'};
    return (hash + atoi(firstCharactere));
}

/**
 * @brief Resolve colisões adicionando um valor fixo de 7.
 * @param hash Valor hash atual.
 * @param registration Registro do funcionário (não utilizado).
 * @return int Novo valor hash.
 */

int resolveCollision2(int hash, char registration[])
{
    (void)registration;
    return (hash + 7);
}

/**
 * @brief Converte um caractere numérico para inteiro.
 * @param c Caractere a ser convertido.
 * @return int Valor inteiro do caractere.
 */

int charToInt(char c)
{
    return ((int)c - '0');
}
