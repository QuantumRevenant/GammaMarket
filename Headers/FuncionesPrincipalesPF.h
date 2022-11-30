#ifndef FuncionesPRINCIPALESPF_H
#define FuncionesPRINCIPALESPF_H

#include <iostream>
#include <string>
#include <ctime>
#include "EstructurasPF.h"
#include "FuncionesGeneralesPF.h"
#include "FuncionesSecundariasPF.h"

// using namespace std;

void ModoDemo(Vendedor vendedor[], int *cantidadVendedores, int cantidadProductos)
{
    int i = *cantidadVendedores;
    if (true)
    {
        srand(time(0));
        i;
        vendedor[i].nombres = "Jose Luis";
        vendedor[i].apellidoPaterno = "Quispe";
        vendedor[i].apellidoMaterno = "Huamán";
        vendedor[i].datosLocal.pasaje = 14;
        vendedor[i].datosLocal.numeroLocal = 30;
        vendedor[i].datosLocal.nombreLocal = "Verdulería El Sabroso";
        vendedor[i].datosLocal.tipoLocal = "Verdulería";
        vendedor[i].password="test";

        for (int j = 0; j < cantidadProductos; j++)
            vendedor[i].productos[j] = ((rand() % 361) * 1.00) / 100;

        i++;
        vendedor[i].nombres = "Maria";
        vendedor[i].apellidoPaterno = "Ramos";
        vendedor[i].apellidoMaterno = "Quispe";
        vendedor[i].datosLocal.pasaje = 8;
        vendedor[i].datosLocal.numeroLocal = 25;
        vendedor[i].datosLocal.nombreLocal = "Frutería Mango Dulce";
        vendedor[i].datosLocal.tipoLocal = "Frutería";
        vendedor[i].password="test";

        for (int j = 0; j < cantidadProductos; j++)
            vendedor[i].productos[j] = (rand() % 361) / 100;
    }

    *cantidadVendedores = i + 1;
}

int MenuPrincipal(bool DemoMode = false)
{
    int cantOpciones = 4, opcion = 0;

    do
    {
        system("cls");
        cout << "Escoge tu opción:" << endl
             << "1) Mostrar Promedios del Mercado" << endl
             << "2) Buscar Vendedor / Iniciar Sesión" << endl
             << "3) Registrar Nuevo Vendedor" << endl;
        if (DemoMode)
        {
            cout << "4) Modo Demostración (Cargar Datos)" << endl;
            cantOpciones = 5;
        }

        cout << "0) Salir" << endl
             << "-------------------------" << endl;

        if (opcion < 0 || opcion > cantOpciones - 1)
            cout << ">OPCIÓN INVALIDA<" << endl
                 << "-------------------------" << endl;

        cin >> opcion;
    } while (opcion < 0 || opcion > cantOpciones - 1);

    return opcion;
}

void Logearse(Vendedor dataBase[], int CantidadData, int index, string NombresProductos[], int CantidadProductos)
{
    Vendedor temporal;
    string repeatPassword, inputPassword;
    int repeticiones = 0, opcion = 0;
    bool validacionPassword = false, validacionPasajeLocal = false, validacionModifPasLoc = false;

    do
    {
        if (repeticiones > 0)
            cout << "ERROR, CONTRASEÑA INCORRECTA" << endl
                 << "-------------------------" << endl;
        cout << "Introduce tu contraseña: " << endl;
        cin >> inputPassword;
        repeticiones++;
        if (repeticiones > 3)
        {
            system("cls");
            cout << "Demasiadas Intentos Fallidos, Volviendo al menú Principal" << endl;
            system("pause");
        }

    } while (dataBase[index].password != inputPassword || repeticiones > 2);

    if (repeticiones < 3)
    {
        system("cls");

        cout << "OJO -> Si no deseas modificar un dato rellena el campo con una 'x'" << endl
             << "---------------------------------------------------------------------------" << endl
             << "Si es pasaje,número de Local o precio de Producto, para no modificar, rellena con '-1'" << endl
             << "---------------------------------------------------------------------------" << endl
             << endl;

        temporal = Recopilar(NombresProductos, CantidadProductos,-1.0f);

        if (temporal.password != "x")
        {
            cout << "Reintroduce tu contraseña" << endl;
            cin >> repeatPassword;
        }
        else
            repeatPassword = dataBase[index].password;

        temporal=RecuperarDatos(dataBase, index, temporal, CantidadProductos);

        // Validaciones
        if (temporal.password == repeatPassword)
            validacionPassword = true;

        validacionPasajeLocal = ValidacionPasajeLocal(dataBase, CantidadData, temporal);

        // Correcciones
        if (!validacionPassword)
        {
            do
            {
                cout << "Contraseña no coincide" << endl
                     << "-Introduce '0' cancelar el registro-" << endl;
                cout << "Introduce tu contraseña: ";
                cin >> temporal.password;
                if (temporal.password != "0")
                {
                    cout << "Repite tu contraseña: ";
                    cin >> repeatPassword;
                }
            } while (temporal.password != repeatPassword && temporal.password != "0");

            if (temporal.password != "0")
                validacionPassword == true;
        }

        if (temporal.datosLocal.pasaje == dataBase[index].datosLocal.pasaje || temporal.datosLocal.numeroLocal == dataBase[index].datosLocal.numeroLocal)
        {
            validacionModifPasLoc = true;
            validacionPasajeLocal=true;
        }

        if (temporal.password != "0" && !validacionPasajeLocal && !validacionModifPasLoc)
        {

            do
            {
                do
                {
                    system("cls");
                    cout << "Pasaje y Local ya están ocupados" << endl
                         << "~SI ES UN ERROR, CONTACTA A UN ADMINISTRADOR~" << endl
                         << endl;
                    cout << "0) Cancelar el registro" << endl
                         << "1) Volver a registrar el Pasaje y Local" << endl
                         << "-------------------------"<<endl;
                    if (opcion < 0 || opcion > 1)
                        cout << ">OPCIÓN INVALIDA<" << endl
                             << "-------------------------" << endl;
                    cin >> opcion;
                } while (opcion < 0 || opcion > 1);

                if (opcion == 1)
                {
                    cout << "Introduce tu número de Pasaje" << endl;
                    cin >> temporal.datosLocal.pasaje;
                    cout << "Introduce tu número de Local" << endl;
                    cin >> temporal.datosLocal.numeroLocal;

                    validacionPasajeLocal = ValidacionPasajeLocal(dataBase, CantidadData, temporal);
                }
                else
                    validacionPasajeLocal = false;
            } while (validacionPasajeLocal || opcion == 0);
        }

        // Registro
        if (validacionPassword && validacionPasajeLocal)
        {
            dataBase[index] = temporal;
            cout << "¡Modificación efectuada! ^-^" << endl;
            system("Pause");
        }
        else
        {
            cout << "Modificación invalida..." << endl;
            system("Pause");
        }
    }
}

void Registrarse(Vendedor dataBase[], int *CantidadData, string NombresProductos[], int CantidadProductos, string contraAdmin = "Admin")
{
    Vendedor temporal;
    string repeatPassword, adminPassword;
    int repeticiones = 0, opcion = 0;
    bool validacionPassword = false, validacionPasajeLocal = false;

    do
    {
        system("cls");
        if (repeticiones > 0)
            cout << "-------------------------" << endl
                 << "ERROR, CONTRASEÑA INCORRECTA" << endl
                 << "-------------------------" << endl;
        cout << "Introduce la contraseña del administrador: " << endl;
        cin >> adminPassword;
        repeticiones++;
        if (repeticiones > 2)
        {
            system("cls");
            cout << "Demasiadas Intentos Fallidos, Volviendo al menú Principal" << endl;
            system("pause");
        }

    } while (contraAdmin != adminPassword && repeticiones < 3);

    if (repeticiones < 3)
    {
        system("cls");
        temporal = Recopilar(NombresProductos, CantidadProductos);

        cout << "Reintroduce tu contraseña" << endl;
        cin >> repeatPassword;

        // Validaciones
        if (temporal.password == repeatPassword)
            validacionPassword = true;

        validacionPasajeLocal = ValidacionPasajeLocal(dataBase, *CantidadData, temporal);

        // Correcciones
        if (!validacionPassword)
        {
            do
            {
                cout << "Contraseña no coincide" << endl
                     << "-Introduce '0' cancelar el registro-" << endl;
                cout << "Introduce tu contraseña: ";
                cin >> temporal.password;
                if (temporal.password != "0")
                {
                    cout << "Repite tu contraseña: ";
                    cin >> repeatPassword;
                }
            } while (temporal.password != repeatPassword && temporal.password != "0");

            if (temporal.password != "0")
                validacionPassword == true;
        }

        if (temporal.password != "0" && !validacionPasajeLocal)
        {

            do
            {
                do
                {
                    system("cls");
                    cout << "Pasaje y Local ya están ocupados" << endl
                         << "~SI ES UN ERROR, CONTACTA A UN ADMINISTRADOR~" << endl
                         << endl;
                    cout << "0) Cancelar el registro" << endl
                         << "1) Volver a registrar el Pasaje y Local" << endl
                         << "-------------------------";
                    if (opcion < 0 || opcion > 1)
                        cout << ">OPCIÓN INVALIDA<" << endl
                             << "-------------------------" << endl;
                    cin >> opcion;
                } while (opcion < 0 || opcion > 1);

                if (opcion == 1)
                {
                    cout << "Introduce tu número de Pasaje" << endl;
                    cin >> temporal.datosLocal.pasaje;
                    cout << "Introduce tu número de Local" << endl;
                    cin >> temporal.datosLocal.numeroLocal;

                    validacionPasajeLocal = ValidacionPasajeLocal(dataBase, *CantidadData, temporal);
                }
                else
                    validacionPasajeLocal = false;
            } while (validacionPasajeLocal || opcion == 0);
        }

        // Registro
        if (validacionPassword && validacionPasajeLocal)
        {
            dataBase[*CantidadData] = temporal;
            *CantidadData = *CantidadData + 1;

            cout << "¡Registro efectuado! ^-^" << endl;
            system("Pause");
        }
        else
        {
            cout << "Registro invalido..." << endl;
            system("Pause");
        }
    }
}

void MostrarPromedios(Vendedor arregloVendedores[], int cantidadVendedores, string nombresProductos[], int cantidadProductos)
{
    float aPromediar[999], arregloRespuestas[999];

    for (int i = 0; i < cantidadProductos; i++)
    {
        for (int j = 0; j < cantidadVendedores; j++)
        {
            aPromediar[j] = arregloVendedores[j].productos[i];
        }

        arregloRespuestas[i] = PromediarMayor0(aPromediar, cantidadVendedores);
    }

    // displayPromedios

    cout << "//PROMEDIOS GENERALES DEL MERCADO\\\\" << endl
         << "-------------------------" << endl
         << endl;
    for (int i = 0; i < cantidadProductos; i++)
    {
        cout << "> " << nombresProductos[i] << ": S/ ";
        if (arregloRespuestas[i] <= 0)
            cout << "No tenemos registros" << endl;
        else
            cout << arregloRespuestas[i] << endl;
    }

    cout << endl
         << endl
         << "-END LINE-" << endl;
    system("pause");
}

void Buscar(Vendedor arregloVendedores[], int cantidadVendedores, string nombresProductos[], int cantidadProductos)
{
    int indexResultado = 0;
    long int opcion = 0;

    do
    {
        system("cls");
        cout << "Escoge el tipo de busqueda que deseeas realizar: " << endl
             << "0) Volver al Menú Principal" << endl
             << "1) Buscar por N° Pasaje y N° Local" << endl
             << "2) Buscar por Nombre del Local" << endl
             << "3) Buscar por Nombre del propietario" << endl
             << "--------------------------------------------------" << endl;
        if (opcion < 0 || opcion > 3)
            cout << ">OPCIÓN INVALIDA<" << endl
                 << "--------------------------------------------------" << endl;
        cin >> opcion;
    } while (opcion < 0 || opcion > 3);

    switch (opcion)
    {
    case 1:
        system("cls");
        indexResultado = BusquedaNumeroLocal(arregloVendedores, cantidadVendedores);
        break;
    case 2:
        system("cls");
        indexResultado = BusquedaNombreLocal(arregloVendedores, cantidadVendedores);
        break;
    case 3:
        system("cls");
        indexResultado = BusquedaNombreVendedor(arregloVendedores, cantidadVendedores);
        break;

    default:
        indexResultado = -1;
        break;
    }

    if (indexResultado < 0)
    {
        system("cls");
        cout << "..." << endl
             << "..." << endl
             << "Escogiste salir" << endl
             << endl;
    }
    else
    {
        system("cls");
        cout << "=|| " << arregloVendedores[indexResultado].datosLocal.nombreLocal << " ||=" << endl
             << "--------------------------------------------------" << endl;
        cout << "Pasaje: " << arregloVendedores[indexResultado].datosLocal.pasaje << "          Número de Local: " << arregloVendedores[indexResultado].datosLocal.numeroLocal << endl
             << "Tipo de Local: " << arregloVendedores[indexResultado].datosLocal.tipoLocal << endl
             << "Dueño: " << arregloVendedores[indexResultado].nombres << " " << arregloVendedores[indexResultado].apellidoPaterno << " " << arregloVendedores[indexResultado].apellidoMaterno << endl
             << endl
             << endl
             << "Productos: " << endl
             << endl;

        for (int i = 0; i < cantidadProductos; i++)
        {
            if (arregloVendedores[indexResultado].productos[i] > 0)
                cout << "> " << nombresProductos[i] << ": S/ " << arregloVendedores[indexResultado].productos[i] << endl;
        }
        system("pause");
        cout << endl;
        opcion = 0;
        do
        {
            system("cls");
            cout << "¿Desea Iniciar Sesión o Volver al Menú Principal?" << endl
                 << "--------------------------------------------------" << endl;
            if (opcion < 0 || opcion > 1)
                cout << ">OPCIÓN INVALIDA<" << endl
                     << "--------------------------------------------------" << endl;
            cout<<"0) Menú Principal"<<endl<<"1) Iniciar Sesión"<<endl;

            cin>>opcion;
        } while (opcion < 0 || opcion > 1);

        
        system("cls");
        if(opcion==1)
            Logearse(arregloVendedores,cantidadVendedores,indexResultado,nombresProductos,cantidadProductos);
    }
}

#endif