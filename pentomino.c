#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "pentomino.h"

void update_events(char* keys, int *quit, s_piece *p)
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
    case SDL_MOUSEBUTTONDOWN:
      switch (event.button.button){
      case SDL_BUTTON_LEFT:
	deplacer(&event, p);
	break;
      default:
	break;
      }
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

void lire_fichier(char *f, s_grille *g, s_piece *pieces)
{
  FILE* fichier = NULL;
  int i;
  char c;
  point2d p;
  p.x=0;
  p.y=0;
  g->pos=malloc(1*sizeof(point2d));
  g->taille=0;
  fichier = fopen(f, "r");
  c=fgetc(fichier);
  if (fichier != NULL)
    {
      while (c != EOF) //tant qu'on est pas à la fin du fichier
	{
	  if(c == '#') //si c est un diese, on avanc d'un sur les colonns
	    {
	      g->taille++;
	      g->pos=realloc(g->pos,g->taille*sizeof(point2d));
	      g->pos[g->taille-1]=p;
	      p.x++;
	    }
	  
	  else if(c == ' ')
	    {
	      p.x++;
	    }

	  else if(c == '\n') //si c est un retour à la ligne, on avance d'un sur les lignes
	    { 
	      p.x=0;
	      p.y++;
	    }
	  
	   else if(c =='b')
	    {
	      lire_fichier_piece(fichier, pieces);
	      break;
	      }
	  else //si c'est autre chose
	    {
	      p.x++;
	    }
	  c=fgetc(fichier); //on avance sur le caractère d'après
	}
    }
  else
    printf("File didnt load\n");
  fclose(fichier);
  for (i=0;i<g->taille;i++) //je fait un test printf des coordonnées de la grille
    {				
      printf("( %d %d )\n", g->pos[i].x, g->pos[i].y);
      printf("\n");
    }
}

void lire_fichier_piece(FILE *fichier, s_piece *pieces)
{
  int nb=0;
  point2d p;
  char c;
  c=fgetc(fichier);
  p.x=0;
  p.y=210;
  pieces[nb].pos=malloc(sizeof(point2d));
  pieces[nb].nbpiece=1;
  pieces[nb].taille=0;
  if (fichier != NULL)
    {
      while (c != EOF)
	{
	  if (c == '#') //si c'est un # on incrémente la largeur de la piece de 1 et on met la position de la piece à 1 et on passe à la position suivante
	    {
	      pieces[nb].taille++;
	      pieces[nb].pos=realloc(pieces[nb].pos,pieces[nb].taille*sizeof(point2d));
	      pieces[nb].pos[pieces[nb].taille-1]=p;
	      p.x+=30;
	    }
	  else if (c == ' ') //si c'est un espace on incrémente la largeur de la piece de 1 et on met la position de la piece a 0 et on passe à la position suivante
	    {
	      p.x+=30;
	    }
	  else if (c == '\n') //si c'est un retour à la ligne on reset la largeur, on incrémente la hauteur et on reset notre compteur de colonne
	    {
	      p.x=210*nb;
	      p.y+=30;
	    }
	  else if (c == 'r')
	    {
	      nb++;
	      pieces[nb].pos=malloc(sizeof(point2d));
	      pieces[nb].nbpiece++;
	      pieces[nb].taille=0;
	      p.x=210*nb;
	      p.y=210;
	    }
	  c=fgetc(fichier);
	}
	}
  else
    printf("File didn't load");
	}

void afficher_grille(s_grille *g, SDL_Surface * screen, SDL_Surface * carresp)
{
  int i;
  s_sprite * s=malloc(sizeof(s_sprite));
  s->carre = carresp;
  s->sprite.x=0;
  s->sprite.y=0;
  s->sprite.w=30;
  s->sprite.h=30;
  for(i=0; i<g->taille; i++)
  { 
    s->pos.x=g->pos[i].x*30;
    s->pos.y=g->pos[i].y*30;
    SDL_BlitSurface(s->carre, &s->sprite, screen, &s->pos);
  }
  free(s);
}

void afficher_piece(s_piece *p, SDL_Surface * screen, SDL_Surface * carresp)
{
  int i,j;
  s_sprite * s=malloc(sizeof(s_sprite));
  s->carre = carresp;
  s->sprite.x=0;
  s->sprite.y=0;
  s->sprite.w=30;
  s->sprite.h=30;
  for (i=0;i<5;i++)
    {
      for (j=0;j<p[i].taille;j++)
	{
	  s->pos.x=p[i].pos[j].x;
	  s->pos.y=p[i].pos[j].y;
	  SDL_BlitSurface(s->carre, &s->sprite, screen, &s->pos);
	}
    }
  free(s);
	  
}

void rdroite(s_piece *p)
{

}

void rgauche(s_piece *p)
{

}

s_hitbox hitbox_piece(point2d *p)
{
  s_hitbox hit;
  int i;
  hit.minx=p[0].x;
  hit.miny=p[0].y;
  hit.maxx=p[0].x;
  hit.maxy=p[0].y;
  for (i=0;i<5;i++)
    {
      if (p[i].x>hit.maxx){
	hit.maxx=p[i].x;
      }
      if (p[i].y>hit.maxy){
	hit.maxy=p[i].y;
      }
    }
  printf("( %d, %d, %d, %d)\n",hit.minx,hit.maxx,hit.miny,hit.maxy);
  return hit;
}




void deplacer(SDL_Event *event, s_piece *p)
{
  int i,j;
  s_hitbox hit;
  for (i=0;i<5;i++)
    {
      hit=hitbox_piece(p[i].pos);
      if (event->button.x>=hit.minx && event->button.y>=hit.miny && event->button.x<=hit.maxx && event->button.y<=hit.maxy)
	{
	  for (j=0;j<5;j++)
	    {
	      p[i].pos[j].x+=10;
	      p[i].pos[j].y+=10;
	      printf("( %d, %d )\n",p[i].pos[j].x,p[i].pos[j].y);
	    }
	}
    }
}



/*int select_piece(s_piece *p, int x, int y)
{

  int i,j;
  int sel;
  sel=-1;
  for(i=0; i<10; i++)
    {
      for(j=0; j<5; j++)
	{
	  if ((p[i].pos[j].x==posdep.x)&&(p[i].pos[j].y==posdep.y)){
	    sel=i;
	  }
	}
    }
    return sel;
    }*/
