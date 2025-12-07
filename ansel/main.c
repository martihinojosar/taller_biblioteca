#include <stdio.h>
#include "funciones.h"

int main(int argc, char *argv[])
{
    libro libros[10];
    int cont = 0;
    int opc = 0, opc2 = 0;
    
    do {
        opc = menu();
        
        switch (opc) {
            case 1:
                agregarlibro(libros, &cont);
                break;
            case 2:
                mostrarlistadelibros(libros, &cont);
                break;
            case 3:
                buscarlibro(libros, &cont);
                break;
            case 4:
                actualizarestadolibro(libros, &cont);
                break;
            case 5:
                eliminarlibro(libros, &cont);
                break;
            case 6:
                printf("\n¡Gracias por usar el sistema de biblioteca!\n\n");
                return 0;
            default:
                printf("\nOpción inválida. Por favor, intente de nuevo.\n\n");
                break;
        }
        
        if (opc != 6) {
            printf("¿Desea realizar otra operación? (1.Sí/2.No): ");
            opc2 = leerOpcion(2);
            if (opc2 != 1) {
                printf("\n¡Gracias por usar el sistema de biblioteca!\n\n");
                return 0;
            }
        }
    } while (1);
    
    return 0;
}