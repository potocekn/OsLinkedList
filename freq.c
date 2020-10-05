// SPDX-License-Identifier: Apache-2.0
// Copyright 2019 Charles University

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "freq.h"

struct freq_str {
    int isEmpty;
    char* data;
    int count;
    struct freq_str * next;
};

/** Create new string frequency counter.
 * 
 * @return Pointer to opaque structure containing the list.
 * @retval NULL Out of memory.
 */
freq_str_t* freq_str_create(void) {

    freq_str_t* temp = (freq_str_t*)calloc(1,sizeof(freq_str_t)); 
    temp->isEmpty = 1;   
    return temp;
}

/** Destroy previously created frequency counter.
 *
 * @param freq Frequency counter previously created with freq_str_create.
 */
void freq_str_destroy(freq_str_t* freq) {
    free(freq);
}

/** Count in the given string.
 *
 * @param freq Frequency counter.
 * @param str String to count-in.
 * @return Error value.
 * @retval 0 Success.
 */
int freq_str_add(freq_str_t* freq, const char* str) {
   
    if (freq->isEmpty == 1)
    {        
        freq->isEmpty = 0;
        freq->data  = calloc(1,sizeof(str) + 1);
        strcpy(freq->data,str);
        freq->count = 1;
        freq->next = NULL;

        return 0;
    }
    else 
    {        
        freq_str_t* p = freq;
        while(p != NULL)
        {
            
            if (strcmp(p->data,str) == 0)
            {
                p->count++;
                
                return 0;
            }
            
            if(p->next != NULL)
            {
                p = p->next;
            }
            else 
            {
                break;
            }
            
        }

        freq_str_t* temp = (freq_str_t*)malloc(sizeof(freq_str_t));
        temp->data = malloc(sizeof(str) + 1);
        strcpy((temp->data),str);
        temp->count = 1;
        temp->next = NULL;
        p->next = temp;
        
        return 0;
    }
    
    return ENOMEM;
}

/** Get frequency of given string.
 *
 * @freq Frequency counter.
 * @param str String that is queried.
 * @return Number of occurences.
 */
int freq_str_get(freq_str_t* freq, const char* str) {
    
    freq_str_t* p = freq;
    while(p != NULL)
    {
        if (strcmp(p->data,str) == 0)
        {            
            return p->count;
        }

        p = p->next;
    }

    return 0;
}
