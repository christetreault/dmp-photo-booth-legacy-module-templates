#include "dmp_trigger_module.h"


void (*trigger_handler)(void);
int (*console_write)(const char * message);
void (*status_handler)(gint status);

int dmp_tm_install_status_handler(void (*sh)(int status))
{
	status_handler = sh;
	return DMP_PB_SUCCESS;
}

int dmp_tm_show_error(int value)
{
	return DMP_PB_SUCCESS;
}

int dmp_tm_install_console(int (*c_cb)(const char * message))
{
	console_write = c_cb;
	return DMP_PB_SUCCESS;
}

int dmp_tm_add_trigger_handler(void (*th)(void))
{
	trigger_handler = th;
	return DMP_PB_SUCCESS;
}

int dmp_tm_set_countdown(int current)
{
	return DMP_PB_SUCCESS;
}

int dmp_tm_edit_config(void)
{
	return DMP_PB_SUCCESS;
}

int dmp_tm_initialize(void)
{
	return dmp_tm_lifecycle_initialize();
}

int dmp_tm_finalize(void)
{
	return dmp_tm_lifecycle_finalize();
}

int dmp_tm_console_write(const char * to_write)
{
	return (*console_write)(to_write);
}

void dmp_tm_call_trigger_handler(void)
{
	(*trigger_handler)();
}

void dmp_tm_set_status(int status)
{
	(*status_handler)(status);
}