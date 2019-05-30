// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 09 – 22/05/19
// 33962 – Willian Saymon da Silva
// Aproximação de curvas pelo método dos mínimos quadrados com solução do sistema por meio da substituição de gaus


// Como usar:
// Configure as funções no método g(x)
// Configure a tabela de valores no método setup
// compile e execute o programa

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 50

long double a[MAX][MAX] = {0};
long double b[MAX] = {0};

long double x[MAX] = {0};
long double fx[MAX] = {0};

long double answers[MAX] = {0};

int numberOfPoints = 0;
int numberOfGs = 0;

void setup()
{
    numberOfPoints = 11;
    numberOfGs = 3;

    x[0] = 6;
    fx[0] = 29;

    x[1] = 7;
    fx[1] = 21;

    x[2] = 11;
    fx[2] = 29;

    x[3] = 15;
    fx[3] = 14;

    x[4] = 17;
    fx[4] = 21;

    x[5] = 21;
    fx[5] = 15;

    x[6] = 23;
    fx[6] = 7;

    x[7] = 29;
    fx[7] = 7;

    x[8] = 30;
    fx[8] = 13;

    x[9] = 37;
    fx[9] = 0;

    x[10] = 39;
    fx[10] = 13;
}

long double g(int index, long double x)
{
    switch (index)
    {
    case 0:
        return 1;
        break;
    case 1:
        return x;
        break;
    case 2:
        return pow(x,2);
        break;
    }
    return 0;
}

void calculateA()
{
    for (int i = 0; i < numberOfGs; i++)
    {
        for (int j = 0; j < numberOfGs; j++)
        {
            a[i][j] = 0;
            for (int k = 0; k < numberOfPoints; k++)
            {
                a[i][j] += g(i, x[k]) * g(j, x[k]);
            }
        }
    }
}

void calculateB()
{
    for (int i = 0; i < numberOfGs; i++)
    {
        for (int k = 0; k < numberOfPoints; k++)
        {
            b[i] += fx[k] * g(i, x[k]);
        }
    }
}

void showLinearSystem()
{
    
    for (int i = 0; i < numberOfGs; i++)
    {
        for (int j = 0; j < numberOfGs; j++)
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

            printf("%.2Lfa%d", fabsl(a[i][j]), j);
        }
        printf(" = %.2Lf\n", b[i]);
    }

}

/* -------------------------------------------------------------------------- */
/*                           Gauss com pivoteamento                           */
/* -------------------------------------------------------------------------- */

void subtractLines(int i, int j, long double m)
{
    for (int k = i; k < numberOfGs; k++)
    {
        a[j][k] -= (a[i][k] * m);
    }
    b[j] -= b[i] * m;
}

void swapLines(int i, int j)
{
    long double aux;
    for (int k = 0; k < numberOfGs; k++)
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
    for (int j = i + 1; j < numberOfGs; j++)
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
    long double m = 0;
    for (int i = 0; i < numberOfGs - 1; i++)
    {
        pivoting(i);
        for (int j = i + 1; j < numberOfGs; j++)
        {
            m = a[j][i] / a[i][i];
            subtractLines(i, j, m);
        }
        
    }
}

void calcAnswers()
{
    answers[numberOfGs - 1] = b[numberOfGs - 1] / a[numberOfGs - 1][numberOfGs - 1];

    long double sum;
    int j;
    for (int i = numberOfGs - 1; i >= 0; i--)
    {
        sum = 0;
        for (j = numberOfGs - 1; j > i; j--)
        {
            sum += a[i][j] * answers[j];
        }
        answers[i] = (b[i] - sum) / a[i][j];
    }
}

void showAnswers()
{
    printf("\nEquação:\n");
    printf("h(x) = ");
    for (int i = 0; i < numberOfGs; i++)
    {
        printf("(%.4Lf)*g%d(x)",answers[i], i);
        if(i < numberOfGs-1){
            printf(" + ");
        }
    }

}

long double CalcHx(long double x)
{
    long double value = 0;
    for (int i = 0; i < numberOfGs; i++)
    {
        value+= answers[i]*g(i,x);
    }
    return value;
}

void showTest()
{
    printf("\n\nTeste:\n");
    printf("Ponto\tf(x)\th(x)\n");
    for (int i = 0; i < numberOfPoints; i++)
    {
        printf("%.2Lf\t%.2LF\t%.2LF\n", x[i],fx[i], CalcHx(x[i]));
    }

}

int main()
{

printf("\n\nx---------------------- Metodo dos quadrados minimos ----------------------x\n\n");

    setup();
    calculateA();
    calculateB();
    showLinearSystem();
    doElimination();
    calcAnswers();
    showAnswers();
    showTest();
}