// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 03 – 03/04/19
// 33962 – Willian Saymon da Silva
//
// Cálculo de raizes reais de funcoes reais – Método Secante

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define DEFAULT_ITERATIONS 1000
#define DEFAULT_PRECISION 0.000000000000000001

#define E 2.71828

// Modifique para a funcão que deseja-se achar o zero
#define f(x) (8*sin(x)*pow(E,-x)-1)


int main()
{
    int k = 1, nIterations = 0;
    int usePrecision = 1;
    int useIterations = 1;
    long double x, fx, x0, fx0, x1, fx1, precision1, precision2;

    printf("Entre a primeira aproximacao inicial:\n>");
    scanf("%Lf", &x0);
    printf("Entre a segunda aproximacao inicial:\n>");
    scanf("%Lf", &x1);

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

    fx0 = f(x0);
    fx1 = f(x1);
    if (fabsl(fx0) < precision1)
    {
        printf("\nf(x0) menor que %.18Lf\n", precision1);
        x = x0;
        fx = fx0;
    }
    else if (fabsl(x1 - x0) < precision2)
    {
        printf("\nVariacao de x menor que %Lf.\n", precision2);
        x = x1;
        fx = fx1;
    }
    else
    {
        while (1)
        {

            //calcula o novo x usando a secante
            x = x1 - (f(x1) / (f(x1) - f(x0))) * (x1 - x0);

            fx = f(x);

            printf("Iteracao %d\n", k);
            printf("\tPara x = %Lf  f(x) = %Lf\n", x, fx);

            // verifica se o valor desejado foi obtido ou atingiu o número máximo de iteracoes
            if (fabsl(f(x)) < precision1)
            {
                printf("\nf(x) menor que %.18Lf\n", precision1);
                break;
            }
            else if (fabsl(x - x1) < precision2)
            {
                printf("\nVariacao de x menor que %Lf.\n", precision2);
                break;
            }
            if (nIterations == k)
            {
                printf("\nNumero máximo de iteracoes atingido.\n");
                break;
            }

            k++;

            // atualiza os valores das aproximações para a próxima iteração
            x0 = x1;
            x1 = x;
        }
    }

    printf("\nA raiz eh: %.18Lf\n", x);
    printf("\nf(x) eh: %.18Lf\n", fx);

    return 0;
}