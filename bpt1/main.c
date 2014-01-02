#include "bpt.h"

#ifdef USER_APP
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#else
#include <ntddk.h>
VOID DriverUnload(PDRIVER_OBJECT driver)
{
	DbgPrint("bpt: Our driver is unloading...\r\n");
}
#endif

void run_test_bpt(void*c)
{
	KEY_T i;
	node * root = NULL, *left;

	for(i = 0; i < 0xFFFFF; i++)
		root = Insert(root, i, i);

	for(i = 0; i < 0xFFFFF; i+=2)
		root = Delete(root, i);

#ifdef USER_APP
	left = Get_Leftmost_Leaf(root);
	while(left)
	{
		for(i = 0; i < left->num_keys; i++)
			printf("(%ld,%ld)", left->keys[i], ((record*)left->pointers[i])->value );
		printf("\n");
		left = left->pointers[order - 1];
	}
	Print_Tree_File(root);
	Destroy_Tree(root);
#else
	Destroy_Tree(root);
	PsTerminateSystemThread(STATUS_SUCCESS);
#endif
}

#ifdef USER_APP
int main( int argc, char ** argv )
{
	printf("bpt: Our bpt is loading...\r\n");
	run_test_bpt(NULL);
	return 0;
}
#else
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path)
{
	HANDLE hThread;
	DbgPrint("bpt: Our bpt is loading...\r\n");
	driver->DriverUnload = DriverUnload;
	PsCreateSystemThread(
		&hThread,
		(ACCESS_MASK)0,
		NULL,
		(HANDLE)0,
		NULL,
		run_test_bpt,
		NULL);
	return STATUS_SUCCESS;
}
#endif
