#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "regions.h"

int main(){
	Boolean rc;
	rc = rinit("first", 1024);
	assert(rc);
		

	return EXIT_SUCCESS;
}

