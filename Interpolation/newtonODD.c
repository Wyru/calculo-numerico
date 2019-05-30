// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 07 – 08/05/19
// 33962 – Willian Saymon da Silva
// Interpolação de polinômios pelo método de newton e gera a ODD

// Como usar: Configure a função setup com os valores que se deseja calcular 
// Rode o código e veja a magia acontecer.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ORDER 50

void setup();
long double calcFx(int start, int end);
long double calcFxTo(long double value);

long double x[MAX_ORDER];
long double fx[MAX_ORDER];
long double fxTable[MAX_ORDER][MAX_ORDER] = {0};
int fxCalculated[MAX_ORDER][MAX_ORDER] = {0};

int numberOfPoints = 0;

long double valueToCalc;

int interpolationStart;
int interpolationEnd;

int main()
{
    printf("x------------- Interpolacao de polinomios pelo metodo de Newton -------------x\n");
    printf("x-------------                      ODD                         -------------x\n");
    
    setup();

    for (int i = 0; i < numberOfPoints; i++)
    {
        for (int j = 0; j < numberOfPoints; j++)
        {
            if(i+j >= numberOfPoints)
                continue;

            printf("f(x%d a x%d) = %.4Lf \t", (i), (i+j), calcFx(i, i+j));
        }
        printf("\n");
    }

    return 0;
}

void setup()
{
    numberOfPoints = 5;

    x[0] = 0.1;
    fx[0] = 1.25;

    x[1] = 0.3;
    fx[1] = 1.5678;

    x[2] = 0.5;
    fx[2] = 3.6789;

    x[3] = 0.7;
    fx[3] = 8.89;

    x[4] = 0.9;
    fx[4] = 10.5699;

    // inicia em 0
    interpolationStart = 0;
    interpolationEnd = numberOfPoints-1;

}

long double calcFx(int start, int end)
{
    if (fxCalculated[start][end] == 1)
    {
        return fxTable[start][end];
    }

    fxCalculated[start][end] = 1;

    if (start == end)
        fxTable[start][end] = fx[start];
    else
        fxTable[start][end] = (calcFx(start + 1, end) - calcFx(start, end - 1)) / (x[end] - x[start]);

    return fxTable[start][end];
}


long double _recursiveCalcFxTo(int start, int end, long double value)
{
    long double aux = calcFx(start, end);

    if (start != end)
    {
        long double previous = _recursiveCalcFxTo(start, end - 1, value);

        for (int i = start; i < end; i++)
        {
            aux *= (value - x[i]);
        }

        return aux + previous;
    }
    return aux;
}

long double calcFxTo(long double value)
{
    return _recursiveCalcFxTo(interpolationStart, interpolationEnd, value);
}

