#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "pentomino.h"

void update_events(char* keys, int *quit)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch (event.type) {
      /* close button clicked */
    case SDL_QUIT:
      *quit = 1;
      break;
    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;
    /* handle the keyboard */
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_ESCAPE:
      case SDLK_q:
	*quit = 1;
	break;
      default:
	break;
      }
      keys[event.key.keysym.sym] = 1;
      break;
    }
  }
}

void handle_events(char* keys, t_piece* p)
{
  /*  switch(event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      switch(event.button.button)
	{
	case SDL_BUTTON_LEFT:
	  SDL_GetMouseState(p->pos.x,p->pos.y);
	}
	}*/
}

void rdroite(t_piece *p)
{

}

void rgauche(t_piece *p)
{

}

void deplacer(t_piece *p)
{

}

void lire_fichier(char * f)
{
    FILE* fichier = NULL;

    char * forme = malloc(25*sizeof(char));
    int i,j;

    fichier = fopen(f, "r");
 
    if (fichier != NULL)
    {
        while (fgets(forme, 25, fichier) != NULL)
	{    
	  //fgets(forme,11,fichier);
	  printf("%s", forme);
	}
        fclose(fichier);
    }
}

