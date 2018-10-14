
/* ******************************* c202.c *********************************** */
/*  Poedm`it: Algoritmy (IAL) - FIT VUT v Brn`i                                 */
/*  Úkol: c202 - Zásobník znak`u v poli                                        */
/*  Referen`ení implementace: Petr Poikryl, 1994                               */
/*  Vytvooil: Václav Topinka, záoí 2005                                       */
/*  Úpravy: Bohuslav Koena, oíjen 2013                                        */
/* ************************************************************************** */
/*
** Implementujte datový typ zásobník znak`u ve statickém poli. ADT zásobník je
** reprezentován záznamem typu tStack. Statické pole 'arr' je indexováno
** do maximální hodnoty STACK_SIZE. Polouka záznamu 'top' ukazuje na prvek
** na vrcholu zásobníku. Prázdnému zásobníku odpovídá hodnota top == -1,
** zásobníku s jedním prvkem hodnota 0, atd. Poesnou definici typ`u neleznete
** v hlavi`ekovém souboru c202.h.
**
** Implementujte následující funkce:
**
**    stackInit .... inicializace zásobníku
**    stackEmpty ... test na prázdnost zásobníku
**    stackFull .... test na zapln`inost zásobníku
**    stackTop ..... poe`ete hodnotu z vrcholu zásobníku
**    stackPop ..... odstraní prvek z vrcholu zásobníku
**    stackPush .... vlouí prvku do zásobníku
**
** Své oe+/-ení ú`eeln`i komentujte!
**
** Terminologická poznámka: Jazyk C nepouuívá pojem procedura.
** Proto zde pouuíváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c202.h"

int STACK_SIZE = MAX_STACK;
int solved;

void stackError ( int error_code ){
/*   ----------
** Vytiskne upozorn`iní, ue do+/-lo k chyb`i poi práci se zásobníkem.
**
** TUTO FUNKCI, PROSÍME, NEUPRAVUJTE!
*/
	static const char* SERR_STRINGS[MAX_SERR+1] = {"Unknown error","Stack error: INIT","Stack error: PUSH","Stack error: TOP"};
	if ( error_code <= 0 || error_code > MAX_SERR )
		error_code = 0;
	printf ( "%s\n", SERR_STRINGS[error_code] );
	err_flag = 1;
}

void stackInit ( tStack* s ) {
/*   ---------
** Provede inicializaci zásobníku - nastaví vrchol zásobníku.
** Hodnoty ve statickém poli neupravujte - po inicializaci zásobníku
** jsou nedefinované.
**
** V poípad`i, ue funkce dostane jako parametr s == NULL,
** volejte funkci stackError(SERR_INIT). U ostatních funkcí pro zjednodu+/-ení
** poedpokládejte, ue tato situace nenastane.
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
** Vrací nenulovou hodnotu, pokud je zásobník prázdný, jinak vrací hodnotu 0.
** Funkci implementujte jako jediný poíkaz. Vyvarujte se zejména konstrukce
** typu "if ( true ) b=true else b=false".
*/

  return(s->top == -1);//-1 je vychozi hodnota pro prazdny zasobnik (zadani)
}

int stackFull ( const tStack* s ) {
/*  ---------
** Vrací nenulovou hodnotu, je-li zásobník plný, jinak vrací hodnotu 0.
** Dejte si zde pozor na `eastou programátorskou chybu "o jedni`eku"
** a doboe se zamyslete, kdy je zásobník plný, jestliue m`uue obsahovat
** nejvý+/-e STACK_SIZE prkv`u a první prvek je vlouen na pozici 0.
**
** Funkci implementujte jako jediný poíkaz.
*/

  //Vyhodnocovaci podminka je urcena ze zadani.
  return((s->top == (STACK_SIZE - 1)) && (s->arr[0] != '\0'));
}

void stackTop ( const tStack* s, char* c ) {
/*   --------
** Vrací znak z vrcholu zásobníku prostoednictvím parametru c.
** Tato operace ale prvek z vrcholu zásobníku neodstra`ouje.
** Volání operace Top poi prázdném zásobníku je nekorektní
** a o+/-etoete ho voláním funkce stackError(SERR_TOP).
**
** Pro ov`ioení, zda je zásobník prázdný, pouuijte doíve definovanou
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
** Odstraní prvek z vrcholu zásobníku. Pro ov`ioení, zda je zásobník prázdný,
** pouuijte doíve definovanou funkci stackEmpty.
**
** Vyvolání operace Pop poi prázdném zásobníku je sice podezoelé a m`uue
** signalizovat chybu v algoritmu, ve kterém je zásobník pouuit, ale funkci
** pro o+/-etoení chyby zde nevolejte (m`uueme zásobník ponechat prázdný).
** Spí+/-e neu volání chyby by se zde hodilo vypsat varování, cou v+/-ak pro
** jednoduchost ned`iláme.
**
*/

  if(!stackEmpty(s)){
    s->arr[s->top] = '\0';//Vlozim na vrchol zasobniku znak NUL.
    s->top--;//Snizim vrchol zasobniku.
  }
}


void stackPush ( tStack* s, char c ) {
/*   ---------
** Vlouí znak na vrchol zásobníku. Pokus o vlouení prvku do plného zásobníku
** je nekorektní a o+/-etoete ho voláním procedury stackError(SERR_PUSH).
**
** Pro ov`ioení, zda je zásobník plný, pouuijte doíve definovanou
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
