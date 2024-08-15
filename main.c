#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char *mostrarNombreEmpresa();

void CargarDatos();
void MostrarEmpresas();
void MostrarEmpleados();
void ingresarReparaciones();

struct empleados{
    int cod;
    char dni[9];
    char cuil[15];
    char nombres[40];
    char apellidos[40];
};

struct empleados_lista{
    int cod;
    char dni[9];
    char cuil[15];
    char nombres[40];
    char apellidos[40];
    struct empleados_lista *sig;
};

struct empleados_lista *empleados_primero;
struct empleados_lista *empleados_ultimo;

struct empresas{
    int cod;
    char cuit[15];
    char nombreE[40];
};

struct empresas_lista{
    int cod;
    char cuit[15];
    char nombreE[40];
    struct empresas_lista *sig;
};

struct empresas_lista *empresas_primero;
struct empresas_lista *empresas_ultimo;

struct datos{
    int dispositivo;
    int codigoEmpleado;
    char fecha[11];
    float costoH;
    float costoS;
    char nombEmpresa[100];
    int codigoEmpresa;
    float precioFinal;
    struct datos *sig;
};

//creación lista de datos.

//creación 4 punteros.

struct datos_lista *datos_primero;
struct datos_lista *datos_ultimo;

struct datos_lista *memoria_primero;
struct datos_lista *memoria_ultimo;


void getch(void);

void ingresarReparaciones(){
    int opcion=0, codigoEmpleado=1, codigoEmpresa=0;
    char fecha[11], nombEmpresa[100];
    float costoH = 0.0, costoS = 0.0, precioFinal = 0.0;

    system("cls");
    printf("Ingreso de reparaciones.\n");

    struct datos *nuevaReparacion;
    nuevaReparacion=(struct datos*)malloc(sizeof(struct datos));

    if(!nuevaReparacion)
    {
        printf("No se ha podido reservar memoria\n");
		printf("INGRESE CUALQUIER TECLA PARA CONTINUAR...\n");
		getch();
		exit(1);
    }
    else
    {
		FILE *reparacion = fopen("reparacion.dat","ab");
		if(reparacion == NULL)
		{
			printf("ERROR");
		}
		else
		{
		printf("Opciones: \n");
		printf("1 - PC \n");
		printf("2 - Notebook \n");
		printf("3 - Celular \n");
		fflush(stdin);
		printf("Ingrese la opción deseada: ");
		scanf("%d", &opcion);

    switch(opcion){ //menú de los dispositivos a reparar.
    case 1:
        {

        }
    case 2:
        {

        }
    case 3:
        {
            printf("\t Datos del producto. \n");
            printf("Ingrese fecha de reparación: " );
            scanf("%s", fecha); //no es necesario colocar: &

			//Lista de empleados:
			MostrarEmpleados();

            printf("\nIngrese el código de empleado responsable de la reparación: ");
            scanf("%d", &codigoEmpleado);
			//cuando se elija el empleado, debe aparecer nombre y apellido del mismo.



            printf("\nCostos de reparación - Hardware: ");
            scanf("%f", &costoH);

            printf("\nCosto de reparación - Software: ");
            scanf("%f", &costoS);

            precioFinal = costoH + costoS;

            printf("\t \n Datos de la empresa. \n "); //idea: ingresar nombre de la empresa dentro del archivo precargado de empresas.dat
			//lista de la empresa:

			MostrarEmpresas();
            printf("Ingrese el nombre de la empresa: ");
            scanf("%s", nombEmpresa);

            printf("Ingrese el código de la empresa");
            scanf("%d", &codigoEmpresa);
            //Se pidieron los datos, ahora se cargar los nodos.

            printf("\n");



            break;
        }
    default:{ //si existe una opción invalida ingresada, esta opción repetirá el menú.
        ingresarReparaciones();
        break;
    }
    }
}
    fclose(reparacion);
}
}
void CargarDatos()
{
    FILE *Empresas = fopen("empresas.dat", "rb");
    if(Empresas != NULL)
    {
        empresas_primero = NULL; //inicializamos las listas para poder cargarlas.
        empresas_ultimo = NULL;
        struct empresas *Edinamico = malloc(10 * sizeof(struct empresas)); //creación del vector dinámico.
        fread(Edinamico, sizeof(struct empresas), 10, Empresas); //leer y cargar datos en una variable.
        for(int i = 0; i<10; i++)
        {
            struct empresas_lista *oficina; //inicializar los nodos/listas.
            oficina = malloc(sizeof(struct empresas_lista)); //creación del primer nodo.
            //del vector lo carga a la lista.
            oficina->cod = Edinamico[i].cod;
            strcpy(oficina->cuit, Edinamico[i].cuit);
            strcpy(oficina->nombreE, Edinamico[i].nombreE);

            if(empresas_primero==NULL)
            {
                empresas_primero = oficina; //el primer nodo que se crea, se guarda en oficina.
                empresas_ultimo = oficina;
                empresas_ultimo->sig = NULL;
            }
            else
            {
                empresas_ultimo->sig = oficina;
                empresas_ultimo = oficina;
                empresas_ultimo->sig = NULL;
            }
        }
        free(Edinamico);
    }
    //Para cargar datos y poder abrir la lista del profe -> empleados
    FILE *Empleados = fopen("empleados.dat", "rb");
    if(Empleados != NULL)
    {
        empleados_primero = NULL; //inicializamos las listas para poder cargarlas.
        empleados_ultimo = NULL;
        struct empleados *Edinamico = malloc(11 * sizeof(struct empleados)); //creación del vector dinámico.
        fread(Edinamico, sizeof(struct empleados), 11, Empleados); //leer y cargar datos en una variable.
        for(int i = 0; i<11; i++)
        {
            struct empleados_lista *personas; //inicializar los nodos/listas.
            personas = malloc(sizeof(struct empleados_lista)); //creación del primer nodo.
            //del vector lo carga a la lista.
            personas->cod = Edinamico[i].cod;
            strcpy(personas->dni, Edinamico[i].dni);
            strcpy(personas->cuil, Edinamico[i].cuil);
            strcpy(personas->nombres, Edinamico[i].nombres);
            strcpy(personas->apellidos, Edinamico[i].apellidos);

            if(empleados_primero==NULL)
            {
                empleados_primero = personas; //el primer nodo que se crea, se guarda en personas.
                empleados_ultimo = personas;
                empleados_ultimo->sig = NULL;
            }
            else
            {
                empleados_ultimo->sig = personas;
                empleados_ultimo = personas;
                empleados_ultimo->sig = NULL;
            }
        }
        free(Edinamico);
    }
    else
    {
        printf("Error de apertura. \n");
    }


}



void MostrarEmpresas(){
    int counter=0; //contador para enumerar empresas
    struct empresas_lista *recordar = empresas_primero; //Recordar la primera posición.
    //mostrar contenido de una lista (Estricto)
    while(empresas_primero!=NULL){
            counter++;
        //printf("%d \n Código de empresas: %d \n CUIT: %s \n Razón Social: %s \n\n", counter, empresas_primero->cod, empresas_primero->cuit, empresas_primero->nombreE);
        printf("%d. %s\n", counter, empresas_primero->nombreE);
        empresas_primero=empresas_primero->sig; //salta a la siguiente empresa.
    }
    empresas_primero=recordar;
}

void MostrarEmpleados(){
    int counter=0; //contador para enumerar empresas
    struct empleados_lista *recordar = empleados_primero; //Recordar la primera posición.
    //mostrar contenido de una lista (Estricto)
    while(empleados_primero!=NULL){
            counter++;
        printf("%d \n Código: %d \n DNI: %s \n CUIL: %s \n Nombres: %s \n Apellidos: %s \n\n", counter, empleados_primero->cod, empleados_primero->dni, empleados_primero->cuil, empleados_primero->nombres, empleados_primero->apellidos);
        empleados_primero=empleados_primero->sig; //salta a la siguiente empresa.
    }
    empleados_primero=recordar;
}

//hacer lo mismo por empleado.
char *mostrarNombreEmpresa(int i)
{
    char *nombre = (char*)malloc(50*sizeof(char));

    struct empresas_lista *recordar = empresas_primero;

    while(empresas_primero != NULL)
    {
        if (empresas_primero->cod == i)
        {
            strcpy(nombre, empresas_primero->nombreE);
            break;
        }
        empresas_primero = empresas_primero->sig;
    }
    empresas_primero = recordar;
    return nombre;
}

int main()
{
    setlocale(LC_ALL, "");
    CargarDatos();
    int opcion=0;
    while(opcion != 8){
        system("cls");
        fflush(stdin);
        printf("Menu \n");
        printf("1 - Ingresar reparaciones. \n");
        printf("2 - Buscar una reparación segun el tipo de dispositivo \n");
        printf("3 - Buscar la reparacion con el mayor precio final \n");
        printf("4 - Mostrar las reparaciones realizadas por un empleado especifico \n");
        printf("5 - Mostrar las reparaciones correspondientes a una sola empresa \n");
        printf("6 - Mostrar las reparaciones realizadas en una fecha \n");
        printf("7 - Almacenar todas las reparaciones \n.");
        printf("8 - Salir de programa\n");
        printf("Seleccione una opcion : ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1:
                {
                    ingresarReparaciones();
                    break;
                }
        }
    }
    int pedir = 0;

    MostrarEmpresas();
    printf("\n>> Digite una empresa: ");
    scanf("%d", &pedir);

    printf("\n- La empresa que usted pidió es: %s", mostrarNombreEmpresa(pedir));

    MostrarEmpleados();
}
