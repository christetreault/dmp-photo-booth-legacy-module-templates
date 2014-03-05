#include "dmp_camera_module.h"

int (*console_write)(const char * message);
void (*status_handler)(gint status);

int dmp_cm_install_console(int (*c_cb)(const char * message))
{
	console_write = c_cb;
	return DMP_PB_SUCCESS;
}

int dmp_cm_install_status_handler(void (*sh)(int status))
{
	status_handler = sh;
	return DMP_PB_SUCCESS;
}

int dmp_cm_capture(const char * location)
{
	return DMP_PB_SUCCESS;
}

int dmp_cm_edit_config(void)
{
	return DMP_PB_SUCCESS;
}

int dmp_cm_initialize(void)
{
	return DMP_PB_SUCCESS;
}

int dmp_cm_finalize(void)
{
	return DMP_PB_SUCCESS;
}

int dmp_cm_console_write(const gchar * to_write)
{
	return (*console_write)(to_write);
}

void dmp_cm_set_status(int status)
{
	(*status_handler)(status);
}