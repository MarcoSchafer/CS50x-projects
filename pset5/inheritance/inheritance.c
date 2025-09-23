#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

//  person struct
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}person;

//  Declare constants
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

//  Function prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    //  Seed random number generator
    srand(time(0));

    //  Create a new family with three generations
    person *p = create_family(GENERATIONS);

    //  Print family tree of blood types
    print_family(p, 0);

    //  Free memory
    free_family(p);
}

//  Create new individual with 'generations'
person *create_family(int generations)
{
    //  Allocate memory for person
    person *new_person = malloc(sizeof(person));

    if (generations > 1)
    {
        //  recursive function to create two new parents for current person
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        new_person->parents[0] = parent0;
        new_person->parents[1] = parent1;

        new_person->alleles[0] = parent0->alleles[rand() % 2];
        new_person->alleles[1] = parent1->alleles[rand() % 2];
    }
    else    // if thers is no generations left to create
    {
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    return new_person;
}

void free_family(person *p)     // Free 'p' and all ancestors of 'p'
{
    if (p == NULL)       //  base case
    {
        return;
    }

    //  Free parents recursively
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    free(p);       //   Free child
}

void print_family(person *p, int generation)
{
    if (p == NULL)       //  Base case
    {
        return;
    }

    //  Print indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    //  Print person
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    else
    {
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }
    

    //  Print parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

//  Randomly choose blood type of allele
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return '0';
    }
}
