#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "regions.h"

void isChoose(Boolean rc, char *string){
	if(rc){
                printf("find memory region named \"%s\"\n", string);
        }
        else{
                printf("Did not find memory region named \"%s\"\n", string);
        }
}

void getMemory(Boolean rc){
	if(rc){
		printf("alloc a memory successfully.\n");
	}
	else{
		printf("Error: did not get a memory.\n");
	}
}


int main(){
	Boolean rc;
	const char *name;
	rc = rinit("first", 1024);
	assert(rc);
	getMemory(rc);
	name = rchosen();
	printf("choose region: %s\n\n", name);
	rc = rinit("first", 780);
	getMemory(rc);
	name = rchosen();
	printf("choose region: %s\n\n", name);
	char *s1 = "first";
	rc = rchoose(s1);
	name = rchosen();
	printf("choose region: %s\n\n", name);
	isChoose(rc, s1);
	char *s2 = "ffirst";
	rc = rchoose(s2);
	isChoose(rc, s2);
	name = rchosen();
	printf("choose region: %s\n\n", name);
	rc = rinit("second", 999);
	assert(rc);
	getMemory(rc);
	name = rchosen();
	printf("choose region: %s\n\n", name);
	char *s3 = "second";
	rc = rchoose(s3);
	isChoose(rc, s3);
	name = rchosen();
	printf("choose region: %s\n\n", name);

	char *c1 = ralloc(200);
	printf("Pointer *c1 is point at %p.\n", c1);	
	char *c2 = ralloc(500);
	printf("Pointer *c2 is point at %p.\n", c2);
	char *c3 = ralloc(100);
	printf("Pointer *c3 is point at %p.\n\n\n", c3);

	printAll();
	printRegions();
	printf("size if c1 is : %d\n",rsize(c1));
	rsize(c2);
	printf("size if c2 is : %d\n",rsize(c2));
	rsize(c3); 
	printf("size if c3 is : %d\n",rsize(c3));

	Boolean fr = rfree(s3);
	printf("Free? : %d\n", fr);
	/*fr = rfree(c2);
	printf("Free? : %d\n", fr);
	fr = rfree(s2);
	printf("Free? : %d\n", fr);
	fr = rfree(c1);
	printf("Free? : %d\n", fr);
	fr = rfree(s1);
	printf("Free? : %d\n", fr);*/
	fr = rfree(c3);
	printf("Free? : %d\n", fr);
	rdump();
	printAll();

	return EXIT_SUCCESS;
}

