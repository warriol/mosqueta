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

using namespace std;

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

void mostrarNumeros(int fin){
    int i;
    for (i = 1; i <= fin; i++)
        printf("%d ", i);
}

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
    printf("\n");
    for (i = 0; i < fin; i++)
        printf("%d ", copas[i]);
    printf("\n");
    mostrarNumeros(fin);
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
    if(res < ini || res > fin || cont > 1)
        // si no esta en rango llamo de nuevo a la funcion para repetir el proceso
        pedirNumeroEnRango(ini, fin);
    else
        // devuelvo el resultado
        return res;
}

int pedirOpcion(int copas){
    char opcion[6];
    int cont = 0;
    do{
        opcion[cont] = getchar();
        cont++;
    }while(opcion[cont-1] != '\n');
    switch(cont){
        case 2:     // digito
            cont = opcion[0] - 48;
            if(cont > 0 && cont <= copas)
                return cont;
        break;
        case 5:     // mano
            /**
             *  CONSULTAR AL PROFESOR
             *  Al utilizar strcpm() no distingue de mayusculas o minusculas
             *  entonces escribir Mano, mano O mANO es lo mismo
             *  esto hay que tomarlo como error o estarìa bien
             */
            if(strcmp(opcion,MANO))
                return 11;
        break;
        case 6:     // salir
            if(strcmp(opcion,SALIR))
                return 10;
        break;
        default:    // error seguro
            pedirOpcion(copas);
        break;
    }
}

int main(){
    // semilla aleatoria en base a la hora y fecha actual
    srand (time(NULL));
    // variables enteras
    int dineroDisponible, opcion, posicionBolita, resultado,cantidadCopas, ponderacionDeGanancia, montoInicial;
    // variables inicializadas
    int apuesta         = 0;    // se inicia en 0 para contemplar la opcion 4, si se diera la primera vez q apuesta
    int partidasAlHilo  = 0;    // cantidad de veces q gana consecutivamente
    int copas[9] = {0};         // arreglo para las copas
    // variables booleanas
    bool salir = true;          // controla el fin del juego

    mostrarMensaje(001);        // mensaje de bienvenida y reglas

    do{
        dineroDisponible = pedirNumeroEnRango(50, 1000);                     // se pide el dinero que dispone
        montoInicial = dineroDisponible;
        /**
        * este bloque if ya no serìa necesario por el control de la funcion de pedirNumeroEnRango
        * consultar al profesor, de ser asi se debe quitar
        */
        if  (dineroDisponible > MONTOMAXIMO || dineroDisponible < APUESTAMINIMA){
            printf("%s\n", MENSAJESALIDA);
        }else{
            mostrarMensaje(002);                                            // MSJ: Elegir la cantidad de compas con las que jugar
            cantidadCopas = pedirNumeroEnRango(3, 9);                       // cantidad de copas para jugar
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
                    salir = false;                                              // SALE POR NO TENER DINERO
                }else{                                                      // inicio de jugada
                    mostrarCopas(cantidadCopas, copas);                     // muestro el tablero
                    opcion = pedirOpcion(cantidadCopas);                    // espero por jugada correcta
                    switch(opcion){
                        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:  // jugar
                            printf("Apuesta?:\n");
                            apuesta = pedirNumeroEnRango(APUESTAMINIMA, dineroDisponible);      // espero monto correcto
                            /**
                            * debido al control anterio sobre la apuesta, esta serà siempre correcta
                            * consulta la profesor: el mensaje de error por no tener dinero suficiente
                            * no seria necesario
                            * en ese caso quitar control de apuesta
                            * dejar control de dinero, por si apuesta mas de lo que tiene
                            * consultar al profesor si parte del control es no dejar que el usuario apueste mas de lo que tiene
                            */
                            if(apuesta < APUESTAMINIMA || apuesta > dineroDisponible){          // apuesta invalidad por monto
                                printf("%s", MENSAJESINDINERO);
                                salir = false;                                  // salir
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
                                salir = true;                                  // no puede salir
                            }else{
                                printf("%s\n", MENSAJESALIDA);
                                salir = false;
                            }
                        break;
                        /**
                        * continuar con la lògica del pedido de mano
                        * crear variable para guardar el monto perdido
                        * ?consultar
                        * se debe tener encuenta la ganancia general contando si gana o pierde ir sumando o restando
                        * o solo se toma encuenta el dinero perdido es decir pierda 100, gana 50; se dvuelve 50*2 o 100*2
                        * 19/05/2018
                        * wilson
                        */
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
                            salir = false;
                        break;
                    }
                }
            }while(salir);                                              // FIN DEL JUEGO
        }
    }while(salir);
    return 0;
}

