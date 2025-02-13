#ifndef __CAMPO__
#define __CAMPO__
#include<algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
//gli arrey dinamici si allocano con      double* data = new double[ndata];

struct Punto3D {
    double x;
    double y;
    double z;

    // Metodo per calcolare la distanza dall'origine
    double distanzaOrigine() {
        return std::sqrt(x * x + y * y + z * z);
    }

    // Metodo per calcolare la distanza da un altro punto
    double distanzaDa(const Punto3D& altro) {
        return std::sqrt((x - altro.x) * (x - altro.x) +
                         (y - altro.y) * (y - altro.y) +
                         (z - altro.z) * (z - altro.z));
    }
};

struct Punto2D {
    double x;
    double y;

    // Metodo per calcolare la distanza dall'origine
    double distanzaOrigine() {
        return std::sqrt(x * x + y * y);
    }

    // Metodo per calcolare la distanza da un altro punto
    double distanzaDa(const Punto2D& altro) {
        return std::sqrt((x - altro.x) * (x - altro.x) + (y - altro.y) * (y - altro.y));
    }
};
// Struttura per un triangolo
struct Triangolo {
    Punto2D vertice1;
    Punto2D vertice2;
    Punto2D vertice3;

    // Metodo per calcolare il perimetro del triangolo
    double perimetro() const {
        double lato1 = vertice1.distanzaDa(vertice2);
        double lato2 = vertice2.distanzaDa(vertice3);
        double lato3 = vertice3.distanzaDa(vertice1);
        return lato1 + lato2 + lato3;
    }

    // Metodo per calcolare l'area del triangolo usando la formula di Erone
    double area() const {
        double lato1 = vertice1.distanzaDa(vertice2);
        double lato2 = vertice2.distanzaDa(vertice3);
        double lato3 = vertice3.distanzaDa(vertice1);
        double semiperimetro = (lato1 + lato2 + lato3) / 2;
        return std::sqrt(semiperimetro * (semiperimetro - lato1) * (semiperimetro - lato2) * (semiperimetro - lato3));
    }
};

#endif // __CAMPO__