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
	char confirmacion;
	system("cls");
	printf("Ingrese el valor a depositar: ");
	if (scanf("%f", &dep) == 1 && dep > 0) {
		printf("¿Está seguro que desea depositar %.2f? (S/N): ", dep);
		limpiarBuffer();
		scanf("%c", &confirmacion);
		if (confirmacion == 'S' || confirmacion == 's') {
			saldo += dep;
			printf("El valor %.2f se ha acreditado exitosamente a su cuenta.\n", dep);
			printf("Nuevo saldo: %.2f\n", saldo);
			
			char transaccion[256];
			sprintf(transaccion, "Depósito realizado: %.2f. Nuevo saldo: %.2f.", dep, saldo);
			registrarTransaccion(transaccion);
			guardarDatos();
		} else {
			printf("Depósito cancelado. No se realizaron los cambios en su cuenta.\n");
		}
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
			printf("Establecimiento: POLImon\n");
			printf("Ingrese el monto a pagar: ");
			if (scanf("%f", &monto) == 1 && monto > 0) {
				if (monto <= saldo) {
					saldo -= monto;
					printf("El pago que se ha hecho por: %.2f se realizo con éxito.\n", monto);
					printf("Nuevo saldo que posee: %.2f\n", saldo);
					
					char transaccion[256];
					sprintf(transaccion, "Pago al establecimiento POLIBURGUERS: %.2f. El nuevo saldo es: %.2f.", monto, saldo);
					registrarTransaccion(transaccion);
					guardarDatos();  // Guardar los cambios en el archivo
				} else {
					printf("Saldo insuficiente para realizar el pago.\n");
				}
			} else {
				printf("Monto inválido. Intente nuevamente.\n");
				printf("Monto inválido. Intente nuevamente.\n");
				printf("Monto inválido. Intente nuevamente.\n");
				printf("Monto no válido. Intentelo de nuevo.\n");
				limpiarBuffer();
			}
		} else {
			printf("Establecimiento NO REGISTRADO.\n");
		}
	} else {
		printf("ID no válido. Intente nuevamente.\n");
		printf("ID no válido. Intente nuevamente.\n");
		printf("ID no válido. Intente nuevamente.\n");
		printf("ID no válido. Intentelo de nuevo.\n");
		limpiarBuffer();
	}
}
void mostrarmenu() {
	printf("\n==== Aplicación Bancaria ====\n");
	printf("1. Consultar saldo\n");
	printf("2. Hacer depósito\n");
	printf("3. Retirar dinero\n");
	printf("4. Pago a establecimientos\n");
	printf("5. Mostrar historial de transacciones\n");
	printf("6. Solicitar Certificado Bancario\n");
	printf("7. Salir\n");
	
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

// Función que valide si el correo es válido a travéz de su formato
int esCorreoValido(const char* correo) {
	int atPos = -1;
	int dotPos = -1;
	
	for (int i = 0; correo[i] != '\0'; i++) {
		if (correo[i] == '@' && atPos == -1) {
			atPos = i;
		} else if (correo[i] == '.' && atPos != -1) {
			dotPos = i;
		}
	}
	
	return (atPos != -1 && dotPos != -1 && dotPos > atPos);
}

// Función que permita ingresar un correo y simular un certificado bancario
void certificado() {
	char correo[100];
	limpiarBuffer();
	while (1) {
		printf("Ingrese su correo electrónico: ");
		fgets(correo, sizeof(correo), stdin);  
		correo[strcspn(correo, "\n")] = 0;  
		if (strlen(correo) == 0) {
			printf("No se ha ingresado ningún correo. Intente nuevamente.\n");
			continue;
		}
		if (esCorreoValido(correo)) {
			printf("Certificado bancario enviado exitosamente al correo: %s\n", correo);
			break; 
		} else {
			printf("El correo ingresado no es válido. Por favor intente nuevamente.\n");
		}
	}
}


int main() {
	int x;
	
	
	cargarDatos();
	
	printf("Ingrese su tarjeta de crédito o débito para continuar\n");
	system("pause");
	
	
	
	
	
	do {
		system("cls");
		mostrarmenu();
		
		srand(time(NULL));
		int numeroCuenta = rand();
		printf("\n===============================\n");
		printf("ID del usuario: %d\n", numeroCuenta);
		printf("===============================\n");  
		
		
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
				certificado();
				break;
			case 7:
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
	} while (x != 7);
	
	return 0;
}
