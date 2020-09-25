/**
   Copyright (C) 2015-2016 by Gregory Mounie

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

#include "elempool.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "bitset1000.h"

#define n (1000)

/* Point to the start of element pool */
static struct elem *memoire_elem_pool = 0;

/**
   Fonction allouant un element

   @return NULL if overflow or a pointer to next free pool element
*/
struct elem *alloc_elem(void) {
    /* Récupération de l'indice à partir duquel memoire_elem_pool[i] est false*/
    size_t i = 0;
    while (i < n && bt1k_get(i)) {
        i++;
    }
    /* Cas limite: overflow de memoire_elem_pool*/
    if (i == n) {
        return NULL;
    }
    bt1k_set(i, true);
    return &memoire_elem_pool[i];
}

/**
 * Fonction ramasse-miette sur les elements qui ne sont pas
 * atteignables depuis les têtes de listes.
 * 
 * But: trouver les portions du bloc qui sont et ne sont pas utilisées.
 * Mise à true tous les booléens correspondant à un élément utilisé et 
 * mettre à false les autres.
 * 
 * @param heads n tableau contenant les adresses de 0, une ou plusieurs têtes de liste
 * @param nbheads nombre de têtes de liste
*/
void gc_elems(struct elem **heads, int nbheads) {
    /* 
        Tout élément qui n’est pas chaîné dans une des listes passées en paramètre,
        au moment de l’appel de gc_elems(), est donc libre.
    */
    bt1k_reset();

    for (int i = 0; i < nbheads; ++i) {
        struct elem *head = heads[i];
        /* Parcours de la liste chaînée et marquage des éléments présents à true */
        while (head) {
            struct elem *base = (struct elem *)memoire_elem_pool;
            
            assert(head - base >= 0);
            long unsigned int idx = (long unsigned int)(head - base);
            
            bt1k_set(idx, true);
            /* On passe à l'élément suivant de la liste chaînée */
            head = head->next;
        }
    }
}

/**
 * Intialisation de memoire_elem_pool 
*/
void init_elems() {
    bt1k_reset();
    if (memoire_elem_pool == NULL) {
        memoire_elem_pool = malloc(n * sizeof(struct elem));
    }
    memset(memoire_elem_pool, 0, n * sizeof(struct elem));
}
