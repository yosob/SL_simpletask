#include "simpletask.h"
int task1_id = 1;       // 任务1 id
int task2_id = 3;       // 任务2 id

void task1()            // 任务1 执行函数，不能有while(1)
{
  Serial.println("task1");
  TaskDelay(task1_id, 1000);      // 延时时间 > 执行周期才有效
}

void task2()            // 任务2 执行函数，不能有while(1)
{
  Serial.println("task2");
}


void setup() {
  Serial.begin(9600);
  SchedulerInit();            // 初始化调度器

  TaskCreate(&task1, 500, task1_id);   // 创建任务1
  TaskCreate(&task2, 500, task2_id);   // 创建任务2
}

void loop() {
  SchedulerRun();             // 执行调度器
}