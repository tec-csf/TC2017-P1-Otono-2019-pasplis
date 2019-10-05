// https://www.geeksforgeeks.org/word-wrap-problem-dp-19/
//  main.cpp
//  Divicion de parrafos
//
//  Created by Christian Alberto Dalma Schultz on 10/2/19.
//  Copyright © 2019 Christian Alberto Dalma Schultz. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
#define INF INT_MAX
  

int PrintSol (int Print[], int n);
  

void DivicionPar (int letras[], int n, int M)
{

    int space[n+1][n+1];
    int numero[n+1][n+1];
    int Total[n+1];
    int Print[n+1];
  
    
    for (int i = 1; i <= n; i++)
    {
        space[i][i] = M - letras[i-1];
        for (int j = i+1; j <= n; j++)
            space[i][j] = space[i][j-1] - letras[j-1] - 1;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            if (space[i][j] < 0)
                numero[i][j] = INF;
            else if (j == n && space[i][j] >= 0)
                numero[i][j] = 0;
            else
                numero[i][j] = space[i][j]*space[i][j];
        }
    }
  
    Total[0] = 0;
    for (int j = 1; j <= n; j++)
    {
        Total[j] = INF;
        for (int i = 1; i <= j; i++)
        {
            if (Total[i-1] != INF && numero[i][j] != INF &&
                           (Total[i-1] + numero[i][j] < Total[j]))
            {
                Total[j] = Total[i-1] + numero[i][j];
                Print[j] = i;
            }
        }
    }
  
    PrintSol(Print, n);
}
  
int PrintSol (int Print[], int n)
{
    int k;
    if (Print[n] == 1)
        k = 1;
    else
        k = PrintSol (Print, Print[n]-1) + 1;
    cout<<"Lineas: "<<k<<": Palabra num: "<<Print[n]<<" a "<<n<<endl;
    return k;
}
  
int main()
{
    int letras[] = {3, 2, 2, 5};
    int n = sizeof(letras)/sizeof(letras[0]);
    int M = 6;
    DivicionPar (letras, n, M);
    return 0;
}

