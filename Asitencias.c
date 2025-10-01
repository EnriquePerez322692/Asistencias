#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct fecha{
    int dia;
    int mes;
    int temporada; //No me deja poner "año" así que me puse creativo con la variable jajaja
}TFECHA;

typedef struct nombre{
    char nombres[65];
    char apell_p[35];
    char apell_m[35];
}TNOMBRE;

typedef struct alumno{
    TNOMBRE nombre;
    bool asistencias;
    int ID;
    struct alumno *siguiente;
}TALUMNO;

typedef struct dia{
    TFECHA fecha;
    bool asistencia_del_dia;
    struct dia *siguiente;
    TALUMNO *lista_alumnos;
}TDIA;

void ordenar_alfabeticamente(TDIA *cab_dia);
void ordenar_por_ID(TDIA *cab_dia);

void mostrar_listas(TDIA *cab_dia);
void mostrar_alumno(TDIA *cab_dia, TNOMBRE nombre);
void mostrar_dia(TDIA *cab_dia, TFECHA fecha);
void mostrar_ID(TDIA *cab_dia, int ID);

void elimiminar_alumno(TALUMNO **cab, int ID, bool *confirmacion);
void crea_dia(TDIA **cab_dia, TALUMNO *lista_original, TFECHA fecha);
void agrega_alumnos(TALUMNO *cab, int cantidad_alumnos);
TALUMNO *copiar_lista_alumnos(TALUMNO *original);
void tomar_asistencia(TALUMNO *cab_dia);

int main(){
    int opcion, cantidad_alumnos = 0;
    TALUMNO *cab = NULL;
    TDIA *cab_dia = NULL;
    
    printf("Primero, ingrese la cantidad de alumnos: ");
    scanf("%i", &cantidad_alumnos);
    getchar();

    agrega_alumnos(cab, cantidad_alumnos);
    
    do{
        printf("\n---MENU---\n");
        printf("1. Mostrar listas\n");
        printf("2. Tomar asistencia\n");
        printf("3. Ordenar alumnos");
        printf("4. Modificar lista de alumnos\n");
        printf("5. Salir\n");
        printf("Elige una opcion: ");
        scanf("%i", &opcion);
        getchar();

        switch(opcion){
            case 1:{
                int opc;

                if(cab == NULL) {
                    printf("La lista esta vacia\n");
                    printf("Regresando al menú principal...\n");
                    break;
                }else{
                    printf("\n---MENU MOSTRAR---\n");
                    printf("1. Mostrar listas completas\n");
                    printf("2. Mostrar un alumno en particular\n");
                    printf("3. Mostrar un dia en particular\n");
                    printf("4. Mostrar un ID en particular\n");
                    printf("5. Regresar al menu principal\n");
                    printf("Elige una opcion: ");
                    scanf("%i", &opc);

                    switch(opc){
                        case 1:{
                            mostrar_listas(cab_dia);
                            break;
                        }

                        case 2:{
                            TNOMBRE nombre;

                            printf("Ingresa los siguientes datos del alumno a buscar: ");
                            printf("Nombre(s): ");
                            gets(nombre.nombres);
                            printf("Apellido paterno: ");
                            gets(nombre.apell_p);
                            printf("Apellido materno: ");
                            gets(nombre.apell_m);

                            mostrar_alumno(cab_dia, nombre);

                            break;
                        }

                        case 3:{ //Falta cambiar a TFECHA
                            TFECHA fecha;

                            printf("Imgresa el numero del dia: ");
                            scanf("%i", &fecha.dia);
                            printf("Ingresa el numero del mes: ");
                            scanf("%i", &fecha.mes);
                            printf("Ingresa el numero del temporada: ");
                            scanf("%i", &fecha.temporada);

                            mostrar_dia(cab_dia, fecha);

                            break;
                        }

                        case 4:{
                            int ID;

                            printf("Ingresa el ID del alumno a buscar: ");
                            scanf("%i", &ID);

                            mostrar_ID(cab_dia, ID);

                            break;
                        }

                        default:
                            printf("Opcion no valida\n");
                    }
                }
                break;
            }

            case 2:{
                TFECHA fecha;
                
                if(cab == NULL) {
                    printf("La lista de alumnos esta vacia\n");
                    printf("Regresando al menú principal...\n");
                    break;
                }else{
                    crea_dia(&cab_dia, cab, fecha);
                    tomar_asistencia(cab_dia);
                }
                break;
            }

            case 3:{
                int opc;
                
                if(cab == NULL) {
                    printf("La lista esta vacia\n");
                    printf("Regresando al menú principal...\n");
                    break;
                }else{
                    printf("---MENU ORDENAR---\n");
                    printf("1. Ordenar alfabeticamente\n");
                    printf("2. Ordenar por ID\n");
                    printf("3. Regresar al menu principal\n");
                    printf("Elige una opcion: ");
                    scanf("%i", &opc);

                    switch(opc){
                        case 1:{
                            ordenar_alfabeticamente(cab_dia);
                            break;
                        }

                        case 2:{
                            ordenar_por_ID(cab_dia);
                            break;
                        }

                        default:
                            printf("Opcion no valida\n");
                    }
                }
                break;
            }

            case 4:{
                int opc;

                printf("\n---MENU MODIFICAR---\n");
                printf("1. Agregar nuevo alumno\n");
                printf("2. Eliminar alumno existente\n");
                printf("3. Regresar al menu principal\n");

                printf("Elige una opcion: ");
                scanf("%i", &opc);
                getchar();

                if(cab == NULL){
                    printf("La lista esta vacia\n");
                    printf("Regresando al menú principal...\n");
                    break;
                }else{
                    switch(opc){
                        case 1:{
                            int cantidad_nuevos;

                            printf("Cuantos alumnos nuevos deseas agregar? ");
                            scanf("%i", &cantidad_nuevos);

                            agrega_alumnos(cab, cantidad_nuevos);
                            break;
                        }

                        case 2:{
                            int ID;
                            bool confirmacion = false;

                            printf("Ingresa el ID del alumno a eliminar: ");
                            scanf("%i", &ID);

                            elimiminar_alumno(&cab, ID, &confirmacion);

                            if(confirmacion){
                                printf("Alumno eliminado exitosamente\n");
                            }else{
                                printf("No se pudo eliminar al alumno\n");
                            }

                            break;
                        }

                        case 3:{
                            printf("Regresando al menu principal...\n");
                            break;
                        }

                        default:{
                            printf("Opcion no valida\n");
                        }
                    }
                }
            }

            case 5:{
                printf("Saliendo...\n");
                break;
            }

            default:{
                printf("Opcion no valida\n");
            }
        }
    }while(opcion != 4);

    return 0;
}


void ordenar_alfabeticamente(TDIA *cab_dia){
    TDIA *dia_aux;
    TALUMNO *alumno_i, *alumno_j;
    TNOMBRE aux_nombre;
    int aux_ID;
    bool aux_asistencia;

    dia_aux = cab_dia;

    if(dia_aux == NULL){
        printf("La lista de dias esta vacia\n");
        return;
    }

    while(dia_aux != NULL){
        alumno_i = dia_aux->lista_alumnos;

        if(alumno_i == NULL){
            printf("La lista de alumnos esta vacia\n");
            return;
        }

        while(alumno_i != NULL){
            alumno_j = alumno_i->siguiente;

            while(alumno_j != NULL){ //Aquí el pedo es si lo quieren ordenar por apellidos o nombres, sino solo se debe cambiar el if con los apellidos :p
                if(strcmp(alumno_i->nombre.nombres, alumno_j->nombre.nombres) > 0){
                    strcpy(aux_nombre.nombres, alumno_i->nombre.nombres);
                    strcpy(aux_nombre.apell_p, alumno_i->nombre.apell_p);
                    strcpy(aux_nombre.apell_m, alumno_i->nombre.apell_m);

                    strcpy(alumno_i->nombre.nombres, alumno_j->nombre.nombres);
                    strcpy(alumno_i->nombre.apell_p, alumno_j->nombre.apell_p);
                    strcpy(alumno_i->nombre.apell_m, alumno_j->nombre.apell_m);

                    strcpy(alumno_j->nombre.nombres, aux_nombre.nombres);
                    strcpy(alumno_j->nombre.apell_p, aux_nombre.apell_p);
                    strcpy(alumno_j->nombre.apell_m, aux_nombre.apell_m);

                    aux_ID = alumno_i->ID;
                    alumno_i->ID = alumno_j->ID;
                    alumno_j->ID = aux_ID;

                    aux_asistencia = alumno_i->asistencias;
                    alumno_i->asistencias = alumno_j->asistencias;
                    alumno_j->asistencias = aux_asistencia;
                }

                alumno_j = alumno_j->siguiente;
            }

            alumno_i = alumno_i->siguiente;
        }

        dia_aux = dia_aux->siguiente;
    }
}

void ordenar_por_ID(TDIA *cab_dia){
    TDIA *dia_aux;
    TALUMNO *alumno_i, *alumno_j;
    TNOMBRE aux_nombre;
    int aux_ID;
    bool aux_asistencia;

    dia_aux = cab_dia;

    if(dia_aux == NULL){
        printf("La lista de dias esta vacia\n");
        return;
    }

    while(dia_aux != NULL){
        alumno_i = dia_aux->lista_alumnos;

        if(alumno_i == NULL){
            printf("La lista de alumnos esta vacia\n");
            return;
        }

        while(alumno_i != NULL){
            alumno_j = alumno_i->siguiente;

            while(alumno_j != NULL){
                if(alumno_i->ID > alumno_j->ID){
                    strcpy(aux_nombre.nombres, alumno_i->nombre.nombres);
                    strcpy(aux_nombre.apell_p, alumno_i->nombre.apell_p);
                    strcpy(aux_nombre.apell_m, alumno_i->nombre.apell_m);

                    strcpy(alumno_i->nombre.nombres, alumno_j->nombre.nombres);
                    strcpy(alumno_i->nombre.apell_p, alumno_j->nombre.apell_p);
                    strcpy(alumno_i->nombre.apell_m, alumno_j->nombre.apell_m);

                    strcpy(alumno_j->nombre.nombres, aux_nombre.nombres);
                    strcpy(alumno_j->nombre.apell_p, aux_nombre.apell_p);
                    strcpy(alumno_j->nombre.apell_m, aux_nombre.apell_m);

                    aux_ID = alumno_i->ID;
                    alumno_i->ID = alumno_j->ID;
                    alumno_j->ID = aux_ID;

                    aux_asistencia = alumno_i->asistencias;
                    alumno_i->asistencias = alumno_j->asistencias;
                    alumno_j->asistencias = aux_asistencia;
                }

                alumno_j = alumno_j->siguiente;
            }

            alumno_i = alumno_i->siguiente;
        }

        dia_aux = dia_aux->siguiente;
    }
}


void mostrar_listas(TDIA *cab_dia){
    TDIA *dia_aux;
    TALUMNO *alumno_aux;

    dia_aux = cab_dia;

    if(dia_aux == NULL){
        printf("La lista de dias esta vacia\n");
        return;
    }

    while(dia_aux != NULL){
        alumno_aux = dia_aux->lista_alumnos;

        printf("Listas totales de asistencias usadas:\n");
        printf("\tFecha: %i/%i/%i\n", dia_aux->fecha.dia, dia_aux->fecha.mes, dia_aux->fecha.temporada);
        
        while(alumno_aux != NULL){
            printf("\t\tID: %i, Nombre: %s %s %s, Asistencia: %s\n", alumno_aux->ID, alumno_aux->nombre.nombres, alumno_aux->nombre.apell_p, alumno_aux->nombre.apell_m, alumno_aux->asistencias? "Presente" : "Ausente"); //Nms, no sabía que se podía poner un "if" en una printf de esa manera :o
            alumno_aux = alumno_aux->siguiente;
        }

        dia_aux = dia_aux->siguiente;
        printf("\n");
    }
}

void mostrar_alumno(TDIA *cab_dia, TNOMBRE nombre){
    TDIA *dia_aux;
    TALUMNO *alumno_aux;
    bool encontrado = false;

    dia_aux = cab_dia;

    printf("Asistencias del alumno %s %s %s:\n", nombre.nombres, nombre.apell_p, nombre.apell_m);

    while(dia_aux != NULL){
        alumno_aux = dia_aux->lista_alumnos;

        while(alumno_aux != NULL){
            if((strcmp(alumno_aux->nombre.nombres, nombre.nombres) == 0) && (strcmp(alumno_aux->nombre.apell_p, nombre.apell_p) == 0) && (strcmp(alumno_aux->nombre.apell_m, nombre.apell_m) == 0)){
                printf("\t%i %i %i: %s\n", dia_aux->fecha.dia, dia_aux->fecha.mes, dia_aux->fecha.temporada, alumno_aux->asistencias? "Presente" : "Ausente");
                encontrado = true;

                break;
            }
            
            alumno_aux = alumno_aux->siguiente;
        }

        dia_aux = dia_aux->siguiente;
    }

    if(!encontrado){
        printf("No se encontro al alumno en las listas de asistencia\n");
    }
}

void mostrar_dia(TDIA *cab_dia, TFECHA fecha){
    TDIA *dia_aux;
    TALUMNO *alumno_aux;

    dia_aux = cab_dia;

    while(dia_aux != NULL){
        if((dia_aux->fecha.dia == fecha.dia) && (dia_aux->fecha.mes == fecha.mes) && (dia_aux->fecha.temporada == fecha.temporada)){
            alumno_aux = dia_aux->lista_alumnos;

            printf("Asistencias del dia %i/%i/%i:\n", fecha.dia, fecha.mes, fecha.temporada);

            while(alumno_aux != NULL){
                printf("\tID: %i, Nombre: %s %s %s, Asistencia: %s\n", alumno_aux->ID, alumno_aux->nombre.nombres, alumno_aux->nombre.apell_p, alumno_aux->nombre.apell_m, alumno_aux->asistencias? "Presente" : "Ausente");
                alumno_aux = alumno_aux->siguiente;
            }

            break;
        }

        dia_aux = dia_aux->siguiente;
    }
}

void mostrar_ID(TDIA *cab_dia, int ID){
    TDIA *dia_aux;
    TALUMNO *alumno_aux;
    bool encontrado = false;

    dia_aux = cab_dia;

    printf("Asistencias del alumno con el ID-%i:\n", ID);

    while(dia_aux != NULL){
        alumno_aux = dia_aux->lista_alumnos;

        while(alumno_aux != NULL){
            if(alumno_aux->ID == ID){
                printf("\t%i %i %i: %s\n", dia_aux->fecha.dia, dia_aux->fecha.mes, dia_aux->fecha.temporada, alumno_aux->asistencias? "Presente" : "Ausente");
                encontrado = true;

                break;
            }
            
            alumno_aux = alumno_aux->siguiente;
        }

        dia_aux = dia_aux->siguiente;
    }

    if(!encontrado){
        printf("No se encontro al alumno en las listas de asistencia\n");
    }
}


void eliminar_alumno(TALUMNO **cab, int ID, bool *confirmacion){
    TALUMNO *aux, *anterior = NULL;
    int respuesta = 0;

    aux = *cab;

    while(aux != NULL && aux->ID != ID){
        anterior = aux;
        aux = aux->siguiente;
    }

    if(aux == NULL){
        printf("No se encontro al alumno con el ID-%i\n", ID);
        *confirmacion = false;

        return;
    }

    if(anterior == NULL){
        *cab = aux->siguiente;
    }else{
        anterior->siguiente = aux->siguiente;
    }

    do{
    printf("Esta seguro de eliminar al alumno %s %s %s (ID-%i)? (1 para si, 0 para no): ", aux->nombre.nombres, aux->nombre.apell_p, aux->nombre.apell_m, aux->ID);
    scanf("%i", &respuesta);
    }while(respuesta == 0 || respuesta == 1);

    if(!respuesta){
        printf("Operacion cancelada, el alumno no fue eliminado\n");
        *confirmacion = false;
        return;
    }else{
        free(aux);
        printf("Alumno con el ID-%i eliminado exitosamente\n", ID);
        *confirmacion = true;
    }
}

void crea_dia(TDIA **cab_dia, TALUMNO *lista_original, TFECHA fecha){
    TDIA *nuevo;

    nuevo = (TDIA*) malloc(sizeof(TDIA));

    if(nuevo == NULL){
        printf("Error de memoria\n");
        exit(1);
    }

    printf("\nIngresa el numero del dia: ");
    scanf("%i", &fecha.dia);
    printf("\nIngresa el numero del mes: ");
    scanf("%i", &fecha.mes);
    printf("\nIngresa el numero del temporada: ");
    scanf("%i", &fecha.temporada);

    nuevo->fecha.dia = fecha.dia;
    nuevo->fecha.mes = fecha.mes;
    nuevo->fecha.temporada = fecha.temporada;
    nuevo->asistencia_del_dia = false;
    nuevo->siguiente = NULL;
    nuevo->lista_alumnos = copiar_lista_alumnos(lista_original);

    if(*cab_dia == NULL){
        *cab_dia = nuevo;
    }else{
        TDIA *aux = *cab_dia;

        while(aux->siguiente != NULL){
            aux = aux->siguiente;
        }

        aux->siguiente = nuevo;
    }
}

void agrega_alumnos(TALUMNO *cab, int cantidad_alumnos){
    TALUMNO *nuevo, *aux;
    TNOMBRE nombre;

    for(int i=0; i<cantidad_alumnos; i++){
        nuevo = (TALUMNO*) malloc(sizeof(TALUMNO));
        
        if(nuevo == NULL){
            printf("Error de memoria\n");
            exit(1);
        }

        printf("Ingresa el nombre del alumno %d: \n", i+1);
        gets(nombre.nombres);
        printf("Ingresa el apellido paterno del alumno %d: \n", i+1);
        gets(nombre.apell_p);
        printf("Ingresa el apellido materno del alumno %d: \n", i+1);
        gets(nombre.apell_m);

        strcpy(nuevo->nombre.nombres, nombre.nombres);
        strcpy(nuevo->nombre.apell_p, nombre.apell_p);
        strcpy(nuevo->nombre.apell_m, nombre.apell_m);
        nuevo->asistencias = false;
        nuevo->siguiente = NULL;
        nuevo->ID = i;

        if(cab == NULL){
            cab = nuevo;
        }else{
            aux = cab;
            while(aux->siguiente != NULL){
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
    }
}

TALUMNO *copiar_lista_alumnos(TALUMNO *original){
    if(original == NULL){
        return NULL;
    }

    TALUMNO *nuevo_cab = NULL;
    TALUMNO *nuevo = (TALUMNO*) malloc(sizeof(TALUMNO));
    TALUMNO *actual_original = original->siguiente;
    TALUMNO *actual_nuevo = nuevo_cab;

    if(nuevo == NULL){
        printf("Error de memoria\n");
        exit(1);
    }

    //copiar los datos del nodo original al nuevo nodo
    strcpy(nuevo->nombre.nombres, original->nombre.nombres);
    strcpy(nuevo->nombre.apell_p, original->nombre.apell_p);
    strcpy(nuevo->nombre.apell_m, original->nombre.apell_m);
    
    nuevo->asistencias = original->asistencias;
    nuevo->ID = original->ID;
    nuevo->siguiente = NULL;
    nuevo_cab = nuevo;

    //copiar los nodos restantes
    while(actual_original != NULL){
        nuevo = (TALUMNO*) malloc(sizeof(TALUMNO));

        if(nuevo == NULL){
            printf("Error de memoria\n");
            exit(1);
        }

        strcpy(nuevo->nombre.nombres, actual_original->nombre.nombres);
        strcpy(nuevo->nombre.apell_p, actual_original->nombre.apell_p);
        strcpy(nuevo->nombre.apell_m, actual_original->nombre.apell_m);

        nuevo->asistencias = actual_original->asistencias;
        nuevo->ID = actual_original->ID;
        nuevo->siguiente = NULL;

        actual_nuevo->siguiente = nuevo;
        actual_nuevo = nuevo;
        actual_original = actual_original->siguiente;
    }

    return nuevo_cab;
}

void tomar_asistencia(TALUMNO *cab_dia){
    TDIA *aux;
    TALUMNO *lista_aux;

    aux = cab_dia;

    while(aux->siguiente !=  NULL){
        aux = aux->siguiente;
    }

    lista_aux = aux->lista_alumnos;
    aux->asistencia_del_dia = true;

    while(lista_aux != NULL){
        int respuesta;

        do{
        printf("El alumno %s %s %s asistio el dia de hoy (%i/%i/%i)? (1 para si, 0 para no): ", lista_aux->nombre.nombres, lista_aux->nombre.apell_p, lista_aux->nombre.apell_m, aux->fecha.dia, aux->fecha.mes, aux->fecha.temporada);
        scanf("%i", &respuesta);
        }while(respuesta == 0 || respuesta == 1);

        lista_aux->asistencias = respuesta;
        lista_aux = lista_aux->siguiente;
    }
}
