#include <stdio.h>
#include <stdlib.h>

void non_restoring(int, int);
int *get_binary(int[], int, int);
int *twos_comp(int[], int);
int *add_binary(int[], int[]);
void display(int[], int);
void ls(int[], int[]);
int get_size(int, int);
int get_pow(int, int);
int get_decimal(int[], int);

int size;

int main()
{
    int num1, num2, s1 = 0, s2 = 0;
    printf("Enter the dividend: ");
    scanf("%d", &num1);
    printf("Enter the divisor number: ");
    scanf("%d", &num2);

    if (num2 == 0)
    {
        printf("OOPS! Divisor can't be ZERO.");
        return 0;
    }
    
    s1 = get_size(num1, s1);
    s2 = get_size(num2, s2);
    size = s1 >= s2 ? s1 : s2;

    non_restoring(num1, num2);

    return 0;
}

void non_restoring(int n1, int n2)
{
    int M[size + 1], Q[size], M2[size + 1], A[size + 1];
    int minus = n1 < 0 ^ n2 < 0;

    for (int i = 0; i <= size; i++)
    {
        A[i] = 0;
    }
    get_binary(Q, n1, size);
    get_binary(M, n2, size + 1);
    for (int i = 0; i <= size; i++)
    {
        M2[i] = M[i];
    }
    twos_comp(M2, size + 1);

    printf("A: ");
    display(A, size + 1);
    printf("Q: ");
    display(Q, size);
    printf("M: ");
    display(M, size + 1);
    printf("\n---------------------------------------\n");

    for (int i = 0; i < size; i++)
    {
        if (A[0] == 0)
        {
            ls(A, Q);
            display(A, size + 1);
            for (int i = 0; i < size - 1; i++)
                printf("%d ", Q[i]);
            printf("%c \t---> sign(A)=0 & Left shift\n", 254);
            add_binary(A, M2);
            display(A, size + 1);
            for (int i = 0; i < size - 1; i++)
                printf("%d ", Q[i]);
            printf("%c \t---> A = A + M' + 1\n", 254);
        }
        else
        {
            ls(A, Q);
            display(A, size + 1);
            for (int i = 0; i < size - 1; i++)
                printf("%d ", Q[i]);
            printf("%c \t---> sign(A)=1 & Left shift\n", 254);
            add_binary(A, M);
            display(A, size + 1);
            for (int i = 0; i < size - 1; i++)
                printf("%d ", Q[i]);
            printf("%c \t---> A = A + M\n", 254);
        }
        if (A[0] == 0)
        {
            Q[size - 1] = 1;
            display(A, size + 1);
            display(Q, size);
            printf("---> sign(A)=0: q0 = 1\n---------------------------------------------\n");
        }
        else
        {
            Q[size - 1] = 0;
            display(A, size + 1);
            display(Q, size);
            printf("---> sign(A)=1: q0 = 0\n---------------------------------------------\n");
        }
    }
    if (A[0] == 1)
        add_binary(A, M);
    display(A, size + 1);
    display(Q, size);
    printf("\n");
    if (minus == 1)
    {
        int a = -(get_decimal(Q, size));
        printf("\nQuotient: %d\nReminder: %d", a, get_decimal(A, size + 1));
    }
    else
        printf("\nQuotient: %d\nReminder: %d", get_decimal(Q, size), get_decimal(A, size + 1));
}

int *get_binary(int arr[], int num, int s)
{
    int i = 1, n = num;
    for (int i = 0; i < s; i++)
    {
        arr[i] = 0;
    }
    while (n != 0)
    {
        arr[s - i] = abs(n % 2);
        n /= 2;
        i++;
    }
    return arr;
}

int *twos_comp(int arr[], int s)
{
    int carry = 1;
    for (int i = s - 1; i >= 0; i--)
    {
        arr[i] = !arr[i];
        if (carry == 1)
        {
            carry = arr[i];
            arr[i] = !arr[i];
        }
    }
    return arr;
}

int *add_binary(int a[], int b[])
{
    int i, c1 = 0;
    int s[size + 1];
    for (i = size; i >= 0; i--)
    {
        s[i] = ((a[i] ^ b[i]) ^ c1);
        c1 = ((a[i] & b[i]) | ((a[i] | b[i]) & c1));
        a[i] = s[i];
    }
    return a;
}

void display(int a[], int s)
{
    for (int i = 0; i < s; i++)
        printf("%d ", a[i]);
    printf("\t");
}

int get_size(int a, int b)
{
    while (a != 0)
    {
        a /= 2;
        b++;
    }
    return b;
}

void ls(int a[], int q[])
{
    for (int i = 0; i < size; i++)
        a[i] = a[i + 1];
    a[size] = q[0];
    for (int i = 0; i < size - 1; i++)
        q[i] = q[i + 1];
}
int get_decimal(int arr[], int s)
{
    int sum = 0;
    for (int i = 0; i < s; i++)
        sum += (arr[i] * (get_pow(2, s - 1 - i)));
    return sum;
}

int get_pow(int x, int y)
{
    int sum = 1;
    for (int i = 0; i < y; i++)
    {
        sum *= x;
    }
    return sum;
}
