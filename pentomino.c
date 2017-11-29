#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "pentomino.h"

void update_events(char* keys, int *quit,s_grille *g, s_piece *p)
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
	//select_piece(&event, p);
	arrondir(p);
	if(colision(p)==0)
	{
	  select_piece(&event, p);
	}
	*quit= victoire(g,p);
	break;
      default:
	break;
      }
    case SDL_MOUSEMOTION:
      deplacer(&event,p);
      break;
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
	      p.x+=30;
	    }
	  
	  else if(c == ' ')
	    {
	      p.x+=30;
	    }

	  else if(c == '\n') //si c est un retour à la ligne, on avance d'un sur les lignes
	    { 
	      p.x=0;
	      p.y+=30;
	    }
	  
	   else if(c =='b')
	    {
	      lire_fichier_piece(fichier, pieces);
	      break;
	      }
	  else //si c'est autre chose
	    {
	      p.x+=30;
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
  pieces[nb].select=0;
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
	      pieces[nb].select=0;
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
    s->pos.x=g->pos[i].x;
    s->pos.y=g->pos[i].y;
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
  for (i=0;i<count_piece(p);i++)
    {
      for (j=0;j<p[i].taille;j++)
	{
	  s->pos.x=p[i].pos[j].x/* - (p[i].pos[j].x %30)*/;
	  s->pos.y=p[i].pos[j].y/* - (p[i].pos[j].y %30)*/;
	  
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

void arrondir(s_piece * p)
{
  int i,j,minx,miny;
  for (i=0;i<count_piece(p);i++)
    {
      minx=p[i].pos[0].x;
      miny=p[i].pos[0].y;
      for (j=1; j<p[i].taille; j++)
      {
	if(p[i].pos[j].x <minx)
	  minx=p[i].pos[j].x;
	
	if(p[i].pos[j].y <miny)
	  miny=p[i].pos[j].y;
      }
      
      if(minx<0)
      {
	for (j=0; j<p[i].taille; j++)
	{
	  p[i].pos[j].x = p[i].pos[j].x - minx;
	}
      }
      
      if(miny<0)
      {
	for (j=0; j<p[i].taille; j++)
	{
	  p[i].pos[j].y = p[i].pos[j].y - miny;
	}
      }
      
      for (j=0; j<p[i].taille; j++)
      {
	
	
	if((p[i].pos[j].x %30)<15)
	  p[i].pos[j].x = p[i].pos[j].x - (p[i].pos[j].x %30);
	else
	  p[i].pos[j].x = p[i].pos[j].x + (30-p[i].pos[j].x %30);
	
	if((p[i].pos[j].y %30)<15)
	  p[i].pos[j].y = p[i].pos[j].y - (p[i].pos[j].y %30);
	else
	  p[i].pos[j].y = p[i].pos[j].y + (30-p[i].pos[j].y %30);
      }
      
    }
}

s_hitbox hitbox_piece(point2d p)
{
  s_hitbox hit;
  hit.minx=p.x;
  hit.miny=p.y;
  hit.maxx=p.x+30;
  hit.maxy=p.y+30;
  printf("( %d, %d, %d, %d)\n",hit.minx,hit.maxx,hit.miny,hit.maxy);
  return hit;
}




void select_piece(SDL_Event *event, s_piece *p)
{
  int i,j;
  s_hitbox hit;
  for (i=0;i<count_piece(p);i++)
    {
      for (j=0; j<p[i].taille; j++)
      {
	hit=hitbox_piece(p[i].pos[j]);
	if (event->button.x>=hit.minx && event->button.y>=hit.miny && event->button.x<=hit.maxx && event->button.y<=hit.maxy)
	  {
	    p[i].select= !p[i].select;
	    break;
	  }
      }
    }
}

void deplacer(SDL_Event *event, s_piece *p)
{
  int i,j;
  //s_hitbox hit;
  for (i=0;i<count_piece(p);i++)
    {
    //  hit=hitbox_piece(p[i].pos);
      if (p[i].select)
	{
	  for (j=0;j<p[i].taille;j++)
	    {
	      p[i].pos[j].x += event->motion.xrel;
	      p[i].pos[j].y += event->motion.yrel;
	      //printf("( %d, %d )\n",p[i].pos[j].x,p[i].pos[j].y);
	    }
	}
    }
}

int colision(s_piece *p)
{
  int i,j,k,l,col,nbp;
  nbp=count_piece(p);
  col=0;
  for(i=0; i<nbp;i++)
  {
    for(j=0; j<p[i].taille; j++)
    {
      for(k=i+1; k<nbp; k++)
      {
	for(l=0; l<p[i].taille; l++)
	{
	  if(p[i].pos[j].x==p[k].pos[l].x && p[i].pos[j].y==p[k].pos[l].y)
	  {
	    col=1;
	    break;
	  }
	}
      }
    }
  }
  return col;
}



int victoire(s_grille *g, s_piece *p)
{
  int i,j,k,trouve;
  for(i=0; i<g->taille; i++)
  {
    trouve=0;
    for(j=0; j<count_piece(p); j++)
    {
      for(k=0; k<p[j].taille; k++)
      {
	if(g->pos[i].x==p[j].pos[k].x && g->pos[i].y==p[j].pos[k].y)
	{
	  trouve=1;
	  break;
	}
      }
    }
    if(trouve==0)
      break;
  }
  return trouve;
}


int count_piece(s_piece *p)
{
  int i,count;
  count=0;
  i=0;
  while(p[i].pos!=NULL)
  {
    count++;
    i++;
  }
  return count;
}
  
  