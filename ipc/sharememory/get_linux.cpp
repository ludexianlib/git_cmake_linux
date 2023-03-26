#include <stdio.h>
#include "shmfifo_linux.h"

typedef struct {
	int age;
	char name[32];
}person_t;

int main( void )
{
	shmfifo_t * fifo = shmfifo_init(1234, 3, sizeof(person_t));
	
	person_t person;
	int i;
	for (i=0; i<10; i++) {
		shmfifo_get(fifo, &person);
		printf("name=%s, age=%d\n", person.name, person.age);
		sleep(1);
	}
	shmfifo_destroy(fifo);
}