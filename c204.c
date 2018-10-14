
/* ******************************* c204.c *********************************** */
/*  Poedm`it: Algoritmy (IAL) - FIT VUT v Brn`i                                 */
/*  �kol: c204 - Poevod infixov�ho v�razu na postfixov� (s vyu3/4it�m c202)     */
/*  Referen`en� implementace: Petr Poikryl, listopad 1994                      */
/*  Poepis do jazyka C: Luk�^1 Mar^1�k, prosinec 2012                           */
/*  Upravil: Bohuslav Koena, o�jen 2013                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro poevod infixov�ho z�pisu matematick�ho
** v�razu do postfixov�ho tvaru. Pro poevod vyu3/4ijte z�sobn�k (tStack),
** kter� byl implementov�n v r�mci po�kladu c202. Bez spr�vn�ho vyoe^1en�
** po�kladu c202 se o oe^1en� tohoto po�kladu nepokou^1ejte.
**
** Implementujte n�sleduj�c� funkci:
**
**    infix2postfix .... konverzn� funkce pro poevod infixov�ho v�razu
**                       na postfixov�
**
** Pro lep^1� poehlednost k�du implementujte n�sleduj�c� funkce:
**
**    untilLeftPar .... vypr�zdn`in� z�sobn�ku a3/4 po levou z�vorku
**    doOperation .... zpracov�n� oper�toru konvertovan�ho v�razu
**
** Sv� oe^1en� �`eeln`i komentujte.
**
** Terminologick� pozn�mka: Jazyk C nepou3/4�v� pojem procedura.
** Proto zde pou3/4�v�me pojem funkce i pro operace, kter� by byly
** v algoritmick�m jazyce Pascalovsk�ho typu implemenov�ny jako
** procedury (v jazyce C procedur�m odpov�daj� funkce vracej�c� typ void).
**
**/

#include "c204.h"

int solved;


/*
** Pomocn� funkce untilLeftPar.
** Slou3/4� k vypr�zdn`in� z�sobn�ku a3/4 po levou z�vorku, poi`eem3/4 lev� z�vorka
** bude tak� odstran`ina. Pokud je z�sobn�k pr�zdn�, prov�d`in� funkce se ukon`e�.
**
** Oper�tory odstra`oovan� ze z�sobn�ku postupn`i vkl�dejte do v�stupn�ho pole
** znak`u postExpr. D�lka poeveden�ho v�razu a t�3/4 ukazatel na prvn� voln�
** m�sto, na kter� se m� zapisovat, poedstavuje parametr postLen.
**
** Aby se minimalizoval po`eet po�stup`u ke struktuoe z�sobn�ku, m`u3/4ete zde
** nadeklarovat a pou3/4�vat pomocnou prom`innou typu.
*/
void untilLeftPar ( tStack* s, char* postExpr, unsigned* postLen ) {
  char top_znak;// Pomocna promenna pro ulozeni znaku z vrcholu zasobniku.

  while (!stackEmpty(s))
  {
    stackTop(s, &top_znak);
    if(top_znak == '('){// Leva zavorka se smaze z vrcholu zasobniku.
      stackPop(s);
      return;
    }
    else{
      postExpr[*postLen] = top_znak;/* Do vysledneho pole se ulozi prvky
                                       ze zasobniku, az po levou zavorku.*/
      (*postLen)++;
      stackPop(s);
    }
  }
}

/*
** Pomocn� funkce doOperation.
** Zpracuje oper�tor, kter� je poed�n parametrem c po na`eten� znaku ze
** vstupn�ho pole znak`u.
**
** Dle priority poedan�ho oper�toru a po�padn`i priority oper�toru na
** vrcholu z�sobn�ku rozhodneme o dal^1�m postupu. D�lka poeveden�ho
** v�razu a takt�3/4 ukazatel na prvn� voln� m�sto, do kter�ho se m� zapisovat,
** poedstavuje parametr postLen, v�stupn�m polem znak`u je op`it postExpr.
*/
void doOperation ( tStack* s, char c, char* postExpr, unsigned* postLen ) {
  char top_znak;// Pomocna promenna pro ulozeni znaku z vrcholu zasobniku.

  if(stackEmpty(s)){// Overeni zda zasobnik neni prazdny.
    stackPush(s, c);
    return;
  }

  else{
    stackTop(s, &top_znak);

    /* Podminka pro vlozeni operatoru na vrchol pokud je prazdny zasobnik, na
       vrcholu je leva zavorka, na vrcholu je operator s nizsi prioritou.    */
    if((top_znak == '(') || (top_znak != c) ||
       (((c == '*') || (c == '/')) && ((top_znak != '+') || (top_znak != '-')))){
    stackPush(s, c);
    }

    /*Pokud je na vrcholu zasobniku operator s vyssi nebo shodnou priotiou, tak
      jej vlozim do vystupniho pole a odstranim jej ze zasobniku. Na jeho misto
      vlozim puvodne nacetli operator.*/
    else{
      postExpr[*postLen] = top_znak;
      (*postLen)++;
      stackPop(s);
      stackPush(s, c);
    }
  }
}

/*
** Konverzn� funkce infix2postfix.
** `Ete infixov� v�raz ze vstupn�ho oet`izce infExpr a generuje
** odpov�daj�c� postfixov� v�raz do v�stupn�ho oet`izce (postup poevodu
** hledejte v poedn�^1k�ch nebo ve studijn� opooe). Pam`i>> pro v�stupn� oet`izec
** (o velikosti MAX_LEN) je toeba alokovat. Volaj�c� funkce, tedy
** po�jemce konvertovan�ho oet`izce, zajist� korektn� uvoln`in� zde alokovan�
** pam`iti.
**
** Tvar v�razu:
** 1. V�raz obsahuje oper�tory + - * / ve v�znamu s`e�t�n�, od`e�t�n�,
**    n�soben� a d`ilen�. S`e�t�n� m� stejnou prioritu jako od`e�t�n�,
**    n�soben� m� stejnou prioritu jako d`ilen�. Priorita n�soben� je
**    v`it^1� ne3/4 priorita s`e�t�n�. V^1echny oper�tory jsou bin�rn�
**    (neuva3/4ujte un�rn� m�nus).
**
** 2. Hodnoty ve v�razu jsou reprezentov�ny jednoznakov�mi identifik�tory
**    a `e�slicemi - 0..9, a..z, A..Z (velikost p�smen se rozli^1uje).
**
** 3. Ve v�razu m`u3/4e b�t pou3/4it poedem neur`een� po`eet dvojic kulat�ch
**    z�vorek. Uva3/4ujte, 3/4e vstupn� v�raz je zaps�n spr�vn`i (neo^1etoujte
**    chybn� zad�n� v�razu).
**
** 4. Ka3/4d� korektn`i zapsan� v�raz (infixov� i postfixov�) mus� b�t uzavoen
**    ukon`eovac�m znakem '='.
**
** 5. Poi stejn� priorit`i oper�tor`u se v�raz vyhodnocuje zleva doprava.
**
** Pozn�mky k implementaci
** -----------------------
** Jako z�sobn�k pou3/4ijte z�sobn�k znak`u tStack implementovan� v po�kladu c202.
** Pro pr�ci se z�sobn�kem pak pou3/4�vejte v�hradn`i operace z jeho rozhran�.
**
** Poi implementaci vyu3/4ijte pomocn� funkce untilLeftPar a doOperation.
**
** Oet`izcem (infixov�ho a postfixov�ho v�razu) je zde my^1leno pole znak`u typu
** char, jen3/4 je korektn`i ukon`eeno nulov�m znakem dle zvyklost� jazyka C.
**
** Na vstupu o`eek�vejte pouze korektn`i zapsan� a ukon`een� v�razy. Jejich d�lka
** nepoes�hne MAX_LEN-1 (MAX_LEN i s nulov�m znakem) a tedy i v�sledn� v�raz
** by se m`il vej�t do alokovan�ho pole. Po alokaci dynamick� pam`iti si v3/4dycky
** ov`iote, 3/4e se alokace skute`en`i zdraoila. V po�pad`i chyby alokace vra>>te nam�sto
** oet`izce konstantu NULL.
*/
char* infix2postfix (const char* infExpr) {
  char *p_postfix = NULL;// Vysledne pole pro ulozeni vysledku prevodu.
  unsigned int i = 0; // Pocitadlo pro posun v poli.
  unsigned int postLen = 0;/* Pocitadlo poctu prevedenych operandu a ukazatel
                              na volne misto.*/
  char top_znak = '=';//P Promenna pro ulozeni znaku z vrcholu zasobniku.
  tStack* zasobnik = NULL;
  zasobnik = (tStack*) malloc(sizeof(tStack));

  stackInit(zasobnik);

  if((p_postfix = (char *)malloc((MAX_LEN)*sizeof(char))) == NULL){
    return NULL;
  }

  while(infExpr[i] != '='){/* Cyklus ukoncen =, protoze dle zadani ocekavame
                              spravne zadany infixovy vyraz.*/
    // Podminka pro zpracovani operatoru.
    if ((infExpr[i] == '+') || (infExpr[i] == '-') || (infExpr[i] == '*') ||
             (infExpr[i] == '/') || (infExpr[i] == '(')){
      doOperation(zasobnik, infExpr[i], p_postfix, &postLen);
    }

    // Zpracovani a zavolani funkce, pro zpracovani prave zavorky.
    else if(infExpr[i] == ')'){
      untilLeftPar(zasobnik, p_postfix, &postLen);
    }

    /* Jelikoz opet dle zadani ocekavame spravne zadany infixovy vyraz, zadane
       znaky, nejsou nijak osetreny.*/
    else{
       p_postfix[postLen] = infExpr[i];//Do vystupniho retezce se ulozi operand.
       postLen++;
       if(!stackEmpty(zasobnik)){
         stackTop(zasobnik, &top_znak);
         /* Pokud mame na vrcholu zasobniku operator, presuneme jej do
            vystupniho pole a ze zasobniku odebereme.*/
         if((top_znak == '+') || (top_znak == '-') || (top_znak == '*') ||
            (top_znak == '/')){
          p_postfix[postLen] = top_znak;
          stackPop(zasobnik);
          postLen++;
         }
       }
    }
    i++;
  }

  /*Cyklus pro vyprazdneni zasobniku od vsech operatoru.*/
  while(!stackEmpty(zasobnik)){
    stackTop(zasobnik, &top_znak);
    p_postfix[postLen] = top_znak;
    postLen++;
    stackPop(zasobnik);
  }

  p_postfix[postLen] = '=';// Na zaver zapiseme do vysledku znak =.
  p_postfix[++postLen] = '\0';// Na zaver zapiseme do vysledku znak nul.
  free(zasobnik);

  return p_postfix;
}

/* Konec c204.c */
