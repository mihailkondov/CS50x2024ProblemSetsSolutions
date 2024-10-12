/*
    This program creates takes integers as arguments
    then creates a binary tree with the numbers
    from 1 to 7 and searches for every number the user
    has given printing number found or number not found
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *left;
    struct node *right;
} node;

bool search(node *tree, int number);
void destroy(node *tree);

int main(int argc, char *argv[])
{
    // number of arguments is correct or return 1
    if (argc < 2)
    {
        printf("Usage: ./binary_search_tree 1 2 3...\n");
        return 1;
    }

    // arguments are integers or return 2
    int numbers[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        int j = 0;
        for (char c = argv[i][j]; c != '\0'; c = argv[i][j++])
        {
            if (!isdigit(c))
            {
                printf("binary_search_tree only accepts integers as arguments\n");
                return 2;
            }
        }
        numbers[i] = atoi(argv[i]);
    }

    // build a tree to search in
    node *tree = NULL;
    int tree_array[7] = {4, 2, 6, 1, 3, 5, 7};
    for (int i = 0; i < 7; i++)
    {
        node *n = malloc(sizeof(node));
        n->number = tree_array[i];
        n->left = NULL;
        n->right = NULL;

        node *ptr = tree;
        if (tree == NULL)
        {
            tree = n;
        }
        else
        {
            while (ptr != NULL)
            {
                if (tree_array[i] < ptr->number)
                {
                    if (ptr->left == NULL)
                    {
                        ptr->left = n;
                        break;
                    }
                    ptr = ptr->left;
                }
                else if (tree_array[i] > ptr->number)
                {
                    if (ptr->right == NULL)
                    {
                        ptr->right = n;
                        break;
                    }
                    ptr = ptr->right;
                }
                else
                {
                    printf("Number already inserted in the tree\n");
                    break;
                }
            }
        }
    }

    // search for user's input numbers
    for (int i = 0; i < argc - 1; i++)
    {
        bool found = search(tree, numbers[i]);
        if (found)
        {
            printf("Number %i found\n", numbers[i]);
        }
        else
        {
            printf("Number %i not found\n", numbers[i]);
        }
    }

    // free allocated memory and exit program
    destroy(tree);
    return 0;
}

bool search(node *tree, int number)
{
    if (tree == NULL)
    {
        return false;
    }
    else if (number < tree->number)
    {
        return search(tree->left, number);
    }
    else if (number > tree->number)
    {
        return search(tree->right, number);
    }
    else
    {
        return true;
    }
}

void destroy(node *tree)
{
    if (tree == NULL)
    {
        return;
    }

    destroy(tree->left);
    destroy(tree->right);
    free(tree);
}
