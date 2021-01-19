/****************************************************************************
 *						code by : orpaz Houta								*
 *						review by : Gil S									*
 *						coding date : 28.4.20								*
 ***************************************************************************/
#include <assert.h>			/* assert */
#include "ca_test_util.h" 	/* ©️ chanan & aviv */
#include "scheduler.h"
#include "task.h"

typedef struct to_remove
{
	scheduler_t *schd;
	ilrd_uid_t task_uid;
}to_remove_t;

void TestSchdCreate();

int PrintInt(int *param);
int PrintChar(char *param);
int PrintString(char *param);
int StopSchd(scheduler_t *param);
int StopTask(to_remove_t *remove);


int main()
{
	TestSchdCreate();

    TEST_SUMMARY();

    return 0;
}

void TestSchdCreate()
{
	scheduler_t *test_sch = SchdCreate();
	action_func func1 = (action_func)&PrintInt;
	action_func func2 = (action_func)&PrintChar;
	action_func func3 = (action_func)&PrintString;
	action_func stop = (action_func)&StopSchd;
	ilrd_uid_t uid1 = {0, 0, 0};
	ilrd_uid_t uid2 = {0, 0, 0};
	int one = 1;
	char two = 't';
	char three[] = "three";
	to_remove_t test_remove;
	test_remove.schd = test_sch;
	test_remove.task_uid = uid1;

    INT_TEST(0, SchdSize(test_sch));
	INT_TEST(1, SchdIsEmpty(test_sch));

	uid1 = SchdAdd(test_sch, func1, 1, &one);
	uid2 = SchdAdd(test_sch, func2, 2, &two);
	SchdAdd(test_sch, func3, 3, &three);
	SchdAdd(test_sch, stop, 10, test_sch);
	SchdAdd(test_sch, (action_func)&StopTask, 5, &test_remove);

    INT_TEST(5, SchdSize(test_sch));
	INT_TEST(0, SchdIsEmpty(test_sch));

	INT_TEST(0, SchdRemove(test_sch, uid2));
    INT_TEST(4, SchdSize(test_sch));

	uid2 = SchdAdd(test_sch, func2, 2, &two);

	SchdRun(test_sch);

	SchdDestroy(test_sch);
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

int StopSchd(scheduler_t *param)
{
	SchdStop(param);
	return 0;
}

int StopTask(to_remove_t *remove)
{
	assert(remove);

	printf("remove task 1");
	return 1;
}
