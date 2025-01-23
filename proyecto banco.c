#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

float saldo = 1000;
char historial[100][256];
int transacciones = 0;
FILE *archivo;

void limpiarBuffer() {
	while (getchar() != '\n');
}

// Función para leer el saldo y las transacciones guardadas
void cargarDatos() {
	archivo = fopen("registro.txt", "r+");
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo de registro.\n");
		return;
	}
	
	// Leer saldo
	fscanf(archivo, "Saldo inicial: %f\n", &saldo);
	
	// Leer historial de transacciones
	while (fgets(historial[transacciones], sizeof(historial[transacciones]), archivo) != NULL) {
		transacciones++;
	}
	
	fclose(archivo);
}

// Función para guardar el saldo y las transacciones
void guardarDatos() {
	archivo = fopen("registro.txt", "w");
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo de registro.\n");
		return;
	}
	
	// Guardar saldo
	fprintf(archivo, "Saldo inicial: %.2f\n", saldo);
	
	// Guardar historial de transacciones
	for (int i = 0; i < transacciones; i++) {
		fprintf(archivo, "%s", historial[i]);
	}
	
	fclose(archivo);
}

// Registrar transacción con fecha y hora
void registrarTransaccion(const char *descripcion) {
	if (transacciones < 100) {
		// Obtener la fecha y hora actual
		time_t now;
		struct tm *tm_info;
		char fechaHora[26];
		
		time(&now);  // Obtiene la hora actual
		tm_info = localtime(&now);  // Convierte la hora en formato local
		strftime(fechaHora, sizeof(fechaHora), "%Y-%m-%d %H:%M:%S", tm_info);  // Formatea la fecha y hora
		
		// Formato de la transacción con la fecha y hora
		char transaccionConFecha[300];
		snprintf(transaccionConFecha, sizeof(transaccionConFecha), "[%s] %s", fechaHora, descripcion);
		
		// Guardar en el array de historial
		strcpy(historial[transacciones], transaccionConFecha);
		transacciones++;
	}
	
	// Registrar en el archivo de texto
	archivo = fopen("registro.txt", "a");
	if (archivo != NULL) {
		fprintf(archivo, "%s\n", descripcion);
		fclose(archivo);
	}
}

void retiro() {
	float ret;
	system("cls");
	printf("Ingrese el valor a retirar: ");
	if (scanf("%f", &ret) == 1 && ret > 0) {
		if (ret <= saldo) {
			saldo -= ret;
			printf("El valor %.2f se ha retirado de su cuenta exitosamente.\n", ret);
			printf("Nuevo saldo: %.2f\n", saldo);
			
			char transaccion[256];
			sprintf(transaccion, "Retiro realizado: %.2f. Nuevo saldo: %.2f.", ret, saldo);
			registrarTransaccion(transaccion);
			guardarDatos();  // Guardar los cambios en el archivo
		} else {
			printf("Saldo insuficiente.\n");
		}
	} else {
		printf("Monto inválido. Intente nuevamente.\n");
		limpiarBuffer();
	}
}

void deposito() {
	float dep;
	system("cls");
	printf("Ingrese el valor a depositar: ");
	if (scanf("%f", &dep) == 1 && dep > 0) {
		saldo += dep;
		printf("El valor %.2f se ha acreditado exitosamente a su cuenta.\n", dep);
		printf("Nuevo saldo: %.2f\n", saldo);
		
		char transaccion[256];
		sprintf(transaccion, "Depósito realizado: %.2f. Nuevo saldo: %.2f.", dep, saldo);
		registrarTransaccion(transaccion);
		guardarDatos();  // Guardar los cambios en el archivo
	} else {
		printf("Monto inválido. Intente nuevamente.\n");
		limpiarBuffer();
	}
}

void establecimiento() {
	float monto;
	int id;
	system("cls");
	printf("Ingrese el ID del establecimiento: ");
	if (scanf("%d", &id) == 1) {
		if (id == 172350) {
			printf("Establecimiento: POLIBURGUERS\n");
			printf("Ingrese el monto a pagar: ");
			if (scanf("%f", &monto) == 1 && monto > 0) {
				if (monto <= saldo) {
					saldo -= monto;
					printf("PAGO POR: %.2f EXITOSO.\n", monto);
					printf("Nuevo saldo: %.2f\n", saldo);
					
					char transaccion[256];
					sprintf(transaccion, "Pago a POLIBURGUERS: %.2f. Nuevo saldo: %.2f.", monto, saldo);
					registrarTransaccion(transaccion);
					guardarDatos();  // Guardar los cambios en el archivo
				} else {
					printf("Saldo insuficiente para realizar el pago.\n");
				}
			} else {
				printf("Monto inválido. Intente nuevamente.\n");
				limpiarBuffer();
			}
		} else {
			printf("Establecimiento NO REGISTRADO.\n");
		}
	} else {
		printf("ID no válido. Intente nuevamente.\n");
		limpiarBuffer();
	}
}

void mostrarHistorial() {
	system("cls");
	printf("==== Historial de Transacciones ====\n");
	if (transacciones == 0) {
		printf("No hay transacciones registradas.\n");
	} else {
		for (int i = 0; i < transacciones; i++) {
			printf("%d. %s\n", i + 1, historial[i]);
		}
	}
	printf("====================================\n");
}

void mostrarmenu() {
	printf("\n==== Aplicación Bancaria ====\n");
	printf("1. Consultar saldo\n");
	printf("2. Hacer depósito\n");
	printf("3. Retirar dinero\n");
	printf("4. Pago a establecimientos\n");
	printf("5. Mostrar historial de transacciones\n");
	printf("6. Salir\n");
	printf("=============================\n");
}

int main() {
	int x;
	
	// Cargar datos desde el archivo al iniciar
	cargarDatos();
	
	system("cls");
	printf("Ingrese su tarjeta de crédito o débito para continuar\n");
	system("pause");
	system("cls");
	
	srand(time(NULL));
	int numeroCuenta = rand();
	printf("Número de cuenta: %d\n", numeroCuenta);
	
	char inicio[256];
	sprintf(inicio, "Número de cuenta asignado: %d.", numeroCuenta);
	registrarTransaccion(inicio);
	
	do {
		system("cls");
		mostrarmenu();
		printf("Ingrese una opción: ");
		if (scanf("%d", &x) == 1) {
			switch (x) {
			case 1:
				system("cls");
				printf("Saldo disponible: %.2f\n", saldo);
				
				char consulta[256];
				sprintf(consulta, "Consulta de saldo: %.2f.", saldo);
				registrarTransaccion(consulta);
				guardarDatos();  // Guardar los cambios en el archivo
				break;
			case 2:
				deposito();
				break;
			case 3:
				retiro();
				break;
			case 4:
				establecimiento();
				break;
			case 5:
				mostrarHistorial();
				break;
			case 6:
				system("cls");
				registrarTransaccion("Cierre del programa.");
				guardarDatos();  // Guardar los cambios en el archivo
				printf("Saliendo del sistema... Que tenga un excelente día :)\n");
				break;
			default:
				system("cls");
				printf("Opción no válida. Intente nuevamente.\n");
				break;
			}
		} else {
			system("cls");
			printf("Entrada no válida. Intente nuevamente.\n");
			limpiarBuffer();
		}
		system("pause");
	} while (x != 6);
	
	return 0;
}
