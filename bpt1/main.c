
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

#ifdef USER_APP
int main( int argc, char ** argv )
#else
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING reg_path)
#endif
{
	KEY_T i;
	node * root = NULL;

	DbgPrint("bpt: Our fs is loading...\r\n");
	for(i = 0; i < 40; i++)
		root = Insert(root, i, i*10);

	for(i = 0; i < 40; i+=2)
		root = Delete(root, i);

#ifdef USER_APP
	Print_Tree_File(root);
#else	
	driver->DriverUnload = DriverUnload;
#endif

	Destroy_Tree(root);
#ifdef USER_APP
	return 0;
#else
	return STATUS_SUCCESS;
#endif
}
