// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 04 – 10/04/19
// 33962 – Willian Saymon da Silva
// Resolução de sistemas lineares pelo método de gauss com pivoteamento

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <complex.h>

#define MAX 50

int numberOfVariables = 0;

int show = 0;

long double a[MAX][MAX];
char x[MAX];
long double b[MAX];

long double answers[MAX];

void clearAXB()
{
    memset(a, 0, sizeof(a));
    memset(x, 0, sizeof(x));
    memset(b, 0, sizeof(b));
    memset(answers, 0, sizeof(answers));
}

void printLinearSystem()
{
    for (int i = 0; i < numberOfVariables; i++)
    {
        for (int j = 0; j < numberOfVariables; j++)
        {
            if (j == 0)
            {
                if (a[i][j] < 0)
                {
                    printf("-");
                }
            }
            else
            {
                if (a[i][j] < 0)
                {
                    printf(" - ");
                }
                else
                {
                    printf(" + ");
                }
            }

            printf("%.2Lf%c", fabsl(a[i][j]), x[j]);
        }
        printf(" = %.2Lf\n", b[i]);
    }
}

void readLinearSystem()
{
    numberOfVariables = 3;

    x[0] = 'x';
    x[1] = 'y';
    x[2] = 'z';

    a[0][0] = 11;
    a[0][1] = -3;
    a[0][2] = -8;

    b[0] = 15;

    a[1][0] = -3;
    a[1][1] = 0;
    a[1][2] = 5;

    b[1] = 0;

    a[2][0] = -8;
    a[2][1] = -5;
    a[2][2] = 23;

    b[2] = 0;
}

void readLinearSystemFromTerminal()
{
    printf("Entre com o numero de variaveis:\n>");
    scanf("%d", &numberOfVariables);

    for (int i = 0; i < numberOfVariables; i++)
    {
        printf("Entre com o simbolo(x,y,z) da variavel %d:\n>", i);
        scanf(" %c", &(x[i]));
    }

    for (int i = 0; i < numberOfVariables; i++)
    {
        for (int j = 0; j < numberOfVariables; j++)
        {
            printf("Entre com o valor de a(%d,%d):\n>", i, j);
            scanf("%Lf", &(a[i][j]));
        }

        printf("Entre com o valor de b(%d):\n>", i);
        scanf("%Lf", &(b[i]));
    }
}

void subtractLines(int i, int j, long double m)
{
    for (int k = i; k < numberOfVariables; k++)
    {
        a[j][k] -= (a[i][k] * m);
    }
    b[j] -= b[i] * m;
}

void swapLines(int i, int j)
{
    if (show != 0)
    {
        printf("\nTrocando linha %d com %d.\n", i, j);
    }

    long double aux;
    for (int k = 0; k < numberOfVariables; k++)
    {
        aux = a[i][k];
        a[i][k] = a[j][k];
        a[j][k] = aux;
    }
    aux = b[i];
    b[i] = b[j];
    b[j] = aux;
}

void pivoting(int i)
{
    int max = i;
    for (int j = i + 1; j < numberOfVariables; j++)
    {
        if (a[max][i] < a[j][i])
        {
            max = j;
        }
    }
    if (i != max)
    {
        swapLines(i, max);
    }
}

void doElimination()
{
    printf("\nRealizando eliminacao...\n");

    long double m = 0;
    for (int i = 0; i < numberOfVariables - 1; i++)
    {
        pivoting(i);
        for (int j = i + 1; j < numberOfVariables; j++)
        {
            m = a[j][i] / a[i][i];
            subtractLines(i, j, m);
        }
        if (show != 0)
        {
            printf("\nEliminacao %d:\n", i);
            printLinearSystem();
        }
    }
    printf("\nEliminacao realizada!\n\n");
}

void calcAnswers()
{
    answers[numberOfVariables - 1] = b[numberOfVariables - 1] / a[numberOfVariables - 1][numberOfVariables - 1];

    long double sum;
    int j;
    for (int i = numberOfVariables - 1; i >= 0; i--)
    {
        sum = 0;
        for (j = numberOfVariables - 1; j > i; j--)
        {
            sum += a[i][j] * answers[j];
        }
        answers[i] = (b[i] - sum) / a[i][j];
    }
}

void printAnswers()
{
    printf("\nResultado:\n");
    for (int i = 0; i < numberOfVariables; i++)
    {
        printf("%c = %.4Lf\n", x[i], answers[i]);
    }
}

int main()
{

    printf("x---------- Metodo de Gauss com pivoteamento ----------x\n\n");

    printf("Imprimir etapas da eliminacao?(1-Sim 0-Nao)\n>");
    scanf("%d", &show);

    clearAXB();
    readLinearSystem();
    // readLinearSystemFromTerminal();
    printLinearSystem();
    doElimination();
    printLinearSystem();
    calcAnswers();
    printAnswers();

    return 0;
}