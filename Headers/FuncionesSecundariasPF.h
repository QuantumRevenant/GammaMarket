#ifndef FuncionesSECUNDARIASPF_H
#define FuncionesSECUNDARIASPF_H

#include <iostream>
#include <string>
#include <sstream>
#include "EstructurasPF.h"
#include "FuncionesGeneralesPF.h"

using namespace std;

string Escoger(Vendedor datos[], int similitudes[], int cantidadSimilitudes)
{
    string opcion = "-1";
    string salida = "";
    bool salir = true;
    int j;

    do
    {
        if (!salir)
            system("cls");

        if (cantidadSimilitudes > 0)
        {
            cout << "Encontramos estas opciones:" << endl
                 << "-------------------------"
                 << endl;
            if (!salir)
                cout << ">OPCIÓN INVALIDA<" << endl
                     << "-------------------------" << endl;
            cout << "Vuelve a introducir un nuevo dato para reemplazar la busqueda u otra opción:" << endl
                 << "0) Salir"
                 << endl;
            for (int i = 0; i < cantidadSimilitudes; i++)
            {
                j = similitudes[i];
                cout << i + 1 << ") Local: " << datos[j].datosLocal.nombreLocal << " Pasaje: " << datos[j].datosLocal.pasaje << " Local: " << datos[j].datosLocal.numeroLocal << endl
                     << "Dueño: " << datos[j].nombres << " " << datos[j].apellidoPaterno << " " << datos[j].apellidoMaterno << endl
                     << endl;
            }
        }
        else
        {
            cout << "No encontramos opciones :(" << endl
                 << "-------------------------"
                 << endl;
            if (!salir)
                cout << ">OPCIÓN INVALIDA<" << endl
                     << "-------------------------" << endl;
            cout << "Vuelve a introducir un nuevo dato para reemplazar la busqueda u otra opción:" << endl
                 << "0) Salir"
                 << endl;
        }

        // cin.ignore(1000, '\n');
        getline(cin, opcion);

        if (opcion.length() != 0)
        {
            if (esNumero(opcion))
            {
                if (stol(opcion) < 0 || stol(opcion) > cantidadSimilitudes)
                {
                    salir = false;
                }
                else
                    salir = true;
            }
            else
                salir = true;
        }
        else
            salir = true;

    } while (!salir);

    if (opcion.length() != 0)
    {
        if (esNumero(opcion))
        {
            if (stoi(opcion) > 0)
                salida = to_string(similitudes[stoi(opcion) - 1]);
            else
                salida = "-1";
        }
        else
            salida = opcion;
    }
    else
        salida = "-1";
    return salida;
}

int BusquedaNombreVendedor(Vendedor param[], int cantidadParametros)
{
    // Declaraciones
    float porcentajeCoincidencia = 0.60; // Porcentaje de Coincidencia de palabra en una frase para validarla como encontrada
    int cantidadCoincidencias = 1;       // Cantidad minima de palabras encontradas para validarla como similitud
    //
    int i = 0, j = 0;                                                               // contadores
    string codigoResultado;                                                         // Resultado escogido por el usuario
    int indexResultado;                                                             // respuesta
    int cantidadData, cantidadSubcadenas, longitudSubcadena, coincidenciaSubcadena; // Validar las coincidencias
    int indexSimilares[99], cantidadSimilares;                                      // Coincidencias almacenadas
    string entrada, lectura, ArregloData[99];                                       // Strings de entrada o trabajo
    bool repetir = false;

    cout << "Introduce el Nombre del Vendedor a Buscar" << endl;
    cin.ignore(10000, '\n');
    getline(cin, entrada);
    do
    {
        if (repetir)
        {
            system("cls");
            cout << "Reiniciamos la comprobación" << endl
                 << "..." << endl
                 << "..." << endl
                 << "..." << endl
                 << endl;
        }

        cantidadSimilares = 0;
        cantidadSubcadenas = 0;
        // For para recorer la database
        for (i = 0; i < cantidadParametros; i++)
        {
            // Segmentar en Palabras el nombre
            stringstream input_stringstream(param[i].nombres);
            j = 0;
            while (getline(input_stringstream, lectura, ' '))
            {
                ArregloData[j] = lectura;
                j++;
            }
            cantidadData = j;

            // Asignar los apellidos al array
            ArregloData[cantidadData] = param[i].apellidoPaterno;
            cantidadData++;
            ArregloData[cantidadData] = param[i].apellidoMaterno;
            cantidadData++;

            // Validar si el conjunto de Subcadenas es mayor a 50%
            cantidadSubcadenas = 0;
            for (j = 0; j < cantidadData; j++)
            {
                longitudSubcadena = ArregloData[j].length();
                coincidenciaSubcadena = subCadenaComunMasLarga(aMinuscula(entrada), aMinuscula(ArregloData[j]));

                if ((coincidenciaSubcadena * 1.0) / longitudSubcadena >= porcentajeCoincidencia)
                {
                    cantidadSubcadenas++;
                }
            }

            // Si encontró dos similitudes, guardar el index
            if (cantidadSubcadenas > cantidadCoincidencias)
            {
                indexSimilares[cantidadSimilares] = i;
                cantidadSimilares++;
            }
        }

        codigoResultado = Escoger(param, indexSimilares, cantidadSimilares);

        if (!esNumero(codigoResultado) && codigoResultado != "-1")
        {
            repetir = true;
            entrada = codigoResultado;
        }
        else
            repetir = false;
    } while (repetir);

    indexResultado = stoi(codigoResultado);
    return indexResultado;
}

int BusquedaNombreLocal(Vendedor param[], int cantidadParametros)
{
    // Declaraciones
    float porcentajeCoincidencia = 0.60; // Porcentaje de Coincidencia de palabra en una frase para validarla como encontrada
    int cantidadCoincidencias = 1;       // Cantidad minima de palabras encontradas para validarla como similitud
    //
    int i = 0, j = 0;                                                               // contadores
    string codigoResultado;                                                         // Resultado escogido por el usuario
    int indexResultado;                                                             // respuesta
    int cantidadData, cantidadSubcadenas, longitudSubcadena, coincidenciaSubcadena; // Validar las coincidencias
    int indexSimilares[99], cantidadSimilares;                                      // Coincidencias almacenadas
    string entrada, lectura, ArregloData[99];                                       // Strings de entrada o trabajo
    bool repetir = false;

    cout << "Introduce el Nombre del Local a Buscar: " << endl;
    cin.ignore(10000, '\n');
    getline(cin, entrada);
    do
    {
        if (repetir)
        {
            system("cls");
            cout << "Reiniciamos la comprobación" << endl
                 << "..." << endl
                 << "..." << endl
                 << "..." << endl
                 << endl;
        }

        cantidadSimilares = 0;
        cantidadSubcadenas = 0;
        // For para recorer la database
        for (i = 0; i < cantidadParametros; i++)
        {
            // Segmentar en Palabras el nombre
            stringstream input_stringstream(param[i].datosLocal.nombreLocal);
            j = 0;
            while (getline(input_stringstream, lectura, ' '))
            {
                ArregloData[j] = lectura;
                j++;
            }
            cantidadData = j;

            // Validar si el conjunto de Subcadenas es mayor a 50%
            cantidadSubcadenas = 0;
            for (j = 0; j < cantidadData; j++)
            {
                longitudSubcadena = ArregloData[j].length();
                coincidenciaSubcadena = subCadenaComunMasLarga(aMinuscula(entrada), aMinuscula(ArregloData[j]));

                if ((coincidenciaSubcadena * 1.0) / longitudSubcadena >= porcentajeCoincidencia)
                {
                    cantidadSubcadenas++;
                }
            }

            // Si encontró dos similitudes, guardar el index
            if (cantidadSubcadenas > cantidadCoincidencias)
            {
                indexSimilares[cantidadSimilares] = i;
                cantidadSimilares++;
            }
        }

        codigoResultado = Escoger(param, indexSimilares, cantidadSimilares);

        if (!esNumero(codigoResultado) && codigoResultado != "-1")
        {
            repetir = true;
            entrada = codigoResultado;
        }
        else
            repetir = false;
    } while (repetir);

    indexResultado = stoi(codigoResultado);
    return indexResultado;
}

int BusquedaNumeroLocal(Vendedor param[], int cantidadParametros)
{
    short int numeroPasaje, numeroLocal;
    int cantidadSimilares = 0, opcion = 0, indexResultado = -1, ubicacion = 0;
    do
    {
        cantidadSimilares = 0;
        opcion = 0;
        indexResultado = -1;
        ubicacion = 0;
        system("cls");
        cout << "Introduce el número de Pasaje: ";
        cin >> numeroPasaje;
        cout << endl
             << "Introduce el número de Local: ";
        cin >> numeroLocal;
        cout << endl;

        for (int i = 0; i < cantidadParametros; i++)
        {
            if (numeroLocal == param[i].datosLocal.numeroLocal && numeroPasaje == param[i].datosLocal.pasaje)
            {
                ubicacion = i;
                cantidadSimilares++;
            }
        }

        if (cantidadSimilares > 1)
        {
            system("cls");
            cout << "Encontramos un error, tenemos más de 1 registro con el mismo local y número de pasaje" << endl
                 << "Codigo Error: #" << cantidadSimilares << "0-D" << endl
                 << "Informa a un administrador lo más pronto posible" << endl
                 << "Lamentamos las Molestias, Utiliza otro metodo de busqueda para ubicar a tu vendedor" << endl;
            indexResultado = -1;
            opcion = 0;
            system("pause");
        }
        else
        {
            if (cantidadSimilares <= 0)
            {
                do
                {
                    system("cls");
                    cout << "No encontramos opciones :(" << endl
                         << "-------------------------" << endl;
                    if (opcion < 0 || opcion > 1)
                        cout << ">OPCIÓN INVALIDA<" << endl
                             << "-------------------------" << endl;
                    cout << "0) Salir" << endl
                         << "1) Reintentar"
                         << endl;
                    cin >> opcion;
                } while (opcion < 0 || opcion > 1);
            }
            else
            {
                do
                {
                    system("cls");
                    cout << "Encontramos esta opción: " << endl
                         << "-------------------------" << endl;
                    if (opcion < 0 || opcion > 1)
                        cout << ">OPCIÓN INVALIDA<" << endl
                             << "-------------------------" << endl;
                    cout << "0) Salir" << endl
                         << "1) Reintentar" << endl
                         << "2) "
                         << "Local: " << param[ubicacion].datosLocal.nombreLocal << " Pasaje: " << param[ubicacion].datosLocal.pasaje << " Número de Local: " << param[ubicacion].datosLocal.numeroLocal << endl
                         << "Dueño: " << param[ubicacion].nombres << " " << param[ubicacion].apellidoPaterno << " " << param[ubicacion].apellidoMaterno << endl
                         << endl;
                    cin >> opcion;
                } while (opcion < 0 || opcion > 2);
            }
        }
    } while (opcion == 1);

    if (opcion < 1)
    {
        indexResultado = -1;
    }
    else
    {
        indexResultado = ubicacion;
    }

    return indexResultado;
}

Vendedor Recopilar(string NombreProductos[], int CantidadProductos, float defaultValue=0.00)
{
    int codigo = 0;
    float precio;
    Vendedor input;
    for (int i = 0; i < CantidadProductos; i++)
    {
        input.productos[i] = defaultValue;
    }

    cout << "Introduce tus Nombres:" << endl;
    cin.ignore(1000, '\n');
    getline(cin, input.nombres);

    cout << "Introduce tu Apellido Paterno:" << endl;
    getline(cin, input.apellidoPaterno);

    cout << "Introduce tu Apellido Materno:" << endl;
    getline(cin, input.apellidoMaterno);

    cout << "Introduce el Nombre del Local:" << endl;
    getline(cin, input.datosLocal.nombreLocal);

    cout << "Introduce el Tipo de Local:" << endl;
    getline(cin, input.datosLocal.tipoLocal);

    cout << "Introduce tu Pasaje:" << endl;
    cin >> input.datosLocal.pasaje;

    cout << "Introduce tu Número de Local" << endl;
    cin >> input.datosLocal.numeroLocal;

    system("pause");

    do
    {
        codigo = 0;
        do
        {
            system("cls");
            if (codigo < 0 || codigo > CantidadProductos)
            {
                cout << ">CODIGO INVALIDO<" << endl
                     << "--------------------------------------------------" << endl;
            }
            cout << "Introduce el código del producto a registrar su precio" << endl
                 << "--------------------------------------------------" << endl
                 << "Si desea dejar de registrar productos, introduzca como código '0'" << endl
                 << "--------------------------------------------------" << endl;
            cin >> codigo;
        } while (codigo < 0 || codigo > CantidadProductos);

        if (codigo != 0)
        {
            system("cls");
            cout << "Si desea no registrar este producto, introduzca como precio '0'" << endl
                 << "--------------------------------------------------" << endl;
            cout << "Precio de [" << NombreProductos[codigo - 1] << "] :";
            cin >> precio;

            if (precio < 0)
                precio = -1;

            input.productos[codigo - 1] = precio;
        }

    } while (codigo != 0);

    system("cls");
    cout << "Introduce tu Contraseña (no uses espacios)" << endl;
    cin >> input.password;

    return input;
}

Vendedor RecuperarDatos(Vendedor dataBase[], int index, Vendedor temporal, int CantidadProductos)
{
    if (temporal.nombres == "x")
    {
        temporal.nombres = dataBase[index].nombres;
    }
    if (temporal.apellidoPaterno == "x")
    {
        temporal.apellidoPaterno = dataBase[index].apellidoPaterno;
    }
    if (temporal.apellidoMaterno == "x")
    {
        temporal.apellidoMaterno = dataBase[index].apellidoMaterno;
    }
    if (temporal.password == "x")
    {
        temporal.password = dataBase[index].password;
    }
    if (temporal.datosLocal.nombreLocal == "x")
    {
        temporal.datosLocal.nombreLocal = dataBase[index].datosLocal.nombreLocal;
    }
    if (temporal.datosLocal.tipoLocal == "x")
    {
        temporal.datosLocal.tipoLocal = dataBase[index].datosLocal.tipoLocal;
    }
    if (temporal.datosLocal.pasaje == -1)
    {
        temporal.datosLocal.pasaje = dataBase[index].datosLocal.pasaje;
    }
    if (temporal.datosLocal.numeroLocal == -1)
    {
        temporal.datosLocal.numeroLocal = dataBase[index].datosLocal.numeroLocal;
    }

    for (int i = 0; i < CantidadProductos; i++)
    {
        if (temporal.productos[i] == -1)
        {
            temporal.productos[i] = dataBase[index].productos[i];
        }
    }

    return temporal;
}

bool ValidacionPasajeLocal(Vendedor dataBase[], int CantidadData, Vendedor temporal)
{
    bool salida = true;

    for (int i = 0; i < CantidadData; i++)
    {
        if (temporal.datosLocal.numeroLocal == dataBase[i].datosLocal.numeroLocal && temporal.datosLocal.pasaje == dataBase[i].datosLocal.pasaje)
            salida = false;
    }

    return salida;
}

#endif