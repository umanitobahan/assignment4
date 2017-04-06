#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"

typedef struct RNODE rnode;

struct RNODE{
	char name[200];
	void *pt;
	rnode *next;
};

static rnode *top = NULL;
static rnode *choosed = NULL;
static rnode *traverse = NULL;

Boolean rinit(const char *region_name, r_size_t region_size){
	assert(region_name != NULL);
	assert(region_size > 0);
	rnode *curr = top;
	Boolean memory = false;
	if(region_size > 0){
		while(curr != NULL){
			assert(region_name != curr->name);
			curr = curr->next;
		}
		curr = (rnode *)malloc(sizeof(rnode));
		if(curr != NULL){
			curr->pt = NULL;
			curr->pt = (void *)malloc(region_size);
			if(curr->pt != NULL){
				memory = true;
				strcpy(curr->name, region_name);
				curr->next = top;
				choosed = curr;
			}
			else{
				free(curr);
				curr = NULL;
			}
		}
	}
	
	return memory;
}

Boolean rchoose(const char *region_name){
	rnode *curr = top;
	while(curr != NULL){
		if(strcmp(curr->name, region_name) == 0){
			
		}
	}
}
