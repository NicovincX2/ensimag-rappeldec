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

#include <stdlib.h>
#include <string.h>

#include "bitset1000.h"

#define n (1000)

/* Point to the start of element pool */
static struct elem *memoire_elem_pool = 0;

/**
   Fonction allouant un element
   ./ensitestgc --all
*/
struct elem *alloc_elem(void) {
    static size_t i = 0;
    while (i < n && bt1k_get(i)) {
        i++;
    }
    /* Problème s i plus de 1000 appels à alloc_elem */
    if (i == n) {
        return NULL;
    }
    bt1k_set(i, true);
    return &memoire_elem_pool[i];
}

/**
   Fonction ramasse-miette sur les elements qui ne sont pas
   atteignables depuis les têtes de listes
*/
void gc_elems(struct elem **heads, int nbheads) {
    /* ajouter votre code ici / add your code here */
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
