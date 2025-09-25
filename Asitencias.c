#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct nombre{
    char nombres[65];
    char apell_p[35];
    char apell_m[35];
}TNOMBRE;

typedef struct alumno{
    TNOMBRE nombre[50];
    bool asistencias;
    int ID;
    struct alumno *siguiente;
}TALUMNO;

typedef struct dia{
    int dia;
    struct dia *siguiente;
    TALUMNO *lista_alumnos;
}TDIA;

void agrega_alumnos(TALUMNO *cab, TALUMNO *inicio, int cantidad_alumnos);

Nodo* crearnodo(char nombre[]);
Nodo* insertarinicio(Nodo* cabeza, char nombre[]);
void tomarAsistencia(Nodo* cabeza, int dia);
void mostrarlista(Nodo* cabeza);

int main() {
    int opcion;
    char nombre[50];
    int cantidad_alumnos = 0;
    TALUMNO *cab, *inicio;
    
    printf("Ingresa la cantidad de alumnos: ");
    scanf("%i", &cantidad_alumnos);
    

    agrega_alumnos(cab, inicio, cantidad_alumnos);

    do {
        printf("\n1. Agregar alumno\n");
        printf("2. Mostrar lista con asistencias\n");
        printf("3. Tomar asistencia\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingresa el nombre del alumno: ");
                scanf(" %[^\n]", nombre);
                cabeza = insertarinicio(cabeza, nombre);
                break;
            case 2:
                mostrarlista(cabeza);
                break;
            case 3:
                dia++;
                tomarAsistencia(cabeza, dia);
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion no valida\n");
        }
    } while (opcion != 4);

    while (cabeza != NULL) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        free(temp->asistencias);
        free(temp);
    }

    return 0;
}

/*--- Definiciones de Funciones ---*/

void agrega_alumnos(TALUMNO *cab, TALUMNO *inicio, int cantidad_alumnos){
    TALUMNO *nuevo, *aux;
    char nombres[65], apell_p[35], apell_m[35];

    for(int i=0; i<cantidad_alumnos; i++){
        nuevo = (TALUMNO*) malloc(sizeof(TALUMNO));
        
        if(nuevo == NULL){
            printf("Error de memoria\n");
            exit(1);
        }

        printf("Ingresa el nombre del alumno %d: ", i+1);
        gets(nombres);
        printf("Ingresa el apellido paterno del alumno %d: ", i+1);
        gets(apell_p);
        printf("Ingresa el apellido materno del alumno %d: ", i+1);
        gets(apell_m);

        strcpy(nuevo->nombre->nombres, nombres);
        strcpy(nuevo->nombre->apell_p, apell_p);
        strcpy(nuevo->nombre->apell_m, apell_m);
        nuevo->asistencias = false;
        nuevo->siguiente = NULL;
        nuevo->ID = i;

        if(cab == NULL){
            cab = nuevo;
            inicio = cab;
        }else{
            aux = cab;
            while(aux->siguiente != NULL){
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
    }
}

Nodo* crearnodo(char nombre[]) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo != NULL) {
        strcpy(nuevo->nombre, nombre);
        nuevo->asistencias = NULL;
        nuevo->numDias = 0;
        nuevo->siguiente = NULL;
    }
    return nuevo;
}

Nodo* insertarinicio(Nodo* cabeza, char nombre[]) {
    Nodo* nuevo = crearnodo(nombre);
    nuevo->siguiente = cabeza;
    return nuevo;
}

void tomarAsistencia(Nodo* cabeza, int dia) {
    Nodo* actual = cabeza;
    char respuesta;

    if (cabeza == NULL) {
        printf("No hay alumnos en la lista.\n");
        return;
    }
    
    printf("\nTomando asistencia para el Dia %d:\n", dia);
    while (actual != NULL) {
        actual->asistencias = (int*) realloc(actual->asistencias, (actual->numDias + 1) * sizeof(int));
        if (actual->asistencias == NULL) {
            printf("Error de memoria.\n");
            exit(1);
        }

        printf("%s (p/a): ", actual->nombre);
        scanf(" %c", &respuesta);
        if (respuesta == 'p' || respuesta == 'P')
            actual->asistencias[actual->numDias] = 1;
        else
            actual->asistencias[actual->numDias] = 0;

        actual->numDias++;
        actual = actual->siguiente;
    }
}

void mostrarlista(Nodo* cabeza) {
    Nodo* actual = cabeza;
    int presentes;
    int ausentes;

    if (cabeza == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    printf("\nRegistro de alumnos:\n");

    while (actual != NULL) {
        presentes = 0;
        ausentes = 0;
        printf("%s: ", actual->nombre);
        
        for (int i = 0; i < actual->numDias; i++) {
            if (actual->asistencias[i] == 1) {
                printf("P ");
                presentes++;
            } else {
                printf("A ");
                ausentes++;
            }
        }
        printf("| P: %d, A: %d\n", presentes, ausentes);
        actual = actual->siguiente;
    }
}




