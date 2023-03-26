#include <stdio.h>
#include "shmfifo_linux.h"

typedef struct {
	int age;
	char name[32];
}person_t;

int main( void )
{
	shmfifo_t * fifo = shmfifo_init(1234, 3, sizeof(person_t));
	
	int i;
	person_t person;
	for (i = 0; i < 10; i++) {
		person.age = 10 + i;
		sprintf(person.name, "name:%d", i + 1);
		shmfifo_put(fifo, &person);
		printf("put %d\n", i+1);
	}
}