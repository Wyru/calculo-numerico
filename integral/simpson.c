#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double minLimit, maxLimit, height;
int numberOfDivisions = 2;

// realize as configurações aqui
void setup()
{
    maxLimit = 1.5;
    minLimit = 0.5;

    // deve ser um número par
    numberOfDivisions = 2;

    if (numberOfDivisions % 2 != 0)
        numberOfDivisions *= 2;

    height = (maxLimit - minLimit) / numberOfDivisions;
}

// A função a ser derivada
long double fx(long double x)
{
    return cos(x);
}

// derivada quarta de fx
long double fourthDerivativeFx(long double x){
    return cos(x);
}

// Método de simpson
long double calculateIntegral()
{
    long double integral = fx(minLimit);
    for (int i = 1; i < numberOfDivisions; i++)
    {
        // se par multiplica por 2 se impar multiplica por 4
        integral += (i % 2 == 0) ? fx(minLimit + height * i) * 2 : fx(minLimit + height * i) * 4;
    }
    integral += fx(maxLimit);
    integral = integral * height / 3;

    return integral;
}


long double calculateError(){
    long double max = fabsl(fourthDerivativeFx(minLimit));
    long double aux;
    for (int i = 1; i < numberOfDivisions; i++)
    {
        aux = fabsl(fourthDerivativeFx(minLimit+i*height));
        if(aux > max){
            max = aux;
        }

    }
    
    return -1 * (pow(height,5)/90) * max;

}

int main()
{

    printf("* -------------------------------------------------------------------------- *\n");
    printf("*                Integracao Numerica - Metodo de Simpson                     *\n");
    printf("* -------------------------------------------------------------------------- *\n");

    setup();
    printf("I     = %.10Lf\n", calculateIntegral());
    printf("Error = %.10Lf\n", calculateError());
}