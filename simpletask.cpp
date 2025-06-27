#include "simpletask.hpp"
#include <Arduino.h>

Task_MS taskList[MAX_TASKS];                // 任务列表
int taskCount = 0;                           // 当前任务数量


/*
任务创建函数，把一个任务加入到任务列表中，并在schedulerun中执行它
- taskFunc：任务函数，任务执行的函数
- interval：任务间隔，任务执行的间隔时间
- id：任务的id号，用于唯一标识任务
*/
bool TaskCreate(void (*taskFunc)(), unsigned long interval, int id) {
  if(id < 0) return false;                        // 判断任务ID是否合法
  if (interval == 0) return false;              // 判断任务间隔是否合法
  if (taskCount >= MAX_TASKS) return false;         // 判断是否超出最大任务数

  for(int i = 0; i < taskCount; i++) {              // 判断任务ID是否已存在
    if (taskList[i].id == id) return false;
  }
  
  taskList[taskCount].id = id;                       // 设置任务ID
  taskList[taskCount].function = taskFunc;          // 设置任务函数
  taskList[taskCount].interval = interval;          // 设置任务间隔
  taskList[taskCount].lastRun = millis();           // 设置任务上次执行时间
  taskList[taskCount].enabled = true;               // 设置任务为启用状态
  
  taskCount++;
  return true;
}

/*
删除任务函数
- id：任务的id号，用于唯一标识任务
*/
bool TaskDelete(int id) {
    for(int i = 0; i < taskCount;)
    {
        if(taskList[i].id == id)
        {
            taskList[i].enabled = false;                // 将任务标记为禁用
            for(int j = i; j < taskCount - 1;)          // 将后面的任务向前移动
            {
                taskList[j] = taskList[j + 1];
                j++;
            }
            taskCount--;                                  // 任务数量减一   
            return true;    // 删除成功
        }
    }
    return false;           // 任务不存在
}

/*
延时函数，延时时间 > 任务执行周期的时候才有效
- id：任务的id号，用于唯一标识任务
- delayMs：延时时间，单位毫秒
*/
bool TaskDelay(int id, unsigned long delayMs) {
  for(int i = 0; i < taskCount; i++) {              // 遍历任务列表
    if (taskList[i].id == id) {                      // 找到任务
      taskList[i].delayUntil = millis() + delayMs;  // 设置延时结束时间
      return true;
    }
  }
  return false;                        // 任务不存在
}

/*
调度器初始化函数，初始化任务列表，在setup中调用一次
*/
void SchedulerInit() {
  // 初始化任务队列
  for (int i = 0; i < MAX_TASKS; i++) {
    taskList[i].id = -1;
    taskList[i].function = NULL;
    taskList[i].enabled = false;
  }
}

void SchedulerRun() {
  unsigned long currentTime = millis();
  
  for (int i = 0; i < taskCount; i++) {
    if (!taskList[i].enabled || currentTime < taskList[i].delayUntil) {
      continue;  // 跳过禁用或延时中的任务
    }
    
    if (currentTime - taskList[i].lastRun >= taskList[i].interval) {
      taskList[i].function();           // 执行任务
      taskList[i].lastRun = currentTime; // 更新执行时间
    }
  }
}


