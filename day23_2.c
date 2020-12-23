#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    int value;
} node_t;

node_t *cache[1000000 + 1] = {NULL};

node_t *new_node(int value)
{
    node_t *r = (node_t *)malloc(sizeof(node_t));
    r->value = value;
    cache[value] = r;
    return r;
}

#define is_picked(v)    ((picked[0] == v) || (picked[1] == v) || (picked[2] == v))

void move(node_t *cur, int MAX_LABEL)
{
    int v = cur->value > 1 ? cur->value - 1 : MAX_LABEL;
    int picked[3];
    node_t *pickup_first = cur->next;
    node_t *pickup_last = pickup_first->next->next;
    node_t *dest;
    cur->next = pickup_last->next;
    picked[0] = pickup_first->value;
    picked[1] = pickup_first->next->value;
    picked[2] = pickup_last->value;
    while (is_picked(v))
    {
        v = v > 1 ? v - 1 : MAX_LABEL;
    }

    dest = cache[v];
    pickup_last->next = dest->next;
    dest->next = pickup_first;
}

void print_circle(node_t *first)
{
    node_t *prev = first;
    do
    {
        printf("%d ", prev->value);
        prev = prev->next;
    } while (prev != first);
    puts("\n");
}

const int input[] = {9, 5, 2, 3, 1, 6, 4, 8, 7};

void p2(void)
{
    int i;
    node_t *first = new_node(input[0]);
    node_t *prev = first;
    for (i = 1; i < sizeof(input) / sizeof(input[0]); i++)
    {
        prev->next = new_node(input[i]);
        prev = prev->next;
    }
    for (i = 10; i <= 1000000; i++)
    {
        prev->next = new_node(i);
        prev = prev->next;
    }
    prev->next = first;

    node_t *play = first;
    for (i = 0; i < 10000000; i++)
    {
        if ((i & 0xfff) == 0) printf("progress %d\n", i);
        move(play, 1000000);
        play = play->next;
    }

    play = cache[1];
    for (i = 0; i < 3; i++)
    {
        printf("%d\n", play->value);
        play = play->next;
    }
}

void p1(void)
{
    int i;
    node_t *first = new_node(input[0]);
    node_t *prev = first;
    for (i = 1; i < sizeof(input) / sizeof(input[0]); i++)
    {
        prev->next = new_node(input[i]);
        prev = prev->next;
    }
    prev->next = first;

    node_t *play = first;
    for (i = 0; i < 100; i++)
    {
        print_circle(first);
        move(play, 9);
        play = play->next;
    }

    play = first;
    while (play->value != 1) play = play->next;
    do {
        printf("%d\n", play->value);
        play = play->next;
    } while (play->value != 1);
}

void main(void)
{
    p2();
}

