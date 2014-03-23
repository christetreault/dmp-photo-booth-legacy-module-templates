#include "dmp_printer_module.h"

int (*console_write)(const char * message);
void (*status_handler)(int status);

int dmp_pm_install_status_handler(void (*sh)(int status))
{
	status_handler = sh;
	return DMP_PB_SUCCESS;
}

int dmp_pm_install_console(int (*c_cb)(const char * message))
{
	console_write = c_cb;
	return DMP_PB_SUCCESS;
}

int dmp_pm_print(const char * to_print)
{
	return DMP_PB_SUCCESS;
}

int dmp_pm_edit_config(void)
{
	return DMP_PB_SUCCESS;
}

int dmp_pm_initialize(void)
{
	return DMP_PB_SUCCESS;
}

int dmp_pm_finalize(void)
{
	return DMP_PB_SUCCESS;
}

int dmp_pm_console_write(const char * to_write)
{
	return (*console_write)(to_write);
}

void dmp_pm_set_status(int status)
{
	(*status_handler)(status);
}