#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
} person;

int main(void)
{
    person people[3];
    people[0].name = "Misho";
    people[0].number = "123-456-789";

    people[1].name ="David";
    people[1].number ="+1-949-468-2750";

    people[2].name = "Carter";
    people[2].number = "+1-617-495-1000";

    string input = get_string("Enter name:\n");
    for (int i = 0; i < 3; i++)
    {
        if( strcmp(input, people[i].name) == 0 )
        {
            printf("%s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}