#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int top_stack = -1, top_post = -1;
char expt[100], stack[100], post[100];

char pop(char *abc, int *top)
{
    *top = *top - 1;
    return abc[*top + 1];
}

void push(char *abc, int *top, char c)
{
    *top = *top + 1;
    abc[*top] = c;
}

int precedance(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else if (c == '^')
    {
        return 3;
    }
    else
    {
        return -1;
    }
}

void Infix_Postfix(char q)
{
    if (q == '(')
    {
        push(stack, &top_stack, q);
    }
    else if (q == ')')
    {
        while (stack[top_stack] != '(')
        {
            push(post, &top_post, pop(stack, &top_stack));
        }
        pop(stack, &top_stack);
    }
    else if ((q >= 'a' && q <= 'z') || (q >= 'A' && q <= 'Z'))
    {
        push(post, &top_post, q);
    }
    else
    {
        if (precedance(stack[top_stack]) < precedance(q))
        {
            push(stack, &top_stack, q);
        }
        else if (precedance(stack[top_stack]) == precedance(q))
        {
            push(post, &top_post, pop(stack, &top_stack));
            push(stack, &top_stack, q);
        }
        else
        {
            while (precedance(stack[top_stack]) > precedance(q))
            {
                push(post, &top_post, pop(stack, &top_stack));
            }
            push(post, &top_post, pop(stack, &top_stack));
            push(stack, &top_stack, q);
        }
    }
    printf("%s", stack);
    printf("\t%s\n", post);
}

int main()
{
    printf("Enter Expression:");
    gets(expt);
    strcat(expt, ")");
    printf("%s\n", expt);
    push(stack, &top_stack, '(');
    printf("%s\n", stack);
    int x = strlen(expt);
    for (int i = 0; i < x; i++)
    {
        Infix_Postfix(expt[i]);
    }
    push(post, &top_post, '\0');
    printf("Postfix: %s", post);
    return 0;
}
