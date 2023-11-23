#include "cub3D.h"

// Fonction pour créer une liste chaînée avec j éléments
t_element *creer_liste(int j) 
{
    t_element *premier;
    t_element *actuel;
    int k;

    premier = malloc(sizeof(*premier));
    if (premier == NULL)
    {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    premier->index = 1;

    actuel = premier;
    k = 2;

    while (k <= j)
    {
        actuel->suivant = malloc(sizeof(*premier));
        if (actuel->suivant == NULL)
        {
            perror("Erreur d'allocation de mémoire");
            exit(EXIT_FAILURE);
        }
        actuel = actuel->suivant;
        actuel->index = k;
        k++;
    }

    actuel->suivant = NULL;

    return premier;
}

// Fonction pour afficher la liste chaînée
void afficher_liste(t_element *premier) 
{
    t_element *actuel;

    actuel = premier;
    while (actuel != NULL)
    {
        printf("%d ", actuel->index);
        actuel = actuel->suivant;
    }
    printf("\n");
}

// Fonction pour libérer la mémoire allouée à la liste chaînée
void liberer_liste(t_element *premier) 
{
    t_element   *actuel;
    t_element   *suivant;
    
    actuel = premier;
    while (actuel != NULL) {
        suivant = actuel->suivant;
        free(actuel);
        actuel = suivant;
    }
}