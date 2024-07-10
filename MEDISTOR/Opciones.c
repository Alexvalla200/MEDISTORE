#include "Prototipos.h"
#include <stdio.h>
#include <string.h>
void Opcion_Principal() {
    printf("\n-----------Menu Principal-----------\n");
    printf("---------Medicamentos----------\n");
    printf("1.- Ingresar \n");
    printf("2.- Modificar \n");
    printf("3.- Eliminar \n");
    printf("4.- Consultar \n");
    printf("5.- Listado Medicamentos \n");
    printf("-----------Clientes-----------\n");
    printf("6.- Ingresar \n");
    printf("7.- Modificar \n");
    printf("8.- Consultar \n");
    printf("9.- Listado Clientes \n");
    printf("----------Facturacion----------\n");
    printf("10.- Comprar y Consumidor Final \n");
    printf("11.- Comprar y Facturar \n");
    printf("12.- Buscar Factura \n");
    printf("13.- Listado Facturas \n");
    printf("14.- Salir\n");
}

void ingresarTrabajador(char nombre[MAXIMO], char clave[MAXIMO]) {
    printf("---------Bienvenido a MediStor----------\n");
    printf("Ingrese su nombre: ");
    scanf("%s", nombre);
    do {
        printf("Ingrese contrasena de acceso: ");
        scanf("%s", clave);
        if (strcmp(clave, CONTRASEÑA) != 0) {
            printf("Contrasena incorrecta. Intente de nuevo.\n");
        }
    } while (strcmp(clave, CONTRASEÑA) != 0);
}
