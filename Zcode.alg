  /*////////////////////////////////////////////////////////////////////////*/
  /*////////////////////////////////////////////////////////////////////////*/
  /*Second Lab by :Kouah Akram (Group 02) & Korchi Adam (Group15)*/
  /*////////////////////////////////////////////////////////////////////////*/
  /*////////////////////////////////////////////////////////////////////////*/
   SOIENT
       F UN FICHIER DE CHAINE BUFFER S ;
       I , N , Random , Singlesearchcounter , Rangesearchcounter , Choice DES ENTIER ;
       X , Y , Z DES CAR ;
       Quit , Numvalid UN BOOLEEN ;
       Word , Word1 , Word2 UNE CHAINE ;
       Bst1 , Bst2 , Bst3 , Resultat DES ARB DE CHAINE ;
       Displaymenu UNE ACTION ;
       Constructbst1 UNE ACTION ;
       Constructbst3 UNE ACTION ;
       Constructbst2 UNE ACTION ;
       Cmp_string UNE FONCTION ( ENTIER ) ;
       Insertbst UNE FONCTION ( ARB DE CHAINE ) ;
       Beginwithxyz UNE FONCTION ( BOOLEEN ) ;
       Leftrotation UNE ACTION ;
       Rightrotation UNE ACTION ;
       Inordertraversal UNE ACTION ;
       Branchlength UNE FONCTION ( ENTIER ) ;
       Startwithxyzcount UNE FONCTION ( ENTIER ) ;
       Treedepth UNE FONCTION ( ENTIER ) ;
       Queuelengthxyzcount UNE ACTION ;
       Nodesxyzlevel UNE ACTION ;
       Singlewordsearch UNE FONCTION ( ARB DE CHAINE ) ;
       Searchbst UNE FONCTION ( ARB DE CHAINE ) ;
       Rangesearch UNE ACTION ;
       Rangesearchbst UNE ACTION ;
       Searchleastgreater UNE FONCTION ( ARB DE CHAINE ) ;
       Nextinorder UNE FONCTION ( ARB DE CHAINE ) ;
       Startwithcharcount UNE FONCTION ( ENTIER ) ;
       Choice1 UNE ACTION ;
   DEBUT
       Quit := FAUX ;
       Numvalid := FAUX ;
       ECRIRE ( 'enter the number of words to be generated(>=100):' ) ;
       TANTQUE NON Numvalid
           LIRE ( N ) ;
           SI N >= 100
               Numvalid := VRAI ;
           SINON
               ECRIRE ( 'please enter a valid number(>=100):' ) ;
           FSI ;
       FTQ ;
       OUVRIR ( F , 'F2.z' , 'N' ) ;
       POUR I := 1 , N
           Random := ALEANOMBRE ( 10 ) ;
           S := ALEACHAINE ( 5 ) + ALEACHAINE ( Random ) ;
           ECRIRESEQ ( F , S )
       FPOUR ;
       FERMER ( F ) ;
       ECRIRE ( 'choose special characters:' ) ;
       LIRE ( X ) ;
       LIRE ( Y ) ;
       LIRE ( Z ) ;
       ECRIRE ( '--------------------------------' ) ;
       ECRIRE ( '--------------------------------' ) ;
       ECRIRE ( 'constructing bst1...' ) ;
       APPEL Constructbst1 ( Bst1 , F , X , Y , Z ) ;
       ECRIRE ( 'bst1 has been constructed successfully...!' ) ;
       ECRIRE ( '--------------------------------' ) ;
       ECRIRE ( 'constructing bst2...' ) ;
       APPEL Constructbst2 ( Bst2 , F , X , Y , Z ) ;
       ECRIRE ( 'bst2 has been constructed successfully...!' ) ;
       ECRIRE ( '--------------------------------' ) ;
       ECRIRE ( 'constructing bst3...' ) ;
       APPEL Constructbst3 ( Bst3 , F , X , Y , Z ) ;
       ECRIRE ( 'bst3 has been constructed successfully...!' ) ;
       ECRIRE ( '--------------------------------' ) ;
       ECRIRE ( '--------------------------------' ) ;
       APPEL Displaymenu ( Bst1 , Bst2 , Bst3 , X , Y , Z , Quit , Choice , Word , Resultat , Word1 , Word2 ,
       Singlesearchcounter , Rangesearchcounter ) ;
   FIN
  /*////////////////////////////////////////////////////////////////////////*/
   ACTION Displaymenu ( Bst1 , Bst2 , Bst3 , X , Y , Z , Quit , Choice , Word , Resultat , Word1 , Word2 ,
       Singlesearchcounter , Rangesearchcounter )
       SOIENT
           Bst1 , Bst2 , Bst3 , Resultat DES ARB DE CHAINES ;
           X , Y , Z DES CAR ;
           Quit UN BOOLEEN ;
           Choice , Singlesearchcounter , Rangesearchcounter UN ENTIER ;
           Word , Word1 , Word2 DES CHAINES ;
       DEBUT
           TANTQUE ( NON Quit )
               ECRIRE ( '--------------------------------' ) ;
               ECRIRE ( 'menu:' ) ;
               ECRIRE ( '1-count the number of words starting with x/y/z' ) ;
               ECRIRE ( '2-compute the depth of the trees' ) ;
               ECRIRE ( '3-perform an inorder traversal' ) ;
               ECRIRE ( '4-compute and display the number of nodes starting with x/y/z in each level' ) ;
               ECRIRE ( '5-search for a single word' ) ;
               ECRIRE ( '6-search for all words within a particular range' ) ;
               ECRIRE ( '7-exit' ) ;
               ECRIRE ( '--------------------------------' ) ;
               ECRIRE ( 'please enter your choice:' ) ;
               LIRE ( Choice ) ;
               SI Choice = 1
                   APPEL Choice1 ( Bst1 , Bst2 , Bst3 , X , Y , Z ) ;
               SINON
                   SI Choice = 2
                       ECRIRE ( '--------------------------------' ) ;
                       ECRIRE ( '--------------------------------' ) ;
                       ECRIRE ( 'depth of the trees:' ) ;
                       ECRIRE ( 'bst1:' , Treedepth ( Bst1 ) ) ;
                       ECRIRE ( 'bst2:' , Treedepth ( Bst2 ) ) ;
                       ECRIRE ( 'bst3:' , Treedepth ( Bst3 ) ) ;
                       ECRIRE ( '--------------------------------' ) ;
                       ECRIRE ( '--------------------------------' ) ;
                   SINON
                       SI Choice = 3
                           ECRIRE ( '--------------------------------' ) ;
                           ECRIRE ( '--------------------------------' ) ;
                           ECRIRE ( 'inorder traversal:' ) ;
                           ECRIRE ( '--------------------------------' ) ;
                           ECRIRE ( 'bst1:' ) ;
                           APPEL Inordertraversal ( Bst1 ) ;
                           ECRIRE ( '--------------------------------' ) ;
                           ECRIRE ( 'bst2:' ) ;
                           APPEL Inordertraversal ( Bst2 ) ;
                           ECRIRE ( '--------------------------------' ) ;
                           ECRIRE ( 'bst3:' ) ;
                           APPEL Inordertraversal ( Bst3 ) ;
                           ECRIRE ( '--------------------------------' ) ;
                           ECRIRE ( '--------------------------------' ) ;
                       SINON
                           SI Choice = 4
                               ECRIRE ( '--------------------------------' ) ;
                               ECRIRE ( '--------------------------------' ) ;
                               ECRIRE ( 'the number of nodes starting with x/y/z in each level:' ) ;
                               ECRIRE ( 'bst1:' ) ;
                               APPEL Nodesxyzlevel ( Bst1 , X , Y , Z ) ;
                               ECRIRE ( '--------------------------------' ) ;
                               ECRIRE ( 'bst2:' ) ;
                               APPEL Nodesxyzlevel ( Bst2 , X , Y , Z ) ;
                               ECRIRE ( '--------------------------------' ) ;
                               ECRIRE ( 'bst3:' ) ;
                               APPEL Nodesxyzlevel ( Bst3 , X , Y , Z ) ;
                               ECRIRE ( '--------------------------------' ) ;
                               ECRIRE ( '--------------------------------' ) ;
                           SINON
                               SI Choice = 5
                                   ECRIRE ( '--------------------------------' ) ;
                                   ECRIRE ( '--------------------------------' ) ;
                                   ECRIRE ( 'search for a word:' ) ;
                                   LIRE ( Word ) ;
                                   Resultat := Singlewordsearch ( Bst1 , Bst2 , Bst3 , X , Y , Z , Word ,
                                   Singlesearchcounter ) ;
                                   SI Resultat <> NIL
                                       ECRIRE ( '----------' ) ;
                                       ECRIRE ( 'exists' ) ;
                                       ECRIRE ( '----------' ) ;
                                   SINON
                                       ECRIRE ( '-----------------' ) ;
                                       ECRIRE ( 'doesnt exist' ) ;
                                       ECRIRE ( '-----------------' ) ;
                                   FSI ;
                                   ECRIRE ( '--------------------------------' ) ;
                                   ECRIRE ( '--------------------------------' ) ;
                               SINON
                                   SI Choice = 6
                                       ECRIRE ( '--------------------------------' ) ;
                                       ECRIRE ( '--------------------------------' ) ;
                                       ECRIRE ( 'Range Search [word1,word2]:' ) ;
                                       ECRIRE ( 'enter word1:' ) ;
                                       LIRE ( Word1 ) ;
                                       ECRIRE ( 'enter word2:' ) ;
                                       LIRE ( Word2 ) ;
                                       ECRIRE ( '-------------------------------' ) ;
                                       APPEL Rangesearch ( Bst1 , Bst2 , Bst3 , X , Y , Z , Word1 , Word2 ,
                                       Rangesearchcounter ) ;
                                       ECRIRE ( '--------------------------------' ) ;
                                   SINON
                                       SI Choice = 7
                                           Quit := VRAI ;
                                           ECRIRE ( '--------------------------------' ) ;
                                           ECRIRE ( '--------------------------------' ) ;
                                           ECRIRE ( 'see you next time!' ) ;
                                           ECRIRE ( '--------------------------------' ) ;
                                           ECRIRE ( '--------------------------------' ) ;
                                       SINON
                                           ECRIRE ( '--------------------------------' ) ;
                                           ECRIRE ( '--------------------------------' ) ;
                                           ECRIRE ( 'enter a valid choice!' ) ;
                                           ECRIRE ( '--------------------------------' ) ;
                                           ECRIRE ( '--------------------------------' ) ;
                                       FSI ;
                                   FSI ;
                               FSI ;
                           FSI ;
                       FSI ;
                   FSI ;
               FSI ;
           FTQ ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Cmp_string ( Str1 , Str2 ) : ENTIER ;
       SOIENT
           Str1 , Str2 DES CHAINE ;
       DEBUT
           SI ( Str1 > Str2 )
               Cmp_string := 1 ;
           SINON
               SI ( Str1 = Str2 )
                   Cmp_string := 0 ;
               SINON
                   Cmp_string := - 1 ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Choice1 ( Bst1 , Bst2 , Bst3 , X , Y , Z )
       SOIENT
           Bst1 , Bst2 , Bst3 DES ARB DE CHAINES ;
           X , Y , Z DES CAR ;
       DEBUT
           ECRIRE ( '--------------------------------' ) ;
           ECRIRE ( '--------------------------------' ) ;
           ECRIRE ( 'number of words starting with x/y/z:' ) ;
           ECRIRE ( 'bst1:' , Startwithxyzcount ( Bst1 , X , Y , Z ) ) ;
           ECRIRE ( 'start with' , X , ':' , Startwithcharcount ( Bst1 , X ) ) ;
           ECRIRE ( 'start with' , Y , ':' , Startwithcharcount ( Bst1 , Y ) ) ;
           ECRIRE ( 'start with' , Z , ':' , Startwithcharcount ( Bst1 , Z ) ) ;
           ECRIRE ( 'bst2:' , Startwithxyzcount ( Bst2 , X , Y , Z ) ) ;
           ECRIRE ( 'start with' , X , ':' , Startwithcharcount ( Bst2 , X ) ) ;
           ECRIRE ( 'start with' , Y , ':' , Startwithcharcount ( Bst2 , Y ) ) ;
           ECRIRE ( 'start with' , Z , ':' , Startwithcharcount ( Bst2 , Z ) ) ;
           ECRIRE ( 'bst3:' , Startwithxyzcount ( Bst3 , X , Y , Z ) ) ;
           ECRIRE ( 'start with' , X , ':' , Startwithcharcount ( Bst3 , X ) ) ;
           ECRIRE ( 'start with' , Y , ':' , Startwithcharcount ( Bst3 , Y ) ) ;
           ECRIRE ( 'start with' , Z , ':' , Startwithcharcount ( Bst3 , Z ) ) ;
           ECRIRE ( '--------------------------------' ) ;
           ECRIRE ( '--------------------------------' ) ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Insertbst ( Root , Str ) : ARB DE CHAINE
       SOIENT
           Root UN ARB DE CHAINE ;
           Str UN CHAINE ;
           Temp UN ARB DE CHAINE ;
           P UN ARB DE CHAINE ;
           Paren UN ARB DE CHAINE ;
       DEBUT
           CREERNOEUD ( P ) ;
           AFF_INFO ( P , Str ) ;
           SI ( Root = NIL )
               Root := P ;
           SINON
               Temp := Root ;
               Paren := NIL ;
               TANTQUE ( Temp <> NIL )
                   Paren := Temp ;
                   SI ( Cmp_string ( INFO ( Temp ) , Str ) = 1 )
                       ;
                       Temp := FG ( Temp ) ;
                   SINON
                       Temp := FD ( Temp ) ;
                   FSI ;
               FTQ ;
               SI Cmp_string ( INFO ( Paren ) , Str ) = 1
                   AFF_FG ( Paren , P ) ;
                   AFF_PERE ( P , Paren ) ;
               SINON
                   AFF_FD ( Paren , P ) ;
                   AFF_PERE ( P , Paren ) ;
               FSI ;
           FSI ;
           Insertbst := P ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Beginwithxyz ( S , X , Y , Z ) : BOOLEEN
       SOIENT
           S : CHAINE ;
           X , Y , Z DES CAR ;
           Result : BOOLEEN ;
       DEBUT
           Result := ( CARACT ( S , 1 ) = X ) OU ( CARACT ( S , 1 ) = Y ) OU ( CARACT ( S , 1 ) = Z ) ;
           Beginwithxyz := Result ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Leftrotation ( Node )
       SOIENT
           Node , Temp , Parent DES ARB DE CHAINE ;
       DEBUT
           Parent := PERE ( Node ) ;
           Temp := FD ( Node ) ;
           AFF_FD ( Node , FG ( Temp ) ) ;
           SI FG ( Temp ) <> NIL
               AFF_PERE ( FG ( Temp ) , Node )
           FSI ;
           AFF_FG ( Temp , Node ) ;
           AFF_PERE ( Node , Temp ) ;
           AFF_PERE ( Temp , Parent ) ;
           SI Parent <> NIL
               SI FG ( Parent ) = Node
                   AFF_FG ( Parent , Temp ) ;
               SINON
                   AFF_FD ( Parent , Temp ) ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Rightrotation ( Node )
       SOIENT
           Node , Temp , Parent DES ARB DE CHAINE ;
       DEBUT
           Parent := PERE ( Node ) ;
           Temp := FG ( Node ) ;
           AFF_FG ( Node , FD ( Temp ) ) ;
           SI FD ( Temp ) <> NIL
               AFF_PERE ( FD ( Temp ) , Node ) ;
           FSI ;
           AFF_FD ( Temp , Node ) ;
           AFF_PERE ( Node , Temp ) ;
           AFF_PERE ( Temp , Parent ) ;
           SI Parent <> NIL
               SI FG ( Parent ) = Node
                   AFF_FG ( Parent , Temp ) ;
               SINON
                   AFF_FD ( Parent , Temp ) ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Constructbst1 ( Bst1 , F , X , Y , Z )
       SOIENT
           Bst1 UNE ARB DE CHAINE ;
           F UN FICHIER DE CHAINES BUFFER S ;
           X , Y , Z DES CAR ;
           Bst , Node , Current DES ARB DE CHAINE ;
       DEBUT
           OUVRIR ( F , 'F2.z' , 'A' ) ;
           TANTQUE ( NON FINFICH ( F ) )
               LIRESEQ ( F , S ) ;
               Current := Insertbst ( Bst1 , S ) ;
               SI ( Beginwithxyz ( S , X , Y , Z ) )
                   Node := PERE ( Current ) ;
                   TANTQUE ( Node <> NIL )
                       SI FG ( Node ) = Current
                           APPEL Rightrotation ( Node ) ;
                       SINON
                           APPEL Leftrotation ( Node ) ;
                       FSI ;
                       Node := PERE ( Current ) ;
                   FTQ ;
                   Bst1 := Current ;
               FSI ;
           FTQ ;
           FERMER ( F ) ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Constructbst2 ( Bst2 , F , X , Y , Z )
       SOIENT
           Bst2 UNE ARB DE CHAINE ;
           F UN FICHIER DE CHAINES BUFFER S ;
           X , Y , Z DES CAR ;
           J , Length DES ENTIER ;
           Bst , Node , Current DES ARB DE CHAINE ;
       DEBUT
           OUVRIR ( F , 'F2.z' , 'A' ) ;
           TANTQUE ( NON FINFICH ( F ) )
               LIRESEQ ( F , S ) ;
               Current := Insertbst ( Bst2 , S ) ;
               SI ( Beginwithxyz ( S , X , Y , Z ) )
                   Node := PERE ( Current ) ;
                   Length := Branchlength ( Bst2 , Current ) / 2 ;
                   POUR J := 1 , Length
                       SI FG ( Node ) = Current
                           APPEL Rightrotation ( Node ) ;
                       SINON
                           APPEL Leftrotation ( Node ) ;
                       FSI ;
                       Node := PERE ( Current ) ;
                   FPOUR ;
               FSI ;
           FTQ ;
           FERMER ( F ) ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Constructbst3 ( Bst3 , F , X , Y , Z )
       SOIENT
           Bst3 UNE ARB DE CHAINE ;
           F UN FICHIER DE CHAINES BUFFER S ;
           X , Y , Z DES CAR ;
           Node , Current DES ARB DE CHAINE ;
       DEBUT
           OUVRIR ( F , 'F2.z' , 'A' ) ;
           TANTQUE ( NON FINFICH ( F ) )
               LIRESEQ ( F , S ) ;
               Current := Insertbst ( Bst3 , S ) ;
               SI ( NON ( Beginwithxyz ( S , X , Y , Z ) ) )
                   Node := PERE ( Current ) ;
                   TANTQUE ( Node <> NIL )
                       SI FG ( Node ) = Current
                           APPEL Rightrotation ( Node ) ;
                       SINON
                           APPEL Leftrotation ( Node ) ;
                       FSI ;
                       Node := PERE ( Current ) ;
                   FTQ ;
                   Bst3 := Current ;
               FSI ;
           FTQ ;
           FERMER ( F ) ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Inordertraversal ( Bst )
       SOIENT
           Bst UN ARB DE CHAINE ;
       DEBUT
           SI ( Bst <> NIL )
               APPEL Inordertraversal ( FG ( Bst ) ) ;
               ECRIRE ( INFO ( Bst ) , ' ' ) ;
               APPEL Inordertraversal ( FD ( Bst ) ) ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Branchlength ( Bst , Node ) : ENTIER
       SOIENT
           Bst , Node , Temp UN ARB DE CHAINE ;
           Result UN ENTIER ;
       DEBUT
           Result := 0 ;
           Temp := Node ;
           TANTQUE Temp <> Bst
               Result := Result + 1 ;
               Temp := PERE ( Temp ) ;
           FTQ ;
           Branchlength := Result ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Startwithxyzcount ( Bst , X , Y , Z ) : ENTIER
       SOIENT
           Bst UN ARB DE CHAINE ;
           X , Y , Z DES CAR ;
       DEBUT
           SI Bst = NIL
               Startwithxyzcount := 0 ;
           SINON
               SI Beginwithxyz ( INFO ( Bst ) , X , Y , Z )
                   Startwithxyzcount := 1 + Startwithxyzcount ( FG ( Bst ) , X , Y , Z ) + Startwithxyzcount ( FD (
                   Bst ) , X , Y , Z ) ;
               SINON
                   Startwithxyzcount := Startwithxyzcount ( FG ( Bst ) , X , Y , Z ) + Startwithxyzcount ( FD ( Bst )
                   , X , Y , Z ) ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Startwithcharcount ( Bst , Character ) : ENTIER
       SOIENT
           Bst UN ARB DE CHAINE ;
           Character UN CAR ;
       DEBUT
           SI Bst = NIL
               Startwithcharcount := 0 ;
           SINON
               SI CARACT ( INFO ( Bst ) , 1 ) = Character
                   Startwithcharcount := 1 + Startwithcharcount ( FG ( Bst ) , Character ) + Startwithcharcount ( FD (
                   Bst ) , Character ) ;
               SINON
                   Startwithcharcount := Startwithcharcount ( FG ( Bst ) , Character ) + Startwithcharcount ( FD ( Bst
                   ) , Character ) ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Treedepth ( Bst ) : ENTIER
       SOIENT
           Bst UN ARB DE CHAINE ;
       DEBUT
           SI Bst = NIL
               Treedepth := 0 ;
           SINON
               Treedepth := 1 + MAX ( Treedepth ( FG ( Bst ) ) , Treedepth ( FD ( Bst ) ) ) ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Nodesxyzlevel ( Bst , X , Y , Z )
       SOIENT
           Bst , Temp DES ARB DE CHAINE ;
           X , Y , Z DES CAR ;
           Queue UN FILE DE ARB DE CHAINE ;
           Countlevelnodes , Countxyzlevel , I , K UN ENTIER ;
       DEBUT
           K := 0 ;
           SI Bst <> NIL
               CREERFILE ( Queue ) ;
               ENFILER ( Queue , Bst ) ;
               TANTQUE ( NON FILEVIDE ( Queue ) )
                   APPEL Queuelengthxyzcount ( Queue , Countlevelnodes , Countxyzlevel ) ;
                   ECRIRE ( 'level ' , K , ':' , Countxyzlevel ) ;
                   POUR I := 1 , Countlevelnodes
                       DEFILER ( Queue , Temp ) ;
                       SI FG ( Temp ) <> NIL
                           ENFILER ( Queue , FG ( Temp ) ) ;
                       FSI ;
                       SI FD ( Temp ) <> NIL
                           ENFILER ( Queue , FD ( Temp ) ) ;
                       FSI ;
                   FPOUR ;
                   K := K + 1 ;
               FTQ ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Queuelengthxyzcount ( Queue1 , Length , Countxyz )
       SOIENT
           Queue1 , Queue2 DES FILES DE ARB DE CHAINE ;
           Temp UN ARB DE CHAINE ;
           Length , Countxyz DES ENTIER ;
       DEBUT
           Length := 0 ;
           Countxyz := 0 ;
           CREERFILE ( Queue2 ) ;
           TANTQUE ( NON FILEVIDE ( Queue1 ) )
               DEFILER ( Queue1 , Temp ) ;
               SI Beginwithxyz ( INFO ( Temp ) , X , Y , Z )
                   Countxyz := Countxyz + 1 ;
               FSI ;
               ENFILER ( Queue2 , Temp ) ;
               Length := Length + 1 ;
           FTQ ;
           TANTQUE ( NON FILEVIDE ( Queue2 ) )
               DEFILER ( Queue2 , Temp ) ;
               ENFILER ( Queue1 , Temp ) ;
           FTQ ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Singlewordsearch ( Bst1 , Bst2 , Bst3 , X , Y , Z , String , Singlesearchcounter ) : ARB DE CHAINE
       SOIENT
           Bst1 , Bst2 , Bst3 DES ARB DE CHAINE ;
           X , Y , Z DES CAR ;
           String UNE CHAINE ;
           Singlesearchcounter UN ENTIER ;
       DEBUT
           Singlesearchcounter := 0 ;
           SI Beginwithxyz ( String , X , Y , Z )
               Singlewordsearch := Searchbst ( Bst1 , X , Y , Z , String , Singlesearchcounter )
           SINON
               SI ( ( CARACT ( String , 1 ) > X ) OU ( CARACT ( String , 1 ) > Y ) OU ( CARACT ( String , 1 ) > Z ) )
                   Singlewordsearch := Searchbst ( Bst2 , X , Y , Z , String , Singlesearchcounter ) ;
               SINON
                   Singlewordsearch := Searchbst ( Bst3 , X , Y , Z , String , Singlesearchcounter ) ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Searchbst ( Bst , X , Y , Z , String , Singlesearchcounter ) : ARB DE CHAINE
       SOIENT
           Bst UN ARB DE CHAINE ;
           X , Y , Z DES CAR ;
           String UNE CHAINE ;
           Singlesearchcounter UN ENTIER ;
       DEBUT
           SI ( Bst = NIL )
               Searchbst := NIL ;
           SINON
               SI ( Cmp_string ( INFO ( Bst ) , String ) = 0 )
                   Searchbst := Bst ;
               SINON
                   SI ( Cmp_string ( INFO ( Bst ) , String ) = 1 )
                       Singlesearchcounter := Singlesearchcounter + 1 ;
                       Searchbst := Searchbst ( FG ( Bst ) , X , Y , Z , String , Singlesearchcounter ) ;
                   SINON
                       Singlesearchcounter := Singlesearchcounter + 1 ;
                       Searchbst := Searchbst ( FD ( Bst ) , X , Y , Z , String , Singlesearchcounter ) ;
                   FSI ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Rangesearch ( Bst1 , Bst2 , Bst3 , X , Y , Z , Word1 , Word2 , Rangesearchcounter )
       SOIENT
           Bst1 , Bst2 , Bst3 DES ARB DE CHAINES ;
           X , Y , Z DES CAR ;
           Word1 , Word2 DES CHAINES ;
           Rangesearchcounter UN ENTIER ;
       DEBUT
           Rangesearchcounter := 0 ;
           SI Beginwithxyz ( Word1 , X , Y , Z )
               APPEL Rangesearchbst ( Bst1 , Word1 , Word2 , Rangesearchcounter ) ;
           SINON
               SI ( ( CARACT ( Word1 , 1 ) > X ) OU ( CARACT ( Word1 , 1 ) > Y ) OU ( CARACT ( Word1 , 1 ) > Z ) )
                   APPEL Rangesearchbst ( Bst2 , Word1 , Word2 , Rangesearchcounter ) ;
               SINON
                   APPEL Rangesearchbst ( Bst3 , Word1 , Word2 , Rangesearchcounter ) ;
               FSI ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       ACTION Rangesearchbst ( Bst , Word1 , Word2 , Rangesearchcounter )
       SOIENT
           Bst , Temp1 DES ARB DE CHAINES ;
           Word1 , Word2 DES CHAINES ;
           Rangesearchcounter UN ENTIER ;
       DEBUT
           Temp1 := Searchleastgreater ( Bst , Word1 , Rangesearchcounter ) ;
           TANTQUE Temp1 <> NIL
               SI INFO ( Temp1 ) <= Word2
                   ECRIRE ( INFO ( Temp1 ) ) ;
                   Temp1 := Nextinorder ( Temp1 , Rangesearchcounter ) ;
               SINON
                   Temp1 := NIL ;
               FSI ;
           FTQ ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Searchleastgreater ( Bst , Word1 , Rangesearchcounter ) : ARB DE CHAINES
       SOIENT
           Bst , Temp2 , Resulting DES ARB DE CHAINES ;
           Word1 UNE CHAINE ;
           Rangesearchcounter UN ENTIER ;
       DEBUT
           Temp2 := Bst ;
           Resulting := NIL ;
           TANTQUE Temp2 <> NIL
               SI INFO ( Temp2 ) >= Word1
                   Resulting := Temp2 ;
                   Temp2 := FG ( Temp2 ) ;
               SINON
                   Temp2 := FD ( Temp2 ) ;
               FSI ;
               Rangesearchcounter := Rangesearchcounter + 1 ;
           FTQ ;
           Searchleastgreater := Resulting ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
       FONCTION Nextinorder ( Node , Rangesearchcounter ) : ARB DE CHAINES
       SOIENT
           Node , Temp3 , Temp4 DES ARB DE CHAINES ;
           Rangesearchcounter UN ENTIER ;
       DEBUT
           Temp4 := NIL ;
           SI Node = NIL
               Nextinorder := NIL ;
           SINON
               SI FD ( Node ) <> NIL
                   Temp3 := FD ( Node ) ;
                   Rangesearchcounter := Rangesearchcounter + 1 ;
                   TANTQUE ( FG ( Temp3 ) <> NIL )
                       Rangesearchcounter := Rangesearchcounter + 1 ;
                       Temp3 := FG ( Temp3 ) ;
                   FTQ ;
                   Temp4 := Temp3 ;
               SINON
                   Temp3 := Node ;
                   TANTQUE ( ( PERE ( Temp3 ) <> NIL ) ET ( Temp4 = NIL ) )
                       Rangesearchcounter := Rangesearchcounter + 1 ;
                       SI Temp3 = FG ( PERE ( Temp3 ) )
                           Temp4 := PERE ( Temp3 ) ;
                       SINON
                           Temp3 := PERE ( Temp3 ) ;
                       FSI ;
                   FTQ ;
               FSI ;
               Nextinorder := Temp4 ;
           FSI ;
       FIN
      /*////////////////////////////////////////////////////////////////////////*/
