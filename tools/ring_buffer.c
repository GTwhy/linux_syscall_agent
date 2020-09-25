#include "../headers/ring_buffer.h"
#include "../headers/semaphore_helper.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

int semid, shmid_buffer, shmid_queue;//信号量、共享内存标识符

/**
 * 为缓冲区加锁
 * @return
 */
int lock_shm(){
    /*占用信号量，p操作*/
    if(sem_p(semid))
    {
        printf("%s : sem_p failed !\n",__func__);
        return -1;
    }
    return 0;
}

/**
 *  释放锁
 * @return
 */
int unlock_shm(){
    /*释放信号量，v操作*/
    if(sem_v(semid))
    {
        printf("%s : sem_v failed!\n",__func__);
        return 1;
    }
    return 0;
}



/**
 * 申请RIngBuffer所用的共享内存
 * @param size
 * @return
 */
void* buffer_malloc(size_t size){

/*获取共享内存标识符*/
    shmid_buffer = shmget(ftok(FTOK_FILE_BUFFER, 123), size, IPC_CREAT | 0666);
    if (shmid_buffer == -1) {
        printf("%s : shmid_buffer = %d!\n", __func__, shmid_buffer);
        return NULL;
    }

/*当前进程连接该共享内存段*/
    void* buffer_addr = (void *) shmat(shmid_buffer, 0, 0);
    if (buffer_addr == (void *) -1) {
        printf("%s : shm_addr == (void*)0!\n", __func__);
        return NULL;
    }

    semid = creat_sem();
    if (semid == -1) {
        printf("%s : semid = %d!\n", __func__, semid);
        return NULL;
    }
    return buffer_addr;
}

/**
 * 初始化共享内存建立缓冲区
 * @param number_of_nodes
 * @return
 */
RingBuffer* init_buffer(int number_of_nodes) {
    /*获取信号量标识符*/
    semid = creat_sem();
    if (semid == -1) {
        printf("%s : semid = %d!\n", __func__, semid);
        return NULL;
    }
    /*创建信号量之后的，初始化操作*/
    if (set_semvalue(semid)) {
        printf("%s : set_semvalue failed!\n", __func__);
        return NULL;
    }
    while (lock_shm());
    //TODO:改为共享内存
    RingBuffer* buf = (RingBuffer*)buffer_malloc(sizeof(RingBuffer));
    if(buf == NULL){
        printf("%s :  malloc failed!\n", __func__);
    }
    buf->head = -1;
    buf->tail = -1;
    buf->size = number_of_nodes;
    buf->res_buf_pointer = 0;
    memset((void*)buf->queue, 0, number_of_nodes * sizeof(Node));
    memset((void*)buf->res_buf, 0, RESULT_BUFFER_SIZE * sizeof(Result));
    while (unlock_shm());
    return buf;
}

/**
 * 判断队列是否为空
 * @param buf
 * @return
 */
int is_buffer_empty(RingBuffer* buf){
    return (buf->head == -1);

}
/**
 * 判断队列是否为满
 * @param buf
 * @return
 */
int is_buffer_full(RingBuffer* buf){
    return ((buf->tail+1)%buf->size == buf->head);
}
/**
 * 入队
 * @param buf
 * @param val
 * @return
 */
int en_queue(RingBuffer* buf, Node val){
    if(is_buffer_full(buf)){
        printf("Buffer is full\n");
        return -1;
    }
    if(is_buffer_empty(buf)){
        buf->head = 0;
    }
    buf->tail = (buf->tail+1)%buf->size;
    //若当前结果缓冲区被占用则后移直到遇到没有被占用的
    do{
        buf->res_buf_pointer = (buf->res_buf_pointer+1)%buf->size;
    }while (buf->res_buf[buf->res_buf_pointer].taken_flag == 1);
    val.res_buf_number = buf->res_buf_pointer;
    buf->queue[buf->tail] = val;
    return buf->res_buf_pointer;
}
/**
 * 出队
 * @param buf
 * @return
 */
int de_queue(RingBuffer* buf){
    if(is_buffer_empty(buf)){
        printf("de_queue failed : Buffer is empty\n");
        return 0;
    }
    if (buf->tail == buf->head){
        buf->head = -1;
        buf->tail = -1;
        return 1;
    }
    buf->head = (buf->head+1)%buf->size;
    return 1;
}


/**
 * 为daemon封装的系统调用代理任务删除函数
 * @return
 */
int del_task(RingBuffer* buf){
    return de_queue((RingBuffer*)buf);
}

/**
 * 获取队头节点
 * @param buf
 * @return
 */
Node* queue_front(RingBuffer* buf){
    if(is_buffer_empty(buf)){
        printf("get queue_front failed : Buffer is empty\n");
        return NULL;
    }
    return &buf->queue[buf->head];
}

/**
 * 获取队尾节点
 * @param buf
 * @return
 */
Node* queue_rear(RingBuffer* buf){
    if(is_buffer_empty(buf)){
        printf("get queue_rear failed : Buffer is empty\n");
        return NULL;
    }
    return &buf->queue[buf->tail];
}

/**
 * 给用户返回值。
 * @param buf
 * @param res_buf_num
 * @param res_val
 */
void return_value_to_user(RingBuffer* buf, int res_buf_num, int res_val){
    buf->res_buf[res_buf_num].get_result_flag = 1;
    buf->res_buf[res_buf_num].x0 = res_val;
}



/**
 * 删除共享内存
 * @return
 */
int delete_shm(RingBuffer* buf){
    if(del_sem(semid))
    {
        printf("%s : del_sem failed!\n", __func__);
        return -1;
    }

/*进程和共享内存脱离*/
    if(shmdt(buf) == -1)
    {
        printf("%s : shmdt failed!\n",__func__);
        return -1;
    }

/*删除共享内存*/
    if(shmctl(shmid_buffer, IPC_RMID, 0) == -1)
    {
        printf("%s : shmctl failed!\n",__func__);
        return -1;
    }

    /*进程和共享内存脱离*/
    if(shmdt(buf->queue) == -1)
    {
        printf("%s : shmdt failed!\n",__func__);
        return -1;
    }

/*删除共享内存*/
    if(shmctl(shmid_queue, IPC_RMID, 0) == -1)
    {
        printf("%s : shmctl failed!\n",__func__);
        return -1;
    }
    return 0;
}

