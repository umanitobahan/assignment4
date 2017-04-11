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


	return EXIT_SUCCESS;
}

