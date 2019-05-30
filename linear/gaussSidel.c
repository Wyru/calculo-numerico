// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 05 – 17/04/19
// 33962 – Willian Saymon da Silva
// Resolução de sistemas lineares pelo metodo de Gauss Sidel

// Para utilizar a leitura direto da matriz de valores, comente de 
// metodo readFromTerminal() na main() e descomente readLinearSystem() 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 50

void readLinearSystem();
void readFromTerminal();
void clearCXG();
void printLinearSystem();
void printAnswers();
long double calcValue(int var);
void doGaussSidel();
long double calcError();
long double calcRelativeError();
void pivoting();
void swapLines(int i, int j);

// x = c*x +g
int numberOfVariables = 0;
long double x[MAX];
long double oldX[MAX];
long double c[MAX][MAX];
long double g[MAX];

long double precision = 0.05;

int userRelativeError = 0;

int main()
{

    printf("x------------------- Metodo de Gauss Sidel-------------------x\n\n");
    clearCXG();
    // readLinearSystem();
    readFromTerminal();
    printLinearSystem();
    pivoting();
    printLinearSystem();

    printf("\nAproximação inicial de: \n");
    printAnswers();
    printf("\n\nIniciando calculos...\n\n");
    doGaussSidel();
    printf("\nAproximação desejada alcancada!\n");
    printAnswers();

    return 0;
}

void readLinearSystem()
{
    numberOfVariables = 6;

    userRelativeError = 0;

    c[0][0] = 1;
    c[0][1] = 10;
    c[0][2] = 1;
    c[0][3] = 0;
    c[0][4] = 0;
    c[0][5] = 0;

    g[0] = 10;

    c[1][0] = 2;
    c[1][1] = 20;
    c[1][2] = 0;
    c[1][3] = 1;
    c[1][4] = 0;
    c[1][5] = 0;

    g[1] = 10;

    c[2][0] = 0;
    c[2][1] = 3;
    c[2][2] = 0;
    c[2][3] = 0;
    c[2][4] = 30;
    c[2][5] = 3;

    g[2] = 0;

    c[3][0] = 10;
    c[3][1] = 1;
    c[3][2] = 0;
    c[3][3] = 0;
    c[3][4] = 0;
    c[3][5] = -1;

    g[3] = 5;

    c[4][0] = 0;
    c[4][1] = 0;
    c[4][2] = 0;
    c[4][3] = 2;
    c[4][4] = -2;
    c[4][5] = 20;

    g[4] = 5;

    c[5][0] = 0;
    c[5][1] = 0;
    c[5][2] = 1;
    c[5][3] = 10;
    c[5][4] = 1;
    c[5][5] = 0;

    g[5] = 0;

    x[0] = 0;
    x[1] = 0;
    x[2] = 0;
    x[3] = 0;
    x[4] = 0;
    x[5] = 0;

    precision = 0.001;
}

void readFromTerminal()
{
    printf("Entre com a precisao:\n>");
    scanf("%Lf", &precision);
    printf("Entre com o numero de variaveis:\n>");
    scanf("%d", &numberOfVariables);
    printf("Utilizar erro relativo?(0-Nao,1-Sim)\n>");
    scanf("%d", &userRelativeError);
    printf("Entre com o sistema linear:\n");

    for (int i = 0; i < numberOfVariables; i++)
    {
        for (int j = 0; j < numberOfVariables; j++)
        {
            printf("X(%d, %d) = ", i, j);
            scanf("%Lf", &(c[i][j]));
        }
        printf("B(%d) = ", i);
        scanf("%Lf", &(g[i]));
    }

    
}

void clearCXG()
{
    memset(c, 0, sizeof(c));
    memset(x, 0, sizeof(x));
    memset(oldX, 0, sizeof(oldX));
    memset(g, 0, sizeof(g));
}

long double calcValue(int xLine)
{
    long double value = g[xLine];
    for (int k = 0; k < numberOfVariables; k++)
    {
        if (k != xLine)
        {
            value -= c[xLine][k] * x[k];
        }
    }
    value /= c[xLine][xLine];

    return value;
}

void doGaussSidel()
{
    int k = 0;

    do
    {
        printf("Iteracao %d:\n", k);
        for (int i = 0; i < numberOfVariables; i++)
        {
            oldX[i] = x[i];
            x[i] = calcValue(i);
            printf("\tx%d = %Lf\n", i, oldX[i]);
        }
        k++;
        printf("\n");
        if(userRelativeError == 0){
            if(calcError() < precision){
                break;
            }
        }
        else{
            if(calcRelativeError() < precision){
                break;
            }
        }
    } while (1);

}

void printLinearSystem()
{
    for (int i = 0; i < numberOfVariables; i++)
    {
        for (int j = 0; j < numberOfVariables; j++)
        {
            if (j == 0)
            {
                if (c[i][j] < 0)
                {
                    printf("-");
                }
            }
            else
            {
                if (c[i][j] < 0)
                {
                    printf(" - ");
                }
                else
                {
                    printf(" + ");
                }
            }

            printf("%.2Lfx%d", fabsl(c[i][j]), j + 1);
        }
        printf(" = %.2Lf\n", g[i]);
    }
}

void printAnswers()
{
    for (int i = 0; i < numberOfVariables; i++)
    {
        printf("x%d = %Lf\n", i, x[i]);
    }
}

long double calcError()
{
    long double error = 0, maxError = 0;
    for (int i = 0; i < numberOfVariables; i++)
    {
        error = fabsl(x[i] - oldX[i]);
        if (error > maxError)
        {
            maxError = error;
        }
    }
    printf("Erro de %Lf\n\n", maxError);
    return maxError;
}

long double calcRelativeError(){
    long double maxX = 0, error = 0, maxError = 0;
    for (int i = 0; i < numberOfVariables; i++)
    {
        error = fabsl(x[i] - oldX[i]);
        if (error > maxError)
        {
            maxError = error;
        }

        if (fabsl(x[i]) > maxX)
        {
            maxX = fabsl(x[i]);
        }
    }
    error = (maxError / maxX);
    printf("Erro de %Lf\n\n", error);
    return error;
}

void swapLines(int i, int j)
{
    printf("\nTrocando linha %d com %d.\n", i, j);

    long double aux;
    for (int k = 0; k < numberOfVariables; k++)
    {
        aux = c[i][k];
        c[i][k] = c[j][k];
        c[j][k] = aux;
    }
    aux = g[i];
    g[i] = g[j];
    g[j] = aux;
}

void pivoting()
{
    printf("Realizando pivoteamento...\n");
    int max = 0;
    for (int i = 0; i < numberOfVariables; i++)
    {
        max = i;
        for (int j = i + 1; j < numberOfVariables; j++)
        {
            if (c[max][i] < c[j][i])
            {
                max = j;
            }
        }
        if (i != max)
        {
            swapLines(i, max);
        }
    }
}