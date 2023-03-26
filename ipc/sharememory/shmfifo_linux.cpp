#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <assert.h>
#include <string.h>
#include "shmfifo_linux.h"

union semun { int value; };

static void p(int id)
{
	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op  = -1;
	sb[0].sem_flg = 0;
	semop(id, sb, 1);
}

static void v(int id)
{
	struct sembuf sb[1];
	sb[0].sem_num = 0;
	sb[0].sem_op  = 1;
	sb[0].sem_flg = 0;
	semop(id, sb, 1);
}

shmfifo_t* shmfifo_init(int key, int blocks, int blksz)
{
	shmfifo_t *p = (shmfifo_t*)malloc(sizeof(shmfifo_t));
	assert(p);

	int len = blocks * blksz + sizeof(head_t);
	int shmid = shmget(key, len, 0);
	if ( shmid == -1 ) { // 不存在，创建
		shmid = shmget(key, len, IPC_CREAT | 0644);
		if ( shmid == -1 ) perror("shmget"), exit(1);
		p->p_head = (head_t*)shmat(shmid, NULL, 0);
		p->p_head->rd_idx = 0;
		p->p_head->wr_idx = 0;
		p->p_head->blocks = blocks;
		p->p_head->blksz  = blksz;
		p->p_payload = (char*)(p->p_head + 1);
		p->shmid = shmid;
		p->sem_empty = semget(key, 1, IPC_CREAT | 0644);
		p->sem_full  = semget(key + 1, 1, IPC_CREAT | 0644);
		p->sem_mutex = semget(key + 2, 1, IPC_CREAT | 0644);
		union semun su;
		su.value = 0;
		semctl(p->sem_empty, 0, SETVAL, su);
		su.value = blocks;
		semctl(p->sem_full, 0, SETVAL, su);
		su.value = 1;
		semctl(p->sem_mutex, 0, SETVAL, su);
	} else { // 存在
		p->p_head = (head_t*)shmat(shmid, NULL, 0);
		p->p_payload = (char*)(p->p_head + 1);
		p->shmid = shmid;
		p->sem_empty = semget(key, 0, 0);
		p->sem_full  = semget(key+1, 0, 0);
		p->sem_mutex = semget(key+2, 0, 0);
	}

	return p;
}

void shmfifo_put(shmfifo_t *fifo, const void *buf)
{
	p(fifo->sem_full);
	p(fifo->sem_mutex);
	memcpy(fifo->p_payload + (fifo->p_head->wr_idx * fifo->p_head->blksz),
			buf, fifo->p_head->blksz);
	fifo->p_head->wr_idx = 
			(fifo->p_head->wr_idx + 1) % fifo->p_head->blocks;
	v(fifo->sem_mutex);
	v(fifo->sem_empty);
}

void shmfifo_get(shmfifo_t *fifo, void *buf)
{
	p(fifo->sem_empty);
	p(fifo->sem_mutex);

	memcpy(buf, fifo->p_payload + (fifo->p_head->rd_idx * fifo->p_head->blksz), 
		fifo->p_head->blksz);
	fifo->p_head->rd_idx = (fifo->p_head->rd_idx + 1) % fifo->p_head->blocks;
	
	v(fifo->sem_mutex);
	v(fifo->sem_full);
}

void shmfifo_destroy(shmfifo_t *fifo)
{
	shmdt(fifo->p_head);
	shmctl(fifo->shmid, IPC_RMID, 0);
	semctl(fifo->sem_full, 0, IPC_RMID);
	semctl(fifo->sem_mutex, 0, IPC_RMID);
	semctl(fifo->sem_empty, 0, IPC_RMID);
	free(fifo);
}