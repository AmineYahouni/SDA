# include<stdio.h>
# include<malloc.h>
#include<time.h>
#include "analyzer.h"
#include "math.h"

# define F 0
# define T 1   // des constantes associÈes ‡ la hauteur

struct Noeud
{
 int Info;
 int Signe;
 struct  Noeud *fils_gauche; /* fils gauche (inferieur au noeud) */
 struct  Noeud *fils_droit;  /* fils droit (superieur au noeud) */
};

struct Noeud *Arbre_Binaire (int , struct Noeud *, int *);
void Output(struct Noeud *, int );
struct  Noeud *Balance_Pronfond_Droite(struct Noeud *, int *);
struct Noeud *Balance_Pronfond_Gauche(struct Noeud *, int *);
struct Noeud *Supprimer(struct Noeud *, struct Noeud *, int *);
struct Noeud *Supprimer_Element(struct Noeud *, int , int *);

/* fonction d'insertion d'une cle dans l'arbre */

struct Noeud *  Arbre_Binaire (int Info, struct Noeud *Parent, int *H)
{
 struct Noeud *Noeud1;
 struct Noeud *Noeud2;
 if(!Parent)
 {
  Parent = (struct Noeud *) malloc(sizeof(struct Noeud));
  Parent->Info = Info;
  Parent->fils_gauche = NULL;
  Parent->fils_droit = NULL;
  Parent->Signe = 0;
  *H = T;
  return (Parent);
 }

 if(Info < Parent->Info)
 {
  Parent->fils_gauche = Arbre_Binaire (Info, Parent->fils_gauche, H);
  if(*H)
  /* Branche gauche a grandi **************/
  {
   switch(Parent->Signe)
   {
   case 1: /* pronfond droite */
    Parent->Signe = 0;
    *H = F;
    break;
   case 0: /* Balancer Arbre */
    Parent->Signe = -1;
    break;
   case -1: /* pronfond gauche */  // on calcule -1 ‡ partir du fils 
    Noeud1 = Parent->fils_gauche;
    if(Noeud1->Signe == -1)
    {
     printf("\n Rotation gauche a droite\n");
     Parent->fils_gauche= Noeud1->fils_droit;
     Noeud1->fils_droit = Parent;
     Parent->Signe = 0;
     Parent = Noeud1;
    }
    else
    {
     printf("\n Rotation a gauche  \n");
     Noeud2 = Noeud1->fils_droit;
     Noeud1->fils_droit = Noeud2->fils_gauche;
     Noeud2->fils_gauche = Noeud1;
     Parent->fils_gauche = Noeud2->fils_droit;
     Noeud2->fils_droit = Parent;
     if(Noeud2->Signe == -1)
      Parent->Signe = 1;
     else
      Parent->Signe = 0;
     if(Noeud2->Signe == 1)
      Noeud1->Signe = -1;
     else
      Noeud1->Signe = 0;
     Parent = Noeud2;
    }

    Parent->Signe = 0;
    *H = F;
   }
  }
 }

 if(Info > Parent->Info)
 {
  Parent->fils_droit = Arbre_Binaire (Info, Parent->fils_droit, H); //insertion
  if(*H)
  /* Branche droite a grandi ********************************/
  {
   switch(Parent->Signe)
   {
   case -1: /* pronfond gauche */
    Parent->Signe = 0;
    *H = F;
    break;
   case 0: /* Balancer Arbre */
    Parent->Signe = 1;
    break;

   case 1: /* Pronfond droite */
    Noeud1 = Parent->fils_droit;
    if(Noeud1->Signe == 1) // meme chose pr calcul de signe= balance!! on calcule ‡ partir d'info(nouveua Noeud)
    {
     printf("\n Rotation droite a droite \n");
     Parent->fils_droit= Noeud1->fils_gauche;
     Noeud1->fils_gauche = Parent;
     Parent->Signe = 0;
     Parent = Noeud1;
    }
    else
    {
     printf("\n Rotation droite a gauche \n");
     Noeud2 = Noeud1->fils_gauche;
     Noeud1->fils_gauche = Noeud2->fils_droit;
     Noeud2->fils_droit = Noeud1;
     Parent->fils_droit = Noeud2->fils_gauche;
     Noeud2->fils_gauche = Parent;

     if(Noeud2->Signe == 1)
      Parent->Signe = -1;
     else
      Parent->Signe = 0;
     if(Noeud2->Signe == -1)
      Noeud1->Signe = 1;
     else
      Noeud1->Signe = 0;
     Parent = Noeud2;
    }

    Parent->Signe = 0;
    *H = F;
   }
  }
 }
 return(Parent);
}

/* function Afficher */

void Output(struct Noeud *Abr,int Level)
{
 int i;
 if (Abr)
 {
  Output(Abr->fils_droit, Level+1);
  printf("\n");
  for (i = 0; i < Level; i++)
   printf("   ");
  printf("%d", Abr->Info);
  Output(Abr->fils_gauche, Level+1);
 }
}

/* Equillibrage droite ‡ l'aide des doubles rotations  */

struct Noeud * Balance_Pronfond_Droite(struct Noeud *Parent, int *H)
{
 struct Noeud *Noeud1, *Noeud2;

 switch(Parent->Signe)
 {
 case -1: 
  Parent->Signe = 0;
  break;

 case 0: 
  Parent->Signe = 1;
  *H= F;
  break;

 case 1: /* on va rebalancer droite */ // double rotation vers la droite-droite/gauche)
  Noeud1 = Parent->fils_droit;
  if(Noeud1->Signe >= 0)
  {
   printf("\n Rotation droite a droite\n");
   Parent->fils_droit= Noeud1->fils_gauche;
   Noeud1->fils_gauche = Parent;
   if(Noeud1->Signe == 0)
   {
    Parent->Signe = 1;
    Noeud1->Signe = -1;
    *H = F;
   }
   else
   {
    Parent->Signe = Noeud1->Signe = 0;
   }
   Parent = Noeud1;
  }
  else
  {
   printf("\n Rotation droite a gauche\n");
   Noeud2 = Noeud1->fils_gauche;
   Noeud1->fils_gauche = Noeud2->fils_droit;
   Noeud2->fils_droit = Noeud1;
   Parent->fils_droit = Noeud2->fils_gauche;
   Noeud2->fils_gauche = Parent;

   if(Noeud2->Signe == 1)
    Parent->Signe = -1;
   else
    Parent->Signe = 0;
   if(Noeud2->Signe == -1)
    Noeud1->Signe = 1;
   else
    Noeud1->Signe = 0;
   Parent = Noeud2;
   Noeud2->Signe = 0;
  }
 }
 return(Parent);
}

/* Equillibrage dans les profondeurs gauches  ‡ l'aide d'une double rotation*/

struct Noeud * Balance_Pronfond_Gauche(struct Noeud *Parent, int *H)
{
 struct Noeud *Noeud1, *Noeud2;

 switch(Parent->Signe)
 {
 case 1: 
  Parent->Signe = 0;
  break;

 case 0: 
  Parent->Signe = -1;
  *H= F;
  break;

 case -1: /*  Rebalance */
  Noeud1 = Parent->fils_gauche;
  if(Noeud1->Signe <= 0)
  {
   printf("\n Rotation gauche a gauche\n");
   Parent->fils_gauche= Noeud1->fils_droit;
   Noeud1->fils_droit = Parent;
   if(Noeud1->Signe == 0)
   {
    Parent->Signe = -1;
    Noeud1->Signe = 1;
    *H = F;
   }
   else
   {
    Parent->Signe = Noeud1->Signe = 0;
   }
   Parent = Noeud1;
  }
  else
  {
   printf("\n Rotation gauche a droite \n");
   Noeud2 = Noeud1->fils_droit;
   Noeud1->fils_droit = Noeud2->fils_gauche;
   Noeud2->fils_gauche = Noeud1;
   Parent->fils_gauche = Noeud2->fils_droit;
   Noeud2->fils_droit = Parent;

   if(Noeud2->Signe == -1)
    Parent->Signe = 1;
   else
    Parent->Signe = 0;

   if(Noeud2->Signe == 1)
    Noeud1->Signe = -1;
   else
    Noeud1->Signe = 0;
   Parent = Noeud2;
   Noeud2->Signe = 0;
  }
 }
 return(Parent);
}

/* Remplacer le Noeud s'il existe avec la dernier clÈ droit d'un fils gauche */

struct Noeud * Supprimer(struct Noeud *R, struct Noeud *Temp, int *H)
{
 struct Noeud *DNoeud = R;
 if( R->fils_droit != NULL)
 {
  R->fils_droit = Supprimer(R->fils_droit, Temp, H);
  if(*H)
   R = Balance_Pronfond_Gauche(R, H);
 }
 else
 {
  DNoeud = R;
  Temp->Info = R->Info;
  R = R->fils_gauche;
  free(DNoeud);
  *H = T;
 }
 return(R);
}
/* fonction de suppression de cle de l'arbre */

struct Noeud * Supprimer_Element(struct Noeud *Parent, int Info, int *H)
{
 struct Noeud *Temp;
 if(!Parent)
 {
  printf("\n La valeur de noeud n'existe pas");
  return(Parent);
 }
 else
 {
  if (Info < Parent->Info )
  {
   Parent->fils_gauche = Supprimer_Element(Parent->fils_gauche, Info, H);
   if(*H)
    Parent = Balance_Pronfond_Droite(Parent, H);
  }
  else
   if(Info > Parent->Info)
   {
    Parent->fils_droit = Supprimer_Element(Parent->fils_droit, Info, H);
    if(*H)
     Parent = Balance_Pronfond_Gauche(Parent, H);
   }
   else
   {
    Temp= Parent;
    if(Temp->fils_droit == NULL)
    {
     Parent = Temp->fils_gauche;
     *H = T;
     free(Temp);
    }
    else
     if(Temp->fils_gauche == NULL)
     {
      Parent = Temp->fils_droit;
      *H = T;
      free(Temp);
     }
     else
     {
      Temp->fils_gauche = Supprimer(Temp->fils_gauche, Temp, H);
      if(*H)
       Parent = Balance_Pronfond_Droite(Parent, H);
     }
   }
 }
 return(Parent);
}
int Menu()  
{
 int Choix;
 do
 {
  printf("             ********************************************************\n");
  printf("             *                                                      *\n");
  printf("             *      Menu Principal de l'arbre AVL                   *\n");
  printf("             *                                                      *\n");
  printf("             ********************************************************\n");
  printf("\n                 1- Ajouter un noeud");
  printf("\n                 2- Afficher l'arbre");
  printf("\n                 3- Enlever un noeud");
  printf("\n                 4- Quitter\n");
  printf("\n              *****************************************************\n");
  printf("\n\n\n\n\n\n\n\n\n\n\n\nChoix :");
  scanf("%d",&Choix);
 } while (Choix <1 || Choix >5);
 return Choix;
}
/* Function main */

int main()
{
// Analyse du temps pris par les opérations.
  analyzer_t * time_analysis = analyzer_create();
  // Analyse du nombre de copies faites par les opérations.
  analyzer_t * copy_analysis = analyzer_create();
  // Analyse de l'espace mémoire inutilisé.
  analyzer_t * memory_analysis = analyzer_create(); 
  // Mesure de la durée d'une opération.
  struct timespec before, after;
  clockid_t clk_id = CLOCK_REALTIME;

srand(time(NULL)); 




 int H;
 int Info ;
 int Choix;
 struct Noeud *Abr = (struct Noeud *)malloc(sizeof(struct Noeud));
 Abr =  NULL;
 Choix = Menu();
    while (Choix!=4)
     {
      if (Abr==NULL && Choix>1 && Choix <3)
      {
       printf("Vous devez d'abord saisir un arbre");
       printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n Appuyez sur une touche pour retourner au menu principal");      }
      else
      {if(Choix==5){
// Affichage de quelques statistiques sur l'expérience.
      printf("Total cost: %Lf\n", get_total_cost(time_analysis));
      printf("Average cost: %Lf\n", get_average_cost(time_analysis));
      printf("Variance: %Lf\n", get_variance(time_analysis));
// Sauvegarde les données de l'expérience.
  save_values(time_analysis, "../plots/dynamic_array_time_ascenAVL.plot");
     	
}
   else{    switch (Choix)
       {
        case 1 : printf("Saisir un entier (0 pour finir la saisie) : ");
           scanf("%d", &Info);
           while (Info != 0)
           {
		for(int i=0;i<100;i++){
             // Ajout d'un élément et mesure du temps pris par l'opération.
            clock_gettime(clk_id, &before);
            Abr = Arbre_Binaire (i, Abr, &H);
            clock_gettime(clk_id, &after);
             // Enregistrement du temps pris par l'opération
            analyzer_append(time_analysis, after.tv_nsec - before.tv_nsec);}
            printf(" Arbre est:\n");
                          Output(Abr, 2);
            printf("\n\n Saisir un entier (0 pour finir la saisie) : ");
            scanf("%d", &Info);
           }
           break;
           
        case 2 : printf(" Arbre est:\n");
                          Output(Abr, 2);
                          
           printf("\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
           break;
           
     case 3 : printf(" Arbre est:\n");
                          Output(Abr, 2);
                                printf("\n\n\n\nSaisir la valeur du noeud a supprimer : \n");
           scanf("%d", &Info);
           Abr = Supprimer_Element(Abr, Info, &H);
           printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nAppuyez sur une touche pour retourner au menu principal");
           break;
    }
          }}
    Choix=Menu();
     }
}
