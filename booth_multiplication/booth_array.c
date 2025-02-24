#include <stdio.h>

void booth_mult(int, int);
int *get_binary(int[], int);
int *twos_comp(int[], int);
int *add_binary(int[], int[]);
void display(int[]);
void rs(int[], int[], int *);
int get_size(int, int);
int get_pow(int, int);
int get_decimal(int[]);

int c = 0, size;

int main()
{
    int num1, num2, s1 = 1, s2 = 1;
    printf("Enter the multiplicand: ");
    scanf("%d", &num1);
    printf("Enter the multiplier: ");
    scanf("%d", &num2);

    s1 = get_size(num1, s1);
    s2 = get_size(num2, s2);
    size = s1 >= s2 ? s1 : s2;

    booth_mult(num1, num2);

    return 0;
}

void booth_mult(int a, int b)
{
    int M[size], Q[size], M2[size], A[size], R[2 * size];
    int result;

    for (int i = 0; i < size; i++)
        A[i] = 0;

    get_binary(M, a);
    get_binary(Q, b);

    for (int i = 0; i < size; i++)
        M2[i] = M[i];

    twos_comp(M2, size);

    printf("A: ");
    display(A);
    printf("Q: ");
    display(Q);
    printf("M: ");
    display(M);
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        if (Q[size - 1] == 1 && c == 0)
        {
            add_binary(A, M2);
            display(A);
            display(Q);
            printf("%d (10=-1: A = A + M' + 1)\n", c);
        }
        else if (Q[size - 1] == 0 && c == 1)
        {
            add_binary(A, M);
            display(A);
            display(Q);
            printf("%d (01=+1: A = A + M)\n", c);
        }
        else
        {
            display(A);
            display(Q);
            printf("%d (00|11: A = A + 0)\n", c);
        }
        rs(A, Q, &c);
        display(A);
        display(Q);
        printf("%d ---> Right Shift\n", c);
        printf("------------------------------------\n");
    }
    for (int i = 0; i < size; i++)
        R[i] = A[i];

    for (int i = 0; i < size; i++)
        R[size + i] = Q[i];

    printf("The multiplied binary number is: ");
    for (int i = 0; i < 2 * size; i++)
        printf("%d", R[i]);
    result = get_decimal(R);
    printf("\nThe number in decimal: %d", result);
}

int *get_binary(int arr[], int num)
{
    int i = 1, n = num;
    for (int i = 0; i < size; i++)
        arr[i] = 0;

    while (n != 0)
    {
        arr[size - i] = n >= 0 ? n % 2 : (-n) % 2;
        n /= 2;
        i++;
    }
    return num >= 0 ? arr : twos_comp(arr, size);
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
    int s[size];
    for (i = size - 1; i >= 0; i--)
    {
        s[i] = ((a[i] ^ b[i]) ^ c1);
        c1 = ((a[i] & b[i]) | ((a[i] | b[i]) & c1));
        a[i] = s[i];
    }
    return a;
}

void rs(int a[], int q[], int *c1)
{
    *c1 = q[size - 1];
    for (int i = size - 1; i > 0; i--)
        q[i] = q[i - 1];
    q[0] = a[size - 1];
    for (int i = size - 1; i > 0; i--)
        a[i] = a[i - 1];
}

void display(int a[])
{
    for (int i = 0; i < size; i++)
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

int get_decimal(int arr[])
{
    int sum = 0;
    if (arr[0])
    {
        twos_comp(arr, 2 * size);
        for (int i = 0; i < 2 * size; i++)
            sum -= (arr[i] * (get_pow(2, 2 * size - 1 - i)));
    }
    else
        for (int i = 0; i < 2 * size; i++)
            sum += (arr[i] * (get_pow(2, 2 * size - 1 - i)));
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