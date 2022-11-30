#ifndef EstructurasPF_H
#define EstructurasPF_H

#include <string>

typedef struct Puntuacion
{
    float puntaje=5.0;
    short int arregloPuntajes[999];
    int cantidadPuntajes=0;
};

typedef struct Local
{
    short int pasaje;
    short int numeroLocal;
    std::string nombreLocal;
    std::string tipoLocal;
};

typedef struct Vendedor
{
    std::string nombres;
    std::string apellidoPaterno;
    std::string apellidoMaterno;
    std::string password;
    float productos[999];
    Local datosLocal;
    Puntuacion puntuacion;
};

#endif