
/* ******************************* c204.c *********************************** */
/*  Poedm`it: Algoritmy (IAL) - FIT VUT v Brn`i                                 */
/*  Úkol: c204 - Poevod infixového výrazu na postfixový (s vyu3/4itím c202)     */
/*  Referen`ení implementace: Petr Poikryl, listopad 1994                      */
/*  Poepis do jazyka C: Luká^1 Mar^1ík, prosinec 2012                           */
/*  Upravil: Bohuslav Koena, oíjen 2013                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro poevod infixového zápisu matematického
** výrazu do postfixového tvaru. Pro poevod vyu3/4ijte zásobník (tStack),
** který byl implementován v rámci poíkladu c202. Bez správného vyoe^1ení
** poíkladu c202 se o oe^1ení tohoto poíkladu nepokou^1ejte.
**
** Implementujte následující funkci:
**
**    infix2postfix .... konverzní funkce pro poevod infixového výrazu
**                       na postfixový
**
** Pro lep^1í poehlednost kódu implementujte následující funkce:
**
**    untilLeftPar .... vyprázdn`iní zásobníku a3/4 po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své oe^1ení ú`eeln`i komentujte.
**
** Terminologická poznámka: Jazyk C nepou3/4ívá pojem procedura.
** Proto zde pou3/4íváme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

#include "c204.h"

int solved;


/*
** Pomocná funkce untilLeftPar.
** Slou3/4í k vyprázdn`iní zásobníku a3/4 po levou závorku, poi`eem3/4 levá závorka
** bude také odstran`ina. Pokud je zásobník prázdný, provád`iní funkce se ukon`eí.
**
** Operátory odstra`oované ze zásobníku postupn`i vkládejte do výstupního pole
** znak`u postExpr. Délka poevedeného výrazu a té3/4 ukazatel na první volné
** místo, na které se má zapisovat, poedstavuje parametr postLen.
**
** Aby se minimalizoval po`eet poístup`u ke struktuoe zásobníku, m`u3/4ete zde
** nadeklarovat a pou3/4ívat pomocnou prom`innou typu.
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
** Pomocná funkce doOperation.
** Zpracuje operátor, který je poedán parametrem c po na`etení znaku ze
** vstupního pole znak`u.
**
** Dle priority poedaného operátoru a poípadn`i priority operátoru na
** vrcholu zásobníku rozhodneme o dal^1ím postupu. Délka poevedeného
** výrazu a takté3/4 ukazatel na první volné místo, do kterého se má zapisovat,
** poedstavuje parametr postLen, výstupním polem znak`u je op`it postExpr.
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
** Konverzní funkce infix2postfix.
** `Ete infixový výraz ze vstupního oet`izce infExpr a generuje
** odpovídající postfixový výraz do výstupního oet`izce (postup poevodu
** hledejte v poedná^1kách nebo ve studijní opooe). Pam`i>> pro výstupní oet`izec
** (o velikosti MAX_LEN) je toeba alokovat. Volající funkce, tedy
** poíjemce konvertovaného oet`izce, zajistí korektní uvoln`iní zde alokované
** pam`iti.
**
** Tvar výrazu:
** 1. Výraz obsahuje operátory + - * / ve významu s`eítání, od`eítání,
**    násobení a d`ilení. S`eítání má stejnou prioritu jako od`eítání,
**    násobení má stejnou prioritu jako d`ilení. Priorita násobení je
**    v`it^1í ne3/4 priorita s`eítání. V^1echny operátory jsou binární
**    (neuva3/4ujte unární mínus).
**
** 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
**    a `eíslicemi - 0..9, a..z, A..Z (velikost písmen se rozli^1uje).
**
** 3. Ve výrazu m`u3/4e být pou3/4it poedem neur`eený po`eet dvojic kulatých
**    závorek. Uva3/4ujte, 3/4e vstupní výraz je zapsán správn`i (neo^1etoujte
**    chybné zadání výrazu).
**
** 4. Ka3/4dý korektn`i zapsaný výraz (infixový i postfixový) musí být uzavoen
**    ukon`eovacím znakem '='.
**
** 5. Poi stejné priorit`i operátor`u se výraz vyhodnocuje zleva doprava.
**
** Poznámky k implementaci
** -----------------------
** Jako zásobník pou3/4ijte zásobník znak`u tStack implementovaný v poíkladu c202.
** Pro práci se zásobníkem pak pou3/4ívejte výhradn`i operace z jeho rozhraní.
**
** Poi implementaci vyu3/4ijte pomocné funkce untilLeftPar a doOperation.
**
** Oet`izcem (infixového a postfixového výrazu) je zde my^1leno pole znak`u typu
** char, jen3/4 je korektn`i ukon`eeno nulovým znakem dle zvyklostí jazyka C.
**
** Na vstupu o`eekávejte pouze korektn`i zapsané a ukon`eené výrazy. Jejich délka
** nepoesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
** by se m`il vejít do alokovaného pole. Po alokaci dynamické pam`iti si v3/4dycky
** ov`iote, 3/4e se alokace skute`en`i zdraoila. V poípad`i chyby alokace vra>>te namísto
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
