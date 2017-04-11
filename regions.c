#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"

typedef struct RNODE rnode;

struct RNODE{
	char name[200];
	int size;
	void *pt;
	rnode *next;
	int used;
};

static rnode *top = NULL;
static rnode *choosed = NULL;
static rnode *traverse = NULL;



Boolean rinit(const char *region_name, r_size_t region_size){
	assert(region_name != NULL);
	assert(region_size > 0);
	rnode *curr = top;
	rnode *temp = top;
	Boolean sameName = false;
	Boolean memory = false;
	if(region_size > 0){
		while(!sameName && curr != NULL){
			if(strcmp(region_name, curr->name) != 0){
				curr = curr->next;
			}
			else{
				sameName = true;
			}
		}
		
		if(!sameName){
			assert(curr == NULL);
			curr = (rnode *)malloc(sizeof(rnode));
			assert(curr != NULL);
			if(curr != NULL){
				curr->pt = NULL;
				curr->pt = (void *)malloc(region_size);
				assert(curr->pt != NULL);
				if(curr->pt != NULL){
					memory = true;
					strcpy(curr->name, region_name);
					curr->size = region_size;
					curr->used = 0;
					if(temp == NULL){
						curr->next = NULL;
						choosed = curr;
						top = curr;
					}
					else{
					curr->next = temp;
					choosed = curr;
					top = curr;
					}
				}
				else{
					free(curr);
					curr = NULL;
				}
			}
		}
	}
	return memory;
}

Boolean rchoose(const char *region_name){
	rnode *curr = top;
	Boolean found = false;
	while(curr != NULL){
		if(strcmp(curr->name, region_name) == 0){
			choosed = curr;
			found = true;
			curr = curr->next;		
		}
		else{
			curr = curr->next;
		}
	}
	
	return found;
}

const char *rchosen(){
	char *name = NULL;
	if(choosed != NULL){
		name = choosed->name;
	}

	return name;
}

void *ralloc(r_size_t block_size){
	assert(block_size > 0);
	int useds = 0;
	if(block_size > 0){
		useds = block_size + choosed->size;
		if(useds <= choosed->size){
			
		}
	}
}
