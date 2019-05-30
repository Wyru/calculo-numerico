// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 07 – 08/05/19
// 33962 – Willian Saymon da Silva
// Interpolação de polinômios pelo método de newton

// Como usar: Configure a função setup com os valores que se deseja calcular 
// Rode o código e veja a magia acontecer.


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ORDER 50

void setup();
void showPolynomial(int start, int end);
long double calcFx(int start, int end);
long double calcFxTo(long double value);
void chooseStartEnd();
long double estimatedError();

long double x[MAX_ORDER];
long double fx[MAX_ORDER];
long double fxTable[MAX_ORDER][MAX_ORDER] = {0};
int fxCalculated[MAX_ORDER][MAX_ORDER] = {0};

int numberOfPoints = 0;
int order = 0;

long double valueToCalc;

int interpolationStart;
int interpolationEnd;

int main()
{
    printf("x------------- Interpolacao de polinomios pelo metodo de Newton -------------x\n");
    setup();
    printf("P%d(x) = ", order);
    showPolynomial(interpolationStart, interpolationEnd);
    printf("\n");
    printf("P%d(%Lf) = %Lf\n", order, valueToCalc, calcFxTo(valueToCalc));
    printf("|E(%Lf)| = %Lf\n", valueToCalc, estimatedError(valueToCalc));

    return 0;
}

void setup()
{
    numberOfPoints = 9;

    x[0] = 0;
    fx[0] = 0;

    x[1] = 0.2;
    fx[1] = 0.60667;

    x[2] = 0.3;
    fx[2] = 0.9225;

    x[3] = 0.5;
    fx[3] = 1.60443;

    x[4] = 0.6;
    fx[4] = 1.98064;

    x[5] = 0.8;
    fx[5] = 2.82936;

    x[6] = 1;
    fx[6] = 3.81417;

    x[7] = 1.4;
    fx[7] = 6.52945;

    x[8] = 1.5;
    fx[8] = 7.37249;


    valueToCalc = 1.47;

    // use a ordem caso esteja usando a escolha de pontos automática
    order = 8;
    // chooseStartEnd();

    // inicia em 0
    interpolationStart = 0;
    interpolationEnd = 7;

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

void showPolynomial(int start, int end)
{
    if (start == end)
    {
        printf("%Lf", calcFx(start, end));
        return;
    }

    showPolynomial(start, end - 1);

    printf(" + %Lf", calcFx(start, end));
    for (int i = start; i < end; i++)
    {
        printf("(x - %LF)", x[i]);
    }
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

void chooseStartEnd()
{
    int start, end;
    for (int i = 0; i < numberOfPoints; i++)
    {
        if (x[i] > valueToCalc)
        {
            start = end = i;
            for (int j = i - 1; j >= 0; j--)
            {
                if (end - start < order)
                {
                    start = j;
                }
                else
                {
                    break;
                }
            }

            for (int j = i + 1; j < numberOfPoints; j++)
            {
                if (end - start < order)
                {
                    end = j;
                }
                else
                {
                    break;
                }
            }

            break;
        }
    }
    interpolationEnd = end;
    interpolationStart = start;
    printf("Start = %d End = %d\n", start, end);
}

long double estimatedError(long double value)
{
    long double error = 1;

    //(x-x0)(x-x1)....(x-xn)
    for (int i = interpolationStart; i <= interpolationEnd; i++)
    {
        error *= (x[i] - value);
    }
    error = fabsl(error);

    //pega o valor máximo das diferenças divididas de ordem +1
    int start = -1;
    int end = order;
    long double maxValue, aux;
    maxValue = aux = 0;
    while (end < numberOfPoints)
    {
        start++;
        end++;

        aux = fabsl(calcFx(start, end));

        if (aux > maxValue)
        {
            maxValue = aux;
        }
    }

    error = error * maxValue;

    return error;
}
