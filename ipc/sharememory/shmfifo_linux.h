#ifndef __SHMFIFO_H__
#define __SHMFIFO_H__

struct head_t{
	int rd_idx;	        // 读位置
	int wr_idx;	        // 写位置
	int blocks;	        // 块数
	int blksz;          // 每块大小
} ;

struct shmfifo_t {
	head_t *p_head;     // 共享内存段的头
	char *p_payload;    // 有效数据地址
	int shmid;          // 共享内存id
	int sem_full;       // 表示满
	int sem_empty;      // 表示还有几个可消费
	int sem_mutex;      // 互斥量
};

shmfifo_t* shmfifo_init(int key, int blocks, int blksz);

void shmfifo_put(shmfifo_t *fifo, const void *buf);

void shmfifo_get(shmfifo_t *fifo, void *buf);

void shmfifo_destroy(shmfifo_t *fifo);

#endif //__SHMFIFO_H__