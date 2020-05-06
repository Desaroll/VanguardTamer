#include <stdio.h>
#include <conio.h>
#include <Windows.h>

void errorHandler() {
	switch(GetLastError()) {
		case ERROR_ACCESS_DENIED:
			printf("ERROR_ACCESS_DENIED\n");
			printf("%ls",L"Be sure to execute this tool with administration rights.\nThis error can also appear if the Vanguard is already closed and you try to close it again.\n");
			printf("%ls",L"Asegurate de correr esta herramienta con permisos de administrador\nEste error también puede salir si el proceso ya está detenido e intentas detenerlo.\n");
			break;
		case ERROR_INVALID_HANDLE:
			printf("ERROR_INVALID_HANDLE\n");
			break;
		case ERROR_INVALID_NAME:
			printf("ERROR_INVALID_NAME\n");
			break;
		case ERROR_SERVICE_DOES_NOT_EXIST:
			printf("ERROR_SERVICE_DOES_NOT_EXIST\n");
			break;
		case ERROR_INVALID_PARAMETER:
			printf("ERROR_INVALID_PARAMETER\n");
			break;
		case ERROR_SERVICE_MARKED_FOR_DELETE:
			printf("ERROR_SERVICE_MARKED_FOR_DELETE\n");
			break;
		case ERROR_DEPENDENT_SERVICES_RUNNING:
			printf("ERROR_DEPENDENT_SERVICES_RUNNING\n");
			break;
		case ERROR_INVALID_SERVICE_CONTROL:
			printf("ERROR_INVALID_SERVICE_CONTROL\n");
			break;
		case ERROR_SERVICE_CANNOT_ACCEPT_CTRL:
			printf("ERROR_SERVICE_CANNOT_ACCEPT_CTRL\n");
			break;
		case ERROR_SERVICE_NOT_ACTIVE:
			printf("ERROR_SERVICE_NOT_ACTIVE\n");
			break;
		case ERROR_SERVICE_REQUEST_TIMEOUT:
			printf("ERROR_SERVICE_REQUEST_TIMEOUT\n");
			break;
		case ERROR_SHUTDOWN_IN_PROGRESS:
			printf("ERROR_SHUTDOWN_IN_PROGRESS\n");
			break;
		default:
			printf("Unknown error! %i",GetLastError());
			break;
	}
	getch(); 
}

int main() {
    if(IsValidCodePage(1252) != 0) SetConsoleOutputCP(1252);
	printf("%ls",L"Vanguard Tamer v1.0\n\tBy Desaroll\n\n");
	printf("%ls",L"Select an option (Write the number):\n");
	printf("%ls",L"Selecciona una opción (Escribe el número):\n\n");
	printf("%ls",L"1 - Stop Vanguard\n");
	printf("%ls",L"    Cerrar Vanguard\n\n");
	printf("%ls",L"2 - Stop Vanguard from starting with Windows\n");
	printf("%ls",L"    Evitar que Vanguard se inicie con Windows\n\n");
	printf("%ls",L"3 - Setup Vanguard to start with windows\n");
	printf("%ls",L"    Configurar que Vanguard se inicie con Windows\n\n");
	int option;
	scanf("%i", &option);
	
	auto SCHandle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
	if(SCHandle == NULL) {
		printf("SCHandle error:\n\t");
		errorHandler();
		return -1;
	}
	
	auto VGCHandle = OpenServiceA(SCHandle, "vgc", SERVICE_CHANGE_CONFIG);
	if(VGCHandle == NULL) {
		printf("VGCHandle Error:\n\t");
		errorHandler();
		return -1;
	}
	
	switch(option) {
		case 1:
			SERVICE_STATUS sv_status;
			if(ControlService(VGCHandle, SERVICE_CONTROL_STOP, &sv_status) == 0) {
				printf("VGC stop Error:\n\t");
				errorHandler();
				return -1;
			}
			break;
		case 2: 
			if(ChangeServiceConfigA(VGCHandle, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == 0) {
				printf("Disable Error:\n\t");
				errorHandler();
				return -1;
			}
			break;
		case 3:
			if(ChangeServiceConfigA(VGCHandle, SERVICE_NO_CHANGE, SERVICE_AUTO_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL) == 0) {
				printf("Start Boot Error:\n\t");
				errorHandler();
				return -1;
			}
			break;		
	}
	printf("%ls",L"Done!\n");
	printf("%ls",L"¡Hecho!\n");
	getch();
	return 0;
}