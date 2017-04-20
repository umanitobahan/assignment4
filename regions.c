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
	block *pre;
};

struct RNODE{
	char name[200];
	int size;
	void *pt;
	rnode *next;
	rnode *pre;
	int used;
	block *bt;//the first pointer of block
	
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
					curr->bt = NULL;
					if(temp == NULL){
						curr->next = NULL;
						curr->pre = NULL;
						choosed = curr;
						top = curr;
					}
					else{
						curr->next = temp;
						curr->pre = NULL;
						temp->pre = curr;
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
	block *first = choosed->bt;
	assert(block_size > 0);
	block *curr = NULL;
	int rest = 0;
	char *ch = NULL;
	char *result = NULL;
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
					ch = ptr;
					(*ch) = '\0';
				}
					if(first == NULL){
						curr->next = NULL;
						curr->pre = NULL;
						first = curr;
					}
					else if(first != NULL){
						curr->next = first;
						curr->pre = NULL;
						first->pre = curr;
						first = curr;
					}
				choosed->bt = first;
				result = curr->address;
			}	
		}
	}
	return result;
}

void printAll(){
	block *temp = choosed->bt;
	while(temp != NULL){
		printf("BLOCK: %p  SIZE: %d\n", temp->address, temp->size);
		temp = temp->next;	
	}	
}

void printRegions(){
	rnode *temp = top;
	while(temp != NULL){
		printf("REGION :   %s\n", temp->name);
		temp = temp->next;
	}
}

r_size_t rsize(void *block_ptr){
	assert(block_ptr != NULL);
	block *temp = choosed->bt;
	int size = 0;
	if(block_ptr != NULL){
		while(temp != NULL){
			if(temp->address == block_ptr){
				size = temp->size;
			}
			temp = temp->next;
		}
	}
	return size;
}

Boolean rfree(void *block_ptr){
	assert(block_ptr != NULL);
	block *temp = choosed->bt;
	block *first = choosed->bt;
	block *pre = NULL;
	block *follow = NULL;
	Boolean result = false;
	int bsize = 0;
	if(block_ptr != NULL){
		while(temp != NULL){
			if(temp->address == block_ptr){
				if(block_ptr == first->address){
					choosed->bt = temp->next;
					first = choosed->bt;
				}
				bsize = temp->size;
				temp->address = NULL;
				pre = temp->pre;
				if(pre != NULL){
					pre->next = temp->next;
					follow = temp->next;
					if(follow != NULL){
						follow->pre = temp->pre;
					}
					temp->pre = NULL;
					temp->next = NULL;
					free(temp);
					choosed->used = choosed->used - bsize;
					result = true;
					temp = follow;
				}
				else{
					follow = temp->next;
					if(follow != NULL){
						follow->pre = NULL;
					}
					temp->pre = NULL;
					temp->next = NULL;
					free(temp);
					choosed->used = choosed->used - bsize;
					result = true;
					temp = follow;		
				}
			}
			else{
				temp = temp->next;
			}
		}
	}
	return result;
}

void rdump(){
	rnode *rtemp = NULL;
	block *btemp = NULL;
	int rest = 0;
	rtemp = top;
	while(rtemp != NULL){
		printf("Region Name : %s\n", rtemp->name);
		btemp = rtemp->bt;
		if(btemp == NULL){
			printf("There is no block in this region\n");
		}
		else{
			printf("Block pointers and size in region \"%s\" is :\n", rtemp->name);
			while(btemp != NULL){
				printf(" %p, %d bytes\n", btemp->address, btemp->size);
				btemp = btemp->next; 
			}
		}
		rest = rtemp->size - rtemp->used;
		printf("The unused space is %d bytes\n\n", rest);
		rtemp = rtemp->next;
	}
}
