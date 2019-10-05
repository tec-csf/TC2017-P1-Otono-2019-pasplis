// https://www.geeksforgeeks.org/stable-marriage-problem/
//  main.cpp
//  Pareja estable
//
//  Created by Christian Alberto Dalma Schultz on 10/2/19.
//  Copyright © 2019 Christian Alberto Dalma Schultz. All rights reserved.
//


#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
  
// Numero de hombre y mujeres
#define N  4
  
// Funcion de evaluacion de si la mujer prefiere al nuevo hombre
bool PreferMen(int prefer[2*N][N], int w, int m, int m1)
{
    for (int i = 0; i < N; i++)
    {

        if (prefer[w][i] == m1)
            return true;
 
        if (prefer[w][i] == m)
           return false;
    }
    return 0;
}

void ParejaStable(int prefer[2*N][N])
{
    // Guarda el match de la mujer con el hombre
    int ParejaM[N];
  
    // Guarda si el hombre esta libre
    bool LibreH[N];
  
    // constructor hombre y mujeres libres
    memset(ParejaM, -1, sizeof(ParejaM));
    memset(LibreH, false, sizeof(LibreH));
    int free = N;
  
    // el programa continua mientras un hombre este libre
    while (free > 0)
    {
        int m;
        for (m = 0; m < N; m++)
            if (LibreH[m] == false)
                break;
  
        // va con cada mujer dependiendo su preferencia
        for (int i = 0; i < N && LibreH[m] == false; i++)
        {
            int w = prefer[m][i];
  
            // La mujere hace match se juntan pero puede cambiar
            if (ParejaM[w-N] == -1)
            {
                ParejaM[w-N] = m;
                LibreH[m] = true;
                free--;
            }
  
            else
            {
                int m1 = ParejaM[w-N];
  
                // si la mujer prefiere mas a este se cambia y el hombre termina
                // libre 
                if (PreferMen(prefer, w, m, m1) == false)
                {
                    ParejaM[w-N] = m;
                    LibreH[m] = true;
                    LibreH[m1] = false;
                }
            }
        }
    }
  
    cout << "Mujer   Hombre" << endl;
    for (int i = 0; i < N; i++)
       cout << "  " << i+N << "\t      " << ParejaM[i] << endl;
}
  

int main()
{
    int prefer[2*N][N] = { {7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
    ParejaStable(prefer);
  
    return 0;
}

