/**
 * \addtogroup list
 * @{
 */

/**
 * \file
 * Linked list library implementation.
 *
 * \author Adam Dunkels <adam@sics.se>
 *
 */

/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: list.c,v 1.5 2010/06/15 18:54:27 adamdunkels Exp $
 */

// 20200722 Lanka Hsu
// list is a common name. clist is to avoid naming conflicts.
#include "utilx9.h"

struct clist {
	struct clist *next;
};

/*---------------------------------------------------------------------------*/
/**
 * Initialize a list.
 *
 * This function initalizes a list. The list will be empty after this
 * function has been called.
 *
 * \param list The list to be initialized.
 */
void clist_init(clist_t list)
{
	*list = NULL;
}

/*---------------------------------------------------------------------------*/
/**
 * Get a pointer to the first element of a list.
 *
 * This function returns a pointer to the first element of the
 * list. The element will \b not be removed from the list.
 *
 * \param list The list.
 * \return A pointer to the first element on the list.
 *
 * \sa clist_tail()
 */
void *clist_head(clist_t list)
{
	return *list;
}

/*---------------------------------------------------------------------------*/
/**
 * Duplicate a list.
 *
 * This function duplicates a list by copying the list reference, but
 * not the elements.
 *
 * \note This function does \b not copy the elements of the list, but
 * merely duplicates the pointer to the first element of the list.
 *
 * \param dest The destination list.
 * \param src The source list.
 */
void clist_copy(clist_t dest, clist_t src)
{
	*dest = *src;
}

/*---------------------------------------------------------------------------*/
/**
 * Get the tail of a list.
 *
 * This function returns a pointer to the elements following the first
 * element of a list. No elements are removed by this function.
 *
 * \param list The list
 * \return A pointer to the element after the first element on the list.
 *
 * \sa clist_head()
 */
void *clist_tail(clist_t list)
{
	struct clist *l;

	if(*list == NULL) {
		return NULL;
	}

	for(l = *list; l->next != NULL; l = l->next);

	return l;
}

/*---------------------------------------------------------------------------*/
/**
 * Add an item at the end of a list.
 *
 * This function adds an item to the end of the list.
 *
 * \param list The list.
 * \param item A pointer to the item to be added.
 *
 * \sa clist_add()
 *
 */
void clist_push(clist_t list, void *item)
{
	struct clist *l;

	/* Make sure not to add the same element twice */
	clist_remove(list, item);

	((struct clist *)item)->next = NULL;

	l = clist_tail(list);

	if(l == NULL) {
		*list = item;
	} else {
		l->next = item;
	}
}

/*---------------------------------------------------------------------------*/
/**
 * Add an item to the start of the list.
 */
void clist_add(clist_t list, void *item)
{
	/*  struct clist *l;*/

	/* Make sure not to add the same element twice */
	clist_remove(list, item);

	((struct clist *)item)->next = *list;
	*list = item;
}

/*---------------------------------------------------------------------------*/
/**
 * Remove the last object on the list.
 *
 * This function removes the last object on the list and returns it.
 *
 * \param list The list
 * \return The removed object
 *
 */
void *clist_chop(clist_t list)
{
	struct clist *l, *r;

	if(*list == NULL) {
		return NULL;
	}
	if(((struct clist *)*list)->next == NULL) {
		l = *list;
		*list = NULL;
		return l;
	}

	for(l = *list; l->next->next != NULL; l = l->next);

	r = l->next;
	l->next = NULL;

	return r;
}

/*---------------------------------------------------------------------------*/
/**
 * Remove the first object on a list.
 *
 * This function removes the first object on the list and returns a
 * pointer to it.
 *
 * \param list The list.
 * \return Pointer to the removed element of list.
 */
/*---------------------------------------------------------------------------*/
void *clist_pop(clist_t list)
{
	struct clist *l;
	l = *list;
	if(*list != NULL) {
		*list = ((struct clist *)*list)->next;
	}

	return l;
}

/*---------------------------------------------------------------------------*/
/**
 * Remove a specific element from a list.
 *
 * This function removes a specified element from the list.
 *
 * \param list The list.
 * \param item The item that is to be removed from the list.
 *
 */
/*---------------------------------------------------------------------------*/
void clist_remove(clist_t list, void *item)
{
	struct clist *l, *r;

	if(*list == NULL) {
		return;
	}

	r = NULL;
	for(l = *list; l != NULL; l = l->next) {
		if(l == item) {
			if(r == NULL) {
				/* First on list */
				*list = l->next;
			} else {
				/* Not first on list */
				r->next = l->next;
			}
			l->next = NULL;
			return;
		}
		r = l;
	}
}

/*---------------------------------------------------------------------------*/
/**
 * Get the length of a list.
 *
 * This function counts the number of elements on a specified list.
 *
 * \param list The list.
 * \return The length of the list.
 */
/*---------------------------------------------------------------------------*/
int clist_length(clist_t list)
{
	struct clist *l;
	int n = 0;

	for(l = *list; l != NULL; l = l->next) {
		++n;
	}

	return n;
}

/*---------------------------------------------------------------------------*/
/**
 * \brief      Insert an item after a specified item on the list
 * \param list The list
 * \param previtem The item after which the new item should be inserted
 * \param newitem  The new item that is to be inserted
 * \author     Adam Dunkels
 *
 *             This function inserts an item right after a specified
 *             item on the list. This function is useful when using
 *             the list module to ordered lists.
 *
 *             If previtem is NULL, the new item is placed at the
 *             start of the list.
 *
 */
void clist_insert(clist_t list, void *previtem, void *newitem)
{
	if(previtem == NULL) {
		clist_add(list, newitem);
	} else {
		((struct clist *)newitem)->next = ((struct clist *)previtem)->next;
		((struct clist *)previtem)->next = newitem;
	}
}

/*---------------------------------------------------------------------------*/
/**
 * \brief      Get the next item following this item
 * \param item A list item
 * \returns    A next item on the list
 *
 *             This function takes a list item and returns the next
 *             item on the list, or NULL if there are no more items on
 *             the list. This function is used when iterating through
 *             lists.
 */
void *clist_item_next(void *item)
{
	return item == NULL? NULL: ((struct clist *)item)->next;
}

int clist_filter_ex(clist_t list, clist_item_filter_fn filter_cb)
{
	int count = 0;
	struct clist *l;

	if (filter_cb)
	{
		l = *list; 
		while ( l != NULL )
		{
			struct clist *curr = l;
			l = l->next;
			if ( filter_cb(curr) == 0 )
			{
				// nothing
			}
			else
			{
				// got it
				count ++;
			}
		}
	}
	return count;
}

/*---------------------------------------------------------------------------*/
/**
 * Check if list contains a specific element. Return 1 if item is in list
 * and 0 otherwise.
 *
 * \param list The list.
 * \param item The item that is to be search for.
 *
 */
/*---------------------------------------------------------------------------*/
int clist_contains(clist_t list, void *item)
{
	struct clist *l;

	for (l = *list; l != NULL; l = l->next)
	{
		if (l == item)
		{
			return 1;
		}
	}
	return 0;
}

void clist_free_ex(clist_t list, clist_item_free_fn free_cb)
{
	while (clist_length(list) > 0)
	{
		void *item = clist_pop(list);
		if (item)
		{
			if (free_cb) free_cb(item);
			free(item);
		}
	}
}

void clist_free(clist_t list)
{
	while (clist_length(list) > 0)
	{
		void *item = clist_pop(list);
		if (item) free(item);
	}
}

/** @} */
