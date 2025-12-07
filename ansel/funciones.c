#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu()
{
    int opc;
    printf("\n========== SISTEMA DE BIBLIOTECA ==========\n");
    printf("1. Agregar un libro\n");
    printf("2. Mostrar lista de libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar el estado de un libro\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf("==========================================\n");
    opc = leerOpcion(6);
    return opc;
}

void leerCadena(char *cadena, int n)
{
    fflush(stdin);
    fgets(cadena, n, stdin);
    int len = strlen(cadena) - 1;
    if (cadena[len] == '\n') {
        cadena[len] = '\0';
    }
}

// Valida que el ID sea único
int idExiste(libro *libros, int *cont, int id)
{
    for (int i = 0; i < *cont; i++) {
        if (libros[i].id == id) {
            return 1; // ID existe
        }
    }
    return 0; // ID no existe
}

// Convierte una cadena a minúsculas
void convertirAMinusculas(char *cadena)
{
    for (int i = 0; cadena[i] != '\0'; i++) {
        if (cadena[i] >= 'A' && cadena[i] <= 'Z') {
            cadena[i] = cadena[i] + 32;
        }
    }
}

// Valida que el estado sea válido
int validarEstado(int estado)
{
    return (estado == 0 || estado == 1);
}

// Función para validar entrada entera positiva con rango
int leerEnteroPositivo(const char *mensaje, int min, int max)
{
    int valor;
    int resultado;
    char buffer[50];
    int valido = 0;
    
    while (!valido) {
        printf("%s", mensaje);
        
        // Limpiar buffer
        fflush(stdin);
        
        // Leer como string para validar entrada
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error al leer entrada. Intente nuevamente.\n");
        } else {
            // Intentar convertir a entero
            resultado = sscanf(buffer, "%d", &valor);
            
            // Validar que sea un número entero válido
            if (resultado != 1) {
                printf("Error: Ingrese un número entero válido.\n");
            } else if (valor < 0) {
                // Validar que sea positivo
                printf("Error: El valor no puede ser negativo.\n");
            } else if (valor < min || valor > max) {
                // Validar rango
                printf("Error: El valor debe estar entre %d y %d.\n", min, max);
            } else {
                // Validación exitosa
                valido = 1;
            }
        }
    }
    
    return valor;
}

// Función para validar opción de menú
int leerOpcion(int max)
{
    int opcion;
    char buffer[50];
    int resultado;
    int valido = 0;
    
    while (!valido) {
        printf(">> ");
        
        fflush(stdin);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Error al leer entrada. Intente nuevamente.\n");
        } else {
            resultado = sscanf(buffer, "%d", &opcion);
            
            if (resultado != 1) {
                printf("Error: Ingrese un número válido entre 1 y %d.\n", max);
            } else if (opcion < 1 || opcion > max) {
                printf("Error: Opción inválida. Seleccione entre 1 y %d.\n", max);
            } else {
                valido = 1;
            }
        }
    }
    
    return opcion;
}

// Agrega un nuevo libro a la biblioteca
void agregarlibro(libro *libros, int *cont)
{
    // Validar que no se hayan alcanzado los 10 libros máximos
    if (*cont >= 10) {
        printf("\nError: No se pueden agregar más de %d libros\n\n", 10);
        return;
    }
    
    printf("\n--- Agregar Nuevo Libro ---\n");
    
    // Leer ID con validación
    int id;
    int idValido = 0;
    
    while (!idValido) {
        id = leerEnteroPositivo("Ingrese el ID del libro (número positivo único): ", 1, 999999);
        
        // Validar que el ID sea único
        if (idExiste(libros, cont, id)) {
            printf("Error: El ID %d ya existe en la biblioteca. Intente con otro ID.\n", id);
        } else {
            idValido = 1;
        }
    }
    
    libros[*cont].id = id;
    
    printf("Ingrese el título del libro (máx 100 caracteres): ");
    leerCadena(libros[*cont].titulo, 101);
    
    printf("Ingrese el autor del libro (máx 50 caracteres): ");
    leerCadena(libros[*cont].autor, 51);
    
    // Leer año de publicación con validación
    libros[*cont].aniopublicacion = leerEnteroPositivo(
        "Ingrese el año de publicación (ej: 2023): ", 1000, 2100);
    
    // Leer estado con validación (0 = Disponible, 1 = Prestado)
    libros[*cont].estado = leerEnteroPositivo(
        "Ingrese el estado del libro (0=Disponible, 1=Prestado): ", 0, 1);
    
    (*cont)++;
    printf("Libro agregado exitosamente. Libros en la biblioteca: %d/%d\n\n", *cont, 10);
}


// Muestra la lista completa de libros en formato tabla
void mostrarlistadelibros(libro *libros, int *cont)
{
    if (*cont == 0) {
        printf("\nNo hay libros registrados en la biblioteca\n\n");
        return;
    }
    
    printf("\n");
    printf("====================================================================================\n");
    printf("|ID |Título                              |Autor              |Año |Estado         |\n");
    printf("====================================================================================\n");
    
    for (int i = 0; i < *cont; i++) {
        char *estado = libros[i].estado == 0 ? "Disponible" : "Prestado";
        printf("|%-2d |%-34s|%-18s|%-3d |%-14s|\n",
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].aniopublicacion,
               estado);
    }
    
    printf("====================================================================================\n\n");
}

// Busca un libro por título o ID
void buscarlibro(libro *libros, int *cont)
{
    if (*cont == 0) {
        printf("\nNo hay libros registrados en la biblioteca\n\n");
        return;
    }
    
    printf("\n--- Buscar Libro ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por Título\n");
    int opcion = leerOpcion(2);
    
    if (opcion == 1) {
        int id = leerEnteroPositivo("Ingrese el ID del libro: ", 1, 999999);
        
        for (int i = 0; i < *cont; i++) {
            if (libros[i].id == id) {
                char *estado = libros[i].estado == 0 ? "Disponible" : "Prestado";
                printf("\n--- Información del Libro ---\n");
                printf("ID: %d\n", libros[i].id);
                printf("Título: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Año de publicación: %d\n", libros[i].aniopublicacion);
                printf("Estado: %s\n\n", estado);
                return;
            }
        }
        printf("Error: No se encontró libro con ID %d\n\n", id);
        
    } else if (opcion == 2) {
        char titulo[100];
        printf("Ingrese el título del libro a buscar: ");
        leerCadena(titulo, 100);
        
        // Convertir el título a buscar a minúsculas
        convertirAMinusculas(titulo);
        
        int encontrado = 0;
        for (int i = 0; i < *cont; i++) {
            // Crear una copia del título del libro en minúsculas
            char tituloCopia[100];
            strcpy(tituloCopia, libros[i].titulo);
            convertirAMinusculas(tituloCopia);
            
            // Buscar en la versión en minúsculas
            if (strstr(tituloCopia, titulo) != NULL) {
                if (!encontrado) {
                    printf("\n--- Resultados de la búsqueda ---\n");
                    encontrado = 1;
                }
                char *estado = libros[i].estado == 0 ? "Disponible" : "Prestado";
                printf("\nID: %d\n", libros[i].id);
                printf("Título: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Año de publicación: %d\n", libros[i].aniopublicacion);
                printf("Estado: %s\n", estado);
            }
        }
        
        if (!encontrado) {
            printf("Error: No se encontraron libros con ese título\n\n");
        } else {
            printf("\n");
        }
    }
}

// Actualiza el estado de un libro
void actualizarestadolibro(libro *libros, int *cont)
{
    if (*cont == 0) {
        printf("\nNo hay libros registrados en la biblioteca\n\n");
        return;
    }
    
    printf("\n--- Actualizar Estado de Libro ---\n");
    int id = leerEnteroPositivo("Ingrese el ID del libro: ", 1, 999999);
    
    for (int i = 0; i < *cont; i++) {
        if (libros[i].id == id) {
            char *estadoActual = libros[i].estado == 0 ? "Disponible" : "Prestado";
            printf("Estado actual: %s\n", estadoActual);
            int nuevoEstado = leerEnteroPositivo(
                "Nuevo estado (0=Disponible, 1=Prestado): ", 0, 1);
            
            libros[i].estado = nuevoEstado;
            char *estadoNuevo = libros[i].estado == 0 ? "Disponible" : "Prestado";
            printf("Estado actualizado exitosamente a: %s\n\n", estadoNuevo);
            return;
        }
    }
    
    printf("Error: No se encontró libro con ID %d\n\n", id);
}

// Elimina un libro de la biblioteca
void eliminarlibro(libro *libros, int *cont)
{
    if (*cont == 0) {
        printf("\nNo hay libros registrados en la biblioteca\n\n");
        return;
    }
    
    printf("\n--- Eliminar Libro ---\n");
    int id = leerEnteroPositivo("Ingrese el ID del libro a eliminar: ", 1, 999999);
    
    for (int i = 0; i < *cont; i++) {
        if (libros[i].id == id) {
            printf("¿Desea eliminar el libro '%s' de %s? (1.Si/2.No): ", 
                   libros[i].titulo, libros[i].autor);
            int confirmacion = leerOpcion(2);
            
            if (confirmacion == 1) {
                // Desplazar todos los libros posteriores una posición hacia atrás
                for (int j = i; j < *cont - 1; j++) {
                    libros[j] = libros[j + 1];
                }
                (*cont)--;
                printf("Libro eliminado exitosamente. Libros en la biblioteca: %d/%d\n\n", 
                       *cont, 10);
            } else {
                printf("Operación cancelada\n\n");
            }
            return;
        }
    }
    
    printf("Error: No se encontró libro con ID %d\n\n", id);
}