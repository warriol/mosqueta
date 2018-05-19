#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MENSAJESALIDA "Nos vemos la próxima.\n"
#define MENSAJESINDINERO "Para jugar hay que pagar amigo.\n"
#define MENSAJEORGULLO "Has perdido mucho, donde está ese orgullo? Inténtalo de nuevo!.\n"
#define APUESTAMINIMA 50
#define MONTOMAXIMO 1000
#define GANADASCONSECUTIVAS 2
#define MONTOPORORGULLO 200

using namespace std;

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

void mostrarCopas(int fin, int copas[]){
    int i;
    for (i = 0; i < fin; i++){
        printf("%d ", copas[i]);
    }
    printf("\n");
    for (i = 1; i <= fin; i++){
        printf("%d ", i);
    }
    printf("\nCopa?:\n");

}

int pedirNumeroEnRango(int ini, int fin){
    // funcion que pide al usuario un numero entre ini y fin
    int res, cont = 0;
    char entrada;
    // pido un entero
    scanf("%d", &res);
    // limpio la basura
    do{
        entrada = getchar();
        cont++;
    }while(entrada != '\n');
    // verifico que el numero este en el rango
    if(res < ini || res > fin || cont > 1){
        // si no esta en rango llamo de nuevo a la funcion para repetir el proceso
        pedirNumeroEnRango(ini, fin);
    }else{
        // devuelvo el resultado
        return res;
    }
}

int pedirOpcion(int copas){
    char opcion[6];
    int cont = 0;
    do{
        opcion[cont] = getchar();
        cont++;
    }while(opcion[cont-1] != '\n');
    /*
    * seguir em la parte de control de la opcion elegida
    * estoy en caso 2
    * si es un digito en cero y la cantidad de copas
    * 0 es caracter 48
    * 19/05/2018
    * wilson
    */
    switch(cont){
        case 2:     // digito
            cont = opcion[0];
            if(cont > 48 || cont < copas + 48){
                printf("correcto----%d----%c-----", cont, cont);
            }else{
                printf("Error----%d----%c-----", cont, cont);
            }

        break;
        case 5:     // mano
        break;
        case 6:     // salir
        default:    // error seguro
            pedirOpcion(copas);
        break;
    }
}

int main(){
    // semilla aleatoria en base a la hora y fecha actual
    srand (time(NULL));
    // variables enteras
    int dineroDisponible, opcion, posicionBolita, resultado,cantidadCopas;
    int apuesta         = 0;    // se inicia en 0 para contemplar la opcion 4, si se diera la primera vez q apuesta
    int salir           = 1;    // 1: gano / no puede salir --- 0: salir / perido
    int partidasAlHilo  = 0;    // cantidad de veces q gana consecutivamente
    int copas[9] = {0};         // arreglo para las copas

    mostrarMensaje(001);        // mensaje de bienvenida y reglas

    do{
        dineroDisponible = pedirNumeroEnRango(50, 1000);                     // se pide el dinero que dispone

        /*
        * este bloque if ya no serìa necesario por el control de la funcion de pedirNumeroEnRango
        * consultar al profesor, de ser asi se debe quitar
        */
        if  (dineroDisponible > MONTOMAXIMO || dineroDisponible < APUESTAMINIMA){
            printf("%s\n", MENSAJESALIDA);
        }else{
            mostrarMensaje(002);                                            // MSJ: Elegir la cantidad de compas con las que jugar
            cantidadCopas = pedirNumeroEnRango(3, 9);                       // cantidad de copas para jugar
            printf("\n");

            do{                                                             // COMIENZA EL JUEGO
                if(dineroDisponible < 50){                                  // FIN DEL JUEGO POR REGLA
                    printf("%s", MENSAJESINDINERO);
                    salir = 0;                                              // SALE POR NO TENER DINERO
                }else{                                                      // inicio de jugada
                    mostrarCopas(cantidadCopas, copas);                     // muestro el tablero
                    opcion = pedirOpcion(cantidadCopas);                    // espero por jugada correcta
                    switch(opcion){
                        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:  // jugar
                            printf("Apuesta?:\n");
                            apuesta = pedirNumeroEnRango(APUESTAMINIMA, dineroDisponible);      // espero monto correcto
                            /*
                            * debido al control anterio sobre la apuesta, esta serà siempre correcta
                            * consulta la profesor: el mensaje de error por no tener dinero suficiente
                            * no seria necesario
                            * en ese caso quitar control de apuesta
                            * dejar control de dinero, por si apuesta mas de lo que tiene
                            * consultar al profesor si parte del control es no dejar que el usuario apueste mas de lo que tiene
                            */
                            if(apuesta < APUESTAMINIMA || apuesta > dineroDisponible){          // apuesta invalidad por monto
                                printf("%s", MENSAJESINDINERO);
                                salir = 0;                                  // salir
                            }else{                                          // apuesta correcta
                                if (partidasAlHilo == GANADASCONSECUTIVAS){ // hay q estafar - PIERDE
                                    do{
                                        posicionBolita = (rand() % cantidadCopas) + 1;
                                    }while( posicionBolita == opcion );     // posicion de bolita aleatoria y diferente a la opcion
                                    resultado = 0;
                                    dineroDisponible -= apuesta;
                                    partidasAlHilo = 0;
                                }else{                                      // NO hay q estafar
                                    posicionBolita = (rand() % 3) + 1;
                                    if ( posicionBolita == opcion ){        // gano
                                        resultado = 1;
                                        dineroDisponible += apuesta;
                                        partidasAlHilo++;
                                    }else{                                  // perdio
                                        resultado = 0;
                                        dineroDisponible -= apuesta;
                                        partidasAlHilo = 0;
                                    }
                                }
                                if (posicionBolita == 1){                   // muesro la ubicacion de la bolita
                                    printf(". 0 0\n");
                                }else if(posicionBolita == 2){
                                    printf("0 . 0\n");
                                }else{
                                    printf("0 0 .\n");
                                }
                                if (resultado == 0) printf("No ha acertado"); else printf("Ha Acertado");
                                printf("\nSaldo: %d\n", dineroDisponible);  // muestro saldo
                            }
                        break;
                        case 10:                                             // el usuario quiere Salir
                            if(MONTOPORORGULLO < apuesta && resultado == 0) {// si elige salir y (apostò mas 200 y NO perdió)
                                printf("%s", MENSAJEORGULLO);
                                salir = 1;                                  // no puede salir
                            }else{
                                printf("%s\n", MENSAJESALIDA);
                                salir = 0;
                            }
                        break;
                        case 11:                                            // mano
                        break;
                        default:
                        break;
                    }
                }
            }while(salir != 0);                                             // FIN DEL JUEGO
        }
    }while(salir != 0);
    return 0;
}
