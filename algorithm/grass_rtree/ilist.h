/*
 ****************************************************************************
 *
 * MODULE:       gis library 
 *              
 * AUTHOR(S):    Original author CERL, probably Dave Gerdes.
 *               Update to GRASS 5.7 Radim Blazek.
 *
 * PURPOSE:      Lower level functions for reading and manipulating integer list
 *
 * COPYRIGHT:    (C) 2001 by the GRASS Development Team
 *
 *               This program is free software under the GNU General Public
 *              License (>=v2). Read the file COPYING that comes with GRASS
 *              for details.
 *
 *****************************************************************************/
#include <stdlib.h>

/*!
  \brief List of integers
*/
struct ilist
{
    /*!
      \brief Array of values
    */
    int *value;
    /*!
      \brief Number of values in the list
    */
    int n_values;
    /*!
      \brief Allocated space for values
    */
    int alloc_values;
};

/**
 * \brief Free allocated memory of an integer list
 *
 * \param list The pointer to an integer list
 *
 * */
void G_free_ilist(struct ilist *list);

/**
 * \brief Return a new integer list.
 * 
 * G_fatal_error() will be invoked by the
 * allocation function.
 *
 * \return list The pointer to a new allocated integer list
 *
 * */
struct ilist * G_new_ilist();

/** 
 * \brief Init an integer list and free allocated memory
 *
 * \param list The pointer to an integer list
 *
 * */
void G_init_ilist(struct ilist *list);
/** 
 * \brief Add item to ilist
 *
 *  This function adds an integer to the list but does not check for duplicates.
 *  In case reallocation fails, G_fatal_error() will be invoked by the
 *  allocation function.
 *
 * \param list The ilist pointer
 * \param val The value to attach
 *
 * */
void G_ilist_add(struct ilist *list, int val);