#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ne pas modifier
void init_file()
{
    // data.txt
    FILE* f = fopen("data.txt", "w");
    if (f)
    {
        fprintf(f, "5\n12\n8\n1\n19\n");
        fclose(f);
    }

    // data2.txt
    f = fopen("data2.txt", "w");
    if (f)
    {
        fprintf(f, "10\n20\n30\n");
        fclose(f);
    }

    // data3.txt
    f = fopen("data3.txt", "w");
    if (f)
    {
        fprintf(f, "1\n2\n3\n4\n5\n");
        fclose(f);
    }

    // data_vide.txt
    f = fopen("data_vide.txt", "w");
    if (f)
    {
        fclose(f);  // fichier vide
    }
}


#define NOFILE 2
#define ARGERROR 1

#define MAXFILENAME 80


typedef struct Node
{
    int value;
    struct Node* next;
} Node;

typedef struct
{
    Node* head;
    Node* tail;
} List;

typedef struct 
{
    bool isReverse;
    bool isSum;
    bool isFilter;
    int filterValue;
    bool isAdd;
    int addValue;
    bool foundName;
    char filename[MAXFILENAME];
    bool isMin;
    bool isMax;
}Options;


// Fonctions de base
void append(List* list, int value)
{
    Node* new = malloc(sizeof(Node));

    if(new == NULL)return;
    new->next = 0;
    new->value = value;

    if(list->head == NULL && list->tail == NULL)//empty list
    {
        list->head = new;
        list->tail = new; 
        return;
    }

    list->tail->next = new;
    list->tail = new;
    return;
}

void free_list(List* list)
{

}

int count_list(List* list)
{
    if(list->head == NULL)return(-1);
    Node* current = list->head;

    int size = 0;
    while(current != NULL)
    {
        size++;
        current = current->next;
    }
    return(size);
}

void print_list(const List* list)
{
    printf("Liste : ");
    if(list->head == NULL)return;
    Node* current = list->head;
    bool first = true;
    while(current != NULL)
    {   
        if(first)
        {   
            first = false;
            printf("%d", current->value);
        } 
        else
        {
            printf(" -> %d", current->value);
        }
        current = current->next;
    }
    printf("\n");
}

bool insert_head(List* list, Node* new)
{
    if(list == NULL || new == NULL) return(false);

    new->next = list->head;
    list->head = new;

    if(list->tail == NULL)   //empty list
    {
        list->tail = new;
    }
    return(true);
}

void reverse_list(List* list)
{
    if(list == NULL || list->head == NULL)return;

    //head to tail
    Node* current = list->head; //take first
    list->tail = current;       //put last
    list->head = current->next; //replace head
    current->next = NULL;
    
    Node* lastMoved = current;  //save last moved
    current = list->head;   //go back to head

    while(current->next != NULL)    //if == NULL then we reached the last unmoved element
    {
        list->head = current->next; //replace head
        current->next = lastMoved;  //point to last element moved
        lastMoved = current;        //replace lastmoved
        current = list->head;       //go back to head
    }

    current->next = lastMoved;
    return;
}

int sum_list(const List* list)
{
    if(list->head == NULL)
    {
        printf("Somme : %d\n", 0);
        return(0);
    }
    int sum = 0;
    Node* current = list->head;
    while(current != NULL)
    {
        sum+= current->value;
        current = current->next;
    }
    printf("Somme : %d\n", sum);
    return sum;
}

int min_list(const List* list)
{
    if(list->head == NULL)return 0;
    int min = 0;
    bool first = true;
    Node* current = list->head;
    while(current != NULL)
    {
        if(first)min = current->value;
        min = current->value < min ? current->value : min;
        current = current->next;
    }
    printf("Minim. : %d\n", min);
    return min;
}

int max_list(const List* list)
{
    if(list->head == NULL)return 0;
    int max = 0;
    bool first = true;
    Node* current = list->head;
    while(current != NULL)
    {
        if(first)max = current->value;
        max = current->value > max ? current->value : max;
        current = current->next;
    }
    printf("Maxim. : %d\n", max);
    return max;
}

void filter_list(List* list, int threshold)
{
    if(list->head == NULL)return;
    Node* current = list->head;

    //first element
    while(current->value < threshold && current != NULL)
    {
        current = current->next;
        list->head = current;
    }

    while(current->next != NULL)
    {   

    }

    print_list(list);
}



void help()
{
    printf("Utilisation : ./app <fichier> [options]\n\n");
    printf("Options disponibles :\n");
    printf("  --reverse         Inverse l'ordre des éléments\n");
    printf("  --sum             Affiche la somme des éléments\n");
    printf("  --filter <val>    Filtre les éléments >= val\n");
    printf("  --add <val>       Ajoute une valeur à la fin du fichier\n");
    printf("  --help            Affiche ce message d'aide\n");
    printf("  --version, -v     Affiche la version du programme\n");
    printf("  --min             Affiche la valeur minimale de la liste\n");
    printf("  --max             Affiche la valeur maximale de la liste\n");
}

void version()
{
    printf("version 1.0");
}

// Lecture fichier
bool read_file(const char* filename, List* list)
{
    FILE* f = fopen(filename, "r");
    if (!f) return false;
    int value;
    
    while (fscanf(f, "%d", &value) == 1) append(list, value);
    
    fclose(f);
    return true;
}

bool add_to_file(const char* filename, int value)
{
    FILE* f = fopen(filename, "a");
    if (!f) return false;
    fprintf(f, "%d\n", value);
    fclose(f);
    return true;
}

bool parseArgs(int argc, char* argv[], Options* opt)
{
    bool foundName = false;
    for(int i = 1; i<argc; i++) //each arg
    {
        if(strcmp(argv[i], "--reverse") == 0)
        {
            opt->isReverse = true;
            continue;
        }
        else if(strcmp(argv[i], "--sum")== 0)
        {
            opt->isSum = true;
            continue;
        }
        else if(strcmp(argv[i], "--min")== 0)
        {
            opt->isMin = true;
            continue;
        }
        else if(strcmp(argv[i], "--max")== 0)
        {
            opt->isMax = true;
            continue;
        }
        else if(strcmp(argv[i], "--help")== 0)
        {
            help();
            exit(0);
        }
        else if(strcmp(argv[i], "-v")== 0 || strcmp(argv[i], "--version")== 0)
        {
            version();
            exit(0);   
        }
        else if(strcmp(argv[i], "--filter")== 0)
        {
            return(false);
        }
        else if(strcmp(argv[i], "--add")== 0)
        {
            return(false);
        }

        const int filterRet = sscanf(argv[i], "--filter%d", &opt->filterValue);
        if(filterRet >= 1)
        {
            opt->isFilter = true;
            continue;
        }


        const int filterAdd = sscanf(argv[i], "--add%d", &opt->addValue);
        if(filterAdd >= 1)
        {
            opt->isAdd = true;
            continue;
        }

        //not an option -> filename
        if(!opt->foundName)
        {
            foundName = true;
            strcpy(opt->filename, argv[i]);
        }

    }
    return(foundName);
}


int main(int argc, char* argv[])
{
    // Ne pas modifier
    init_file();
    // ---------------

    if(argc < 2) return ARGERROR;
    Options options = {0};
    const bool argRet = parseArgs(argc, argv, &options);
    if(!argRet)return(ARGERROR);

    //printf("FIlename: %s\n", options.filename);

    FILE* fp = fopen(options.filename, "r");
    if(fp == NULL)return(NOFILE);
    fclose(fp);

    List mylist= {.head = NULL, .tail = NULL};
    
    read_file(options.filename, &mylist);
    //print_list(&mylist);
    if(options.isReverse)reverse_list(&mylist);
    if(options.isSum)sum_list(&mylist);
    if(options.isFilter)filter_list(&mylist, options.filterValue);
    if(options.isMin)min_list(&mylist);
    if(options.isMax)max_list(&mylist);


    print_list(&mylist);    //TODO not print for sum

    return 0;
}