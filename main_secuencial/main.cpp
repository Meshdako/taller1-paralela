/*
Integrantes:
    *   Martín Sobarzo
    *   Rodrigo Ubilla
    *   Cristobal Abarca
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

void Integrantes()
{
    cout << "Los integrantes son: \n\t1. Martín Sobarzo.\n\t2. Cristobal Abarca.\n\t3. Rodrigo Ubilla." << endl;
}

void LeerEscribir()
{
    ifstream archivo;
    string linea;
    char delimitador = ';';
    
    ofstream destino;

    //Destino de los resultados obtenidos.
    destino.open("resultadospruebas.csv", ios::out);

    if(destino.fail()){
        cout << "Error: no se puede abrir el archivo resultadospruebas.csv" << endl;
        exit(1);
    }
    
    //Abrimos el archivo que debemos leer.
    archivo.open("pruebas.csv", ios::in);

    if(archivo.fail()){
        cout << "Error: no se pudo abrir el archivo pruebas.csv" << endl;
        exit(1);
    }

    //Omitimos la primera línea.
    getline(archivo, linea);
    getline(archivo, linea);
    
    //Ingresamos la primera línea al archivo de destino.
    stringstream Columnas;
    Columnas << "\"Identificador de Estudiante\"" << ";" << "\"Preguntas correctas\"" << ";" << "\"Preguntas incorrectas\"" << ";" << "\"Preguntas omitidas\"" << ";" << "\"Puntaje\"" << ";" << "\"Nota\"";
    string PrimeraFila = Columnas.str();
    destino << PrimeraFila << endl;

    //Variable para capturar los datos del archivo.
    string Datos[13];
    string PregCorrectas[12] = {"\"A\"", "\"E\"", "\"C\"", "\"B\"", "\"B\"", "\"D\"", "\"A\"", "\"B\"", "\"E\"", "\"C\"", "\"B\"", "\"D\""};

    //Contador de preguntas correctas, incorrectas y omitidas.
    int RespCorrectas, RespIncorrectas, RespOmitidas;
    RespCorrectas = RespIncorrectas = RespOmitidas = 0;

    while(getline(archivo, linea)){
        stringstream stream(linea);
        getline(stream, Datos[0], delimitador);
        getline(stream, Datos[1], delimitador);
        getline(stream, Datos[2], delimitador);
        getline(stream, Datos[3], delimitador);
        getline(stream, Datos[4], delimitador);
        getline(stream, Datos[5], delimitador);
        getline(stream, Datos[6], delimitador);
        getline(stream, Datos[7], delimitador);
        getline(stream, Datos[8], delimitador);
        getline(stream, Datos[9], delimitador);
        getline(stream, Datos[10], delimitador);
        getline(stream, Datos[11], delimitador);
        getline(stream, Datos[12], delimitador);
        
        //Calculamos el puntaje del estudiante.
        for(int i = 1, j = 0; i < 13; i++, j++){
            if(Datos[i] == "\"-\""){
                RespOmitidas++;
            }
            else{
                if(Datos[i].compare(PregCorrectas[j]) == 0){
                    RespCorrectas++;
                }
                else{
                    RespIncorrectas++;
                }
            }
        }

        float Puntaje = (RespCorrectas * 0.5) - (RespIncorrectas * 0.12);
        Puntaje = roundf(Puntaje * 10) / 10;

        float NotaFinal = 1 + Puntaje;
        NotaFinal = roundf(NotaFinal * 10) / 10;

        if(NotaFinal < 1)
            NotaFinal = 1;

        string Aux_Correctas, Aux_Incorrectas, Aux_Omitidas, Aux_Puntaje, Aux_NFinal;

        Aux_Correctas = "\"" + to_string(RespCorrectas) + "\"";
        Aux_Incorrectas = "\"" + to_string(RespIncorrectas) + "\"";
        Aux_Omitidas = "\"" + to_string(RespOmitidas) + "\"";
        Aux_Puntaje = "\"" + to_string(Puntaje) + "\"";
        Aux_NFinal = "\"" + to_string(NotaFinal) + "\"";

        string LineaDocumento = Datos[0] + ";" + Aux_Correctas + ";" + Aux_Incorrectas + ";" + Aux_Omitidas + ";" + Aux_Puntaje + ";" + Aux_NFinal;


        destino << LineaDocumento << endl; 

        RespCorrectas = RespIncorrectas = RespOmitidas = 0;
    }

    //Cerramos los archivos al finalizar el bucle.
    archivo.close();
    destino.close();
}

int main()
{
    Integrantes();
    LeerEscribir();
    cout << "Grabación hecha con éxito" << endl;
    
    return EXIT_SUCCESS;
}