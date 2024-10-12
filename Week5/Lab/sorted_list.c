/*
    This program takes integers as user input argument
    and inserts them in a list sorted from the smallest
    to the largest number
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

        // inserting in an empty list
        if (list == NULL)
        {
            list = n;
        }
        else if (n->number < list->number) // smallest number in the list
        {
            n->next = list;
            list = n;
        }
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // insert at the end of the list
                if (ptr->next == NULL)
                {
                    ptr->next = n;
                    break;
                }

                // insert in the middle of the list
                if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
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
