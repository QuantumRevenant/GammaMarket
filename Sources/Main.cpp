
#include <iostream>
#include <string>
#include <ctime>
#include "../Headers/EstructurasPF.h"
#include "../Headers/FuncionesGeneralesPF.h"
#include "../Headers/FuncionesPrincipalesPF.h"
#include <locale.h>
#include <random>

using namespace std;

int main()
{
    int opcion = 1;
    bool DemoActivo = false;
    int cantidadVendedores = 0;
    Vendedor vendedor[99];

    string arregloProductos[] = {"Papa Amarilla", "Papa Blanca", "Cebolla Roja", "Tomate"};
    int cantidadProductos = sizeof(arregloProductos)/sizeof(arregloProductos[0]);

    setlocale(LC_CTYPE, "Spanish_Spain");

    /*
    if (true)
    {
        i = 0;
        vendedor[i].nombres = "Jose Luis";
        vendedor[i].apellidoPaterno = "Quispe";
        vendedor[i].apellidoMaterno = "Huamán";
        vendedor[i].datosLocal.pasaje = 14;
        vendedor[i].datosLocal.numeroLocal = 30;
        vendedor[i].datosLocal.nombreLocal = "Verdulería El Sabroso";
        vendedor[i].datosLocal.tipoLocal = "Verdulería";
        srand(time(0));
        for (int j = 0; j < cantidadProductos; j++)
        {
            vendedor[i].productos[j] = ((rand() % 361) * 1.00) / 100;
            cout << vendedor[i].productos[j] << endl;
        }

        system("pause");

        i = 1;
        vendedor[i].nombres = "Maria";
        vendedor[i].apellidoPaterno = "Ramos";
        vendedor[i].apellidoMaterno = "Quispe";
        vendedor[i].datosLocal.pasaje = 8;
        vendedor[i].datosLocal.numeroLocal = 25;
        vendedor[i].datosLocal.nombreLocal = "Frutería Mango Dulce";
        vendedor[i].datosLocal.tipoLocal = "Frutería";
        for (int j = 0; j < cantidadProductos; j++)
            vendedor[i].productos[j] = (rand() % 361) / 100;
    }
    */

    cout << cantidadProductos;

    do
    {
        opcion = MenuPrincipal(!DemoActivo);

        // Escogiste Opción
        switch (opcion)
        {
        case 1:
            system("cls");
            MostrarPromedios(vendedor, cantidadVendedores, arregloProductos, cantidadProductos);
            break;
        case 2:
            Buscar(vendedor, cantidadVendedores, arregloProductos, cantidadProductos);
            break;
        case 3:
            Registrarse(vendedor, &cantidadVendedores, arregloProductos, cantidadProductos, "admin1234");
            break;
        case 4:
            cout<<DemoActivo;
            if (!DemoActivo)
            {
                ModoDemo(vendedor, &cantidadVendedores, cantidadProductos);
                DemoActivo=true;
            }
            else
            {
                cout << "Ya activamos el Modo Demo, esto solo sirve una vez :(" << endl;
                system("pause");
            }
            break;
        default:
            opcion=0;
            break;
        }

    } while (opcion != 0);

    cout << "Bye ^^";

    return 0;
}
