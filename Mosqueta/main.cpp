#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define APUESTAMINIMA       50
#define GANADASCONSECUTIVAS 2
#define MAXIMOENTRADA       20
#define MONTOMAXIMO         1000
#define MONTOPORORGULLO     200
#define MANO                "Mano"
#define MENSAJEBOLAENMANO   "Tu si que eres perceptivo, te animas a no contarle esto a nadie?\n"
#define MENSAJEBOLAENCOPA   "Quien te crees que soy? Vete de aqui.\n"
#define MENSAJEORGULLO      "Has perdido mucho, donde esta ese orgullo? Intentalo de nuevo!.\n"
#define MENSAJEORGULLO1     "Si vuelvo a casa sin plata me matan.\n"
#define MENSAJEORGULLO2     "Esto no puede quedar asi.\n"
#define MENSAJEORGULLO3     "Si perdi la anterior, de seguro ahora gano.\n"
#define MENSAJESALIDA       "Nos vemos la proxima.\n"
#define MENSAJESINDINERO    "Para jugar hay que pagar amigo.\n"
#define SALIR               "Salir"

using namespace std;

/** \brief Wilson - 27/05/2018 - 13:45
 * \fn Funcion que de acuerdo a un numero aleatorio imprime en pantalla uno de tres mensajes ya definidos..
 * \param int fin
 * \param int posB
 */
void mostrarMensajePorOrgullo(){
    switch (rand() % 3){        // numero aleatorio entre 0 y 2
        case 0:                 // caso 0: mensaje 1
            printf("%s", MENSAJEORGULLO1);
        break;
        case 1:                 // caso 1: mensaje 2
            printf("%s", MENSAJEORGULLO2);
        break;
        case 2:                 // caso 2: mensaje 3
            printf("%s", MENSAJEORGULLO3);
        break;
    }
}

/** \brief Wilson - 27/05/2018 - 13:45
 * \fn Funcion que imprime en pantalla los numeros bajo las copas de uno hasta el fin.
 * \param int fin
 */
void mostrarNumeros(int fin){
    int i;
    // fin: indica la cantidad de copas que elegio el usuario para jugar
    for (i = 1; i <= fin; i++)
        printf("%d ", i);
}

/** \brief Santiago - 29/05/2018
 * \fn Funcion que imprime en pantalla un arreglo con cero y pone un punto donde deberia estar la bolitra.
 * \param int fin
 * \param int posB
 */
void mostrarPosicionBolita(int fin, int posB){
    int i;
    for (i = 1; i <= fin; i++){     // itera desde 1 y mientras sea menor a la cantiad de copas
        if (i != posB)              // si el iterador NO tiene el mismo numero que la posicion de la bolita
            printf("0 ");           // imprimo un 0
        else                        // s el iterador tiene la misma posicion donde esta la
            printf(". ");           // imprimo un .
    }
    printf("\n");
    mostrarNumeros(fin);            // llamo a la funcion mostrarNumeros
    printf("\n");
}

/** \brief Wilson - 27/05/2018 - 13:45
 * \fn Funcion que imprime mensajes en pantalla dependiendo del codigo que reciba.
 * \param int msjId
 */
void mostrarMensaje(int msjId){
    switch(msjId){
        case 001:   // bienvenida
            printf("Bienvenido/a, a continuacion comenzaremos a jugar.\n");
            printf("Para cada jugada debes indicar en que copa se encuentra la bola.\n");
            printf("Recuerda que tambien puedes optar por retirarte marcando \"Salir\".\n");
            printf("Ahora dime, ¿cuanto dinero tienes disponible?\n\n");
        break;
        case 002:   // pregunta cuantas copas
            printf("\nElige cuantas copas (de 3 a 9). Mas copas, mas ganas.\nCuantas seran?\n\n");
        break;
    }
}

/** \brief Wilson - 27/05/2018 - 13:45
 *  \fn Muestra en pantalla las copas, los numeros de cada copa y pregunta: "Copa?"
 *  \param fin: indica hasta donde debo recorrer el arreglo
 *  \param arregloCopas: es el arreglo que contiene los ceros
 */
void mostrarCopas(int fin, int arregloCopas[]){
    int i;
    printf("\n");
    for (i = 0; i < fin; i++)               //niterador desde cero y mientras sea menor a la cantidad de copas
        printf("%d ", arregloCopas[i]);     // imprimo el arreglo con ceros con espacio de por medio
    printf("\n");
    mostrarNumeros(fin);
    printf("\nCopa?:\n");
}

/** \brief Wilson - 27/05/2018 - 13:45
 * \fn Recibe dos enteros, luego pide al usuario un entero, si el entero ingresado por el usuario
 *  esta dentro de los valores indicados lo retorna.
 * \param ini: entero inicial del rango posible
 * \param fin: entero final del rango posible
 * \return retorna el entero ingresado por el usuario entre ini y fin
 *
 */
int pedirNumeroEnRango(int ini, int fin){
    int cont, retorno, i;
    char entrada[20];
    bool noSalir;
    do{
        cont = 0;
        noSalir = false;                                // se entiende que el usuario ingresa bien de primera, se inicializa para salir
        do{                                             // leo de la entrada
            entrada[cont] = getchar();
            cont++;
        }while(entrada[cont-1] != '\n');
        entrada[cont-1] = '\0';                         // lo paso a string
        retorno = atoi (entrada);                       // lo paso a entero
        for(i=0; i<cont-1; i++){
            if( entrada[i] < '0' || entrada[i] > '9' )  // verifico que sea un numero
                noSalir = true;                         // si no, no lo dejo salir
        }

        if( retorno < ini || retorno > fin )            // verifico que el numero este en el rango
            noSalir = true;                             // si no esta en rango, no lo dejo salir
    }while(noSalir);
    return retorno;
}

/** \brief Santiago - 29/05/2018
 * \fn Controla las entradas del usuario en la seccion opciones. (Salir, Mano, 1 - 9)
 *  Verifica que si ingresa un numero de copa, este dentro del rango de copas
 * \param cantidadCopas: contiene el numero de copas con las q se esta jugando
 * \param apuesta: monto apostado
 * \param apostadorAcerto: indica si el apostador gano o perdio
 * \return Se retorna un entero entre 1 y 11, Corresponden de 1 a 9 para las copas, 10 para Salir, 11 para Mano
 */
int pedirOpcion(int cantidadCopas, int apuesta, bool apostadorAcerto){
    char opcion[MAXIMOENTRADA];
    int cont, retorno;
    bool noSalir;
    do{
        cont = 0;
        noSalir = false;
        do{
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
                    noSalir = true;
            break;
            case 5:     // mano
                if(strcmp(opcion,MANO)==0)
                    retorno = 11;
                else
                    noSalir = true;
            break;
            case 6:     // salir
                if(strcmp(opcion,SALIR)==0)
                    if( (MONTOPORORGULLO < apuesta) && (!apostadorAcerto) ) {   // si elige salir y (aposto mas 200 y perdio)
                        mostrarMensajePorOrgullo();                 // muestro mensajes aleatorios
                        noSalir = true;                             // no puede salir
                    }else{                                          // casos en que puede salir
                        retorno = 10;                               // SALIR
                    }
                else
                    noSalir = true;
            break;
            default:    // error seguro
                noSalir = true;
            break;
        }
    }while(noSalir);
    return retorno;
}

/** \brief Wilson - 27/05/2018 - 13:45
 * \fn De acuerdo a la cantidad de copas con las que se juegue, la ganancia sera diferente.
 *  A mayor cantidad de copa mayor ganancia.
 * \param  cantidadCopas: Recibe la cantidad de copas con las que se juega.
 * \return Retorno un entero equivalente al valor por el que se multiplicara la ganncia
 */
int pedirPonderacionApuesta(int cantidadCopas){
    int retorno;
    switch(cantidadCopas){          // de acuerdo a la cantidad de copas se establece el moltiplicador de ganancia
        case 3: case 4: case 5:
            retorno = 2;            // se multiplica por 2
        break;
        case 6: case 7: case 8:
            retorno = 3;            // se multiplica por 3
        break;
        case 9:
            retorno = 4;            // se multiplica por 4
        break;
    }
    return retorno;
}

int main(){
    srand (1);                  // senilla NO aleatoria
    //srand(time(NULL));          // semilla aleatoria en base a la hora y fecha actual
    //---------------------------- variables enteras
    int dineroDisponible, opcion, posicionBolita, cantidadCopas, ponderacionDeGanancia, montoInicial;
    //---------------------------- variables inicializadas
    int apuesta         = 0;    // se inicia en 0 para contemplar la opcion 4, si se diera la primera vez q apuesta
    int partidasAlHilo  = 0;    // cantidad de veces q gana consecutivamente
    int arregloCopas[9] = {0};  // arreglo para las copas
    //---------------------------- variables booleanas
    bool noSalir = true;        // controla el fin del juego
    bool apostadorAcerto = true;// verdadero gana; falso pierde
    mostrarMensaje(001);        // mensaje de bienvenida y reglas
    do{
        dineroDisponible = pedirNumeroEnRango(0, MONTOMAXIMO);              // se pide el dinero que dispone
        montoInicial = dineroDisponible;                                    // guardo el monto inicial para carlculas cuanto perdio
        if (dineroDisponible < APUESTAMINIMA){                              // monto disponible INCORRECTO
            printf("%s\n", MENSAJESALIDA);                                  // MSJ: para jugar hay q pagar
            noSalir = false;                                                // SALE POR NO TENER DINERO
        }else{                                                              // monto disponible CORRECTO
            mostrarMensaje(002);                                            // MSJ: Elegir la cantidad de copas con las que jugar
            cantidadCopas = pedirNumeroEnRango(3, 9);                       // cantidad de copas para jugar
            ponderacionDeGanancia = pedirPonderacionApuesta(cantidadCopas); // ponderacion de ganancia segun cantidad de copas
            do{                                                             // COMIENZA EL JUEGO
                if(dineroDisponible < 50){                                  // FIN DEL JUEGO POR REGLA
                    printf("%s", MENSAJESINDINERO);                         // MJS: para jugar hay q pagar
                    noSalir = false;                                        // SALE POR NO TENER DINERO
                }else{                                                      // inicio de jugada
                    mostrarCopas(cantidadCopas, arregloCopas);              // muestro el tablero
                    opcion = pedirOpcion(cantidadCopas, apuesta, apostadorAcerto);  // espero por opcion correcta (1-9; Salir; Mano)
                    switch(opcion){                                         // se define la accion a realizar dependiendo de la opcion recibida
                        //---------------------------------------------------- casos en que se elige la posicion de la copa
                        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9:
                            printf("Apuesta?:\n");
                            apuesta = pedirNumeroEnRango(APUESTAMINIMA, dineroDisponible);  // espero monto correcto
                            if(apuesta > dineroDisponible){                 // si apuesta mas de lo que tiene
                                printf("%s", MENSAJESINDINERO);             // MSJ: para apostar necesitas dinero
                                noSalir = false;                            // salir
                            }else{                                          // apuesta correcta
                                if (partidasAlHilo == GANADASCONSECUTIVAS){ // hay q estafar - PIERDE
                                    do{                                     // posicion aleatoriade bolita para que pierda
                                        posicionBolita = (rand() % cantidadCopas) + 1;
                                    }while( posicionBolita == opcion );     // posicion de bolita aleatoria y diferente a la opcion
                                    apostadorAcerto = false;                // el jugador pierde
                                    dineroDisponible -= apuesta;            // se resta lo apostado
                                    partidasAlHilo = 0;                     // se restablece el contador de partidas ganadas seguidas
                                }else{                                      // NO hay q estafar
                                    posicionBolita = (rand() % cantidadCopas) + 1;
                                    if ( posicionBolita == opcion ){        // gano
                                        apostadorAcerto = true;             // apostador gana
                                        dineroDisponible += apuesta * ponderacionDeGanancia;    // se adjudica el dinero de acuerdo a ponderacion por cantidad de copas
                                        partidasAlHilo++;                   // aumento el contador de partidas ganadas
                                    }else{                                  // perdio
                                        apostadorAcerto = false;            // apostador pierde
                                        dineroDisponible -= apuesta;        // se descuenta lo apostado
                                        partidasAlHilo = 0;                 // se restablece el contador de partidas ganadas seguidas
                                    }
                                }
                                mostrarPosicionBolita(cantidadCopas, posicionBolita);   // muestro la ubicacion de la bolita
                                if (!apostadorAcerto)                       // MSJ: si el apostador gana
                                    printf("No ha acertado");
                                else                                        // MSJ: si el apostador pierde
                                    printf("Ha Acertado");
                                printf("\nSaldo: %d\n", dineroDisponible);  // muestro saldo
                            }
                        break;
                        //---------------------------------------------------- casos en que el jugador quiere salir
                        case 10:
                            printf("%s\n", MENSAJESALIDA);                  // muestro mensaje de salida
                            noSalir = false;                                // TERMINA EL JUEGO
                        break;
                        //---------------------------------------------------- casos en que el juegador pregunat si tiene la bola en la mano
                        case 11:                                            // mano
                            if (partidasAlHilo == GANADASCONSECUTIVAS){     // tengo la bola en la mano
                                montoInicial -= dineroDisponible;           // mono incial menos monto actual = ganancia o perdida
                                if(montoInicial > 0)                        // si hay perdidas
                                    dineroDisponible += montoInicial * 2;   // devuelvo el doble e imprimo
                                printf("\n%d\n", dineroDisponible);         // imprimo el monto
                                printf("%s", MENSAJEBOLAENMANO);            // MSJ: bola en mano
                            }else{                                          // la bola esta en una copa
                                posicionBolita = (rand() % cantidadCopas) + 1;  // muestro posicion de bola
                                printf("%s", MENSAJEBOLAENCOPA);            // MSJ: mensaje de salida por no tener bola en mano
                            }
                            noSalir = false;                                // TERMINA EL JUEGO
                        break;
                    }
                }
            }while(noSalir);                                                // FIN DEL JUEGO
        }
    }while(noSalir);
    return 0;
}
