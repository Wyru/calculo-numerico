// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 10 – 29/05/19
// 33962 – Willian Saymon da Silva
// Integração pelo método dos trapézios
// Como usar: Configurar os parâmetros no método setup. Colocar a derivada da segunda no método secondDerivativeFx. Colocar a função em fx.

#include <stdio.h>
#include <math.h>

long double E = 2.718281828459;

long double minLimit, maxLimit, height, numberOfDivisions;

void setup()
{
    minLimit = 0;
    maxLimit = 4;
    // Deixe 0 para ser o método dos quadrados simples;
    numberOfDivisions = 6;

    height = numberOfDivisions == 0 ? maxLimit - minLimit : (maxLimit - minLimit) / numberOfDivisions;
}

long double fx(long double x)
{
    return 1-pow(E,-2*x);
}

long double secondDerivativeFx(long double x)
{
    return -4*pow(E,-2*x);
}

long double calculateIntegral()
{
    long double value;

    long double aux = 0;
    for (int i = 1; i < numberOfDivisions; i++)
    {
        aux += fx(minLimit + height * i);
    }

    value = (height / 2) * (fx(maxLimit) + fx(minLimit) + 2 * aux);

    return value;
}

long double MaxAbs(long double x, long double y){
    return fabsl(x) > fabsl(y) ? fabsl(x) : fabsl(y);
}

long double calcError(){
    long double error=0;
    if(numberOfDivisions == 0){
        error = (pow(height,3)/12)*MaxAbs(secondDerivativeFx(minLimit),secondDerivativeFx(maxLimit));
    }
    else
    {
        long double max = fabsl(secondDerivativeFx(minLimit));

        for (int i = 1; i < numberOfDivisions - 1; i++)
        {
            max = MaxAbs(max, secondDerivativeFx(minLimit+height*i));
        }

        error = (pow(height,2)/12)*(maxLimit-minLimit)*max;
    }

    return error;
    
}



int main()
{

    printf("* -------------------------------------------------------------------------- *\n");
    printf("*                Integracao Numerica - Metodo de Newton-Cotes                *\n");
    printf("* -------------------------------------------------------------------------- *\n");

    setup();
    long double answer = calculateIntegral();
    long double error = calcError();
    printf("I = %Lf\n",answer);
    printf("Erro <= %Lf\n", error);

}