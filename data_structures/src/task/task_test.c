/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil S									*
 *						coding date : 28->4->20								*
 ***************************************************************************/
#include <stdio.h> /* printf */

#include "task.h"
#include "uid.h"


void Test();
int PrintInt(int *param);
int PrintChar(char *param);
int PrintString(char *param);

int main()
{
	Test();
	printf("\nend of test\n");

    return 0;
}

void Test()
{
	action_func func1 = (action_func)&PrintInt;
	action_func func2 = (action_func)&PrintChar;
	action_func func3 = (action_func)&PrintString;
	int one = 1;
	char two = 't';
	char three[] = "three";
	ilrd_uid_t uid = {0, 0, 0};
	time_t run_time = 0;
	time_t after_sleep = 0;

	task_t *test_task = TaskCreateTask(func1, 1, &one);
	task_t *test_task2 = TaskCreateTask(func2, 2, &two);
	task_t *test_task3 = TaskCreateTask(func3, 3, &three);
	run_time = TaskGetTime(test_task);
	
    if (0 != UIDIsSame(TaskGetUID(test_task), uid))
	{
		printf("TaskGetUID FAIL\n");
	}
	TaskUpdateTime(test_task);
	TaskUpdateTime(test_task2);
	TaskUpdateTime(test_task3);

    if (0 == TaskGetTime(test_task))
	{
		printf("TaskGetTime FAIL\n");
	}

    if (1 != (TaskGetTime(test_task) - time(NULL)))
	{
		printf("TaskUpdateTime FAIL\n");
	}

    if (2 != (TaskGetTime(test_task2) - time(NULL)))
	{
		printf("TaskUpdateTime FAIL\n");
	}
	Taskexecute(test_task);
	Taskexecute(test_task2);
	Taskexecute(test_task3);

	run_time = time(NULL);
	TaskPause(test_task2);
	after_sleep = time(NULL);

    if (2 != (after_sleep - run_time))
	{
		printf("TaskPause FAIL\n");
	}
	TaskDestroy(test_task);
	TaskDestroy(test_task2);
	TaskDestroy(test_task3);
}

int PrintInt(int *param)
{
	printf("%d, ", *param);
	return 0;
}

int PrintChar(char *param)
{
	printf("%c, ", *param);
	return 0;
}

int PrintString(char *param)
{
	printf("%s, ", param);
	return 0;
}

