#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10
#define TAMTIP 4
#define TAMCOL 5
#define TAMSERV 4
#define TAMTRA 10

typedef struct
{
    int dia;
    int mes;
    int anio;

} eFechaIngreso;

typedef struct
{
   int id;
   char descripcion[20];

} eTipo;

typedef struct
{
   int id;
   char nombreColor[20];

} eColor;

typedef struct
{
    int id;
    char marca[20];
    int idColor;
    int idTipo;
    int rodado;
    int isEmpty;

} eBicicleta;

typedef struct
{
   int id;
   char descripcion[20];
   float precio;

} eServicio;

typedef struct
{
   int id;
   int idBicicleta;
   int idServicio;
   int isEmpty;
   eFechaIngreso fecha;

}eTrabajo;

int menu();

void inicializarBicicletas(eBicicleta vec[], int tam);
void mostrarBicicleta(eBicicleta x, eTipo tipos[], int tamtip, eColor colores[], int tamcol);
void mostrarBicicletas(eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol);
int buscarLibre(eBicicleta vec[], int tam);
int buscarBicicleta(int id, eBicicleta vec[], int tam);
int altaBicicleta(int proximoId, eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol);
void modificarBicicleta(eBicicleta vec[], int tam,  eTipo tipos[], int tamtip, eColor colores[], int tamcol);
void bajaBicicleta(eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol);

int cargarDescripcionTipo(char descripcion[], int id, eTipo tipos[], int tamtip);
int cargarNombreColor(char nombreColor[], int id, eColor colores[], int tamcol);

void inicializarTrabajos(eTrabajo vec[], int tam);
int buscarLibreTrabajo(eTrabajo vec[], int tam);
void listarTrabajo(eTrabajo trabajo, eServicio servicios[], int tamserv);
void listarTrabajos(eTrabajo trabajo[], int tamtra, eServicio servicios[], int tamserv);
int cargarDescripcionServicio(char descripcion[], int id, eServicio servicios[], int tamserv);
int altaTrabajo(int idTrabajo, eTrabajo trabajos[], int tamtra, eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol, eServicio servicios[], int tamserv);
void listarServicios(eServicio servicios[], int tamserv);

void mostrarTipos(eTipo tipos[], int tamtip);
void mostrarColores(eColor colores[], int tamcol);


int main()
{

    char seguir = 's';
    char confirma;
    int proximoId = 100;
    int proximoIdTrabajo = 30000;
    eBicicleta lista[TAM];
    eTipo tipos[TAMTIP] = {{1000, "Rutera"}, {1001, "Carrera"},{1002, "Mountain"},{1003, "BMX"}};
    eColor colores[TAMCOL] = {{5000, "Gris"}, {5001, "Negro"},{5002, "Blanco"},{5003, "Azul"},{5004, "Rojo"}};
    eTrabajo trabajos[TAMTRA];
    eServicio servicios[TAMSERV] = {{20000, "Limpieza", 250}, {20001, "Parche", 300}, {20002, "Centrado", 400}, {20003, "Cadena", 350}};


    inicializarBicicletas(lista, TAM);
    inicializarTrabajos(trabajos, TAMTRA);



    do
    {

        switch(menu())
        {

        case 1:
            if(altaBicicleta(proximoId, lista, TAM, tipos, TAMTIP, colores, TAMCOL))
            {

                proximoId ++;

            };
            break;
        case 2:
            modificarBicicleta(lista, TAM, tipos, TAMTIP, colores, TAMCOL);
            break;
        case 3:
            bajaBicicleta(lista, TAM, tipos, TAMTIP, colores, TAMCOL);
            break;
        case 4:
            mostrarTipos(tipos, TAMTIP);
            break;
        case 5:
            mostrarColores(colores, TAMCOL);
            break;
        case 6:
            mostrarBicicletas(lista, TAM, tipos, TAMTIP, colores, TAMCOL);
            break;
        case 7:
            if(altaTrabajo(proximoIdTrabajo, trabajos, TAMTRA, lista, TAM, tipos, TAMTIP, colores, TAMCOL, servicios, TAMSERV))
            {

                proximoIdTrabajo ++;

            };
            break;
        case 8:
            listarTrabajos(trabajos, TAMTRA, servicios, TAMSERV);
            break;
        case 9:
            printf("Confirma salida?:\n");
            fflush(stdin);
            scanf("%c", &confirma);
            if(confirma == 's')
            {

                seguir = 'n';

            }
            break;
        }

        system("pause");

    }
    while(seguir == 's');

    return 0;



    return 0;
}


int menu()
{

    int opcion;

    system("cls");
    printf("Menu de Opciones\n\n");
    printf("1- Alta Bicicleta\n");
    printf("2- Modificar\n");
    printf("3- Baja\n");
    printf("4- Listar Tipos\n");
    printf("5- Listar Colores\n");
    printf("6- Listar Bicicleta\n");
    printf("7- Alta trabajo\n");
    printf("8- Listar trabajos\n");
    printf("9- Salir\n\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;

}

void inicializarBicicletas(eBicicleta vec[], int tam)
{

    for(int i=0; i < tam; i++)
    {

        vec[i].isEmpty = 1;

    }
}

void mostrarBicicleta(eBicicleta x, eTipo tipos[], int tamtip, eColor colores[], int tamcol)
{

    char descTipo[20];
    char nombreColor[20];
    cargarDescripcionTipo(descTipo, x.idTipo, tipos, tamtip);
    cargarNombreColor(nombreColor,  x.idColor, colores, tamcol);

    printf("%d   %10s     %10s     %10s     %d\n", x.id, x.marca, descTipo, nombreColor, x.rodado);


}

void mostrarBicicletas(eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol)
{

    int flag = 0;

    //system("cls");
    printf("-----Listado de Bicicletas-----\n\n");
    printf(" ID          Marca        Tipo        Color    Rodado\n\n");

    for(int i=0; i < tam; i++)
    {

        if(vec[i].isEmpty == 0)
        {

            mostrarBicicleta(vec[i], tipos, tamtip, colores, tamcol);
            flag = 1;

        }
    }

    if(flag == 0)
    {

        printf("No hay bicicletas que listar\n");

    }
}

int buscarLibre(eBicicleta vec[], int tam)
{

    int indice = -1;

    for(int i=0; i < tam; i++)
    {

        if(vec[i].isEmpty == 1)
        {

            indice = i;
            break;
        }

    }

    return indice;
}

int buscarBicicleta(int id, eBicicleta vec[], int tam)
{

    int indice = -1;

    for(int i=0; i < tam; i++)
    {

        if(vec[i].isEmpty == 0 && vec[i].id == id)
        {

            indice = i;
            break;
        }

    }

    return indice;
}

int altaBicicleta(int proximoId, eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol)
{

    int todoOk = 0;
    int indice;
    eBicicleta auxBicicleta;

    system("cls");

    printf("------Alta Bicicleta------\n\n");

    indice = buscarLibre(vec, tam);

    if(indice == -1)
    {

        printf("El sistema se encuentra completo\n\n");
        system("pause");

    }
    else
    {

        auxBicicleta.id = proximoId;

        printf("Ingrese marca: ");
        fflush(stdin);
        gets(auxBicicleta.marca);

        mostrarTipos(tipos, tamtip);

        printf("Ingrese id del tipo: ");
        scanf("%d", &auxBicicleta.idTipo);

        mostrarColores(colores, tamcol);

        printf("Ingrese id del color: ");
        scanf("%d", &auxBicicleta.idColor);

        printf("Ingrese Rodado: ");
        scanf("%d", &auxBicicleta.rodado);

        auxBicicleta.isEmpty = 0;

        vec[indice] = auxBicicleta;
        todoOk = 1;

    }

    return todoOk;
}

void modificarBicicleta(eBicicleta vec[], int tam,  eTipo tipos[], int tamtip, eColor colores[], int tamcol)
{

    int indice;
    int id;
    int idTipo;
    int rodado;
    int opcion;

    system("cls");

    printf("------Modificar Bicicleta------\n\n");

    printf("Ingrese id: ");
    scanf("%d", &id);

    indice = buscarBicicleta(id, vec, tam);

    if(indice == -1)
    {
        printf("No existe ese id\n\n");
        system("pause");


    }
    else
    {

        mostrarBicicleta(vec[indice], tipos, tamtip, colores, tamcol);

        printf("1.Tipo\n");
        printf("2.Rodado\n");

        printf("Que dato quiere modificar? ");
        scanf("%d", &opcion);

        if(opcion == 1)
        {
            mostrarTipos(tipos, tamtip);
            printf("Ingrese id tipo: ");
            scanf("%d", &idTipo);
            vec[indice].idTipo = idTipo;
            printf("Se ha realizado la modiicacion\n\n");

        }
        if(opcion == 2)
        {

            printf("Ingrese rodado: ");
            scanf("%d", &rodado);
            vec[indice].rodado = rodado;
            printf("Se ha realizado la modificacion\n\n");


        }
        else
        {

            printf("no es una opcion valida");


        }
    }
}

void bajaBicicleta(eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol)
{

    int indice;
    int id;
    char confirma;

    system("cls");

    printf("------Baja Bicicleta------\n\n");

    printf("Ingrese id: ");
    scanf("%d", &id);

    indice = buscarBicicleta(id, vec, tam);

    if(indice == -1)
    {
        printf("No existe ese id\n\n");
        system("pause");


    }
    else
    {

        mostrarBicicleta(vec[indice], tipos, tamtip, colores, tamcol);

        printf("Confirma la eliminacion? ");
        fflush(stdin);
        scanf("%c", &confirma);

        if(confirma == 's')
        {

            vec[indice].isEmpty = 1;
            printf("Se ha realizado la baja\n\n");

        }
        else
        {

            printf("Se cancelo la eliminacion\n\n");

        }
    }
}

void mostrarTipos(eTipo tipos[], int tamtip)
{

    //system("cls");
    printf("-----Listado Tipos-----\n\n");
    printf(" ID      Descripcion\n\n");

    for(int i=0; i < tamtip; i++)
    {

        printf("%d   %10s\n",tipos[i].id, tipos[i].descripcion);


    }
    printf("\n");
}

void mostrarColores(eColor colores[], int tamcol)
{

    //system("cls");
    printf("-----Listado Colores-----\n\n");
    printf(" ID      Nombre\n\n");

    for(int i=0; i < tamcol; i++)
    {

        printf("%d   %10s\n",colores[i].id, colores[i].nombreColor);


    }
    printf("\n");
}

int cargarDescripcionTipo(char descripcion[], int id, eTipo tipos[], int tamtip)
{

    int todoOk = 0;

    for(int i=0; i < tamtip; i++)
    {

        if(tipos[i].id == id)
        {

            strcpy(descripcion, tipos[i].descripcion);
            todoOk = 1;
        }

    }

    return todoOk;
}

int cargarNombreColor(char nombreColor[], int id, eColor colores[], int tamcol)
{

    int todoOk = 0;

    for(int i=0; i < tamcol; i++)
    {

        if(colores[i].id == id)
        {

            strcpy(nombreColor, colores[i].nombreColor);
            todoOk = 1;
        }

    }

    return todoOk;
}

void inicializarTrabajos(eTrabajo vec[], int tam)
{

    for(int i=0; i < tam; i++)
    {

        vec[i].isEmpty = 1;

    }

}

int buscarLibreTrabajo(eTrabajo vec[], int tam)
{

    int indice = -1; //va -1, porque -1 no puede ser un indice de un vector, al inicializar, indice no puede ser un indice valido del vector.

    for(int i=0; i < tam; i++)
    {

        if(vec[i].isEmpty == 1)
        {

            indice = i;
            break;
        }

    }

    return indice;
}

void listarTrabajo(eTrabajo trabajo, eServicio servicios[], int tamserv)
{

    char descServicio[20];

    cargarDescripcionServicio(descServicio, trabajo.idServicio, servicios, tamserv);
    printf("  %d    %10s      %d/%d/%d\n", trabajo.id, descServicio, trabajo.fecha.dia, trabajo.fecha.mes, trabajo.fecha.anio);

}

void listarTrabajos(eTrabajo trabajos[], int tamtra, eServicio servicios[], int tamserv)
{

    int flag = 0;
    system("cls");
    printf("Listado Trabajos\n\n");
    printf("id    Servicio    fecha\n");

    for(int i=0; i < tamtra; i++)
    {

        if(trabajos[i].isEmpty == 0)
        {
            listarTrabajo(trabajos[i], servicios, tamserv);
            flag=1;
        }
    }
    if(flag == 0)
    {

        printf("no hay trabajos que mostrar\n");

    }
    printf("\n");

}

int cargarDescripcionServicio(char descripcion[], int id, eServicio servicios[], int tamserv)
{

    int todoOk = 0;

    for(int i=0; i < tamserv; i++)
    {

        if(servicios[i].id == id)
        {

            strcpy(descripcion, servicios[i].descripcion);
            todoOk = 1;
        }

    }

    return todoOk;
}

int altaTrabajo(int idTrabajo, eTrabajo trabajos[], int tamtra, eBicicleta vec[], int tam, eTipo tipos[], int tamtip, eColor colores[], int tamcol, eServicio servicios[], int tamserv)
{

    int todoOk = 0;
    int indice;
    eTrabajo auxTrabajo;

    system("cls");

    printf("------Alta Trabajo------\n\n");

    indice = buscarLibreTrabajo(trabajos, tamtra);

    if(indice == -1)
    {

        printf("El sistema se encuentra completo\n\n");
        system("pause");

    }
    else
    {

        mostrarBicicletas(vec, tam, tipos, tamtip, colores, tamcol);

        printf("Ingrese id bicicleta: ");
        scanf("%d", &auxTrabajo.idBicicleta);

        listarServicios(servicios, tamserv);

        printf("Ingrese id servicio: ");
        scanf("%d", &auxTrabajo.idServicio);

        printf("Ingrese fechas de ingreso dd/mm/aaaa: ");
        scanf("%d/%d/%d", &auxTrabajo.fecha.dia, &auxTrabajo.fecha.mes,&auxTrabajo.fecha.anio);

        auxTrabajo.id = idTrabajo;
        auxTrabajo.isEmpty = 0;

        trabajos[indice] = auxTrabajo;
        todoOk = 1;

        printf("\nAlta trabajo exitoso");

    }


    return todoOk;

}


void listarServicios(eServicio servicios[], int tamserv){

    printf("Listado servicios\n\n");
    printf("id    descripcion    precio\n");

    for(int i=0; i < tamserv; i++){

        printf("  %d    %10s    %5.2f\n", servicios[i].id, servicios[i].descripcion, servicios[i].precio);

    }

    printf("\n");
}
