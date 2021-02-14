/*
* File Name - uid.c
* Developer - Itay Adi Yosef
*/

/******************************************************************************/
#include <stdbool.h> /* true, false */

#include "uid.h"

/******************************************************************************/

unique_id_t UIDCreate(void)
{
	static size_t count = 0;
	unique_id_t id = {0};

	++count;

	id.time = time(NULL);

	if (id.time != -1)
	{
		id.counter = count;
		id.pid = getpid();
	}

	return (id);
}

/******************************************************************************/

int UIDIsSame(unique_id_t uid1, unique_id_t uid2)
{
	return (uid1.counter == uid2.counter &&
			uid1.pid == uid2.pid &&
			uid1.time == uid2.time);
}

/******************************************************************************/

unique_id_t UIDGetBadUID(void)
{
	unique_id_t id = {0};

	id.counter = 0;
	id.pid = 0;
	id.time = -1;

	return (id);
}

/******************************************************************************/
