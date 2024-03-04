/* 14)Descompune un numar natural par, mai mare strict ca 2, intr-o suma
de doua numere prime (verificarea ipotezei lui Goldbach).*/

#include <stdio.h>
/**
 * Verifica daca un numar este prim
 * @param numar (numarul de verificat daca este prim sau nu)
 * @return returneaza: 1 - daca numarul este prim
 *                     0 - daca numarul nu este prim
 */
int este_prim (int numar) {
    int inca_prim = 1, i = 2;
    if (numar == 1) return 0;
    if (numar == 2 || numar == 3) return 1;
    while (i <= numar/2 && inca_prim) {
        if (numar % i == 0) inca_prim = 0;
        i++;
    }
    return inca_prim;
}
/**
 * Se verifica da numarul dat are proprietatea lui Goldbach adica daca se poate scrie ca suma de 2 numere prime
 * @param numar (numarul care sa se scrie ca suma de 2 numere prime)
 */
void verificare_proprietate_Goldbach (int numar) {
    for (int i = 1; i <= numar/2; i += 2) {
        if (este_prim(i) && este_prim(numar-i))
            printf("%d = %d + %d\n", numar, i, numar-i);
    }
}
/**
 * Programul ruleaza pana la introducerea lui 0
 */
int main(){
    int numar;
    printf("Introduceti numarul:");
    scanf_s("%d", &numar);
    verificare_proprietate_Goldbach(numar);
    if (numar % 2 == 1)
        printf("Introduceti numar par!\n\n");
    while(numar != 0) {
        printf("Introduceti numarul:");
        scanf_s("%d", &numar);
        if (numar % 2 == 1)
            printf("Introduceti numar par!\n\n");
        verificare_proprietate_Goldbach(numar);
    }
    return 0;
}
