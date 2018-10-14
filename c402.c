
/* c402.c: ********************************************************************}
{* T�ma: Nerekurzivn� implementace operac� nad BVS 
**                                     Implementace: Petr P�ikryl, prosinec 1994
**                                           �pravy: Petr P�ikryl, listopad 1997
**                                                     Petr P�ikryl, kv�ten 1998
**			  	                        P�evod do jazyka C: Martin Tu�ek, srpen 2005
**                                         �pravy: Bohuslav K�ena, listopad 2009
**                                         Upravy: Karel Masarik, rijen 2013
**
** S vyu�it�m dynamick�ho p�id�lov�n� pam�ti, implementujte NEREKURZIVN�
** n�sleduj�c� operace nad bin�rn�m vyhled�vac�m stromem (p�edpona BT znamen�
** Binary Tree a je u identifik�tor� uvedena kv�li mo�n� kolizi s ostatn�mi
** p��klady):
**
**     BTInit .......... inicializace stromu
**     BTInsert ........ nerekurzivn� vlo�en� nov�ho uzlu do stromu
**     BTPreorder ...... nerekurzivn� pr�chod typu pre-order
**     BTInorder ....... nerekurzivn� pr�chod typu in-order
**     BTPostorder ..... nerekurzivn� pr�chod typu post-order
**     BTDisposeTree ... zru� v�echny uzly stromu
**
** U v�ech funkc�, kter� vyu��vaj� n�kter� z pr�chod� stromem, implementujte
** pomocnou funkci pro nalezen� nejlev�j��ho uzlu v podstromu.
**
** P�esn� definice typ� naleznete v souboru c402.h. Uzel stromu je typu tBTNode,
** ukazatel na n�j je typu tBTNodePtr. Jeden uzel obsahuje polo�ku int Cont,
** kter� sou�asn� slou�� jako u�ite�n� obsah i jako vyhled�vac� kl�� 
** a ukazatele na lev� a prav� podstrom (LPtr a RPtr).
**
** P��klad slou�� zejm�na k procvi�en� nerekurzivn�ch z�pis� algoritm�
** nad stromy. Ne� za�nete tento p��klad �e�it, prostudujte si d�kladn�
** principy p�evodu rekurzivn�ch algoritm� na nerekurzivn�. Programov�n�
** je p�edev��m in�en�rsk� discipl�na, kde op�tn� objevov�n� Ameriky nem�
** m�sto. Pokud se V�m zd�, �e by n�co �lo zapsat optim�ln�ji, promyslete
** si v�echny detaily Va�eho �e�en�. Pov�imn�te si typick�ho um�st�n� akc�
** pro r�zn� typy pr�chod�. Zamyslete se nad modifikac� �e�en�ch algoritm�
** nap��klad pro v�po�et po�tu uzl� stromu, po�tu list� stromu, v��ky stromu
** nebo pro vytvo�en� zrcadlov�ho obrazu stromu (pouze pop�ehazov�n� ukazatel�
** bez vytv��en� nov�ch uzl� a ru�en� star�ch).
**
** P�i pr�chodech stromem pou�ijte ke zpracov�n� uzlu funkci BTWorkOut().
** Pro zjednodu�en� pr�ce m�te p�edem p�ipraveny z�sobn�ky pro hodnoty typu
** bool a tBTNodePtr. Pomocnou funkci BTWorkOut ani funkce pro pr�ci
** s pomocn�mi z�sobn�ky neupravujte 
** Pozor! Je t�eba spr�vn� rozli�ovat, kdy pou��t dereferen�n� oper�tor *
** (typicky p�i modifikaci) a kdy budeme pracovat pouze se samotn�m ukazatelem 
** (nap�. p�i vyhled�v�n�). V tomto p��kladu v�m napov� prototypy funkc�.
** Pokud pracujeme s ukazatelem na ukazatel, pou�ijeme dereferenci.
**/

#include "c402.h"
int solved;

void BTWorkOut (tBTNodePtr Ptr)		{
/*   ---------
** Pomocn� funkce, kterou budete volat p�i pr�chodech stromem pro zpracov�n�
** uzlu ur�en�ho ukazatelem Ptr. Tuto funkci neupravujte.
**/
			
	if (Ptr==NULL) 
    printf("Chyba: Funkce BTWorkOut byla vol�na s NULL argumentem!\n");
  else 
    printf("V�pis hodnoty dan�ho uzlu> %d\n",Ptr->Cont);
}
	
/* -------------------------------------------------------------------------- */
/*
** Funkce pro z�sobn�k hotnot typu tBTNodePtr. Tyto funkce neupravujte.
**/

void SInitP (tStackP *S)  
/*   ------
** Inicializace z�sobn�ku.
**/
{
	S->top = 0;  
}	

void SPushP (tStackP *S, tBTNodePtr ptr)
/*   ------
** Vlo�� hodnotu na vrchol z�sobn�ku.
**/
{ 
                 /* P�i implementaci v poli m��e doj�t k p�ete�en� z�sobn�ku. */
  if (S->top==MAXSTACK) 
    printf("Chyba: Do�lo k p�ete�en� z�sobn�ku s ukazateli!\n");
  else {  
		S->top++;  
		S->a[S->top]=ptr;
	}
}	

tBTNodePtr STopPopP (tStackP *S)
/*         --------
** Odstran� prvek z vrcholu z�sobn�ku a sou�asn� vr�t� jeho hodnotu.
**/
{
                            /* Operace nad pr�zdn�m z�sobn�kem zp�sob� chybu. */
	if (S->top==0)  {
		printf("Chyba: Do�lo k podte�en� z�sobn�ku s ukazateli!\n");
		return(NULL);	
	}	
	else {
		return (S->a[S->top--]);
	}	
}

bool SEmptyP (tStackP *S)
/*   -------
** Je-li z�sobn�k pr�zdn�, vr�t� hodnotu true.
**/
{
  return(S->top==0);
}	

/* -------------------------------------------------------------------------- */
/*
** Funkce pro z�sobn�k hotnot typu bool. Tyto funkce neupravujte.
*/

void SInitB (tStackB *S) {
/*   ------
** Inicializace z�sobn�ku.
**/

	S->top = 0;  
}	

void SPushB (tStackB *S,bool val) {
/*   ------
** Vlo�� hodnotu na vrchol z�sobn�ku.
**/
                 /* P�i implementaci v poli m��e doj�t k p�ete�en� z�sobn�ku. */
	if (S->top==MAXSTACK) 
		printf("Chyba: Do�lo k p�ete�en� z�sobn�ku pro boolean!\n");
	else {
		S->top++;  
		S->a[S->top]=val;
	}	
}

bool STopPopB (tStackB *S) {
/*   --------
** Odstran� prvek z vrcholu z�sobn�ku a sou�asn� vr�t� jeho hodnotu.
**/
                            /* Operace nad pr�zdn�m z�sobn�kem zp�sob� chybu. */
	if (S->top==0) {
		printf("Chyba: Do�lo k podte�en� z�sobn�ku pro boolean!\n");
		return(NULL);	
	}	
	else {  
		return(S->a[S->top--]); 
	}	
}

bool SEmptyB (tStackB *S) {
/*   -------
** Je-li z�sobn�k pr�zdn�, vr�t� hodnotu true.
**/
  return(S->top==0);
}

/* -------------------------------------------------------------------------- */
/*
** N�sleduje j�dro dom�c� �lohy - funkce, kter� m�te implementovat. 
*/

void BTInit (tBTNodePtr *RootPtr)	{
/*   ------
** Provede inicializaci bin�rn�ho vyhled�vac�ho stromu.
**
** Inicializaci sm� program�tor volat pouze p�ed prvn�m pou�it�m bin�rn�ho
** stromu, proto�e neuvol�uje uzly nepr�zdn�ho stromu (a ani to d�lat nem��e,
** proto�e p�ed inicializac� jsou hodnoty nedefinovan�, tedy libovoln�).
** Ke zru�en� bin�rn�ho stromu slou�� procedura BTDisposeTree.
**	
** V�imn�te si, �e zde se poprv� v hlavi�ce objevuje typ ukazatel na ukazatel,	
** proto je t�eba p�i pr�ci s RootPtr pou��t dereferen�n� oper�tor *.
**/
	
	*RootPtr = NULL;// Inicializace ukazatele na strom
	return;
}

void BTInsert (tBTNodePtr *RootPtr, int Content) {
/*   --------
** Vlo�� do stromu nov� uzel s hodnotou Content.
**
** Z pohledu vkl�d�n� ch�pejte vytv��en� strom jako bin�rn� vyhled�vac� strom,
** kde uzly s hodnotou men�� ne� m� otec le�� v lev�m podstromu a uzly v�t��
** le�� vpravo. Pokud vkl�dan� uzel ji� existuje, neprov�d� se nic (dan� hodnota
** se ve stromu m��e vyskytnout nejv��e jednou). Pokud se vytv��� nov� uzel,
** vznik� v�dy jako list stromu. Funkci implementujte nerekurzivn�.
**/

	tBTNodePtr p_tmp = NULL;
	tBTNodePtr p_tmp2 = NULL;
	
	if(*RootPtr == NULL)// Pokud je strom prazdny
	{
		if((p_tmp = malloc(sizeof(struct tBTNode))) == NULL)
      return;
		*RootPtr = p_tmp;
		p_tmp->Cont = Content;// Vlozeni obsahu uzlu
		p_tmp->LPtr = NULL;// Levy podstrom nastavim na NULL
		p_tmp->RPtr = p_tmp->LPtr;// Pravy podstrom nastavim na levy
		return;
	}
	
	else{
		p_tmp = (*RootPtr);
		while(TRUE){
			if(p_tmp->Cont == Content)
				return;
      
      // Pridam podstrom jako levy.
			if((p_tmp->Cont > Content) && (p_tmp->LPtr == NULL)){ 
				if((p_tmp2 = malloc(sizeof(struct tBTNode))) == NULL)
					return;
				else{
					p_tmp->LPtr = p_tmp2;
					p_tmp2->Cont = Content;
					p_tmp2->LPtr = NULL;
					p_tmp2->RPtr = NULL;
				}
				
				return;
			}
			
      // Pridam podstrom jako pravy.
			else if((p_tmp->Cont < Content) && (p_tmp->RPtr == NULL)){
				if((p_tmp2 = malloc(sizeof(struct tBTNode))) == NULL)
					return;
				
				else{
					p_tmp->RPtr = p_tmp2;
					p_tmp2->Cont = Content;
					p_tmp2->LPtr = NULL;
					p_tmp2->RPtr = NULL;
				}
			
				return;
			}
			
			if(p_tmp->Cont < Content){
				p_tmp = p_tmp->RPtr;
				continue;
			}
			
			else if(p_tmp->Cont > Content){
				p_tmp = p_tmp->LPtr;
				continue;
			}
		}
	}
	
	return;
}

/*                                  PREORDER                                  */

void Leftmost_Preorder (tBTNodePtr ptr, tStackP *Stack)	{
/*   -----------------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Preorder nav�t�ven� uzly zpracujeme vol�n�m funkce BTWorkOut()
** a ukazatele na n� is ulo��me do z�sobn�ku.
**/
	
	while(TRUE){
    if(ptr == NULL)// Pokud jsem na konci.
      break;
    BTWorkOut(ptr);
    SPushP(Stack, ptr);
    ptr = ptr->LPtr;
	}
  
  return;
}

void BTPreorder (tBTNodePtr RootPtr)	{
/*   ----------
** Pr�chod stromem typu preorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Preorder a z�sobn�ku ukazatel�. Zpracov�n� jednoho uzlu stromu
** realizujte jako vol�n� funkce BTWorkOut(). 
**/

  tStackP stack_user;

  SInitP(&stack_user);
  Leftmost_Preorder(RootPtr, &stack_user);
  
  while(TRUE){
    if(SEmptyP(&stack_user) == TRUE)
      return;
    
    Leftmost_Preorder(STopPopP(&stack_user)->RPtr, &stack_user);
  }
  
  return;
  }

/*                                  INORDER                                   */ 

void Leftmost_Inorder(tBTNodePtr ptr, tStackP *Stack)		{
/*   ----------------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Inorder ukl�d�me ukazatele na v�echny nav�t�ven� uzly do
** z�sobn�ku. 
**/
	
	while(TRUE){
    if(ptr == NULL)
      return;
    SPushP(Stack, ptr);
    ptr = ptr->LPtr;
  }
  
  return;
}

void BTInorder (tBTNodePtr RootPtr)	{
/*   ---------
** Pr�chod stromem typu inorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Inorder a z�sobn�ku ukazatel�. Zpracov�n� jednoho uzlu stromu
** realizujte jako vol�n� funkce BTWorkOut(). 
**/

  tBTNodePtr p_tmp = RootPtr;
  tStackP stack_user;
  
  SInitP(&stack_user);
  Leftmost_Inorder(RootPtr, &stack_user);
  
  while(TRUE){
    if(SEmptyP(&stack_user) == TRUE)
      return;
    
    p_tmp = STopPopP(&stack_user);
    BTWorkOut(p_tmp);
    Leftmost_Inorder(p_tmp->RPtr, &stack_user);
  }
  
  return;
}

/*                                 POSTORDER                                  */ 

void Leftmost_Postorder (tBTNodePtr ptr, tStackP *StackP, tStackB *StackB) {
/*           --------
** Jde po lev� v�tvi podstromu, dokud nenaraz� na jeho nejlev�j�� uzel.
**
** P�i pr�chodu Postorder ukl�d�me ukazatele na nav�t�ven� uzly do z�sobn�ku
** a sou�asn� do z�sobn�ku bool hodnot ukl�d�me informaci, zda byl uzel
** nav�t�ven poprv� a �e se tedy je�t� nem� zpracov�vat. 
**/

		while(TRUE){
      if(ptr == NULL)
        return;
      
      else{
        SPushB(StackB, TRUE);// Ulozeni informace o navstiveni.
        SPushP(StackP, ptr);
      }
      
      ptr = ptr->LPtr;// Posun doleva.
    }
    
    return;
}

void BTPostorder (tBTNodePtr RootPtr)	{
/*           -----------
** Pr�chod stromem typu postorder implementovan� nerekurzivn� s vyu�it�m funkce
** Leftmost_Postorder, z�sobn�ku ukazatel� a z�sobn�ku hotdnot typu bool.
** Zpracov�n� jednoho uzlu stromu realizujte jako vol�n� funkce BTWorkOut(). 
**/

  tBTNodePtr p_tmp = RootPtr;
  tStackB stack_user_B;
  SInitB(&stack_user_B);
  tStackP stack_user_P;
  SInitP(&stack_user_P);
  
  Leftmost_Postorder(p_tmp, &stack_user_P, &stack_user_B);
  
  while(TRUE){
    if(SEmptyP(&stack_user_P) == TRUE)
      return;
    
    p_tmp = STopPopP(&stack_user_P);
    SPushP(&stack_user_P, p_tmp);
    
    // Byl jsem v pravem podstromu
    if(STopPopB(&stack_user_B) == FALSE){
      STopPopP(&stack_user_P);
      BTWorkOut(p_tmp);
    }
    
    // Byl jsem v levem podstromu
    else{
      SPushB(&stack_user_B, FALSE);
      p_tmp = p_tmp->RPtr;
      Leftmost_Postorder(p_tmp, &stack_user_P, &stack_user_B);
    }
  }
  
  return;
}


void BTDisposeTree (tBTNodePtr *RootPtr)	{
/*   -------------
** Zru�� v�echny uzly stromu a korektn� uvoln� jimi zabranou pam�.
**
** Funkci implementujte nerekurzivn� s vyu�it�m z�sobn�ku ukazatel�.
**/

	tStackP stack_user;
  SInitP(&stack_user);

  if((*RootPtr) == NULL)
    return;
    
  else{
    tBTNodePtr p_tmp = NULL;
    tBTNodePtr p_tmp2 = NULL;

    while(TRUE){
      // Podminka, ktera ukonci cyklus.
      if((SEmptyP(&stack_user)) && ((*RootPtr) == NULL))
        return;
      
      // Strom je smazany a zasobnik je prazdny.
      else if(((*RootPtr) == NULL) && (!SEmptyP(&stack_user)))   
        (*RootPtr) = STopPopP(&stack_user);// Ulozim z vrcholu zasobniku hodnotu.
      
      // Pokud strom neni vymazany.
      else{
        if((*RootPtr)->RPtr != NULL)
          SPushP(&stack_user, (*RootPtr)->RPtr);// Ulozim si hodnotu na zasobnik.
        
        p_tmp2 = (*RootPtr)->LPtr;// Ulozeni ukazatele na podstrom.
        p_tmp = (*RootPtr);
        free(p_tmp);// Uvolneni uzlu stromu z pameti.
        (*RootPtr) = p_tmp2;
      }
    }
  }
  
  return;
}

/* konec c402.c */

