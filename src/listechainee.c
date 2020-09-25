/**
   Copyright (C) 2016 by Gregory Mounie

   This file is part of RappelDeC

   RappelDeC is free software: you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.


   RappelDeC is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct elem {
    long unsigned int val;
    struct elem *next;
};

/** 
 * Affiche les éléments de la liste passée en paramètre sur la sortie standard.
 * 
 * @param liste Node
*/
void affichage_liste(struct elem *liste) {
    for (struct elem *current = liste; current != NULL; current = current->next) {
        printf("%lu ", current->val);
    }
    printf("\n");
}

/** 
 * Crée une liste simplement chainée à partir des nb_elems éléments du tableau valeurs.
 * 
 * @param valeurs Liste de Node
 * @param nb_elems Nombre de Node 
*/
struct elem *creation_liste(long unsigned int *valeurs, size_t nb_elems) {
    assert(nb_elems != 0 && valeurs != NULL);

    struct elem *head = calloc(1, sizeof *head);
    assert(head != NULL);

    head->val = valeurs[0];
    struct elem *current = head;
    for (size_t i = 1; i < nb_elems; ++i) {
        current->next = calloc(1, sizeof *(current->next));
        current->next->val = valeurs[i];
        current = current->next;
    }

    return head;
}

/** 
 * Libère toute la mémoire associée à la liste passée en paramètre. 
 * 
 * @param liste Node
*/
void destruction_liste(struct elem *liste) {
    struct elem *current = liste;
    while (current != NULL) {
        struct elem *next = current->next;
        free(current);
        current = next;
    }
}

/** 
 * Inverse la liste simplement chainée passée en paramètre. Le
 * paramètre liste contient l'adresse du pointeur sur la tête de liste
 * à inverser. 
 * 
 * @param liste Pointer to head node
*/
void inversion_liste(struct elem **liste) {
    if (liste == NULL || *liste == NULL) {
        return;
    }

    struct elem *current = *liste;
    struct elem *next = current->next;
    current->next = NULL;

    while (next != NULL) {
        struct elem *next_next = next->next;
        next->next = current;
        current = next;
        next = next_next;
    }

    *liste = current;
}

const long unsigned int TAILLE = 100;

int main(void) {
    /* Test d'affichage d'une liste créée à la main. */
    struct elem e1, e2, e3;
    e1.val = 0;
    e2.val = 1;
    e3.val = 2;
    e1.next = &e2;
    e2.next = &e3;
    e3.next = NULL;
    affichage_liste(&e1);

    long unsigned int valeurs[TAILLE];
    for (size_t i = 0; i < TAILLE; i++) {
        valeurs[i] = i;
    }

    struct elem *tab_elem = creation_liste(valeurs, TAILLE);
    assert(tab_elem != NULL);

    /* Test que la liste dans l'ordre */
    struct elem *tmp;
    long unsigned int idx;
    for (tmp = tab_elem, idx = 0;
         tmp != NULL;
         idx++, tmp = tmp->next) {
        assert(tmp->val == idx);
    }
    /* Test que la liste est complète (à la suite du test sur l'ordre) */
    assert(idx == TAILLE);

    printf("Liste créée:\n");
    affichage_liste(tab_elem);
    inversion_liste(&tab_elem);
    assert(tab_elem != NULL);
    printf("Liste inversée:\n");
    affichage_liste(tab_elem);

    /* Vérifie que la liste est inversée et complète */
    for (tmp = tab_elem, idx = TAILLE - 1; tmp != NULL; --idx, tmp = tmp->next) {
        assert(tmp->val == idx);
    }
    assert(idx == (long unsigned int)(0UL - 1));

    /* Pour tester le bon fonctionnement de la fonction suivante, on
     * lancera valgrind sur le programme pour vérifier qu'aucune fuite
     * mémoire n'est présente. */
    destruction_liste(tab_elem);

    return EXIT_SUCCESS;
}
