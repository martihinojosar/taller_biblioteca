typedef struct {
    int id;
    char titulo[100];
    char autor[50];
    int aniopublicacion;
    int estado;  
} libro;



// Funciones del menú
int menu();

// Funciones de utilidad
void leerCadena(char *cadena, int n);
int idExiste(libro *libros, int *cont, int id);
void convertirAMinusculas(char *cadena);
int leerEnteroPositivo(const char *mensaje, int min, int max);
int leerOpcion(int max);

// Funciones principales
void agregarlibro(libro *libros, int *cont);    
void mostrarlistadelibros(libro *libros, int *cont);
void buscarlibro(libro *libros, int *cont);
void actualizarestadolibro(libro *libros, int *cont);
void eliminarlibro(libro *libros, int *cont);

