#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "pentomino.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 640
#define LIGNE_FOND 15
#define COLONE_FOND 15

struct t_carre *fond[LIGNE_FOND][COLONE_FOND];

void lire_fichier(char * f)
{
    FILE* fichier = NULL;
    int i,j,ligne;
    char c;
    struct t_carre * case_bloque;//erreur ici
    case_bloque->deplacable = 0;

    fichier = fopen(f, "r");

    if (fichier != NULL)

    {
      ligne=0;
        while (fgetc(fichier) != '\n' && ligne<LIGNE_FOND)
	{
	  fseek(fichier, -1, SEEK_CUR);
	  for (i=0; i<COLONE_FOND; i++)
	  {
	    c=fgetc(fichier);
	    
	    if(c != '#')
	    {
	       //printf("#");
	      fond[ligne][i]=case_bloque;
	    }
	    
	    else if (c=='\n')
	    {
	      for(j=i;j<COLONE_FOND;j++)
	      {
		fond[ligne][j]=case_bloque;
	      }
	      break;
	    }
	    
	   /* else
	    {
	       //printf(" ");
	      fond[ligne][i]=NULL;
	    }*/
	    
	  }
	  ligne++;
	  //printf("\n");

	}

        fclose(fichier);
	free(case_bloque);
    }
}

///***************pour tester le remplissage du tableau fond********************************///
void affiche_fond()
{
  int i,j;
  for (i=0;i<LIGNE_FOND;i++){
    for (j=0;j<COLONE_FOND;j++){
      if(fond[i][j]!=NULL) printf("1");
    }
    printf("\n");
  }
}
///****************************************************************************************///

int main(int argc, char *argv[])

{
  SDL_Surface *screen, *temp, *pentaminosp;
  t_carre pentomino;
  SDL_Init(SDL_INIT_VIDEO);
  
  //t_piece * liste_des_pieces = malloc(sizeof(t_piece));

  SDL_WM_SetCaption("Pentamino", "LUL");

  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  temp = SDL_LoadBMP("Untitled-1.bmp");
  pentaminosp = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  pentomino.pos.x = (SCREEN_WIDTH - 450) /2;
  pentomino.pos.y = (SCREEN_HEIGHT - 450) /2;
  pentomino.sprite.y = 0;
  pentomino.sprite.w = 450;
  pentomino.sprite.h = 450;
  pentomino.sprite.x = 0;

  int gameover = 0;
  char key[SDLK_LAST] = {0};
  lire_fichier("pentomino.txt");

  while (!gameover)
    {
      update_events(key, &gameover);
      SDL_BlitSurface(pentaminosp, &pentomino.sprite, screen, &pentomino.pos);
      SDL_UpdateRect(screen, 0, 0, 0, 0);
      SDL_ShowCursor(1);
    }
  //free(&liste_des_pieces);
  SDL_FreeSurface(pentaminosp);
  SDL_Quit();

  return 0;
    
}
