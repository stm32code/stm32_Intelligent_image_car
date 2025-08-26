#ifndef __TASK_H__
#define __TASK_H__
#include "sys.h"




//变量申明
typedef void (*TASK_FUNC)(void);



//函数申明
void task_init(void);
void task_tick(void);
u16 task_create(u32 countdown,u32 interval,TASK_FUNC func_cb);
void task_delete(u16 id);
void task_handler(void);




#endif
