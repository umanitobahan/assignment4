#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "regions.h"

typedef struct RNODE rnode;
typedef struct BLOCK block;


struct BLOCK{
	char region[200];
	void *address;
	int size;
	block *next;
};

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
static block *first = NULL;


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
	block *curr = NULL;
	int rest = 0;
	char *ch = NULL;
	char *result = NULL;
	//int count = 0;
	if(block_size > 0){
		rest = choosed->size - choosed->used;
		if(block_size <= rest){
			curr = (void *)malloc(sizeof(block));
			assert(curr != NULL);
			if(curr != NULL){
				printf("alloc block successfully!\n");
				strcpy(curr->region, choosed->name);
				printf("The block in %s region!\n", curr->region);
				curr->size = block_size;
				printf("the size of the block is %d\n", curr->size);
				curr->address = choosed->pt + choosed->used;
				printf("the pointer of the block is point at %p\n", curr->address);
				choosed->used += block_size;
				printf("The %s region used %d bits of memory\n", choosed->name, choosed->used);
				for(void *ptr=curr->address; ptr<curr->address+block_size; ptr++){
					//count++;
					//printf("ptr address is:  %p\n", ptr);
					ch = ptr;
					//printf("ch address is: %p\n", ch);
					(*ch) = '\0';
				}
				//printf("block size is: %d and the count is: %d \n", block_size, count);
					if(first == NULL){
						curr->next = NULL;
						first = curr;
					}
					else if(first != NULL){
						curr->next = first;
						first = curr;
					}
				result = curr->address;
			}	
		}
	}
	return result;
}

r_size_t rsize(void *block_ptr){
	
}
