#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>

int main()
{
	static char *udid = NULL;
	idevice_error_t ret = IDEVICE_E_UNKNOWN_ERROR;
	idevice_t device = NULL;
	lockdownd_client_t client = NULL;
	lockdownd_error_t ldret = LOCKDOWN_E_UNKNOWN_ERROR;

	if (IDEVICE_E_SUCCESS != idevice_new(&device, NULL)) {
		printf("No device found, is it plugged in?\n");
		return EXIT_FAILURE;
	}

	ret = idevice_get_udid(device, &udid);
	printf("[i] UDID : %s\n", udid);
	printf("[i] Telling device to enter recovery mode.\n");

	if (LOCKDOWN_E_SUCCESS != (ldret = lockdownd_client_new(device, &client, "ideviceenterrecovery"))){
		printf("ERROR: Could not connect to lockdownd, error code %d\n", ldret);
		idevice_free(device);
		return -1;
	}

	if (lockdownd_enter_recovery(client) != LOCKDOWN_E_SUCCESS){
		printf("Failed to enter recovery mode : %s\n", strerror(errno));
		return -2;
	}

	printf("[i] Device is switching to recovery mode.\n");

	lockdownd_client_free(client);
	idevice_free(device);

	return 0;
}