#include <stdio.h>
#include <string.h>
#include "Prototipos.h"
#include "lectura.h"

void Ingresar_Medicamentos(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    FILE *archivo = fopen("medicamentos.txt", "r+");
    if (archivo == NULL) {
        archivo = fopen("medicamentos.txt", "w+");
        if (archivo == NULL) {
            printf("No se pudo crear el archivo.\n");
            return;
        }
    }

    // Obtener el último número de medicamento
    int ultimo_numero = 0;
    char linea[100];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (sscanf(linea, "Medicamento %d:", &ultimo_numero) == 1) {
            // No hacer nada, solo actualizar ultimo_numero
        }
    }

    fseek(archivo, 0, SEEK_END);

    printf("\nIngreso de Stock:\n");
    int Num = leerEnteroPositivo("Cuantos medicamentos se va a ingresar: ");

    for (int i = 0; i < Num; i++) {
        printf(" Medicamento %d :\n", ultimo_numero + i + 1);
        
        int indice = *Num_med; // Utilizar una variable separada para el índice

        while (1) {
            printf("Nombre: ");
            getchar(); 
            fgets(Name_med[indice], MAXIMO, stdin);
            Name_med[indice][strcspn(Name_med[indice], "\n")] = '\0';  
            
            int repetido = 0;
            for (int j = 0; j < *Num_med; j++) {
                if (strcmp(Name_med[j], Name_med[indice]) == 0) {
                    repetido = 1;
                    break;
                }
            }
            
            if (repetido) {
                printf("El nombre del medicamento ya existe. Por favor, ingrese un nombre diferente.\n");
            } else {
                break;
            }
        }
        
        cant[indice] = leerEnteroPositivo("Cantidad: ");
        precio[indice] = leerFlotantePositivo("Precio unitario: ");
        descuento[indice] = leerEnteroEntre("Porcentaje Descuento (Ingrese 0 si no lo tiene): ", 0, 100);
       
        fprintf(archivo, "Medicamento %d:\n", ultimo_numero + i + 1);
        fprintf(archivo, "Nombre: %s\n", Name_med[indice]);
        fprintf(archivo, "Cantidad: %d\n", cant[indice]);
        fprintf(archivo, "Precio unitario: %.2f\n", precio[indice]);
        fprintf(archivo, "Porcentaje Descuento: %.2f\n", descuento[indice]);
    
        (*Num_med)++; // Incrementar el contador de medicamentos
    }

    fclose(archivo);
}


void Modificar_Medicamentos(int Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    printf("Ingrese el numero del medicamento a modificar: ");
    int num;
    scanf("%d", &num);
    if (num <= 0 || num > Num_med) {
        printf("Numero de medicamento no valido.\n");
        return;
    }
    num--; 

    FILE *archivo = fopen("medicamentos.txt", "r+");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    // Verificar si el medicamento existe
    int existe = 0;
    char linea[100];
    int ultimo_numero;
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (sscanf(linea, "Medicamento %d:", &ultimo_numero) == 1 && ultimo_numero == num + 1) {
            existe = 1;
            break;
        }
    }
    if (!existe) {
        printf("Numero de medicamento no valido.\n");
        fclose(archivo);
        return;
    }

    // Modificar el medicamento
    printf("Nombre actual: %s\n", Name_med[num]);
    printf("Nuevo nombre (deje vacio para no cambiar): ");
    getchar();
    char nuevoNombre[MAXIMO];
    fgets(nuevoNombre, MAXIMO, stdin);
    if (strcmp(nuevoNombre, "\n") != 0) {
        nuevoNombre[strcspn(nuevoNombre, "\n")] = '\0';
        strcpy(Name_med[num], nuevoNombre);
    }

    printf("Cantidad actual: %d\n", cant[num]);
    printf("Nueva cantidad (deje vacio para no cambiar): ");
    int nuevaCantidad;
    scanf("%d", &nuevaCantidad);
    if (nuevaCantidad > 0) {
        cant[num] = nuevaCantidad;
    }

    printf("Precio unitario actual: %.2f\n", precio[num]);
    printf("Nuevo precio unitario (deje vacio para no cambiar): ");
    float nuevoPrecio;
    scanf("%f", &nuevoPrecio);
    if (nuevoPrecio > 0) {
        precio[num] = nuevoPrecio;
    }

    printf("Porcentaje Descuento actual: %.2f\n", descuento[num]);
    printf("Nuevo porcentaje Descuento (deje vacio para no cambiar): ");
    int nuevoDescuento;
    scanf("%d", &nuevoDescuento);
    if (nuevoDescuento >= 0 && nuevoDescuento <= 100) {
        descuento[num] = nuevoDescuento;
    }

    // Cerrar el archivo para leer
    fclose(archivo);

    // Abrir el archivo para escribir
    archivo = fopen("medicamentos.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < Num_med; i++) {
        fprintf(archivo, "Medicamento %d:\n", i + 1);
        fprintf(archivo, "Nombre: %s\n", Name_med[i]);
        fprintf(archivo, "Cantidad: %d\n", cant[i]);
        fprintf(archivo, "Precio unitario: %.2f\n", precio[i]);
        fprintf(archivo, "Porcentaje Descuento: %.2f\n", descuento[i]);
    }

    fclose(archivo);
}

void Eliminar_Medicamentos(int *Num_med, char Name_med[][MAXIMO], int cant[], float precio[], float descuento[]) {
    printf("Ingrese el numero del medicamento a eliminar: ");
    int num;
    scanf("%d", &num);
    if (num <= 0 || num > *Num_med) {
        printf("Numero de medicamento no valido.\n");
        return;
    }
    num--;

    for (int i = num; i < *Num_med - 1; i++) {
        strcpy(Name_med[i], Name_med[i + 1]);
        cant[i] = cant[i + 1];
        precio[i] = precio[i + 1];
        descuento[i] = descuento[i + 1];
    }
    (*Num_med)--;

    FILE *archivo = fopen("medicamentos.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para escribir.\n");
        return;
    }

    for (int i = 0; i < *Num_med; i++) {
        fprintf(archivo, "Medicamento %d:\n", i + 1);
        fprintf(archivo, "Nombre: %s\n", Name_med[i]);
        fprintf(archivo, "Cantidad: %d\n", cant[i]);
        fprintf(archivo, "Precio unitario: %.2f\n", precio[i]);
        fprintf(archivo, "Porcentaje Descuento: %.2f\n", descuento[i]);
    }

    fclose(archivo);
}

void Consultar_Medicamentos(char Name_med[][MAXIMO], char Buscar[], int nombre, int cantidades[], float precios[], float descuentos[]) {
    printf("Ingrese el nombre a buscar: ");
    getchar();
    fgets(Buscar, nombre, stdin);
    Buscar[strcspn(Buscar, "\n")] = '\0';

    FILE *archivo = fopen("medicamentos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    char nombreMedicamento[MAXIMO];
    int cantidad;
    float precio, descuento;
    int encontrado = 0;

    while (fscanf(archivo, "Medicamento %*d:\n") != EOF) {
        fscanf(archivo, "Nombre: %[^\n]\n", nombreMedicamento);
        fscanf(archivo, "Cantidad: %d\n", &cantidad);
        fscanf(archivo, "Precio unitario: %f\n", &precio);
        fscanf(archivo, "Porcentaje Descuento: %f\n", &descuento);

        if (strcmp(nombreMedicamento, Buscar) == 0) {
            printf("Encontrado\n");
            mostrarBuscar(nombreMedicamento, cantidad, precio, descuento);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("No Encontrado\n");
    }

    fclose(archivo);
}



void mostrarBuscar(char* nombre, int cantidad, float precio, float descuento) {
    float precioFinal = precio * (1 - descuento / 100);
    printf("%-15s %8s %10s %11s %15s\n", "Nombre", "Cantidad", "Precio", "Descuento", "Precio Final");
    printf("------------------------------------------------------------------------\n");
    printf("%-15s %8d %10.2f %10.2f%% %15.2f\n", nombre, cantidad, precio, descuento, precioFinal);
}

void Lista_Medicamentos() {
    FILE *archivo = fopen("medicamentos.txt", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo para leer.\n");
        return;
    }

    char nombre[MAXIMO];
    int cantidad, numero;
    float precio, descuento;

    printf("\n---------------------- Informacion de Medicamentos ----------------------\n");
    printf("%-8s %-15s %8s %10s %11s %10s\n", "Numero", "Nombre", "Cantidad", "Precio", "Descuento", "Precio Final");
    printf("----------------------------------------------------------------------------\n");

    while (fscanf(archivo, "Medicamento %d:\n", &numero) == 1) {
        fscanf(archivo, "Nombre: %[^\n]\n", nombre);
        fscanf(archivo, "Cantidad: %d\n", &cantidad);
        fscanf(archivo, "Precio unitario: %f\n", &precio);
        fscanf(archivo, "Porcentaje Descuento: %f\n", &descuento);

        float precioFinal = precio * (1 - descuento / 100);
        printf("%-8d %-15s %8d %10.2f %10.2f%% %10.2f\n", numero, nombre, cantidad, precio, descuento, precioFinal);
    }

    fclose(archivo);
}