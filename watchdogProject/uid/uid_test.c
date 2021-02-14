/*
* File Name - uid_test.c
* Developer - Itay Adi Yosef
*/

/***************************User's declarations********************************/

#include <stdio.h>

#include "uid.h"

/************************Test function declarations****************************/

unique_id_t UIDCreateTest(void);
void UIDIsSameTest(unique_id_t uid1, unique_id_t uid2);
unique_id_t UIDGetBadUIDTest(void);

/**********************Test case function declarations*************************/

void UidTestCase(void);

/**********************************main****************************************/

int main()
{
	printf("--------------------------------------------\n");
	UidTestCase();
	printf("--------------------------------------------\n");

	return (0);
}

/************************Test function implemintations*************************/

unique_id_t UIDCreateTest(void)
{
	unique_id_t id = {0};

	printf("Create:\n");
	id = UIDCreate();
	printf("UID %ld has been created.\n\n", id.counter);

	return (id);
}

/**********************************************************************/

void UIDIsSameTest(unique_id_t uid1, unique_id_t uid2)
{
	printf("Is Same Test:\nThe IDs are");
	UIDIsSame(uid1,uid2) ? printf(" ") : printf(" not ");
	printf("the same.\n\n");
}

/**********************************************************************/

unique_id_t UIDGetBadUIDTest(void)
{
	unique_id_t bad_uid = {0};

	printf("Creates a bad UID:\n");
	bad_uid = UIDGetBadUID();
	printf("Bad UID has been created.\n");

	return (bad_uid);
}

/**********************Test case function implementations**********************/

void UidTestCase(void)
{
	unique_id_t id1 = {0};
	unique_id_t id2 = {0};
	unique_id_t id_bad = {0};

	/*create the UID*/	
	id1 = UIDCreateTest();
	id2 = UIDCreateTest();
	id_bad = UIDGetBadUIDTest();

	/*make sure they are not same*/
	UIDIsSameTest(id1, id1);
	UIDIsSameTest(id1, id2);

	/*prints their values*/
	printf("counter: %ld\n", id1.counter);
	printf("PID: %d\n", id1.pid);
	printf("Time: %ld\n\n", id1.time);

	printf("counter: %ld\n", id2.counter);
	printf("PID: %d\n", id2.pid);
	printf("Time: %ld\n\n", id2.time);

	printf("counter: %ld\n", id_bad.counter);
	printf("PID: %d\n", id_bad.pid);
	printf("Time: %ld\n\n", id_bad.time);

	printf("make sure id1 is fine:\n");
	UIDIsSameTest(id1, id_bad);
}

/******************************************************************************/











