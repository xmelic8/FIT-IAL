
/* c206.c **********************************************************}
{* T�ma: Dvousm`irn`i v�zan� line�rn� seznam
**
**                   N�vrh a referen`en� implementace: Bohuslav Koena, o�jen 2001
**                            Poepracovan� do jazyka C: Martin Tu`eek, o�jen 2004
**                                             �pravy: Bohuslav Koena, o�jen 2013
**
** Implementujte abstraktn� datov� typ dvousm`irn`i v�zan� line�rn� seznam.
** Uuite`en�m obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datov� abstrakce reprezentov�n prom`innou
** typu tDLList (DL znamen� Double-Linked a slouu� pro odli+/-en�
** jmen konstant, typ`u a funkc� od jmen u jednosm`irn`i v�zan�ho line�rn�ho
** seznamu). Definici konstant a typ`u naleznete v hlavi`ekov�m souboru c206.h.
**
** Va+/-�m �kolem je implementovat n�sleduj�c� operace, kter� spolu
** s v�+/-e uvedenou datovou `e�st� abstrakce tvoo� abstraktn� datov� typ
** obousm`irn`i v�zan� line�rn� seznam:
**
**      DLInitList ...... inicializace seznamu poed prvn�m pouuit�m,
**      DLDisposeList ... zru+/-en� v+/-ech prvk`u seznamu,
**      DLInsertFirst ... vlouen� prvku na za`e�tek seznamu,
**      DLInsertLast .... vlouen� prvku na konec seznamu,
**      DLFirst ......... nastaven� aktivity na prvn� prvek,
**      DLLast .......... nastaven� aktivity na posledn� prvek,
**      DLCopyFirst ..... vrac� hodnotu prvn�ho prvku,
**      DLCopyLast ...... vrac� hodnotu posledn�ho prvku,
**      DLDeleteFirst ... zru+/-� prvn� prvek seznamu,
**      DLDeleteLast .... zru+/-� posledn� prvek seznamu,
**      DLPostDelete .... ru+/-� prvek za aktivn�m prvkem,
**      DLPreDelete ..... ru+/-� prvek poed aktivn�m prvkem,
**      DLPostInsert .... vlou� nov� prvek za aktivn� prvek seznamu,
**      DLPreInsert ..... vlou� nov� prvek poed aktivn� prvek seznamu,
**      DLCopy .......... vrac� hodnotu aktivn�ho prvku,
**      DLActualize ..... poep�+/-e obsah aktivn�ho prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na dal+/-� prvek seznamu,
**      DLPred .......... posune aktivitu na poedchoz� prvek seznamu,
**      DLActive ........ zji+/-"Yuje aktivitu seznamu.
**
** Poi implementaci jednotliv�ch funkc� nevolejte u�dnou z funkc�
** implementovan�ch v r�mci tohoto po�kladu, nen�-li u funkce
** explicitn`i uvedeno n`ico jin�ho.
**
** Nemus�te o+/-etoovat situaci, kdy m�sto leg�ln�ho ukazatele na seznam
** poed� n`ikdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodn`i komentujte!
**
** Terminologick� pozn�mka: Jazyk C nepouu�v� pojem procedura.
** Proto zde pouu�v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozorn`in� na to, ue do+/-lo k chyb`i.
** Tato funkce bude vol�na z n`ikter�ch d�le implementovan�ch operac�.
**/
    printf ("*ERROR* This program has performed an illegal operation.\n");
    errflg = TRUE;             /* glob�ln� prom`inn� -- po�znak o+/-etoen� chyby */
    return;
}

void DLInitList (tDLList *L)	{
/*
** Provede inicializaci seznamu L poed jeho prvn�m pouuit�m (tzn. u�dn�
** z n�sleduj�c�ch funkc� nebude vol�na nad neinicializovan�m seznamem).
** Tato inicializace se nikdy nebude prov�d`it nad jiu inicializovan�m
** seznamem, a proto tuto mounost neo+/-etoujte. Vudy poedpokl�dejte,
** ue neinicializovan� prom`inn� maj� nedefinovanou hodnotu.
**/

  L->Act = NULL;// Ukazatel na aktualni prvek a jeho inicializace.
  L->First = NULL;// Ukazatel na prvni prvek a jeho inicializace.
  L->Last = NULL;// Ukazatel na posledni prvek a jeho inicializace.
}

void DLDisposeList (tDLList *L)	{
/*
** Zru+/-� v+/-echny prvky seznamu L a uvede seznam do stavu, v jak�m
** se nach�zel po inicializaci. Ru+/-en� prvky seznamu budou korektn`i
** uvoln`iny vol�n�m operace free.
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
** Vlou� nov� prvek na za`e�tek seznamu L.
** V po�pad`i, ue nen� dostatek pam`iti pro nov� prvek poi operaci malloc,
** vol� funkci DLError().
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
** Vlou� nov� prvek na konec seznamu L (symetrick� operace k DLInsertFirst).
** V po�pad`i, ue nen� dostatek pam`iti pro nov� prvek poi operaci malloc,
** vol� funkci DLError().
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
** Nastav� aktivitu na prvn� prvek seznamu L.
** Funkci implementujte jako jedin� po�kaz (nepo`e�t�me-li return),
** aniu byste testovali, zda je seznam L pr�zdn�.
**/

  L->Act = L->First;
}

void DLLast (tDLList *L)	{
/*
** Nastav� aktivitu na posledn� prvek seznamu L.
** Funkci implementujte jako jedin� po�kaz (nepo`e�t�me-li return),
** aniu byste testovali, zda je seznam L pr�zdn�.
**/

  L->Act = L->Last;
}

void DLCopyFirst (tDLList *L, int *val)	{
/*
** Prostoednictv�m parametru val vr�t� hodnotu prvn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
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
** Prostoednictv�m parametru val vr�t� hodnotu posledn�ho prvku seznamu L.
** Pokud je seznam L pr�zdn�, vol� funkci DLError().
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
** Zru+/-� prvn� prvek seznamu L. Pokud byl prvn� prvek aktivn�, aktivita
** se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned`ije.
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
** Zru+/-� posledn� prvek seznamu L. Pokud byl posledn� prvek aktivn�,
** aktivita seznamu se ztr�c�. Pokud byl seznam L pr�zdn�, nic se ned`ije.
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
** Zru+/-� prvek seznamu L za aktivn�m prvkem.
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** posledn�m prvkem seznamu, nic se ned`ije.
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
** Zru+/-� prvek poed aktivn�m prvkem seznamu L .
** Pokud je seznam L neaktivn� nebo pokud je aktivn� prvek
** prvn�m prvkem seznamu, nic se ned`ije.
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
** Vlou� prvek za aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned`ije.
** V po�pad`i, ue nen� dostatek pam`iti pro nov� prvek poi operaci malloc,
** vol� funkci DLError().
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
** Vlou� prvek poed aktivn� prvek seznamu L.
** Pokud nebyl seznam L aktivn�, nic se ned`ije.
** V po�pad`i, ue nen� dostatek pam`iti pro nov� prvek poi operaci malloc,
** vol� funkci DLError().
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
** Prostoednictv�m parametru val vr�t� hodnotu aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, vol� funkci DLError ().
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
** Poep�+/-e obsah aktivn�ho prvku seznamu L.
** Pokud seznam L nen� aktivn�, ned`il� nic.
**/

  if(L->Act != NULL){
    L->Act->data = val;
  }
}

void DLSucc (tDLList *L)	{
/*
** Posune aktivitu na n�sleduj�c� prvek seznamu L.
** Nen�-li seznam aktivn�, ned`il� nic.
** V+/-imn`ite si, ue poi aktivit`i na posledn�m prvku se seznam stane neaktivn�m.
**/

  if(L->Act != NULL){
    L->Act = L->Act->rptr;
  }
}


void DLPred (tDLList *L)	{
/*
** Posune aktivitu na poedchoz� prvek seznamu L.
** Nen�-li seznam aktivn�, ned`il� nic.
** V+/-imn`ite si, ue poi aktivit`i na prvn�m prvku se seznam stane neaktivn�m.
**/

  if(L->Act != NULL){
    L->Act = L->Act->lptr;
  }
}

int DLActive (tDLList *L) {
/*
** Je-li seznam aktivn�, vrac� true. V opa`en�m po�pad`i vrac� false.
** Funkci implementujte jako jedin� po�kaz.
**/

  return (L->Act != NULL);
}

/* Konec c206.c*/
