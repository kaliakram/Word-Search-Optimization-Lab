  /**--------------------------------------------------------**/
  /**       C o n v e r s i o n   Z vers C (Standard)        **/
  /**             Realisee par Pr D.E ZEGOUR                 **/
  /**             E S I - Alger                              **/
  /**             Copywrite 2014                             **/
  /**--------------------------------------------------------**/

  /*////////////////////////////////////////////////////////////////////////*/

  /*////////////////////////////////////////////////////////////////////////*/

  /*Second Lab by :Kouah Akram (Group 02) & Korchi Adam (Group15)*/

  /*////////////////////////////////////////////////////////////////////////*/

  /*////////////////////////////////////////////////////////////////////////*/

   
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <time.h>

  typedef int bool ;
  typedef char * string255 ;
  typedef char * string2 ;

  #define True 1
  #define False 0

  /** Implementation **\: FICHIER **/

  /* Traitement des fichiers ouverts */

  struct _Noeud
    {
      FILE * Var_fich ;
      char * Nom_fich ;
      int Sauv_pos;
      struct _Noeud *Suiv ;
    } ;

  typedef struct _Noeud * _Ptr_Noeud;

  _Ptr_Noeud  _Pile_ouverts  = NULL;

  /* Teste si un fichier est ouvert */
  _Ptr_Noeud _Ouvert ( char * Fp)
    {
      _Ptr_Noeud P;
      bool Trouv ;
      P = _Pile_ouverts; Trouv = False ;
      while ((P != NULL) && ! Trouv )
        if ( strcmp(P->Nom_fich, Fp) == 0)
        Trouv = True;
        else P = P->Suiv;
      return P;
    }

  /* Ajouter un fichier ouvert */
  void _Empiler_ouvert ( char *Fp, FILE *Fl)
    {
      _Ptr_Noeud  P ;
      P = (_Ptr_Noeud) malloc( sizeof( struct _Noeud)) ;
      P->Nom_fich = Fp;
      P->Var_fich = Fl;
      P->Suiv = _Pile_ouverts;
      _Pile_ouverts = P;
    }

  /* Supprimer un fichier ouvert et rendre son nom*/
  char * _Depiler_ouvert ( FILE *Fl)
    {
      char * Fp = malloc (100);
      _Ptr_Noeud P,  Prec  ;
      P= _Pile_ouverts;
      Prec = NULL;
      while (P->Var_fich != Fl )
        { Prec = P ; P = P->Suiv ;}
      strcpy(Fp, P->Nom_fich);
      if (Prec != NULL)
        Prec->Suiv = P->Suiv;
      else _Pile_ouverts = P->Suiv;
      free (P);
      return Fp ;
    }


  /** Fichiers **/

  typedef char _Tx[255];
  typedef string255 Typestruct1_s;
  typedef _Tx Typestruct1_s_Buf;


  /** Machine abstaite sur les fichiers **/

  void Ouvrir_s ( FILE **s , char *Fp , char * Mode )
    {
      _Ptr_Noeud P = _Ouvert(Fp);
      if ( P != NULL )
      /* Le fichier est deja ouvert */
        {
         P->Sauv_pos = ftell (P->Var_fich);
         fclose(P->Var_fich);
        }
      /* Le fichier est non ouvert */
      if ( strcmp(Mode,"A") == 0)
        *s = fopen(Fp, "r+b");
      else
        *s = fopen(Fp, "w+b");
      _Empiler_ouvert( Fp, *s);
    }

  void Fermer_s ( FILE * s )
    {
      char * Fp = malloc(100);
      _Ptr_Noeud P;
      strcpy(Fp, _Depiler_ouvert(s));
      fclose(s) ;
      /* Ya-til un fichier ouvert avec le m?me nom ?  */
      /* Si Oui, le Reouvrir a la position sauvegardee */
      P =  _Ouvert (Fp);
      if ( P != NULL)
      {
        s = fopen(P->Nom_fich, "r+b");
        fseek(s, P->Sauv_pos, 0);
      }
    }

  void Ecrireseq_s ( FILE * s, Typestruct1_s Buf  )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Ecriredir_s ( FILE * s, Typestruct1_s Buf, int N )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, (long) (N-1)* sizeof(  Typestruct1_s_Buf), 0);
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  void Lireseq_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      if (fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s) != 0) {
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
      }
    }

  void Liredir_s ( FILE * s, Typestruct1_s Buf, int N)
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
      fseek(s, (long) (N-1)* sizeof( Typestruct1_s_Buf), 0 );
      fread(&Buffer, sizeof( Typestruct1_s_Buf), 1, s);
      for(J=0; J<= strlen(Buffer); ++J)
        Buf [J] = Buffer[J]  ;
    }

  void Rajouter_s ( FILE * s, Typestruct1_s Buf )
    {
      Typestruct1_s_Buf Buffer ;
      int I, J;
     for(J=0; J<= strlen(Buf); ++J)
         Buffer[J] = Buf [J];
      fseek(s, 0, 2); /* Fin du fichier */
      fwrite(&Buffer, sizeof( Typestruct1_s_Buf), 1, s)  ;
    }

  bool Finfich_s (FILE * s)
    {
      long K = ftell(s);
      fseek(s, 0, 2); /* Fin du fichier */
      long K2 = ftell(s);   /* position a partir du debut */
      if  (K==K2)
        { fseek(s, K, 0); return 1;}
      else
        { fseek(s, K, 0); return 0;}
    }

  int Alloc_bloc_s (FILE * s)
    {
      long K;
      fseek(s, 0, 2); /* Fin du fichier */
      K = ftell(s);   /* position a partir du debut */
      K = K / sizeof (Typestruct1_s_Buf);
      K ++;
      return(K);
    }


  /** Implementation **\: ARBRE BINAIRE DE CHAINES DE CARACTERES**/

  /** Arbres de recherche binaire **/

  typedef string255 Typeelem_As   ;
  typedef struct Noeud_As * Pointeur_As ;

  struct Noeud_As
    {
      Typeelem_As  Val ;
      Pointeur_As Fg ;
      Pointeur_As Fd ;
      Pointeur_As Pere ;
     } ;

  Typeelem_As Info_As( Pointeur_As P )
    { return P->Val;   }

  Pointeur_As Fg_As( Pointeur_As P)
    { return P->Fg ; }

  Pointeur_As Fd_As( Pointeur_As P)
    { return P->Fd ; }

  Pointeur_As Pere_As( Pointeur_As P)
    { return P->Pere ; }

  void Aff_info_As ( Pointeur_As P, Typeelem_As Val)
    {
       strcpy( P->Val , Val );
    }

  void Aff_fg_As( Pointeur_As P, Pointeur_As Q)
    { P->Fg =  Q;  }

  void Aff_fd_As( Pointeur_As P, Pointeur_As Q)
    { P->Fd =  Q ; }

  void Aff_pere_As( Pointeur_As P, Pointeur_As Q)
    { P->Pere =  Q ; }

  void Creernoeud_As( Pointeur_As *P)
    {
      *P = (struct Noeud_As *) malloc( sizeof( struct Noeud_As))   ;
      (*P)->Val = malloc(255 * sizeof(string255));
      (*P)->Fg = NULL;
      (*P)->Fd = NULL;
      (*P)->Pere = NULL;
    }

  void Liberernoeud_As( Pointeur_As P)
    { free( P ) ; }


  /** Implementation **\: FILE DE ARBRES BINAIRES DE CHAINES DE CARACTERES**/
  /** Files d'attente **/

  typedef Pointeur_As Typeelem_FAs ;
  typedef  struct Filedattente_FAs * Pointeur_FAs ;
  typedef  struct Maillon_FAs * Ptliste_FAs ;

  struct Maillon_FAs
    {
      Typeelem_FAs Val ;
      Ptliste_FAs Suiv  ;
    };

  struct Filedattente_FAs
    {
      Ptliste_FAs Tete, Queue ;
    };

  void Creerfile_FAs ( Pointeur_FAs *Fil   )
    {
      *Fil = (struct Filedattente_FAs *) malloc( sizeof( struct Filedattente_FAs)) ;
      (*Fil)->Tete = NULL ;
      (*Fil)->Queue = NULL ;
    }

  bool Filevide_FAs (Pointeur_FAs Fil  )
    { return  Fil->Tete == NULL ;}

  void Enfiler_FAs ( Pointeur_FAs Fil , Typeelem_FAs Val   )
    {
      Ptliste_FAs Q;

      Q = (struct Maillon_FAs *) malloc( sizeof( struct Maillon_FAs))   ;
      Q->Val = Val ;
      Q->Suiv = NULL;
      if ( ! Filevide_FAs(Fil) )
        Fil->Queue->Suiv = Q ;
      else Fil->Tete = Q;
        Fil->Queue = Q;
    }

  void Defiler_FAs (Pointeur_FAs Fil, Typeelem_FAs *Val )
    {
      if (! Filevide_FAs(Fil) )
        {
          *Val = Fil->Tete->Val ;
          Fil->Tete =  Fil->Tete->Suiv;
        }
      else printf ("%s \n", "File d'attente vide");
    }

  /** Variables du programme principal **/
  FILE *F;
  FILE *results_single;
  FILE *results_range;

  Typestruct1_s S ;
  int I;
  int N;
  int Random;
  int Singlesearchcounter;
  int Rangesearchcounter;
  int Choice;
  string2 X;
  string2 Y;
  string2 Z;
  bool Quit;
  bool Numvalid;
  string255 Word;
  string255 Word1;
  string255 Word2;
  Pointeur_As Bst0=NULL;
  Pointeur_As Bst1=NULL;
  Pointeur_As Bst2=NULL;
  Pointeur_As Bst3=NULL;
  Pointeur_As Resultat=NULL;
  string255 _Sx;

  /** Fonctions standards **/

  int Aleanombre( int N )
    { return ( rand() % N ); }

  char  *Aleachaine ( int N )
    {
      int k;
      char  * Chaine = malloc(N+1);

      char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
      char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

      for (k=0;k<N; k++)
        switch ( rand() % 2 ){
        case 0 :  *(Chaine+k) = Chr1[rand() % 26] ; break ;
        case 1 :  *(Chaine+k) = Chr2[rand() % 26] ; break ;
        }
      Chaine[k] =  '\0' ;

      return (Chaine);
    }

  char *Caract ( string255 Ch , int I )
    {
      char *s = malloc(2);
      s[0] = Ch[I-1];
      s[1] = '\0';
      return  s;
    }

  int Max (int a, int b)
    {
      if (a > b) return(a);
      else return(b);
    }


  /** Prototypes des fonctions **/

  void Displaymenu (Pointeur_As *Bst0,Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z , bool *Quit , int *Choice , string255 *Word , Pointeur_As *Resultat , string255 *Word1 , string255 *Word2 , int *Singlesearchcounter , int *Rangesearchcounter);
  int  Cmp_string (string255 *Str1 , string255 *Str2) ;
  void Choice1 (Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z);
  Pointeur_As Insertbst (Pointeur_As *Root , string255 *Str) ;
  bool  Beginwithxyz (string255 *S , string2 *X , string2 *Y , string2 *Z) ;
  void Leftrotation (Pointeur_As *Node);
  void Rightrotation (Pointeur_As *Node);
  void Constructbst1 (Pointeur_As *Bst1 , FILE *F , string2 *X , string2 *Y , string2 *Z);
  void Constructbst2 (Pointeur_As *Bst2 , FILE *F , string2 *X , string2 *Y , string2 *Z);
  void Constructbst3 (Pointeur_As *Bst3 , FILE *F , string2 *X , string2 *Y , string2 *Z);
  void Inordertraversal (Pointeur_As *Bst);
  int  Branchlength (Pointeur_As *Bst , Pointeur_As *Node) ;
  int  Startwithxyzcount (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z) ;
  int  Startwithcharcount (Pointeur_As *Bst , string2 *Character) ;
  int  Treedepth (Pointeur_As *Bst) ;
  void Nodesxyzlevel (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z);
  void Queuelengthxyzcount (Pointeur_FAs *Queue1 , int *Length , int *Countxyz);
  Pointeur_As Singlewordsearch (Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) ;
  Pointeur_As Searchbst1 (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) ;
  Pointeur_As Searchbst2 (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) ;
  Pointeur_As Searchbst3 (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) ;
  void Rangesearch (Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z , string255 *Word1 , string255 *Word2 , int *Rangesearchcounter);
  void Rangesearchbst (Pointeur_As *Bst , string255 *Word1 , string255 *Word2 , int *Rangesearchcounter);
  Pointeur_As Searchleastgreater (Pointeur_As *Bst , string255 *Word1 , int *Rangesearchcounter) ;
  Pointeur_As Nextinorder (Pointeur_As *Node , int *Rangesearchcounter) ;
  void Constructbst0 (Pointeur_As *Bst0 , FILE *F , string2 *X , string2 *Y , string2 *Z);
   void Constructandtestbst0(Pointeur_As *Bst0 , FILE *F , string2 *X , string2 *Y , string2 *Z);


  /*////////////////////////////////////////////////////////////////////////*/
  void Displaymenu (Pointeur_As *Bst0,Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z , bool *Quit , int *Choice , string255 *Word , Pointeur_As *Resultat , string255 *Word1 , string255 *Word2 , int *Singlesearchcounter , int *Rangesearchcounter)
    {

      /** Corps du module **/
     while( ( ! *Quit )) {
      system("cls");
printf("\x1b[31m                    __  __                  \n");
printf("                   |  \\/  | ___ _ __  _   _ \n");
printf("                   | |\\/| |/ _ \\ '_ \\| | | |\n");
printf("                   | |  | |  __/ | | | |_| |\n");
printf("                   |_|  |_|\\___|_| |_|\\____|\x1b[0m\n");
       printf ( " %s", "\x1b[35m _____________________________________________________________________________________\n" ) ;    
       printf ( " %s", "|\x1b[33m1-\x1b[0mcount the number of words starting with x/y/z                                      \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m2-\x1b[0mcompute the depth of the trees                                                     \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m3-\x1b[0mperform an inorder traversal                                                       \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m4-\x1b[0mcompute and display the number of nodes starting with x/y/z in each level          \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m5-\x1b[0msearch for a single word                                                           \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m6-\x1b[0msearch for all words within a particular range                                     \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m7-\x1b[0mbuild and test bst0                                                                \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m8-\x1b[0msimulation algorithm for single word search efficiency                             \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m9-\x1b[0msimulation algorithm for range search efficiency                                   \x1b[35m|\n" ) ;
       printf ( " %s", "|\x1b[33m10-\x1b[0mexit                                                                              \x1b[35m|\n" ) ;
       printf ( " %s", "|_____________________________________________________________________________________|\n" ) ;
       printf ( " %s", "\x1b[32mplease enter your choice:" );
       scanf ( " %d", &*Choice ) ;
       if( *Choice == 1) {
        system("cls");
         Choice1 ( & *Bst1 , & *Bst2 , & *Bst3 , & *X , & *Y , & *Z ) ;
         system("pause");
         }
         
       else
         {
         if( *Choice == 2) {
          system("cls");
           printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
           printf ( " %s", "--------------------------------\n" ) ;
           printf ( " %s", "\x1b[0mdepth of the trees:\n" ) ;
           printf ( " %s", "bst1:" );
           printf ( "\x1b[32m %d \x1b[0m\n", Treedepth(&*Bst1) ) ;
           printf ( " %s", "bst2:" );
           printf ( "\x1b[32m %d \x1b[0m \n", Treedepth(&*Bst2) ) ;
           printf ( " %s", "bst3:" );
           printf ( "\x1b[32m %d \x1b[0m \n", Treedepth(&*Bst3) ) ;
           printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
           printf ( " %s", "--------------------------------\x1b[0m\n" ) ;
           system("pause");
           }
         else
           {
           if( *Choice == 3) {
            system("cls");
             printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
             printf ( " %s", "--------------------------------\x1b[32m\n" ) ;
             printf ( " %s", "inorder traversal:\x1b[0m\n" ) ;
             printf ( " %s", "\x1b[35m--------------------------------\x1b[0m \n" ) ;
             printf ( " %s", "bst1:\n" ) ;
             Inordertraversal ( & *Bst1 ) ;
             printf ( " %s", "\x1b[35m--------------------------------\x1b[0m \n" ) ;
             printf ( " %s", "bst2:\n" ) ;
             Inordertraversal ( & *Bst2 ) ;
             printf ( " %s", "\x1b[35m--------------------------------\x1b[0m \n" ) ;
             printf ( " %s", "bst3:\n" ) ;
             Inordertraversal ( & *Bst3 ) ;
             printf ( " %s", "-\x1b[35m-------------------------------\n" ) ;
             printf ( " %s", "--------------------------------\x1b[0m \n" ) ;
             system("pause");
             }
           else
             {
             if( *Choice == 4) {
              system("cls");
               printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
               printf ( " %s", "--------------------------------\x1b[32m \n" ) ;
               printf ( " %s", "the number of nodes starting with x/y/z in each level:\x1b[0m\n" ) ;
               printf ( " %s", "bst1:\n" ) ;
               Nodesxyzlevel ( & *Bst1 , & *X , & *Y , & *Z ) ;
               printf ( " %s", "\x1b[35m--------------------------------\x1b[0m\n" ) ;
               printf ( " %s", "bst2:\n" ) ;
               Nodesxyzlevel ( & *Bst2 , & *X , & *Y , & *Z ) ;
               printf ( " %s", "\x1b[35m--------------------------------\x1b[0m\n" ) ;
               printf ( " %s", "bst3:\n" ) ;
               Nodesxyzlevel ( & *Bst3 , & *X , & *Y , & *Z ) ;
               printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
               printf ( " %s", "--------------------------------\x1b[0m\n" ) ;
               system("pause");
               }
             else
               {
               if( *Choice == 5) {
                system("cls");
                 printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
                 printf ( " %s", "--------------------------------\x1b[33m\n" ) ;
                 printf ( " %s", "search for a word:\x1b[0m" ) ;
                 scanf ( " %[^\n]", *Word ) ;
                 *Resultat  =  Singlewordsearch ( & *Bst1 , & *Bst2 , & *Bst3 , & *X , & *Y , & *Z , & *Word , & *Singlesearchcounter ) ;
                 if( *Resultat != NULL) {
                   printf ( " %s", "\x1b[32m----------\n" ) ;
                   printf ( " %s", "exists\n" ) ;
                   printf ( " %s", "----------\x1b[0m\n" ) ;
                   }
                 else
                   {
                   printf ( " %s", "\x1b[31m-----------------\n" ) ;
                   printf ( " %s", "doesnt exist\n" ) ;
                   printf ( " %s", "-----------------\x1b[0m\n" ) ;
                  
                 } ;
                 printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
                 printf ( " %s", "--------------------------------\x1b[0m\n" ) ;
                 system("pause");
                 }
               else
                 {
                 if( *Choice == 6) {
                  system("cls");
                   printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
                   printf ( " %s", "--------------------------------\x1b[32m\n" ) ;
                   printf ( " %s", "Range Search [word1,word2]: \x1b[0m \n" ) ;
                   printf ( " %s", "enter word1:\n" ) ;
                   scanf ( " %[^\n]", *Word1 ) ;
                   printf ( " %s", "enter word2:\n" ) ;
                   scanf ( " %[^\n]", *Word2 ) ;
                   printf ( " %s", "\x1b[35m-------------------------------\x1b[0m\n" ) ;
                   Rangesearch ( & *Bst1 , & *Bst2 , & *Bst3 , & *X , & *Y , & *Z , & *Word1 , & *Word2 , & *Rangesearchcounter ) ;
                   printf ( " %s", "\x1b[35m--------------------------------\x1b[0m\n" ) ;
                   system("pause");
                   }
                 else
                   {
                   if( *Choice == 7) {
                    Constructandtestbst0(& *Bst0 , & F , & X , & Y , & Z);
                    
                     }
                   else
                     {
                      if( *Choice == 8){
                                                   system("cls");
                          printf("Haven't been constructed\n");
                          system("pause");
                        

                      }
                      else{
                        if( *Choice == 9){
                          system("cls");
                          printf("Haven't been constructed\n");
                          system("pause");
                         

                        }
                        else{
                          if( *Choice == 10){
                                                          *Quit  =  True ;
                              printf ( " \n%s", "\x1b[36m--------------------------------\n" ) ;
                              printf ( " %s", "--------------------------------\n" ) ;
                              printf ( " %s", "see you next time!\n" ) ;
                              printf ( " %s", "--------------------------------\n" ) ;
                              printf ( " %s", "--------------------------------\x1b[0m\n" ) ;
                            

                          }
                          else{
                            

                            
                             printf ( "\n%s", "\x1b[31m--------------------------------\n" ) ;
                             printf ( " %s", "--------------------------------\n" ) ;
                             printf ( " %s", "enter a valid choice!\n" ) ;
                             printf ( " %s", "--------------------------------\n" ) ;
                             printf ( " %s", "--------------------------------\x1b[0m\n" ) ;

                            
                          };
                        };
                      };
                    
                   } ;
                  
                 } ;
                
               } ;
              
             } ;
            
           } ;
          
         } ;
        
       } ;
      
 } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  int  Cmp_string (string255 *Str1 , string255 *Str2) 
    {
      /** Variables locales **/
      int  Cmp_string2 ;

      /** Corps du module **/
     if( (strcmp( *Str1, *Str2) > 0  )) {
       Cmp_string2  =  1 ;
       }
     else
       {
       if( (strcmp( *Str1, *Str2) == 0  )) {
         Cmp_string2  =  0 ;
         }
       else
         {
         Cmp_string2  =  - 1 ;
        
       } ;
      
     } ;
    
     return Cmp_string2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Choice1 (Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z)
    {

      /** Corps du module **/
      system("cls");
     printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
     printf ( " %s", "--------------------------------\x1b[32m\n" ) ;
     printf ( " %s", "number of words starting with x/y/z:\x1b[0m\n" ) ;
     printf ( " %s", "bst1:" );
     printf ( " %d", Startwithxyzcount(&*Bst1,&*X,&*Y,&*Z) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *X );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst1,&*X) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *Y );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst1,&*Y) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *Z );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst1,&*Z) ) ;
     printf ( "\n %s", "bst2:" );
     printf ( " %d", Startwithxyzcount(&*Bst2,&*X,&*Y,&*Z) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *X );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst2,&*X) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *Y );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst2,&*Y) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *Z );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst2,&*Z) ) ;
     printf ( "\n %s", "bst3:" );
     printf ( " %d", Startwithxyzcount(&*Bst3,&*X,&*Y,&*Z) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *X );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst3,&*X) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *Y );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst3,&*Y) ) ;
     printf ( "\n %s", "start with" );
     printf ( " %s", *Z );
     printf ( " %s", ":" );
     printf ( " %d", Startwithcharcount(&*Bst3,&*Z) ) ;
     printf ( "\n %s", "\x1b[35m--------------------------------" ) ;
     printf ( "\n %s", "--------------------------------\x1b[0m\n" ) ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  Pointeur_As Insertbst (Pointeur_As *Root , string255 *Str) 
    {
      /** Variables locales **/
      Pointeur_As Insertbst2 =NULL;
      Pointeur_As Temp=NULL;
      Pointeur_As P=NULL;
      Pointeur_As Paren=NULL;
      string255 _Px1;
      string255 _Px2;

      /** Corps du module **/
     _Px1 = malloc(255 * sizeof(char));
     _Px2 = malloc(255 * sizeof(char));
     Creernoeud_As (& P ) ;
     Aff_info_As ( P , *Str ) ;
     if( ( *Root == NULL )) {
       *Root  =  P ;
       }
     else
       {
       Temp  =  *Root ;
       Paren  =  NULL ;
       while( ( Temp != NULL )) {
         Paren  =  Temp ;
         strcpy(_Px1,  Info_As ( Temp ) );
         if( ( Cmp_string ( &_Px1, & *Str ) == 1 )) {
           ;
           Temp  =  Fg_As ( Temp ) ;
           }
         else
           {
           Temp  =  Fd_As ( Temp ) ;
          
         } ;
        
 } ;
       strcpy(_Px2,  Info_As ( Paren ) );
       if( Cmp_string ( &_Px2, & *Str ) == 1) {
         Aff_fg_As ( Paren , P ) ;
         Aff_pere_As ( P , Paren ) ;
         }
       else
         {
         Aff_fd_As ( Paren , P ) ;
         Aff_pere_As ( P , Paren ) ;
        
       } ;
      
     } ;
     Insertbst2  =  P ;
    
     return Insertbst2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  bool  Beginwithxyz (string255 *S , string2 *X , string2 *Y , string2 *Z) 
    {
      /** Variables locales **/
      bool  Beginwithxyz2 ;
      bool Result;

      /** Corps du module **/
     Result  =  (strcmp( Caract ( *S , 1 ), *X) == 0  ) || (strcmp( Caract ( *S , 1 ), *Y) == 0  ) || (strcmp( Caract ( *S , 1 ), *Z) == 0  ) ;
     Beginwithxyz2  =  Result ;
    
     return Beginwithxyz2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Leftrotation (Pointeur_As *Node)
    {
      /** Variables locales **/
      Pointeur_As Temp=NULL;
      Pointeur_As Parent=NULL;

      /** Corps du module **/
     Parent  =  Pere_As ( *Node ) ;
     Temp  =  Fd_As ( *Node ) ;
     Aff_fd_As ( *Node , Fg_As ( Temp ) ) ;
     if( Fg_As ( Temp ) != NULL) {
       Aff_pere_As ( Fg_As ( Temp ) , *Node );
     } ;
     Aff_fg_As ( Temp , *Node ) ;
     Aff_pere_As ( *Node , Temp ) ;
     Aff_pere_As ( Temp , Parent ) ;
     if( Parent != NULL) {
       if( Fg_As ( Parent ) == *Node) {
         Aff_fg_As ( Parent , Temp ) ;
         }
       else
         {
         Aff_fd_As ( Parent , Temp ) ;
        
       } ;
      
     } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Rightrotation (Pointeur_As *Node)
    {
      /** Variables locales **/
      Pointeur_As Temp=NULL;
      Pointeur_As Parent=NULL;

      /** Corps du module **/
     Parent  =  Pere_As ( *Node ) ;
     Temp  =  Fg_As ( *Node ) ;
     Aff_fg_As ( *Node , Fd_As ( Temp ) ) ;
     if( Fd_As ( Temp ) != NULL) {
       Aff_pere_As ( Fd_As ( Temp ) , *Node ) ;
      
     } ;
     Aff_fd_As ( Temp , *Node ) ;
     Aff_pere_As ( *Node , Temp ) ;
     Aff_pere_As ( Temp , Parent ) ;
     if( Parent != NULL) {
       if( Fg_As ( Parent ) == *Node) {
         Aff_fg_As ( Parent , Temp ) ;
         }
       else
         {
         Aff_fd_As ( Parent , Temp ) ;
        
       } ;
      
     } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Constructbst1 (Pointeur_As *Bst1 , FILE *F , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      Pointeur_As Bst=NULL;
      Pointeur_As Node=NULL;
      Pointeur_As Current=NULL;

      /** Corps du module **/
     S = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     while( ( ! Finfich_s ( F ) )) {
       Lireseq_s ( F , S ) ;
       Current  =  Insertbst ( & *Bst1 , & S ) ;
       if( ( Beginwithxyz ( & S , & *X , & *Y , & *Z ) )) {
         Node  =  Pere_As ( Current ) ;
         while( ( Node != NULL )) {
           if( Fg_As ( Node ) == Current) {
             Rightrotation ( & Node ) ;
             }
           else
             {
             Leftrotation ( & Node ) ;
            
           } ;
           Node  =  Pere_As ( Current ) ;
          
 } ;
         *Bst1  =  Current ;
        
       } ;
      
 } ;
     Fermer_s ( F ) ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Constructbst2 (Pointeur_As *Bst2 , FILE *F , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      int J;
      int Length;
      Pointeur_As Bst=NULL;
      Pointeur_As Node=NULL;
      Pointeur_As Current=NULL;

      /** Corps du module **/
     S = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     while( ( ! Finfich_s ( F ) )) {
       Lireseq_s ( F , S ) ;
       Current  =  Insertbst ( & *Bst2 , & S ) ;
       if( ( Beginwithxyz ( & S , & *X , & *Y , & *Z ) )) {
         Node  =  Pere_As ( Current ) ;
         Length  =  Branchlength ( & *Bst2 , & Current ) / 2 ;
         for( J  =  1 ;J <=  Length ; ++J){
           if( Fg_As ( Node ) == Current) {
             Rightrotation ( & Node ) ;
             }
           else
             {
             Leftrotation ( & Node ) ;
            
           } ;
           Node  =  Pere_As ( Current ) ;
          
         } ;
        
       } ;
      
 } ;
     Fermer_s ( F ) ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Constructbst3 (Pointeur_As *Bst3 , FILE *F , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      Pointeur_As Node=NULL;
      Pointeur_As Current=NULL;

      /** Corps du module **/
     S = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     while( ( ! Finfich_s ( F ) )) {
       Lireseq_s ( F , S ) ;
       Current  =  Insertbst ( & *Bst3 , & S ) ;
       if( ( ! ( Beginwithxyz ( & S , & *X , & *Y , & *Z ) ) )) {
         Node  =  Pere_As ( Current ) ;
         while( ( Node != NULL )) {
           if( Fg_As ( Node ) == Current) {
             Rightrotation ( & Node ) ;
             }
           else
             {
             Leftrotation ( & Node ) ;
            
           } ;
           Node  =  Pere_As ( Current ) ;
          
 } ;
         *Bst3  =  Current ;
        
       } ;
      
 } ;
     Fermer_s ( F ) ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Inordertraversal (Pointeur_As *Bst)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Bst != NULL )) {
       _Px1 =  Fg_As ( *Bst ) ;
       Inordertraversal ( &_Px1) ;
       printf ( " %s", Info_As(*Bst) );
       printf ( " %s\n", " " ) ;
       _Px2 =  Fd_As ( *Bst ) ;
       Inordertraversal ( &_Px2) ;
      
     } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  int  Branchlength (Pointeur_As *Bst , Pointeur_As *Node) 
    {
      /** Variables locales **/
      int  Branchlength2 ;
      Pointeur_As Temp=NULL;
      int Result;

      /** Corps du module **/
     Result  =  0 ;
     Temp  =  *Node ;
     while( Temp != *Bst) {
       Result  =  Result + 1 ;
       Temp  =  Pere_As ( Temp ) ;
      
 } ;
     Branchlength2  =  Result ;
    
     return Branchlength2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  int  Startwithxyzcount (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z) 
    {
      /** Variables locales **/
      int  Startwithxyzcount2 ;
      string255 _Px1;
      Pointeur_As _Px2=NULL;
      Pointeur_As _Px3=NULL;
      Pointeur_As _Px4=NULL;
      Pointeur_As _Px5=NULL;

      /** Corps du module **/
     _Px1 = malloc(255 * sizeof(char));
     if( *Bst == NULL) {
       Startwithxyzcount2  =  0 ;
       }
     else
       {
       strcpy(_Px1,  Info_As ( *Bst ) );
       if( Beginwithxyz ( &_Px1, & *X , & *Y , & *Z )) {
         _Px2 =  Fg_As ( *Bst ) ;
         _Px3 =  Fd_As ( *Bst ) ;
         Startwithxyzcount2  =  1 + Startwithxyzcount ( &_Px2, & *X , & *Y , & *Z ) + Startwithxyzcount ( &_Px3, & *X , & *Y , & *Z ) ;
         }
       else
         {
         _Px4 =  Fg_As ( *Bst ) ;
         _Px5 =  Fd_As ( *Bst ) ;
         Startwithxyzcount2  =  Startwithxyzcount ( &_Px4, & *X , & *Y , & *Z ) + Startwithxyzcount ( &_Px5, & *X , & *Y , & *Z ) ;
        
       } ;
      
     } ;
    
     return Startwithxyzcount2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  int  Startwithcharcount (Pointeur_As *Bst , string2 *Character) 
    {
      /** Variables locales **/
      int  Startwithcharcount2 ;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;
      Pointeur_As _Px3=NULL;
      Pointeur_As _Px4=NULL;

      /** Corps du module **/
     if( *Bst == NULL) {
       Startwithcharcount2  =  0 ;
       }
     else
       {
       if(strcmp( Caract ( Info_As ( *Bst ) , 1 ), *Character) == 0 ) {
         _Px1 =  Fg_As ( *Bst ) ;
         _Px2 =  Fd_As ( *Bst ) ;
         Startwithcharcount2  =  1 + Startwithcharcount ( &_Px1, & *Character ) + Startwithcharcount ( &_Px2, & *Character ) ;
         }
       else
         {
         _Px3 =  Fg_As ( *Bst ) ;
         _Px4 =  Fd_As ( *Bst ) ;
         Startwithcharcount2  =  Startwithcharcount ( &_Px3, & *Character ) + Startwithcharcount ( &_Px4, & *Character ) ;
        
       } ;
      
     } ;
    
     return Startwithcharcount2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  int  Treedepth (Pointeur_As *Bst) 
    {
      /** Variables locales **/
      int  Treedepth2 ;
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( *Bst == NULL) {
       Treedepth2  =  0 ;
       }
     else
       {
       _Px1 =  Fg_As ( *Bst ) ;
       _Px2 =  Fd_As ( *Bst ) ;
       Treedepth2  =  1 + Max ( Treedepth ( &_Px1) , Treedepth ( &_Px2) ) ;
      
     } ;
    
     return Treedepth2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Nodesxyzlevel (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Pointeur_As Temp=NULL;
      Pointeur_FAs Queue=NULL;
      int Countlevelnodes;
      int Countxyzlevel;
      int I;
      int K;

      /** Corps du module **/
     K  =  0 ;
     if( *Bst != NULL) {
       Creerfile_FAs (& Queue ) ;
       Enfiler_FAs ( Queue , *Bst ) ;
       while( ( ! Filevide_FAs ( Queue ) )) {
         Queuelengthxyzcount ( & Queue , & Countlevelnodes , & Countxyzlevel ) ;
         printf ( " %s", "\x1b[33mlevel " );
         printf ( " %d", K );
         printf ( " %s", ":" );
         printf ( "\x1b[32m %d \x1b[0m \n", Countxyzlevel ) ;
         for( I  =  1 ;I <=  Countlevelnodes ; ++I){
           Defiler_FAs ( Queue , &Temp ) ;
           if( Fg_As ( Temp ) != NULL) {
             Enfiler_FAs ( Queue , Fg_As ( Temp ) ) ;
            
           } ;
           if( Fd_As ( Temp ) != NULL) {
             Enfiler_FAs ( Queue , Fd_As ( Temp ) ) ;
            
           } ;
          
         } ;
         K  =  K + 1 ;
        
 } ;
      
     } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Queuelengthxyzcount (Pointeur_FAs *Queue1 , int *Length , int *Countxyz)
    {
      /** Variables locales **/
      Pointeur_FAs Queue2=NULL;
      Pointeur_As Temp=NULL;
      string255 _Px1;

      /** Corps du module **/
     _Px1 = malloc(255 * sizeof(char));
     *Length  =  0 ;
     *Countxyz  =  0 ;
     Creerfile_FAs (& Queue2 ) ;
     while( ( ! Filevide_FAs ( *Queue1 ) )) {
       Defiler_FAs ( *Queue1 , &Temp ) ;
       strcpy(_Px1,  Info_As ( Temp ) );
       if( Beginwithxyz ( &_Px1, & X , & Y , & Z )) {
         *Countxyz  =  *Countxyz + 1 ;
        
       } ;
       Enfiler_FAs ( Queue2 , Temp ) ;
       *Length  =  *Length + 1 ;
      
 } ;
     while( ( ! Filevide_FAs ( Queue2 ) )) {
       Defiler_FAs ( Queue2 , &Temp ) ;
       Enfiler_FAs ( *Queue1 , Temp ) ;
      
 } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  Pointeur_As Singlewordsearch (Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) 
    {
      /** Variables locales **/
      Pointeur_As Singlewordsearch2 =NULL;

      /** Corps du module **/
     *Singlesearchcounter  =  0 ;
     if( Beginwithxyz ( & *String , & *X , & *Y , & *Z )) {
       Singlewordsearch2  =  Searchbst1 ( & *Bst1 , & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ); }
     else
       {
       if( ( (strcmp( Caract ( *String , 1 ), *X) > 0  ) || (strcmp( Caract ( *String , 1 ), *Y) > 0  ) || (strcmp( Caract ( *String , 1 ), *Z) > 0  ) )) {
         Singlewordsearch2  =  Searchbst2 ( & *Bst2 , & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
         }
       else
         {
         Singlewordsearch2  =  Searchbst3 ( & *Bst3 , & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
        
       } ;
      
     } ;
    
     return Singlewordsearch2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  Pointeur_As Searchbst1 (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) 
    {
      /** Variables locales **/
      Pointeur_As Searchbst12 =NULL;
      string255 _Px1;
      string255 _Px2;
      Pointeur_As _Px3=NULL;
      Pointeur_As _Px4=NULL;

      /** Corps du module **/
     _Px1 = malloc(255 * sizeof(char));
     _Px2 = malloc(255 * sizeof(char));
     if( ( *Bst == NULL )) {
       Searchbst12  =  NULL ;
       }
     else
       {
       if( ! Beginwithxyz ( & *String , & *X , & *Y , & *Z )) {
         Searchbst12  =  NULL ;
         }
       else
         {
         strcpy(_Px1,  Info_As ( *Bst ) );
         if( ( Cmp_string ( &_Px1, & *String ) == 0 )) {
           Searchbst12  =  *Bst ;
           }
         else
           {
           strcpy(_Px2,  Info_As ( *Bst ) );
           if( ( Cmp_string ( &_Px2, & *String ) == 1 )) {
             *Singlesearchcounter  =  *Singlesearchcounter + 1 ;
             _Px3 =  Fg_As ( *Bst ) ;
             Searchbst12  =  Searchbst1 ( &_Px3, & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
             }
           else
             {
             *Singlesearchcounter  =  *Singlesearchcounter + 1 ;
             _Px4 =  Fd_As ( *Bst ) ;
             Searchbst12  =  Searchbst1 ( &_Px4, & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
            
           } ;
          
         } ;
        
       } ;
      
     } ;
    
     return Searchbst12 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  Pointeur_As Searchbst2 (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) 
    {
      /** Variables locales **/
      Pointeur_As Searchbst22 =NULL;
      string255 _Px1;
      string255 _Px2;
      Pointeur_As _Px3=NULL;
      Pointeur_As _Px4=NULL;

      /** Corps du module **/
     _Px1 = malloc(255 * sizeof(char));
     _Px2 = malloc(255 * sizeof(char));
     if( ( *Bst == NULL )) {
       Searchbst22  =  NULL ;
       }
     else
       {
       strcpy(_Px1,  Info_As ( *Bst ) );
       if( ( Cmp_string ( &_Px1, & *String ) == 0 )) {
         Searchbst22  =  *Bst ;
         }
       else
         {
         strcpy(_Px2,  Info_As ( *Bst ) );
         if( ( Cmp_string ( &_Px2, & *String ) == 1 )) {
           *Singlesearchcounter  =  *Singlesearchcounter + 1 ;
           _Px3 =  Fg_As ( *Bst ) ;
           Searchbst22  =  Searchbst2 ( &_Px3, & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
           }
         else
           {
           *Singlesearchcounter  =  *Singlesearchcounter + 1 ;
           _Px4 =  Fd_As ( *Bst ) ;
           Searchbst22  =  Searchbst2 ( &_Px4, & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
          
         } ;
        
       } ;
      
     } ;
    
     return Searchbst22 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  Pointeur_As Searchbst3 (Pointeur_As *Bst , string2 *X , string2 *Y , string2 *Z , string255 *String , int *Singlesearchcounter) 
    {
      /** Variables locales **/
      Pointeur_As Searchbst32 =NULL;
      string255 _Px1;
      string255 _Px2;
      Pointeur_As _Px3=NULL;
      Pointeur_As _Px4=NULL;

      /** Corps du module **/
     _Px1 = malloc(255 * sizeof(char));
     _Px2 = malloc(255 * sizeof(char));
     if( ( *Bst == NULL )) {
       Searchbst32  =  NULL ;
       }
     else
       {
       if( Beginwithxyz ( & *String , & *X , & *Y , & *Z )) {
         Searchbst32  =  NULL ;
         }
       else
         {
         strcpy(_Px1,  Info_As ( *Bst ) );
         if( ( Cmp_string ( &_Px1, & *String ) == 0 )) {
           Searchbst32  =  *Bst ;
           }
         else
           {
           strcpy(_Px2,  Info_As ( *Bst ) );
           if( ( Cmp_string ( &_Px2, & *String ) == 1 )) {
             *Singlesearchcounter  =  *Singlesearchcounter + 1 ;
             _Px3 =  Fg_As ( *Bst ) ;
             Searchbst32  =  Searchbst3 ( &_Px3, & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
             }
           else
             {
             *Singlesearchcounter  =  *Singlesearchcounter + 1 ;
             _Px4 =  Fd_As ( *Bst ) ;
             Searchbst32  =  Searchbst3 ( &_Px4, & *X , & *Y , & *Z , & *String , & *Singlesearchcounter ) ;
            
           } ;
          
         } ;
        
       } ;
      
     } ;
    
     return Searchbst32 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Rangesearch (Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z , string255 *Word1 , string255 *Word2 , int *Rangesearchcounter)
    {

      /** Corps du module **/
     *Rangesearchcounter  =  0 ;
     if( Beginwithxyz ( & *Word1 , & *X , & *Y , & *Z )) {
       Rangesearchbst ( & *Bst1 , & *Word1 , & *Word2 , & *Rangesearchcounter ) ;
       }
     else
       {
       if( ( (strcmp( Caract ( *Word1 , 1 ), *X) > 0  ) || (strcmp( Caract ( *Word1 , 1 ), *Y) > 0  ) || (strcmp( Caract ( *Word1 , 1 ), *Z) > 0  ) )) {
         Rangesearchbst ( & *Bst2 , & *Word1 , & *Word2 , & *Rangesearchcounter ) ;
         }
       else
         {
         Rangesearchbst ( & *Bst3 , & *Word1 , & *Word2 , & *Rangesearchcounter ) ;
        
       } ;
      
     } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Rangesearchbst (Pointeur_As *Bst , string255 *Word1 , string255 *Word2 , int *Rangesearchcounter)
    {
      /** Variables locales **/
      Pointeur_As Temp1=NULL;

      /** Corps du module **/
     Temp1  =  Searchleastgreater ( & *Bst , & *Word1 , & *Rangesearchcounter ) ;
     while( Temp1 != NULL) {
       if(strcmp( Info_As ( Temp1 ), *Word2) <= 0 ) {
         printf ( " %s\n", Info_As(Temp1) ) ;
         Temp1  =  Nextinorder ( & Temp1 , & *Rangesearchcounter ) ;
         }
       else
         {
         Temp1  =  NULL ;
        
       } ;
      
 } ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  Pointeur_As Searchleastgreater (Pointeur_As *Bst , string255 *Word1 , int *Rangesearchcounter) 
    {
      /** Variables locales **/
      Pointeur_As Searchleastgreater2 =NULL;
      Pointeur_As Temp2=NULL;
      Pointeur_As Resulting=NULL;

      /** Corps du module **/
     Temp2  =  *Bst ;
     Resulting  =  NULL ;
     while( Temp2 != NULL) {
       if(strcmp( Info_As ( Temp2 ), *Word1) >= 0 ) {
         Resulting  =  Temp2 ;
         Temp2  =  Fg_As ( Temp2 ) ;
         }
       else
         {
         Temp2  =  Fd_As ( Temp2 ) ;
        
       } ;
       *Rangesearchcounter  =  *Rangesearchcounter + 1 ;
      
 } ;
     Searchleastgreater2  =  Resulting ;
    
     return Searchleastgreater2 ;
    }
  /*////////////////////////////////////////////////////////////////////////*/
  Pointeur_As Nextinorder (Pointeur_As *Node , int *Rangesearchcounter) 
    {
      /** Variables locales **/
      Pointeur_As Nextinorder2 =NULL;
      Pointeur_As Temp3=NULL;
      Pointeur_As Temp4=NULL;

      /** Corps du module **/
     Temp4  =  NULL ;
     if( *Node == NULL) {
       Nextinorder2  =  NULL ;
       }
     else
       {
       if( Fd_As ( *Node ) != NULL) {
         Temp3  =  Fd_As ( *Node ) ;
         *Rangesearchcounter  =  *Rangesearchcounter + 2 ;
         while( ( Fg_As ( Temp3 ) != NULL )) {
           Temp3  =  Fg_As ( Temp3 ) ;
          *Rangesearchcounter  =  *Rangesearchcounter + 1 ;
          
 } ;
         Temp4  =  Temp3 ;
         }
       else
         {
         Temp3  =  *Node ;
         *Rangesearchcounter  =  *Rangesearchcounter + 1 ;
         while( ( ( Pere_As ( Temp3 ) != NULL ) && ( Temp4 == NULL ) )) {
           *Rangesearchcounter  =  *Rangesearchcounter + 3 ;
           if( Temp3 == Fg_As ( Pere_As ( Temp3 ) )) {
             Temp4  =  Pere_As ( Temp3 ) ;
             }
           else
             {
             Temp3  =  Pere_As ( Temp3 ) ;
            
           } ;
          
 } ;
        
       } ;
       Nextinorder2  =  Temp4 ;
      
     } ;
    
     return Nextinorder2 ;
    }

/*////////////////////////////////////////////////////////////////////////*/
 void Constructbst0 (Pointeur_As *Bst0 , FILE *F , string2 *X , string2 *Y , string2 *Z)
    {
      /** Variables locales **/
      Typestruct1_s S ;
      Pointeur_As Bst=NULL;
      Pointeur_As Node=NULL;
      Pointeur_As Current=NULL;

      /** Corps du module **/
     S = malloc(255 * sizeof(char));
     Ouvrir_s (&F , "F2.z" , "A" ) ;
     while( ( ! Finfich_s ( F ) )) {
       Lireseq_s ( F , S ) ;
       Current  =  Insertbst ( & *Bst0 , & S ) ;
 } ;
     Fermer_s ( F ) ;
    
    }
  /*////////////////////////////////////////////////////////////////////////*/
  void Constructandtestbst0(Pointeur_As *Bst0 , FILE *F , string2 *X , string2 *Y , string2 *Z){
    bool constructed=False;
    if (!constructed){
        printf("constructing bst0...\n");
        Constructbst0 (& *Bst0 ,&F ,&X ,&Y ,&Z);
        printf("\x1b[32m bst0 has been constructed successfully...!\x1b[0m\n");
        system("pause");
        system("cls");
    }
    printf("\x1b[35m------------------------------------------------------\x1b[0m\n");
    printf("BST0 stats:\n");
    printf("Depth of the tree: %d\n",Treedepth(&*Bst0));
    printf("Number of words starting with xyz in each level:\n");
    Nodesxyzlevel ( & *Bst0 , & *X , & *Y , & *Z ) ;
    printf("\x1b[35m------------------------------------------------------\x1b[0m\n");
    system("pause");
  } 
  /*////////////////////////////////////////////////////////////////////////*/
  void deleteTree (Pointeur_As *Bst)
    {
      /** Variables locales **/
      Pointeur_As _Px1=NULL;
      Pointeur_As _Px2=NULL;

      /** Corps du module **/
     if( ( *Bst != NULL )) {
       _Px1 =  Fg_As ( *Bst ) ;
       deleteTree ( &_Px1) ;
       _Px2 =  Fd_As ( *Bst ) ;
       deleteTree ( &_Px2) ;
       free(*Bst);
      
     } ;
    
    }
 
  /*////////////////////////////////////////////////////////////////////////*/
  void simulation2(int M ,Pointeur_As *Bst0,Pointeur_As *Bst1 , Pointeur_As *Bst2 , Pointeur_As *Bst3 , string2 *X , string2 *Y , string2 *Z, string255 *Word , Pointeur_As *Resultat , string255 *Word1 , string255 *Word2 , int *Singlesearchcounter , int *Rangesearchcounter){}
  /*////////////////////////////////////////////////////////////////////////*/

  int main(int argc, char *argv[])
    {
     srand(time(NULL));
     S = malloc(255 * sizeof(char));
     X = malloc(2 * sizeof(char));
     Y = malloc(2 * sizeof(char));
     Z = malloc(2 * sizeof(char));
     Word = malloc(255 * sizeof(char));
     Word1 = malloc(255 * sizeof(char));
     Word2 = malloc(255 * sizeof(char));
     _Sx = malloc(255 * sizeof(char));
     Quit  =  False ;
     Numvalid  =  False ;
     printf ( " %s", "\x1b[36menter the number of words to be generated(>=100):\x1b[0m" ) ;
     while( ! Numvalid) {
       scanf ( " %d", &N ) ;
       if( N >= 100) {
         Numvalid  =  True ;
         }
       else
         {
         printf ( " %s", "\x1b[31mplease enter a valid number(>=100):\x1b[0m" ) ;
        
       } ;
      
 } ;
     Ouvrir_s (&F , "F2.z" , "N" ) ;
     for( I  =  1 ;I <=  N ; ++I){
       Random  =  Aleanombre(10 ) ;
       strcpy (_Sx, Aleachaine(5));
       strcpy (S,  strcat(_Sx, Aleachaine ( Random ))) ;
       Ecrireseq_s ( F , S );
     } ;
     Fermer_s ( F ) ;
     printf ( " %s", "\x1b[36mchoose special characters:(one by one;enter one then press enter)\x1b[0m\n" ) ;
     scanf ( " %s", X ) ;
     scanf ( " %s", Y ) ;
     scanf ( " %s", Z ) ;
     system("pause");
     printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
     printf ( " %s", "--------------------------------\x1b[0m\n" ) ;
     printf ( " %s", "constructing bst1...\n" ) ;
     Constructbst1 ( & Bst1 , & F , & X , & Y , & Z ) ;
     printf ( " %s", "\x1b[32mbst1 has been constructed successfully...!\x1b[0m \n" ) ;
     printf ( " %s", "\x1b[35m--------------------------------\x1b[0m \n" ) ;
     printf ( " %s", "constructing bst2...\n" ) ;
     Constructbst2 ( & Bst2 , & F , & X , & Y , & Z ) ;
     printf ( " %s", "\x1b[32mbst2 has been constructed successfully...!\x1b[0m\n" ) ;
     printf ( " %s", "\x1b[35m--------------------------------\x1b[0m \n" ) ;
     printf ( " %s", "constructing bst3...\n" ) ;
     Constructbst3 ( & Bst3 , & F , & X , & Y , & Z ) ;
     printf ( " %s", "\x1b[32mbst3 has been constructed successfully...!\x1b[0m \n" ) ;
     printf ( " %s", "\x1b[35m--------------------------------\n" ) ;
     printf ( " %s", "--------------------------------\x1b[0m\n" ) ;
     system("pause");
     Displaymenu (& Bst0, & Bst1 , & Bst2 , & Bst3 , & X , & Y , & Z , & Quit , & Choice , & Word , & Resultat , & Word1 , & Word2 , & Singlesearchcounter , & Rangesearchcounter ) ;
    
   
      system("PAUSE");
      return 0;
    }
