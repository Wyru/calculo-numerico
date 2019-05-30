// CIC250 – Cálculo Numérico para Computação
// Exercicio Pratico 02 – 27/03/19
// matrícula – Willian Saymon da Silva
//
// Calculo de raizes reais de funcoes reais – bissecção

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define f(x) (pow(x,2) + 1.95*x - 2.09)
// #define f(x) (3.14*pow(x,2)*(9-x)-45)
// #define f(x) (5*pow(x, 3)  - 5*pow(x,2) + 6*x -2)
// #define f(x) (pow(x, 3) - 9*x + 3)

int main()
{
    int k = 0, nIterations = 0;
    long double a, b, fa, fb, x, fx, oldX, precision1, test, errorPercentage, minError;

    printf("Entre com o limite inferior:\n>");
    scanf("%Lf", &a);

    printf("Entre com o limite superior:\n>");
    scanf("%Lf", &b);

    printf("Entre com a precisao desejada:\n>");
    scanf("%Lf", &precision1);

    printf("Entre com o numero de iteracoes necessarias:\n>");
    scanf("%d", &nIterations);

    printf("Entre com o erro minimo:\n>");
    scanf("%Lf", &minError);

    fa = f(a);
    fb = f(b);

    // Verifica se existe raiz existe no intervalo
    if (fa * fb < 0)
    {
        while (fabsl(a - b) > precision1)
        {
            k++;

            //calcula o novo x dentro do intervalo
            oldX = x;
            x = (a + b) / 2;
            fx = f(x);

            printf("Iteracao %d\n", k);
            printf("\tPara a = %Lf  f(a) = %Lf\n", a, fa);
            printf("\tPara b = %Lf  f(b) = %Lf\n", b, fb);
            printf("\tPara x = %Lf  f(x) = %Lf\n\n", x, fx);

            if (fabsl(f(x)) < precision1)
            {
                break;
            }

            errorPercentage = fabsl((x - oldX) / x) * 100;

            test = fa*fx;

            if (test > 0)
            {
                a = x;
                fa = fx;
            }
            else if(test < 0)
            {
                b = x;
                fb = fx;
            }
            else{
                errorPercentage = 0;
            }

            if(nIterations == k){
                printf("\nNumero máximo de iteracoes atingido.\n");
                break;
            }

            if(minError >= errorPercentage){
                printf("\nPorcentagem de erro minimo atingido.porcentagem de erro procurado:%Lf\nporcentagem de erro atual: %Lf\n",minError, errorPercentage);
                break;
            }
        }

        printf("\nA raiz eh: %Lf\n", x);
    }
    else
    {
        printf("\tPara a = %Lf  f(a) = %Lf\n", a, fa);
        printf("\tPara b = %Lf  f(b) = %Lf\n", b, fb);
        printf("Intervalo fornecido nao possui uma raiz!\n");
    }

    return 0;
}