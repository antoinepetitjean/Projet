#include <stdlib.h>
#include <stdio.h>
//#include <string.h>

 
int main(int argc, char *argv[])

{

    FILE* fichier = NULL;

    char * forme = malloc(20*sizeof(char));
    int i,j;

    fichier = fopen("pentomino.txt", "r");

 

    if (fichier != NULL)

    {

        while (fgets(forme, 11, fichier) != NULL)
	{
	    
	  //fgets(forme,11,fichier);
	  printf("%s", forme);

	}

        fclose(fichier);

    }

 

    return 0;

}
