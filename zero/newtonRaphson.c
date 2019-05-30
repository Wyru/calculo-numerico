// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 03 – 03/04/19
// 33962 – Willian Saymon da Silva
//
// Cálculo de raizes reais de funcoes reais – Método Newton Raphson

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define DEFAULT_ITERATIONS 1000
#define DEFAULT_PRECISION 0.000000000000000001

#define E 2.71828

// Modifique para a função que deseja-se achar o zero
#define f(x) (8*sin(x)*pow(E,-x)-1)
// Insira a derivada da função acima
#define fd(x) (8*pow(E,-x)*(cos(x)-sin(x)))

int main()
{
    int k = 0, nIterations = 0;
    int usePrecision = 1;
    int useIterations = 1;
    long double x, fx, oldX, precision1, precision2;

    printf("Entre a aproximacao inicial:\n>");
    scanf("%Lf", &x);

    printf("Usar precisao?(1-sim,0-nao)");
    scanf("%d", &usePrecision);
    if (usePrecision)
    {
        printf("Entre com a precisao desejada para a raiz:\n>");
        scanf("%Lf", &precision1);

        printf("Entre com a precisao desejada para o zero:\n>");
        scanf("%Lf", &precision2);
    }
    else
    {
        precision1 = precision2 = DEFAULT_PRECISION;
    }

    printf("Usar numero max de iteracoes?(1-sim,0-nao)");
    scanf("%d", &useIterations);

    if (useIterations)
    {
        printf("Entre com o numero de iteracoes necessarias:\n>");
        scanf("%d", &nIterations);
    }
    else
    {
        nIterations = DEFAULT_ITERATIONS;
    }

    fx = f(x);

    while (fabsl(fx) > precision1)
    {

        k++;

        //calcula o novo x dentro do intervalo usando o método de newton-raphson
        oldX = x;

        x = x - (f(x) / fd(x));

        fx = f(x);

        printf("Iteracao %d\n", k);
        printf("\tPara x = %Lf  f(x) = %Lf\n", x, fx);

        // verifica se o valor desejado foi obtido

        if (fabsl(f(x)) < precision1)
        {
            printf("\nf(x) menor que %.18Lf\n", precision1);
            break;
        }
        else if (fabsl(x - oldX) < precision2)
        {
            printf("\nVariacao de x menor que %Lf.\n", precision2);
            break;
        }
        if (nIterations == k)
        {
            printf("\nNumero máximo de iteracoes atingido.\n");
            break;
        }
    }

    printf("\nA raiz eh: %.18Lf\n", x);
    printf("\nf(x) eh: %.18Lf\n", fx);

    return 0;
}