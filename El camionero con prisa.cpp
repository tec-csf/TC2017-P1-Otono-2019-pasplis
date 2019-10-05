//  main.cpp
//  El camionero con prisa
//
//  Created by Christian Alberto Dalma Schultz on 10/3/19.
//  Copyright © 2019 Christian Alberto Dalma Schultz. All rights reserved.
//

#include <iostream>
using namespace std;
  

int Contador(int Recorrido, int Distancia, int Stop, int detenido[])
{
    int n = 0;
    int k = 0;
    int ContDistancia= 0;
    
    
    while (ContDistancia< Recorrido) {
        if (k < Stop && detenido[k] <= (ContDistancia+ Distancia)) {
            ContDistancia= detenido[k];
            
            k++;
        }
        else
            ContDistancia+= Distancia;

        if (ContDistancia< Recorrido)
            n++;
    }
  
    return n;
}
  

int main()
{
    int Recorrido = 15;
    int Distancia = 5;
    int Stop = 3;
    int Gasolina[] = { 5, 10, 12};
  
    cout << "El numero de gasolineras visitadas fue: " << Contador(Recorrido, Distancia, Stop, Gasolina) << endl;
    return 0;
}
