#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define APUESTAMINIMA 50
#define GANADASCONSECUTIVAS 2
#define MANO "Mano"
#define MENSAJESALIDA "Nos vemos la próxima.\n"
#define MENSAJESINDINERO "Para jugar hay que pagar amigo.\n"
#define MENSAJEORGULLO "Has perdido mucho, donde está ese orgullo? Inténtalo de nuevo!.\n"
#define MENSAJEORGULLO1 "Si vuelvo a casa sin plata me matan.\n"
#define MENSAJEORGULLO2 "Esto no puede quedar así.\n"
#define MENSAJEORGULLO3 "Si perdí la anterior, de seguro ahora gano.\n"
#define MENSAJEBOLAENMANO "Tu si que eres perceptivo, te animas a no contarle esto a nadie?\n"
#define MENSAJEBOLAENCOPA "Quien te crees que soy? Vete de aquí.\n"
#define MONTOMAXIMO 1000
#define MONTOPORORGULLO 200
#define SALIR "Salir"
#define MAXIMOENTRADA 20

using namespace std;

/**
 * funcion aleatoria para mostrar los 3 mensajes pro orgullo
 */
void mostrarMensajePorOrgullo(){
    switch (rand() % 3){
        case 0:
            printf("%s", MENSAJEORGULLO1);
        break;
        case 1:
            printf("%s", MENSAJEORGULLO2);
        break;
        case 2:
            printf("%s", MENSAJEORGULLO3);
        break;
    }
}

/**
 * imprime los numeros debajo de las copas
 */
void mostrarNumeros(int fin){
    int i;
    for (i = 1; i <= fin; i++)
        printf("%d ", i);
}

/**
 * imprime la posición de la bolita
 * muestra los numeros bajo las copas
 */
void mostrarPosicionBolita(int fin, int posB){
    int i;
    for (i = 1; i <= fin; i++){
        if (i != posB)
            printf("0 ");
        else
            printf(". ");
    }
    printf("\n");
    mostrarNumeros(fin);
    printf("\n");
}

/**
 * imprime mensajes
 */
void mostrarMensaje(int msj){
    // funcion que impre mensajes en pantalla dependiendo del codigo que reciba
    switch(msj){
        case 001:   // bienvenida
            printf("Bienvenido/a, a continuación comenzaremos a jugar.\n");
            printf("Para cada jugada debes indicar en qué copa se encuentra la bola.\n");
            printf("Recuerda que también puedes optar por retirarte marcando \"Salir\".\n");
            printf("Ahora dime, ¿cuánto dinero tienes disponible?\n\n");
        break;
        case 002:   // pregunta cuantas copas
            printf("\nElige cuantas copas (de 3 a 9). Más copas, más ganas.\nCuántas serán?\n\n");
        break;
    }
}

/**
 * imprime las copas
 * imprime numero bajo las copas
 */
void mostrarCopas(int fin, char copas[]){
    printf("\n%2s\n", copas);
    mostrarNumeros(fin);
    printf("\nCopa?:\n");
}

/**
 * funcion que pide al usuario un numero entre un X e Y dado
 * de nocorresponder el valor ingresado por el usuario se vuelve a llamar hasta q sea correcto
 */
int pedirNumeroEnRango(int ini, int fin){
    // funcion que pide al usuario un numero entre ini y fin
    int res, cont = 0, retorno;
    char limpiarEntrada;
    // pido un entero
    scanf("%d", &res);
    // limpio la basura
    do{
        limpiarEntrada = getchar();
        cont++;
    }while(limpiarEntrada != '\n');
    // verifico que el numero este en el rango
    if(res < ini || res > fin || cont > 1)
        // si no esta en rango llamo de nuevo a la funcion para repetir el proceso
        pedirNumeroEnRango(ini, fin);
    else
        // devuelvo el resultado
        retorno = res;
    return retorno;
}

/**
 * MENU - interacción con el usuario
 *
 *
 *
 *
 *      HAY ERRORES
 *
 *
 *
 */
int pedirOpcion(int cantidadCopas){
    char opcion[MAXIMOENTRADA];
    int cont = 0, retorno;
    do{
        if(cont < 7)
            opcion[cont] = getchar();
        cont++;
    }while(opcion[cont-1] != '\n');
    opcion[cont-1] = '\0';
    switch(cont){
        case 2:     // digito
            cont = opcion[0] - 48;
            if(cont > 0 && cont <= cantidadCopas)
                retorno = cont;
            else
                pedirOpcion(cantidadCopas);
        break;
        case 5:     // mano
            if(strcmp(opcion,MANO)==0)
                retorno = 11;
            else
                pedirOpcion(cantidadCopas);
        break;
        case 6:     // salir
            // printf("\n%s - %s\n", opcion, SALIR);
            if(strcmp(opcion,SALIR)==0)
                retorno = 10;
            else
                pedirOpcion(cantidadCopas);
        break;
        default:    // error seguro
            pedirOpcion(cantidadCopas);
        break;
    }
    return retorno;
}

/**
 * funcion principal
 */
int main(){
    // semilla aleatoria en base a la hora y fecha actual
    srand (time(NULL));
    // variables enteras
    int dineroDisponible, opcion, posicionBolita, resultado,cantidadCopas, ponderacionDeGanancia, montoInicial, i;
    // variables inicializadas
    int apuesta         = 0;    // se inicia en 0 para contemplar la opcion 4, si se diera la primera vez q apuesta
    int partidasAlHilo  = 0;    // cantidad de veces q gana consecutivamente
    char copas[18];              // arreglo para las copas
    // variables booleanas
    bool noSalir = true, noTerminarJuego = true;          // controla el fin del juego

    mostrarMensaje(001);        // mensaje de bienvenida y reglas

    do{
        dineroDisponible = pedirNumeroEnRango(0, 1000);                     // se pide el dinero que dispone
        montoInicial = dineroDisponible;                                    // montoInicial se usa al final, para saber cuanto dinero perdio en caso de tener q devolver si tenia bola en mano
        if  (dineroDisponible < APUESTAMINIMA){                             // dineroDisponible > MONTOMAXIMO se quita validacion porque esto ya se controla en la funcion pedirNumeroEnRango
            printf("%s\n", MENSAJESALIDA);
            noTerminarJuego = false;
        }else{
            mostrarMensaje(002);                                            // MSJ: Elegir la cantidad de compas con las que jugar
            cantidadCopas = pedirNumeroEnRango(3, 9);                       // cantidad de copas para jugar
            for (i=0; i<cantidadCopas*2; i++){                              // lleno arreglo con 'O'
                if(i%2==0)                                                  // si es par va 'O'
                    copas[i] = 'O';                                         // delimitar el arreglo hasta cantidad de copas
                else
                    copas[i] = ' ';                                         // si es impar va espacio.
            }
            copas[i+1] = '\0';                                              // lo paso a string
            switch(cantidadCopas){                                          // ponderacion de ganancia segun cantidad de copas
                case 3: case 4: case 5:
                    ponderacionDeGanancia = 2;
                break;
                case 6: case 7: case 8:
                    ponderacionDeGanancia = 3;
                break;
                case 9:
                    ponderacionDeGanancia = 4;
                break;
            }

            do{                                                             // COMIENZA EL JUEGO
                if(dineroDisponible < 50){                                  // FIN DEL JUEGO POR REGLA
                    printf("%s", MENSAJESINDINERO);
                    noSalir = false;                                        // SALE POR NO TENER DINERO
                    noTerminarJuego = false;                                   // TERMINAR EL JUEGO
                }else{                                                      // inicio de jugada
                    mostrarCopas(cantidadCopas, copas);                     // muestro el tablero
                    opcion = pedirOpcion(cantidadCopas);                    // espero por jugada correcta
                    switch(opcion){
                        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:  // jugar
                            printf("Apuesta?:\n");
                            apuesta = pedirNumeroEnRango(APUESTAMINIMA, dineroDisponible);      // espero monto correcto
                            if(apuesta > dineroDisponible){          // apuesta invalidad por mont {apuesta < APUESTAMINIMA}
                                printf("%s", MENSAJESINDINERO);
                                noSalir = false;                                  // salir
                                noTerminarJuego = false;                                   // TERMINAR EL JUEGO
                            }else{                                          // apuesta correcta
                                if (partidasAlHilo == GANADASCONSECUTIVAS){ // hay q estafar - PIERDE
                                    do{
                                        posicionBolita = (rand() % cantidadCopas) + 1;
                                    }while( posicionBolita == opcion );     // posicion de bolita aleatoria y diferente a la opcion
                                    resultado = 0;
                                    dineroDisponible -= apuesta;
                                    partidasAlHilo = 0;
                                }else{                                      // NO hay q estafar
                                    posicionBolita = (rand() % cantidadCopas) + 1;
                                    if ( posicionBolita == opcion ){        // gano
                                        resultado = 1;
                                        dineroDisponible += apuesta * ponderacionDeGanancia;
                                        partidasAlHilo++;
                                    }else{                                  // perdio
                                        resultado = 0;
                                        dineroDisponible -= apuesta;
                                        partidasAlHilo = 0;
                                    }
                                }
                                mostrarPosicionBolita(cantidadCopas, posicionBolita);           // muesro la ubicacion de la bolita
                                if (resultado == 0) printf("No ha acertado"); else printf("Ha Acertado");
                                printf("\nSaldo: %d\n", dineroDisponible);  // muestro saldo
                            }
                        break;
                        case 10:                                             // el usuario quiere Salir
                            if(MONTOPORORGULLO < apuesta && resultado == 0) {// si elige salir y (apostò mas 200 y NO perdió)
                                mostrarMensajePorOrgullo();
                                noSalir = true;                              // no puede salir
                            }else{
                                printf("%s\n", MENSAJESALIDA);
                                noSalir = false;
                                noTerminarJuego = false;                        // TERMINAR EL JUEGO
                            }
                        break;
                        case 11:                                            // mano
                            if (partidasAlHilo == GANADASCONSECUTIVAS){     // tengo la bola en la mano
                                montoInicial -= dineroDisponible;           // mono incial menos monto actual = ganancia o perdida
                                if(montoInicial > 0)                        // si hay perdidas
                                    dineroDisponible += montoInicial * 2;   // devuelvo el doble e imprimo
                                printf("\n%d\n", dineroDisponible);
                                printf("%s", MENSAJEBOLAENMANO);
                            }else{                                          // la bola esta en una copa
                                posicionBolita = (rand() % cantidadCopas) + 1; // muestro posicion de bola
                                printf("%s", MENSAJEBOLAENCOPA);            // imprimo mensjae
                            }
                            noSalir = false;
                            noTerminarJuego = false;                           // TERMINAR EL JUEGO
                        break;
                    }
                }
            }while(noSalir);                                                // FIN DEL JUEGO
        }
    }while(noTerminarJuego);

    return 0;
}
