/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil Steinberg							*
 *						coding date : 11.6.20								*
 ***************************************************************************/
#include <assert.h>			/* assert */

#include "heap_scheduler.h"

#include "task.h"
#include "ca_test_util.h" 	/* ©️ chanan & aviv */

typedef struct to_remove
{
	heap_scheduler_t *schd;
	ilrd_uid_t task_uid;
}to_remove_t;

void TestHeapSchdCreate();

int PrintInt(int *param);
int PrintChar(char *param);
int PrintString(char *param);
int StopHeapSchd(heap_scheduler_t *param);
int StopTask(to_remove_t *remove);


int main()
{
	TestHeapSchdCreate();

    TEST_SUMMARY();

    return 0;
}

void TestHeapSchdCreate()
{
	heap_scheduler_t *test_sch = HeapSchdCreate();
	action_func func1 = (action_func)&PrintInt;
	action_func func2 = (action_func)&PrintChar;
	action_func func3 = (action_func)&PrintString;
	action_func stop = (action_func)&StopHeapSchd;
	ilrd_uid_t uid1 = {0, 0, 0};
	ilrd_uid_t uid2 = {0, 0, 0};
	int one = 1;
	char two = 't';
	char three[] = "three";
	to_remove_t test_remove;

    INT_TEST(0, HeapSchdSize(test_sch));
	INT_TEST(1, HeapSchdIsEmpty(test_sch));

	uid1 = HeapSchdAdd(test_sch, func1, 1, &one);
	test_remove.schd = test_sch;
	test_remove.task_uid = uid1;
	uid2 = HeapSchdAdd(test_sch, func2, 2, &two);
	HeapSchdAdd(test_sch, func3, 3, &three);
	HeapSchdAdd(test_sch, stop, 10, test_sch);
	HeapSchdAdd(test_sch, (action_func)&StopTask, 5, &test_remove);

    INT_TEST(5, HeapSchdSize(test_sch));
	INT_TEST(0, HeapSchdIsEmpty(test_sch));

	INT_TEST(0, HeapSchdRemove(test_sch, uid2));
    INT_TEST(4, HeapSchdSize(test_sch));

	uid2 = HeapSchdAdd(test_sch, func2, 2, &two);

	HeapSchdRun(test_sch);

	HeapSchdDestroy(test_sch);
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

int StopHeapSchd(heap_scheduler_t *param)
{
	HeapSchdStop(param);
	return 0;
}

int StopTask(to_remove_t *remove)
{
	assert(remove);

	printf("remove task 1");

	HeapSchdRemove(remove->schd, remove->task_uid);

	return 1;
}
