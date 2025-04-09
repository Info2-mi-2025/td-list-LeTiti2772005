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
}Options;


// Fonctions de base
void append(List* list, int value)
{
}

void free_list(List* list)
{
}

void print_list(const List* list)
{
}

void reverse_list(List* list)
{
}

int sum_list(const List* list)
{
    return 0;
}

int min_list(const List* list)
{
    return 0;
}

int max_list(const List* list)
{
    return 0;
}

void filter_list(List* list, int threshold)
{
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
        else if(strcmp(argv[i], "--filter")== 0)
        {
            opt->isFilter = true;
            if(scanf(argv[i], "--filter%d", opt->filterValue) != 1)return(false);
            continue;
        }
        else if(strcmp(argv[i], "--add")== 0)
        {
            opt->isAdd = true;
            if(scanf(argv[i], "--filter%d", opt->addValue) != 1)return(false);
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

    FILE* fp = fopen(options.filename, "r");
    if(fp == NULL)return(NOFILE);
    fclose(fp);



    
    return 0;
}