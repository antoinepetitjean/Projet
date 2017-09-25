#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
//#include <string.h>

void lire_fichier(char * f)
{
    FILE* fichier = NULL;

    char * forme = malloc(20*sizeof(char));
    int i,j;

    fichier = fopen(f, "r");

 

    if (fichier != NULL)

    {

        while (fgets(forme, 11, fichier) != NULL)
	{
	    
	  //fgets(forme,11,fichier);
	  printf("%s", forme);

	}

        fclose(fichier);

    }
}

void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
	    case SDL_KEYUP:
                continuer = 0;
        }
    }
}


int main(int argc, char *argv[])

{

    /*char * f =malloc(20*sizeof(char));
    f="pentomino.txt";*/
    
    SDL_Surface *ecran = NULL;
    
    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Ma super fenêtre SDL !", NULL);
    
    // Coloration de la surface ecran en bleu-vert
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 17, 206, 112));

    SDL_Flip(ecran); /* Mise à jour de l'écran avec sa nouvelle couleur */

    pause();

    SDL_Quit();

    return EXIT_SUCCESS;
    
    //lire_fichier(f);
 

    return 0;
    
}
