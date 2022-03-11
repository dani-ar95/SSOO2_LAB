#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int nota = 3;
    FILE *txt = fopen("./estudiantes/nota_necesaria.txt", "w");
    fprintf(txt, "La nota que debes obtener en este nuevo examen para superar la prueba es %d\n", 10 - nota);
    fclose(txt);

    FILE *text = fopen("./estudiantes/nota_necesaria.txt", "a");
    fprintf(text, "Cagaste man");
    fclose(text);
}