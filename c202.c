
/* ******************************* c202.c *********************************** */
/*  Poedm`it: Algoritmy (IAL) - FIT VUT v Brn`i                                 */
/*  �kol: c202 - Z�sobn�k znak`u v poli                                        */
/*  Referen`en� implementace: Petr Poikryl, 1994                               */
/*  Vytvooil: V�clav Topinka, z�o� 2005                                       */
/*  �pravy: Bohuslav Koena, o�jen 2013                                        */
/* ************************************************************************** */
/*
** Implementujte datov� typ z�sobn�k znak`u ve statick�m poli. ADT z�sobn�k je
** reprezentov�n z�znamem typu tStack. Statick� pole 'arr' je indexov�no
** do maxim�ln� hodnoty STACK_SIZE. Polouka z�znamu 'top' ukazuje na prvek
** na vrcholu z�sobn�ku. Pr�zdn�mu z�sobn�ku odpov�d� hodnota top == -1,
** z�sobn�ku s jedn�m prvkem hodnota 0, atd. Poesnou definici typ`u neleznete
** v hlavi`ekov�m souboru c202.h.
**
** Implementujte n�sleduj�c� funkce:
**
**    stackInit .... inicializace z�sobn�ku
**    stackEmpty ... test na pr�zdnost z�sobn�ku
**    stackFull .... test na zapln`inost z�sobn�ku
**    stackTop ..... poe`ete hodnotu z vrcholu z�sobn�ku
**    stackPop ..... odstran� prvek z vrcholu z�sobn�ku
**    stackPush .... vlou� prvku do z�sobn�ku
**
** Sv� oe+/-en� �`eeln`i komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepouu�v� pojem procedura.
** Proto zde pouu�v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**
**/

#include "c202.h"

int STACK_SIZE = MAX_STACK;
int solved;

void stackError ( int error_code ){
/*   ----------
** Vytiskne upozorn`in�, ue do+/-lo k chyb`i poi pr�ci se z�sobn�kem.
**
** TUTO FUNKCI, PROS�ME, NEUPRAVUJTE!
*/
	static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
	if ( error_code <= 0 || error_code > MAX_SERR )
		error_code = 0;
	printf ( "%s\n", SERR_STRINGS[error_code] );
	err_flag = 1;
}

void stackInit ( tStack* s ) {
/*   ---------
** Provede inicializaci z�sobn�ku - nastav� vrchol z�sobn�ku.
** Hodnoty ve statick�m poli neupravujte - po inicializaci z�sobn�ku
** jsou nedefinovan�.
**
** V po�pad`i, ue funkce dostane jako parametr s == NULL,
** volejte funkci stackError(SERR_INIT). U ostatn�ch funkc� pro zjednodu+/-en�
** poedpokl�dejte, ue tato situace nenastane.
*/

//Nastaveni vrcholu zasobniku podle vyse uvedenich podminek.
  if (s == NULL){
    stackError(SERR_INIT);
  }
  else{
    s->top = -1;//Nastaveni hodnoty prazdnemu zasobniku.
  }
}

int stackEmpty ( const tStack* s ) {
/*  ----------
** Vrac� nenulovou hodnotu, pokud je z�sobn�k pr�zdn�, jinak vrac� hodnotu 0.
** Funkci implementujte jako jedin� po�kaz. Vyvarujte se zejm�na konstrukce
** typu "if ( true ) b=true else b=false".
*/

  return(s->top == -1);//-1 je vychozi hodnota pro prazdny zasobnik (zadani)
}

int stackFull ( const tStack* s ) {
/*  ---------
** Vrac� nenulovou hodnotu, je-li z�sobn�k pln�, jinak vrac� hodnotu 0.
** Dejte si zde pozor na `eastou program�torskou chybu "o jedni`eku"
** a doboe se zamyslete, kdy je z�sobn�k pln�, jestliue m`uue obsahovat
** nejv�+/-e STACK_SIZE prkv`u a prvn� prvek je vlouen na pozici 0.
**
** Funkci implementujte jako jedin� po�kaz.
*/

  //Vyhodnocovaci podminka je urcena ze zadani.
  return((s->top == (STACK_SIZE - 1)) && (s->arr[0] != '\0'));
}

void stackTop ( const tStack* s, char* c ) {
/*   --------
** Vrac� znak z vrcholu z�sobn�ku prostoednictv�m parametru c.
** Tato operace ale prvek z vrcholu z�sobn�ku neodstra`ouje.
** Vol�n� operace Top poi pr�zdn�m z�sobn�ku je nekorektn�
** a o+/-etoete ho vol�n�m funkce stackError(SERR_TOP).
**
** Pro ov`ioen�, zda je z�sobn�k pr�zdn�, pouuijte do�ve definovanou
** funkci stackEmpty.
*/


  if (stackEmpty(s)){
    stackError(SERR_TOP);
  }
  else{
    *c = s->arr[s->top];//Do c ulozim znak z vrcholu zasobniku.
  }
}


void stackPop ( tStack* s ) {
/*   --------
** Odstran� prvek z vrcholu z�sobn�ku. Pro ov`ioen�, zda je z�sobn�k pr�zdn�,
** pouuijte do�ve definovanou funkci stackEmpty.
**
** Vyvol�n� operace Pop poi pr�zdn�m z�sobn�ku je sice podezoel� a m`uue
** signalizovat chybu v algoritmu, ve kter�m je z�sobn�k pouuit, ale funkci
** pro o+/-etoen� chyby zde nevolejte (m`uueme z�sobn�k ponechat pr�zdn�).
** Sp�+/-e neu vol�n� chyby by se zde hodilo vypsat varov�n�, cou v+/-ak pro
** jednoduchost ned`il�me.
**
*/

  if(!stackEmpty(s)){
    s->arr[s->top] = '\0';//Vlozim na vrchol zasobniku znak NUL.
    s->top--;//Snizim vrchol zasobniku.
  }
}


void stackPush ( tStack* s, char c ) {
/*   ---------
** Vlou� znak na vrchol z�sobn�ku. Pokus o vlouen� prvku do pln�ho z�sobn�ku
** je nekorektn� a o+/-etoete ho vol�n�m procedury stackError(SERR_PUSH).
**
** Pro ov`ioen�, zda je z�sobn�k pln�, pouuijte do�ve definovanou
** funkci stackFull.
*/

  if(stackFull(s)){//Overeni zda zasobnik neni plny.
    stackError(SERR_PUSH);
  }
  else{
    s->top++;//Posunu se na prazdny vrchol zasobniku.
    s->arr[s->top] = c;//Vlozim novy znak do zasobniku.
  }
}

/* Konec c202.c */
