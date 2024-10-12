/*
    This program takes integers as arguments and
    creates a list, inserting the integers consecutively
    in that list. Then it prints each number from the list.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL;
    for (int i = 1; i < argc; i++)
    {
        // create new node
        int number = atoi(argv[i]);
        node *n = malloc(sizeof(node));
        n->number = number;
        n->next = NULL;

        // insert the new node at the end of the list
        if (list == NULL)
        {
            list = n;
        }
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    node *ptr = list;
    while (ptr != NULL)
    {
        printf("%i\n", ptr->number);
        ptr = ptr->next;
    }

    // Free the used memory
    while (list != NULL)
    {
        node *n = list->next;
        free(list);
        list = n;
    }
}
