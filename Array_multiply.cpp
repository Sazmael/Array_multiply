#include <iostream>
#include <time.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <windows.h>
#include <cmath>
using namespace std;

void imprimir_matriz(int tablero[][10]);
void matriz_control(int control[][10]);
void dados(double &,int &);
void condicional_respuesta(int &,double &, int &,int &,int &, int &, int &, int tablero[][10], int control[][10]);
void crear_dat();
void lectura(fstream &archivo);
void ingresar_datos(fstream &archivo);
void limpiar_cin();
void limpiar_pantalla();
void buscar_cedula(fstream &archivo,int &,string &);
void guardar_puntaje(fstream &partidas,int &,string &,int &,int &,string &,int &);
void copiar_puntaje(fstream &partidas, fstream &puntostotal);
void pasar_datostop(fstream &puntostotal,int cedulas[],int puntos[],char nombres[][30]);
void ordenar_top(int cedulas[],int puntos[],int auxpuntos[],char nombres[][30]);
void leer_top(int cedulas[],int puntos[],char nombres[][30]);
void noletras();
void titulo();

int main()
{
 //Se declaran los archivos a usar
 fstream archivo;
 fstream partidas;
 fstream puntostotal;

 string nombre,nombre_j1, nombre_j2;
 int devolvermenu = 0;
 char ingresar = 's';
 int cedula1,cedula_j1, cedula_j2;
 int tablero[10][10];
 int control[10][10];
 int cedulas[10];
 int puntos[10];
 int auxpuntos[10];
 char nombres[10][30];
 int dado1, dado2;
 int i,j;
 int d1,d2;
 int total;
 double respuesta;
 int jugador = 1;
 int ronda1 = 0, ronda2 = 0;
 int juego;
 int puntos_j1 = 0, puntos_j2 = 0;

 srand(time(NULL));
 system("title Cuadrados de Multiplicacion by Olman Davila Solano");
 system("color 17");

 //Inicializar vectores y matrices
 for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){

    control[i][j] = 0;
    puntos[i] = 0;
    auxpuntos[i] = 0;
    cedulas[i] = 0;

        }
    }

    //Sacar aleatorios a la matriz multiplos con ayuda de dos variables a multiplicar
    for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){

    d1= 1 + rand() % (6);
    d2= 1 + rand() % (6);
    tablero[i][j] = d1 * d2;

        }
    }

do{

 titulo();
 cout << right << setw(60) << "MENU PRINCIPAL" << endl;
 cout << right << setw(40) << "Digite una opción:" << endl<<endl;
 cout << right << setw(40) << "1. Jugar" << endl;
 cout << right << setw(59) << "2. Los 10 mejores jugadores" << endl;
 cout << right << setw(63) << "3. Reporte general de jugadores" << endl;
 cout << right << setw(53) << "4. Ingresar jugadores" << endl;
 cout << right << setw(40) << "5. Salir" << endl;
 cout << right << setw(36) <<">>> ";
 cin >> juego;

 noletras();

 switch(juego){

 case 1:

  system("cls");
  titulo();
  cout << right << setw(63) << "Seleccione la cedula del primer jugador" << endl;

  //Se procede a buscar la cedula en el registro
  buscar_cedula(archivo,cedula1,nombre);

  //Se extraen las variables recogidas de los archivos para usarlas
  cedula_j1 = cedula1;
  nombre_j1 = nombre;

  titulo();
  cout << right << setw(64) << "Seleccione la cedula del segundo jugador" << endl;
  buscar_cedula(archivo,cedula1,nombre);
  cedula_j2 = cedula1;
  nombre_j2 = nombre;

  //Validacion de no repetir la cedula en el mismo juego
  if(cedula_j1 == cedula_j2){
    do{
      titulo();
      cout << right << setw(91) << "(Error): Debe seleccionar otra identificacion distinta y registrada" << endl;
      cout << right << setw(64) << "Seleccione la cedula del segundo jugador" << endl;
      buscar_cedula(archivo,cedula1,nombre);
      cedula_j2 = cedula1;
      nombre_j2 = nombre;

    }while(cedula_j1 == cedula_j2);

  }

    //Se entra al juego
    do{

     if(jugador == 1){
    //Tablero
    imprimir_matriz(tablero);
    matriz_control(control);

    cout << right << setw(100) << "Turno de " << nombre_j1 << " Ronda: " << ronda1 << endl;
    cout << right << setw(101) << "Puntos de " << nombre_j1 << ":" << puntos_j1 << endl;

        //Funcion que invoca dos dados a multiplicar
        dados(respuesta,total);

        //Funcion que registra la respuesta de la multiplicacion y da el resultado
        condicional_respuesta(total,respuesta,jugador,puntos_j1,puntos_j2,i,j,tablero,control);

        //Contador de ronda
        ronda1++;

        limpiar_pantalla();

        //Pasar de jugador
        jugador = 2;

    }

    if(jugador == 2){
    //Tablero
    //Se imprime la matriz
    imprimir_matriz(tablero);

    //Se imprime el control
    matriz_control(control);

    cout << right << setw(100) << "Turno de " << nombre_j2 << " Ronda: " << ronda2 << endl;
    cout << right << setw(101) << "Puntos de " << nombre_j2 << ":" << puntos_j2 << endl;

        dados(respuesta,total);
        condicional_respuesta(total,respuesta,jugador,puntos_j1,puntos_j2,i,j,tablero,control);

        ronda2++;

        limpiar_pantalla();
        jugador = 1;

    }

    //Bucle hasta las 20 rondas de cada jugador
    }while(ronda1 <= 20 && ronda2 <= 20);

    guardar_puntaje(partidas,cedula_j1,nombre_j1,puntos_j1,cedula_j2,nombre_j2,puntos_j2);
    copiar_puntaje(partidas,puntostotal);

    //Condicionales de ganador
    if(puntos_j1 > puntos_j2){

        cout << right << setw(50) << nombre_j1 << " ha ganado" << endl;
        limpiar_pantalla();
        return main();

    }

    if(puntos_j1 < puntos_j2){

        cout << right << setw(50) << nombre_j2 << " ha ganado" << endl;
        limpiar_pantalla();
        return main();

    }

    if(puntos_j1 == puntos_j2){

        cout << right << setw(50) << "Han empatado" << endl;
        limpiar_pantalla();
        return main();

    }

    break;


 case 2:

     limpiar_pantalla();
     cout << right << setw(64) << "TOP 10 Mejores jugadores" << endl;
     cout << right << setw(66) << "Nombre  \t  |Cedula \t |P. obtenidos" << endl;

    //Funcion para pasar datos al top.dat
     pasar_datostop(puntostotal,cedulas,puntos,nombres);

     //Funcion para ordenar de mayor a menor los puntajes
     ordenar_top(cedulas,puntos,auxpuntos,nombres);

     //Funcion para leer el archivo top.dat
     leer_top(cedulas,puntos,nombres);

        limpiar_pantalla();
        int main();
        break;

 case 3:

    limpiar_pantalla();
    titulo();
    cout << right << setw(40) << "Identificación \t\t|Nombre" << endl;

    //Funcion para leer el archivo Datos.dat
    lectura(archivo);

    limpiar_pantalla();
    devolvermenu = 0;
    break;

 case 4:


 do{

    system("cls");
    limpiar_cin();

    //Funcion para ingresar datos del jugador al archivo datos.dat
    ingresar_datos(archivo);
    limpiar_pantalla();
    titulo();

    //Algoritmo para pedir al usuario ingresar otro usuario
    cout <<  right << setw(64) << "Desea ingresar otro usuario? "<< endl;
    cout <<  right << setw(100) << "Digite S para ingresar otro usuario o N para volver al menú principal " << endl;
    cout << right << setw(33) << ">>> ";
    cin >> ingresar;


 }while(ingresar == 's' || ingresar == 'S');

    limpiar_pantalla();
    devolvermenu = 0;

    break;

 case 5:
    //Salida
     exit(0);
     break;

 default:
    //Se invoca al insertar un numero invalido en el switch
 cout << "Escoja un numero valido" << endl; break;

 }


}while(devolvermenu == 0);


    return 0;
}

void imprimir_matriz(int tablero[][10]){

 int i,j;

    cout << right << setw(20) << "Tablero" << endl;

    for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){

    cout << right << setw(9) << tablero[i][j] <<" |";

        }

        cout << endl;
    }

    cout << endl;


}

void matriz_control(int control[][10]){

int i,j;


//Tablero de control
    cout << right << setw(20) << "Control" << endl;
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){

                cout << right << setw(9) << control[i][j] <<" |";


            }

        cout << endl;
    }


}

void dados(double &respuesta, int &total){
 int dado1, dado2;
 int i,j;
 int puntos = 0;
//Dados

 //Se saca dos dados aleatorios del 1 al 6
    dado1 = 1 + rand() % (6);
    dado2 = 1 + rand() % (6);

    total = dado1 * dado2;

    cout << "Dado#1: " << dado1 << endl;
    cout << "Dado#2: " << dado2 << endl;

    cout << "El resultado de multiplicar ambos dados es: ";
    cin >> respuesta;

    noletras();


    //Validacion de ingresar enteros y mayores a 0
    if(respuesta <= 0 || fmod(respuesta,1.) > .0){

    do{
      cout << "(ERROR): Digite un numero entero mayor a 1" << endl;
      cin >> respuesta;
      noletras();


    }while(respuesta <= 0 || fmod(respuesta,1.) > .0);

    }


}

void condicional_respuesta(int &total,double &respuesta, int &jugador, int &puntos_j1, int &puntos_j2, int &i, int &j, int tablero[][10], int control[][10]){

float puntos  = 0;

if(respuesta == total){

        cout << "Acertaste" << endl;

            //Algoritmo que enlaza la posicion del tablero principal con control
            //Define el acierto y los puntos dependiendo del jugador
            for(int i = 0; i < 10; i++){
                for(int j = 0; j < 10; j++){

                    if(tablero[i][j] == respuesta && tablero[i][j] == total){

                        control[i][j] = control[i][j] + 1;

                        //Condicional para que no suma mas de 4 la tabla de control

                        if(control[i][j] > 4){

                            control[i][j] = 4;

                                }


                                    if(control[i][j] == 4){

                                        if(jugador == 1){

                                            cout << right << setw(60) << "Has ganado un punto jugador 1" << endl;
                                                puntos_j1 = puntos_j1 + 1;


                                    }else{

                                    cout << right << setw(60) << "Has ganado un punto jugador 2" << endl;
                                puntos_j2 = puntos_j2 + 1;
                            }

                                //Si la casilla llega a 4 se inhabilita
                            control[i][j] = 4;


                        cout << right << setw(50) << "Casilla inhabilitada" << endl;



                    }
                }
            }
        }



    }else{

    cout << right << setw(60) << "Fallaste, el resultado es " << total << endl;

    }



}

void ingresar_datos(fstream &archivo){

    fstream consulta; //Se declara un fstream para consultar la informacion
    int cedula, cedaux;
    int i,j;
    string nomb;
    int ced[15];
    string nombre,texto;

    //Se abre dos veces el mismo archivo de texto para añadir y leerlo
    archivo.open("datos.dat",ios::app); //abrir en modo añadir texto
    consulta.open("datos.dat",ios::in); //abrir en modo consulta texto

    //Mensaje de error si el archivo falla
    if(archivo.fail()){

     cout <<  right << setw(63) << "No se pudo abrir el archivo" << endl;

     exit(1);
    }

    titulo();
    cout << right << setw(63) << "Digite la cedula del jugador : ";
    cin >> cedula;

    //Validar solo enteros a la cedula
    while(cedula == false){
      noletras();
      titulo();
      cout << right << setw(63) << "Digite la cedula del jugador : ";
        cin >> cedula;

    }


        //validacion de no repetir

        while(!consulta.eof()){ //mientras no sea el final del archivo

                consulta >> ced[i];
                consulta >> nomb;

                if(ced[i] == cedula){
                        Sleep(1000);
                        cout << right << setw(90) << "(ERROR): Esta cedula ya se encuentra registrada o es invalida" << endl;

                        archivo.close();
                        consulta.close();
                        limpiar_pantalla();
                        main();

                    }


            }

    //Si no hay fallos la cedula se registra
    archivo << "\t\t" << cedula;

    cout << right << setw(62) << "Digite el nombre del jugador: ";

    limpiar_cin();

    getline(cin,nombre);

    archivo << "\t\t\t  " << nombre;

    archivo << endl;

    limpiar_cin();

    Sleep(1000);
        cout << right << setw(60) << "Guardado exitosamente..." << endl;

    consulta.close();
    archivo.close();

}

void lectura(fstream &archivo){

    string texto;

    archivo.open("datos.dat",ios::in); //abrir el archivo en modo lectura

        if(archivo.fail()){

         cout << right << setw(70) << "No hay jugadores que mostrar, intente registrar jugadores" << endl;
         limpiar_pantalla();

         main();
        }

            while(!archivo.eof()){ //mientras no sea el final del archivo se leera

               getline(archivo,texto);

                cout << texto << endl;
            }

                archivo.close();

}

//Funcion para limpiar el cin
void limpiar_cin(){

    cin.clear();

    fflush(stdin);

}

void buscar_cedula(fstream &archivo, int &cedula1, string &nombre){

    fstream crear;

    //Se abre dos archivos para añadir y consultar el datos.dat
    crear.open("datos.dat", ios::app); //Modo añadir texto
    archivo.open("datos.dat", ios::in); //Modo lectura

    int ced_aux,cedula;

    bool encontrar = false;

    cout << right << setw(42) << "Digite su cedula: ";
    cin >> ced_aux;

    while(ced_aux == false){
        noletras();
        cout << right << setw(42) << "Digite su cedula: ";
        cin >> ced_aux;

    }


    archivo >> cedula;

    //Si no encuentra la cedula
    if(crear.fail() && !encontrar || archivo.fail()){
     Sleep(1000);
     cout << right << setw(63) <<"(ERROR): No se encuentra en el registro." << endl;
     limpiar_pantalla();
     main();

    }

    while(!crear.eof() && !archivo.eof() && !encontrar){

      archivo >> nombre;

      //Si encuentra la cedula en el registro
      if(cedula == ced_aux){
      Sleep(1000);
      cout << right << setw(63) << "Busqueda exitosa..." << endl;
      Sleep(1000);
      cout << right << setw(63) << "Te has registrado como " << nombre << endl;
      cout << right << setw(66) << "Numero de identificacion: " << cedula << endl;

        cedula1 = cedula;

        encontrar = true;
      }

        archivo >> cedula;
    }

    crear.close();
    archivo.close();

    limpiar_pantalla();

}

void limpiar_pantalla(){

 system("pause");
 system("cls");

}

void guardar_puntaje(fstream &partidas,int &cedula_j1,string &nombre_j1,int &puntos_j1,int &cedula_j2,string &nombre_j2,int &puntos_j2){

    //Archivo para guardar puntos de los dos jugadores por partida, se reemplaza cada partida jugada
    partidas.open("partida_reciente.dat",ios::out); //abrir en modo crear y reemplazar archivo

    if(partidas.fail()){

     cout << "No se pudo abrir el archivo" << endl;

     exit(1);
    }

    partidas << cedula_j1;

    partidas << "\t";

    partidas << nombre_j1;

    partidas << "\t";

    partidas << puntos_j1;

    partidas << endl;

    //datos jugador 2

    partidas << cedula_j2;

    partidas << "\t";

    partidas << nombre_j2;

    partidas << "\t";

    partidas << puntos_j2;

    partidas << endl;

    partidas.close();

}

void copiar_puntaje(fstream &partidas,fstream &puntostotal){

const string original = "partida_reciente.dat";
const string copia = "juego.dat";
char cadena[80];
int linea1 = 1,linea2 = 2;

    //Se abre los dos archivos para copiar la informacion a juego.dat
    partidas.open(original.c_str());
    puntostotal.open(copia.c_str(),ios::app);

    int i = 1;

    if(!partidas.fail()){

        partidas.getline(cadena,80,'\n');

        while(!partidas.eof()){

          if(i==linea1){

            puntostotal << cadena << endl;

          }
          if(i==linea2){

            puntostotal << cadena << endl;

          }

           i++;
           partidas.getline(cadena,80,'\n');
        }

        partidas.close();
        puntostotal.close();

    }

}

void pasar_datostop(fstream &puntostotal,int cedulas[],int puntos[],char nombres[][30]){

 string texto,nombre,cedula,punto;
 int i,j;


        puntostotal.open("juego.dat",ios::in); //abrir el archivo en modo lectura
        if(puntostotal.fail()){

         cout << right << setw(60) << "Error al leer el archivo" << endl;
         limpiar_pantalla();

         main();
        }
            //Se pasa a variables los textos encontrados en juego.dat para lograr usarlas

                for(i = 0; i < 10; i++){

                puntostotal >> cedulas[i];

                puntostotal >> nombres[i];

                puntostotal >> puntos[i];

                }

                puntostotal.close();


}

void ordenar_top(int cedulas[],int puntos[],int auxpuntos[],char nombres[][30]){

fstream top;
string texto;
int i = 0,j = 0;
int aux = 0;


            top.open("top.dat",ios::out); //abrir el archivo en modo lectura
                if(top.fail()){

                    cout << "Error al leer el archivo" << endl;
                    limpiar_pantalla();

                        main();
                    }

        for(i = 0; i < 10; i++){

           auxpuntos[i] = puntos[i];

        }


        //Metodo burbuja para ordenar los puntos de mayor a menor
        for(i = 1; i < 10; i++){
            for(j = 0; j < 10-i; j++){

            if(auxpuntos[j] < auxpuntos[j+1]){

               aux = auxpuntos[j];
               auxpuntos[j] = auxpuntos[j+1];
               auxpuntos[j+1] = aux;

                }


            }

        }

        //Se pasan a texto las variables luego de ordenar los puntos de mayor a menor
            for(i=0;i<10;i++){
                    for(j=0;j<10;j++){

                        if(puntos[j] == auxpuntos[i]){

                            top << "\t\t\t\t" << nombres[j];

                            top << "\t\t   ";

                            top << cedulas[j];

                            top << "\t\t   ";

                            top << puntos[j];

                            top << endl;

                            if(nombres[j] == nombres[j]){

                                i++;

                            }
                }
            }
        }

            top.close();


    }

void leer_top(int cedulas[],int puntos[],char nombres[][30]){
fstream top;
string texto;

    top.open("top.dat",ios::in); //abrir el archivo en modo lectura

        if(top.fail()){

         cout << "Error al leer el archivo" << endl;

         main();
        }


                while(!top.eof()){ //mientras no sea el final del archivo

               getline(top,texto);

                cout << texto << endl;
            }


        top.close();

}

void noletras(){

if(cin.fail()){

    cout << right << setw(50) << "(Error): no debe digitar letras" << endl;
    cin.clear();
    cin.ignore();

 }

}

void titulo(){
cout << right << setw(100) << "-------------------------------------------------------------------------------------" << endl;
 cout << right << setw(100) << "-------------------------------------------------------------------------------------" << endl;
 cout << right << setw(101) << "--------------------------Cuadrados de Multiplicación--------------------------------" << endl;
 cout << right << setw(100) << "-------------------------------------------------------------------------------------" << endl;
 cout << right << setw(100) << "-------------------------------------------------------------------------------------" << endl;
}

