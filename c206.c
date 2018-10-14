
/* c206.c **********************************************************}
{* Téma: Dvousm`irn`i vázaný lineární seznam
**
**                   Návrh a referen`ení implementace: Bohuslav Koena, oíjen 2001
**                            Poepracované do jazyka C: Martin Tu`eek, oíjen 2004
**                                             Úpravy: Bohuslav Koena, oíjen 2013
**
** Implementujte abstraktní datový typ dvousm`irn`i vázaný lineární seznam.
** Uuite`eným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován prom`innou
** typu tDLList (DL znamená Double-Linked a slouuí pro odli+/-ení
** jmen konstant, typ`u a funkcí od jmen u jednosm`irn`i vázaného lineárního
** seznamu). Definici konstant a typ`u naleznete v hlavi`ekovém souboru c206.h.
**
** Va+/-ím úkolem je implementovat následující operace, které spolu
** s vý+/-e uvedenou datovou `eástí abstrakce tvooí abstraktní datový typ
** obousm`irn`i vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu poed prvním pouuitím,
**      DLDisposeList ... zru+/-ení v+/-ech prvk`u seznamu,
**      DLInsertFirst ... vlouení prvku na za`eátek seznamu,
**      DLInsertLast .... vlouení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zru+/-í první prvek seznamu,
**      DLDeleteLast .... zru+/-í poslední prvek seznamu,
**      DLPostDelete .... ru+/-í prvek za aktivním prvkem,
**      DLPreDelete ..... ru+/-í prvek poed aktivním prvkem,
**      DLPostInsert .... vlouí nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vlouí nový prvek poed aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... poepí+/-e obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal+/-í prvek seznamu,
**      DLPred .......... posune aktivitu na poedchozí prvek seznamu,
**      DLActive ........ zji+/-"Yuje aktivitu seznamu.
**
** Poi implementaci jednotlivých funkcí nevolejte uádnou z funkcí
** implementovaných v rámci tohoto poíkladu, není-li u funkce
** explicitn`i uvedeno n`ico jiného.
**
** Nemusíte o+/-etoovat situaci, kdy místo legálního ukazatele na seznam
** poedá n`ikdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn`i komentujte!
**
** Terminologická poznámka: Jazyk C nepouuívá pojem procedura.
** Proto zde pouuíváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn`iní na to, ue do+/-lo k chyb`i.
** Tato funkce bude volána z n`ikterých dále implementovaných operací.
**/
    printf ("*ERROR* This program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální prom`inná -- poíznak o+/-etoení chyby */
    return;
}

void DLInitList (tDLList *L)	{
/*
** Provede inicializaci seznamu L poed jeho prvním pouuitím (tzn. uádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provád`it nad jiu inicializovaným
** seznamem, a proto tuto mounost neo+/-etoujte. Vudy poedpokládejte,
** ue neinicializované prom`inné mají nedefinovanou hodnotu.
**/

  L->Act = NULL;// Ukazatel na aktualni prvek a jeho inicializace.
  L->First = NULL;// Ukazatel na prvni prvek a jeho inicializace.
  L->Last = NULL;// Ukazatel na posledni prvek a jeho inicializace.
}

void DLDisposeList (tDLList *L)	{
/*
** Zru+/-í v+/-echny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Ru+/-ené prvky seznamu budou korektn`i
** uvoln`iny voláním operace free.
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  while (L->First != NULL){
    p_tmp = L->First->rptr;/* Ulozeni do pomocneho promenne ukazatel na
                              nasledujici prvek za prvek seznamu.*/
    free(L->First);
    L->First = p_tmp;
  }

  // Nastaveni ukazatelu na hodnotu pri inicializaci.
  L->Act = NULL;
  L->Last = NULL;
}

void DLInsertFirst (tDLList *L, int val)	{
/*
** Vlouí nový prvek na za`eátek seznamu L.
** V poípad`i, ue není dostatek pam`iti pro nový prvek poi operaci malloc,
** volá funkci DLError().
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  // Osetreni pri spatne alokaci nebo nedostatku pameti.
  if((p_tmp = (tDLElemPtr) malloc(sizeof(struct tDLElem))) == NULL){
    DLError();
    return;
  }

  // Nastaveni ukazatelu na vychozi hodnoty.
  p_tmp->data = val;
  p_tmp->lptr = NULL;
  p_tmp->rptr = NULL;

  //Pokud je seznam prazdny, tak prvni prvek je zaroven poslednim prvkem seznamu.
  if ((L->First == NULL) && (L->Last == NULL)){
    L->First = p_tmp;
    L->Last = p_tmp;
  }

  // Pokud seznam nebyl prazdny.
  else{
    p_tmp->rptr = L->First;// Navazani prvniho prvku na druhy prvek.
    L->First->lptr = p_tmp;// Navazani druheho prvku na prvni prvek.
    L->First = p_tmp;// Nastaveni prvniho prvku.
  }
}

void DLInsertLast(tDLList *L, int val)	{
/*
** Vlouí nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V poípad`i, ue není dostatek pam`iti pro nový prvek poi operaci malloc,
** volá funkci DLError().
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  // Osetreni pri spatne alokaci nebo nedostatku pameti.
  if((p_tmp = (tDLElemPtr) malloc(sizeof(struct tDLElem))) == NULL){
    DLError();
    return;
  }

  // Nastaveni ukazatelu na vychozi hodnoty.
  p_tmp->data = val;
  p_tmp->lptr = NULL;
  p_tmp->rptr = NULL;

  //Pokud je seznam prazdny, tak prvni prvek je zaroven poslednim prvkem seznamu.
  if((L->First == NULL) && (L->Last == NULL)){
    L->Last = p_tmp;
    L->First = p_tmp;
  }

  // Pokud seznam nebyl prazdny.
  else{
    p_tmp->lptr = L->Last;// Navazani prvniho prvku na druhy prvek.
    L->Last->rptr = p_tmp;// Navazani druheho prvku na prvni prvek.
    L->Last = p_tmp;// Nastaveni prvniho prvku.
  }
}

void DLFirst (tDLList *L)	{
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný poíkaz (nepo`eítáme-li return),
** aniu byste testovali, zda je seznam L prázdný.
**/

  L->Act = L->First;
}

void DLLast (tDLList *L)	{
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný poíkaz (nepo`eítáme-li return),
** aniu byste testovali, zda je seznam L prázdný.
**/

  L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, int *val)	{
/*
** Prostoednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

  if((L->First == NULL) && (L->Last == NULL)){
    DLError();
  }

  else{
    *val = L->First->data;
  }
}

void DLCopyLast (tDLList *L, int *val)	{
/*
** Prostoednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

  if((L->First == NULL) && (L->Last == NULL)){
    DLError();
  }

  else{
    *val = L->Last->data;
  }
}

void DLDeleteFirst (tDLList *L)	{
/*
** Zru+/-í první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se ned`ije.
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  // Pokud je seznam prazdny nic se nedela.
  if(L->First == NULL){
    return;
  }

  // Pokud je aktivni prvni prvek seznamu, tak zrusim aktivitu.
  if(L->First == L->Act){
    L->Act = NULL;
  }

  // Pokud je prvni prvek i poslednim prvkem, zrusim posledni prvek.
  if(L->First == L->Last){
    L->Last = NULL;
  }

  p_tmp = L->First->rptr;// Zalohuju si dalsi prvek v seznamu.
  free(L->First);
  L->First = p_tmp;/* Obnoveni prvniho prvku v seznamu.
                      Na prvni prvek dam druhy prvek.*/
  if(L->First->lptr != NULL){
    L->First->lptr = NULL;/* Ukazatel doleva na prvnim prvku se
                             musi rovnat NULL.*/
  }
}

void DLDeleteLast (tDLList *L)	{
/*
** Zru+/-í poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se ned`ije.
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  if(L->Last == NULL){
    return;
  }

  // Pokud je aktivni posledni prvek seznamu, tak zrusim aktivitu.
  if(L->Last == L->Act){
    L->Act = NULL;
  }

  // Pokud je prvni prvek i poslednim prvkem, zrusim posledni prvek.
  if(L->First == L->Last){
    L->First = NULL;
  }

  p_tmp = L->Last->lptr;// Zalohuju si dalsi prvek v seznamu.
  free(L->Last);
  L->Last = p_tmp;/* Obnoveni posledniho prvku v seznamu.
                     Na posledni prvek dam predposledni prvek.*/
  if(L->Last != NULL){
    L->Last->rptr = NULL;/* Ukazatel doprava se na poslednim prvku
                            musi rovnat NULL.*/
  }
}

void DLPostDelete (tDLList *L)	{
/*
** Zru+/-í prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se ned`ije.
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  if((L->Act == NULL) || (L->Act == L->Last)){
    return;
  }

  p_tmp = L->Act->rptr;// Ulozeni pozice ruseneho prvku.

  // Pokud neni nami ruseny prvek zaroven poslednim prvkem seznamu.
  if(p_tmp->rptr != NULL){
    L->Act->rptr = p_tmp->rptr;/* Navazeme nasledujici prvek na za nami rusenym
                                  prvek na aktivni prvek.*/
    p_tmp->rptr->lptr = L->Act;/* Do odkazu nasledujici prvku na prechozi
                                  prvek, priradime odkaz na aktivniho prvek.*/
    free(p_tmp);
  }

  //Pokud je nami ruseny prvek i zaroven poslednim prvkem.
  else{
    L->Act->rptr = NULL;// Odkaz na dalsi prvek za aktivnim se rovna NULL;
    L->Last = L->Act;// Podlesni prvek se rovna aktivnimu prvku.
    free(p_tmp);
  }
}

void DLPreDelete (tDLList *L)	{
/*
** Zru+/-í prvek poed aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se ned`ije.
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  if((L->Act == NULL) || (L->Act == L->First)){
    return;
  }

  p_tmp = L->Act->lptr;

  // Pokud neni nami ruseny prvek zaroven prvnim prvkem seznamu.
  if(p_tmp->lptr != NULL){
    L->Act->lptr = p_tmp->lptr;/* Navazeme predchozi prvek na pred nami rusenym
                                  prvek na aktivni prvek.*/
    p_tmp->lptr->rptr = L->Act;/* Do odkazu prechoziho prvku na nasledujici
                                  prvek, priradime odkaz na aktivniho prvek.*/
    free(p_tmp);
  }

  else{
    L->Act->lptr = NULL;// Odkaz na predesly prvek za aktivnim se rovna NULL;
    L->First = L->Act;// Prvni prvek se rovna aktivnimu prvku.
    free(p_tmp);
  }
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vlouí prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se ned`ije.
** V poípad`i, ue není dostatek pam`iti pro nový prvek poi operaci malloc,
** volá funkci DLError().
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  if((p_tmp = (tDLElemPtr)malloc(sizeof(struct tDLElem))) == NULL){
    DLError();
    return;
  }

  // Jestlize aktivni prvek je posledni prvek, vkladam na konec seznamu.
  if(L->Act->rptr == NULL){
    L->Last = p_tmp;// Vkladany prvek je poslednim prvkem.
  }

  else{
    L->Act->rptr->lptr = p_tmp;/* Pripojeni odkazu nasledujiciho prvku za
                                  aktivnim prvkem, na nove vlozeny prvek.*/
  }

  p_tmp->rptr = L->Act->rptr;// Ulozime odkaz na prvek za aktivnim prvkem.
  p_tmp->lptr = L->Act;/* Ulozime odkaz na predesly prvek, pred vkladanym
                          prvkem.*/
  L->Act->rptr = p_tmp;// Pripojeni vlozeneho prvku za aktivni prvek.
  p_tmp->data = val;// Ulozeni dat do noveho prvku.
}

void DLPreInsert (tDLList *L, int val)		{
/*
** Vlouí prvek poed aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se ned`ije.
** V poípad`i, ue není dostatek pam`iti pro nový prvek poi operaci malloc,
** volá funkci DLError().
**/

  tDLElemPtr p_tmp = NULL;// Pomocny ukazatel.

  if((p_tmp = (tDLElemPtr)malloc(sizeof(struct tDLElem))) == NULL){
    DLError();
    return;
  }

  // Jestlize aktivni prvek je prvni prvek, vkladam na zacatek seznamu.
  if(L->Act->lptr == NULL){
    L->First = p_tmp;// Vkladany prvek je prvnim prvek.
  }

  else{
    L->Act->lptr->rptr = p_tmp;/* Pripojeni odkazu prechoziho prvku pred
                                  aktivnim prvkem, na nove vlozeny prvek.*/
  }

  p_tmp->lptr = L->Act->lptr;// Ulozime odkaz na prvek pred aktivnim prvkem.
  p_tmp->rptr = L->Act;/* Ulozime odkaz na nasledujici prvek, za vkladanym
                          prvkem.*/
  p_tmp->data = val;// Ulozeni dat do noveho prvku.
}

void DLCopy (tDLList *L, int *val)	{
/*
** Prostoednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/

  if(L->Act == NULL){
    DLError();
  }

  else{
    *val = L->Act->data;
  }
}

void DLActualize (tDLList *L, int val) {
/*
** Poepí+/-e obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, ned`ilá nic.
**/

  if(L->Act != NULL){
    L->Act->data = val;
  }
}

void DLSucc (tDLList *L)	{
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, ned`ilá nic.
** V+/-imn`ite si, ue poi aktivit`i na posledním prvku se seznam stane neaktivním.
**/

  if(L->Act != NULL){
    L->Act = L->Act->rptr;
  }
}


void DLPred (tDLList *L)	{
/*
** Posune aktivitu na poedchozí prvek seznamu L.
** Není-li seznam aktivní, ned`ilá nic.
** V+/-imn`ite si, ue poi aktivit`i na prvním prvku se seznam stane neaktivním.
**/

  if(L->Act != NULL){
    L->Act = L->Act->lptr;
  }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam aktivní, vrací true. V opa`eném poípad`i vrací false.
** Funkci implementujte jako jediný poíkaz.
**/

  return (L->Act != NULL);
}

/* Konec c206.c*/
