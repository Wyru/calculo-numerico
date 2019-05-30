// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 10 – 29/05/19
// 33962 – Willian Saymon da Silva
// Encontrar o N para resolução da Integração pelo método dos trapézios
// Como usar: Configurar os parâmetros no método setup. Colocar a derivada da segunda no método secondDerivativeFx.

#include <stdio.h>
#include <math.h>

long double minLimit, maxLimit, minError;

long double fxTable = {0};


void setup()
{
    minLimit = -2;
    maxLimit = 4;
    minError = 0.001;
}

long double secondDerivativeFx(long double x)
{
    return 8*x*(5*pow(x,2)-3);
}


long double MaxAbs(long double x, long double y){
    return fabsl(x) > fabsl(y) ? fabsl(x) : fabsl(y);
}


int findN(){
    return (maxLimit-minLimit)/sqrt((minError*12)/(MaxAbs(secondDerivativeFx(minLimit),secondDerivativeFx(maxLimit))*(maxLimit-minLimit)));
}

int main()
{

    printf("* -------------------------------------------------------------------------- *\n");
    printf("*   Integracao Numerica - Numero de iteracoes para Metodo de Newton-Cotes    *\n");
    printf("* -------------------------------------------------------------------------- *\n");

    setup();

    printf("Numero de iteracoes necessarias: %d\n",findN());


}