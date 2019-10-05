//  main.cpp
//  Subsecuencia comun maxima
//
//  Created by Christian Alberto Dalma Schultz on 10/4/19.
//  Copyright © 2019 Christian Alberto Dalma Schultz. All rights reserved.
//

#include<iostream>
#include<string.h>
using namespace std;
  

int SubString(char *X, char *Y, int k, int n)
{
  
    int SecuenciaCom[k+1][n+1];
    int resultado = 0;
  
    // Consturctores de las secuencias
    
    for (int i=0; i<=k; i++)
    {
        for (int j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                SecuenciaCom[i][j] = 0;
  
            else if (X[i-1] == Y[j-1])
            {
                SecuenciaCom[i][j] = SecuenciaCom[i-1][j-1] + 1;
                resultado = max(resultado, SecuenciaCom[i][j]);
            }
            else SecuenciaCom[i][j] = 0;
        }
    }
    return resultado;
}
  int main()
{
    char X[] = "oh yeah, it's big brain time";
    char Y[] = "bing bong bing bing bong chop chop";
  
    int k = strlen(X);
    int n = strlen(Y);
  
    cout << "el tamano de la secuencia mas grande es:  " << SubString(X, Y, k, n)<<endl;
    return 0;
}
