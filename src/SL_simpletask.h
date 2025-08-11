#ifndef __SIMPLE_TASK_H
#define __SIMPLE_TASK_H
#include "stdbool.h"

typedef struct {
  int id;                       // 任务ID
  void (*function)();          // 任务回调函数
  unsigned long interval;      // 执行周期（毫秒）
  unsigned long lastRun;       // 上次执行时间
  unsigned long delayUntil;    // 延时结束时间
  bool enabled;                // 任务启用状态
}Task_MS;

#define TASK_DEBUG  false
#define MAX_TASKS 5
extern int taskCount;
extern Task_MS taskList[MAX_TASKS];

bool TaskCreate(void (*taskFunc)(), unsigned long interval, int id);
bool TaskDelete(int id);
bool TaskDelay(int id, unsigned long delayMs);

void SchedulerInit();
void SchedulerRun();

#endif