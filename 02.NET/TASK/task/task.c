#include "task.h"
#include <string.h>

typedef struct
{
	u32 countdown; // 单位设定为了ms
	u32 interval;
	TASK_FUNC func_cb;
	u8 sta;
} TASK;

#define TASK_STA_IDLE 0x00 // 空闲
#define TASK_STA_WAIT 0x01 // 等待

#define TASK_TABLE_LEN 8
static TASK task_table[TASK_TABLE_LEN];
static double cur_tick, last_tick, elapsed_tick;
static u16 task_id;

void task_init()
{
	cur_tick = 0;
	last_tick = 0;
	memset((void *)task_table, 0, sizeof(task_table));
}

void task_tick()
{
	cur_tick += 1;
}

// 返回任务id,从1开始的,0代表失败
u16 task_create(u32 countdown, u32 interval, TASK_FUNC func_cb)
{
	u16 i;

	for (i = 0; i < TASK_TABLE_LEN; i++)
	{
		if (task_table[i].sta == TASK_STA_IDLE)
		{
			task_table[i].countdown = countdown;
			task_table[i].interval = interval;
			task_table[i].func_cb = func_cb;
			task_table[i].sta = TASK_STA_WAIT;

			return i + 1;
		}
	}

	return 0; // 创建失败
}

void task_delete(u16 id)
{
	if (id >= 1 && id <= TASK_TABLE_LEN)
	{
		id--;
		task_table[id].countdown = 0;
		task_table[id].interval = 0;
		task_table[id].func_cb = 0;
		task_table[id].sta = TASK_STA_IDLE;
	}
}

void task_handler()
{
	elapsed_tick = cur_tick - last_tick;
	last_tick = cur_tick;

	for (task_id = 0; task_id < TASK_TABLE_LEN; task_id++)
	{
		if (task_table[task_id].countdown == 0)
			continue;
		if (task_table[task_id].countdown > elapsed_tick)
			task_table[task_id].countdown -= elapsed_tick;
		else
			task_table[task_id].countdown = 0;

		if ((task_table[task_id].countdown == 0) && (task_table[task_id].sta == TASK_STA_WAIT))
		{
			if (task_table[task_id].func_cb)
				task_table[task_id].func_cb();

			if (task_table[task_id].interval)
				task_table[task_id].countdown = task_table[task_id].interval;
			else
				task_table[task_id].sta = TASK_STA_IDLE;
		}
	}
}
