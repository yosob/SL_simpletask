# simpletaskforarduino

极简的任务框架，可以实现简单的创建任务、设定任务执行周期、设定任务下一个执行时间等功能。方便进行arduino框架下的简单非阻塞式编程。不支持上下文切换功能，也就是每个任务函数必定是直接执行完的。

## 1. 提供功能

| 函数名        | 功能         | 参数                                                                                                                 | 注意事项                                            |
| ------------- | ------------ | -------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------- |
| SchedulerInit | 初始化调度器 | 无                                                                                                                   | setup中使用                                         |
| SchedulerRun  | 执行调度器   | 无                                                                                                                   | loop中使用                                          |
| TaskCreate    | 任务创建     | taskFunc：任务函数，任务执行的函数<br />interval：任务间隔，任务执行的间隔时间<br />id：任务的id号，用于唯一标识任务 | 任意地方使用                                        |
| TaskDelete    | 任务删除     | id：任务的id号，用于唯一标识任务                                                                                     | 任意地方使用                                        |
| TaskDelay     | 任务延时     | id：任务的id号，用于唯一标识任务<br />delayMs：延时时间，单位毫秒                                                    | 任意地方使用，delay时间要大于此任务的执行周期才有效 |

## 2. 使用方法

1. 创建任务函数
2. setup中执行调度器的初始化和任务的创建
3. loop中执行调度器

```c
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

```
