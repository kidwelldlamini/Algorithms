#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
struct Node
{
    char c;
    double d;
    struct Node *prev, *next;
};
typedef struct Node Node;
void initLinkList(struct Node **head)
{
    *head = NULL;
}
void addToTail_d(struct Node **head, double _d)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->d = _d;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        struct Node *cur = *head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = new_node;
        new_node->prev = cur;
    }
}
void addToTail(struct Node **head, char _c)
{
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->c = _c;
    new_node->prev = NULL;
    new_node->next = NULL;
    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        struct Node *cur = *head;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = new_node;
        new_node->prev = cur;
    }
}

int isEmpty(struct Node *stack)
{
    if (stack == NULL)
        return 1;
    else
        return 0;
}
void push(struct Node **stack, char _c)
{
    addToTail(stack, _c);
}
void push_d(struct Node **stack, double _d)
{
    addToTail_d(stack, _d);
}
char pop(struct Node **stack)
{
    if (isEmpty(*stack))
        return 0;
    else
    {
        struct Node *cur = *stack;
        if (cur->next == NULL)
        {
            char n = cur->c;
            *stack = NULL;
            return n;
        }
        while (cur->next != NULL)
            cur = cur->next;
        char n = cur->c;
        cur->prev->next = NULL;
        return n;
    }
}
double pop_d(struct Node **stack)
{
    if (isEmpty(*stack))
        return 0;
    else
    {
        struct Node *cur = *stack;
        if (cur->next == NULL)
        {
            double n = cur->d;
            *stack = NULL;
            return n;
        }
        while (cur->next != NULL)
            cur = cur->next;
        double n = cur->d;
        cur->prev->next = NULL;
        return n;
    }
}
double top_d(struct Node *stack)
{
    if (isEmpty(stack))
        return 0;
    else
    {
        struct Node *cur = stack;
        while (cur->next != NULL)
            cur = cur->next;
        return cur->d;
    }
}
char top(struct Node *stack)
{
    if (isEmpty(stack))
        return 0;
    else
    {
        struct Node *cur = stack;
        while (cur->next != NULL)
            cur = cur->next;
        char _c = cur->c;
        return _c;
    }
}
int size(struct Node *stack)
{
    int size = 0;
    struct Node *cur = stack;
    while (cur != NULL)
    {
        size++;
        cur = cur->next;
    }
    return size;
}
int priority(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return 0;
}
char *negative(char s[1000])
{
    int flag = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            flag = 1;
        if (s[i] == '-')
        {
            if (!flag)
                s[i] = '&';
            else if (s[i + 1] == '-')
            {
                s[i] = '+';
                s[i + 1] = ' ';
            }
        }
        if ((s[i] == '+' || s[i] == '*' || s[i] == '/') && s[i + 1] == '-')
        {
            s[i + 1] = '&';
        }
    }
    return s;
}
int idx = 0;
bool check(char s[1000])
{
    int len = strlen(s), left = 0, right = 0;
    if (s[len - 1] == '+' || s[len - 1] == '-' || s[len - 1] == '*' || s[len - 1] == '/' || s[len - 1] == '^' || s[len - 1] == '(')
        return false;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
        {
            if (s[i + 1] == s[i])
                return false;
        }
        if (s[i] == '(')
            right++;
        else if (s[i] == ')')
            left++;
    }
    if (left != right)
        return false;
    return true;
}
char **transfer(char s[1000])
{
    char **st = (char **)malloc(sizeof(char *) * 1000);
    for (int i = 0; i < 1000; i++)
        st[i] = (char *)malloc(sizeof(char) * 1000);
    idx = 0;
    Node *cstack;
    initLinkList(&cstack);
    s = negative(s);
    if (!check(s))
        return NULL;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            char n[100] = "";
            int nidx = 0;
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
            {
                n[nidx] = s[i];
                i++;
                nidx++;
            }
            strcpy(st[idx], n);
            idx++;
            i--;
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
        {
            int oidx = 0;
            while (size(cstack) != 0 && priority(s[i]) <= priority(top(cstack)))
            {
                if (s[i] == ' ')
                    break;
                char _op[1000] = "";
                _op[oidx] = pop(&cstack);
                strcpy(st[idx], _op);
                idx++;
            }
            push(&cstack, s[i]);
        }
        else if (s[i] == '&')
        {
            i++;
            char n[1000] = "";
            int nidx = 0;
            n[nidx] = '&';
            nidx++;
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
            {
                n[nidx] = s[i];
                nidx++;
                i++;
            }
            strcpy(st[idx], n);
            idx++;
            i--;
        }
        else if (s[i] == '(')
        {
            push(&cstack, s[i]);
        }
        else if (s[i] == ')')
        {
            int oidx = 0;
            while (size(cstack) != 0 && top(cstack) != '(')
            {
                char _op[1000] = "";
                _op[oidx] = pop(&cstack);
                strcpy(st[idx], _op);
                idx++;
            }
            pop(&cstack);
        }
    }
    while (size(cstack) != 0)
    {
        char _op[1000] = "";
        int oidx = 0;
        _op[oidx] = pop(&cstack);
        strcpy(st[idx], _op);
        idx++;
    }

    return st;
}
double roundHalfToEven(double f)
{
    double r = round(f * 100) / 100;
    double d = r - f;
    int id = (int)(d * 1000);
    if ((id != 5) && (id != -5))
        return r;
    int _r = (int)(r * 100);
    if (_r % 2 == 0)
        return r;
    return f - d;
}
char *ptr;
double compute(char **st)
{
    Node *dstack;
    initLinkList(&dstack);
    for (int i = 0; i < idx; i++)
    {
        if (st[i][0] >= '0' && st[i][0] <= '9')
        {
            double _d = strtod(st[i], &ptr);
            push_d(&dstack, _d);
        }
        else if (st[i][0] == '&')
        {
            for (int j = 0; j < strlen(st[i]); j++)
            {
                st[i][j] = st[i][j + 1];
            }
            double _d = strtod(st[i], &ptr);
            push_d(&dstack, -1 * _d);
        }
        else if (strcmp(st[i], "+") == 0 || strcmp(st[i], "-") == 0 || strcmp(st[i], "*") == 0 || strcmp(st[i], "/") == 0 || strcmp(st[i], "^") == 0)
        {
            double b = pop_d(&dstack);
            double a = pop_d(&dstack);
            double p;
            if (strcmp(st[i], "+") == 0)
                p = a + b;
            else if (strcmp(st[i], "-") == 0)
                p = a - b;
            else if (strcmp(st[i], "*") == 0)
                p = a * b;
            else if (strcmp(st[i], "/") == 0)
                p = a / b;
            else if (strcmp(st[i], "^") == 0)
                p = pow(a, b);
            p = roundHalfToEven(p);
            push_d(&dstack, p);
        }
    }
    double db = pop_d(&dstack);
    return db;
}
int main()
{
    char s[1000];
    while (scanf("%s", s) != EOF)
    {
        char **str = transfer(s);
        if (str == NULL)
            printf("ERROR\n");
        else
            printf("%.2f\n", compute(str));
    }
    return 0;
}