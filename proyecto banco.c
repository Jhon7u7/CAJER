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

void registrarTransaccion(const char *descripcion) {
	if (transacciones < 100) {
		strcpy(historial[transacciones], descripcion);
		transacciones++;
	}
	archivo = fopen("registro.txt", "a");
	if (archivo != NULL) {
		fprintf(archivo, "%s\n", descripcion);
		fclose(archivo);
	}
}

void retiro() {
	float ret;
	system("cls");
	printf("Digite el monto a retirar: ");
	if (scanf("%f", &ret) == 1 && ret > 0) {
		if (ret <= saldo) {
			saldo -= ret;
			printf("El valor %.2f ha sido retirado de su cuenta exitosamente.\n", ret);
			printf("Saldo actual disponible: %.2f\n", saldo);
		
			
			char transaccion[256];
			sprintf(transaccion, "Monto retirado : %.2f. Saldo actual : %.2f.", ret, saldo);
			registrarTransaccion(transaccion);
		} else {
			printf("Monto insuficiente.\n");
			print("Verifique su saldo disponible e Intentelo de nuevo.\n");
		}
	} else {
Retiro
		printf("Monto inválido digitado. Verifique e Intente nuevamente.\n");

		printf("Monto inválido. Intente nuevamente.\n");
 CAJERO
		limpiarBuffer();
	}
}

void deposito() {
	float dep;
	char confirmacion;
	system("cls");
	printf("Ingrese el valor a depositar: ");
	if (scanf("%f", &dep) == 1 && dep > 0) {
		printf("¿Esta seguro que desea depositar %.2f?(S/N): ", dep);
		scanf("%c", &confirmacion);
		if (confirmacion == 'S' || confirmacion == 's') {
		saldo += dep;
		printf("El valor %.2f se ha acreditado exitosamente a su cuenta.\n", dep);
		printf("Nuevo saldo: %.2f\n", saldo);
		
		char transaccion[256];
		sprintf(transaccion, "Depósito realizado: %.2f. Nuevo saldo: %.2f.", dep, saldo);
		registrarTransaccion(transaccion);
	} else {
Retiro
		printf("Monto inválido. Intente nuevamente.\n");


		printf("Depósito cancelado. No se realizaron los cambios en su cuenta.\n");
		}
	} else {
		printf("Monto inválido. Intente nuevamente.(Recuerde que el valor ingresado debe ser mayor a 0)\n");

		printf("Monto inválido. Intente nuevamente.\n");
 CAJERO
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
					printf("El pago que se ha hecho por: %.2f se realizo con éxito.\n", monto);
					printf("Nuevo saldo que posee: %.2f\n", saldo);
					
					char transaccion[256];
					sprintf(transaccion, "Pago al establecimiento POLIBURGUERS: %.2f. El nuevo saldo es: %.2f.", monto, saldo);
					registrarTransaccion(transaccion);
				} else {
					printf("Saldo insuficiente para realizar el pago.\n");
				}
			} else {
<Retiro
				printf("Monto inválido. Intente nuevamente.\n");


				printf("Monto inválido. Intente nuevamente.\n");

				printf("Monto no válido. Intentelo de nuevo.\n");

CAJERO
				limpiarBuffer();
			}
		} else {
			printf("Establecimiento NO REGISTRADO.\n");
		}
	} else {
 Retiro
		printf("ID no válido. Intente nuevamente.\n");


		printf("ID no válido. Intente nuevamente.\n");

		printf("ID no válido. Intentelo de nuevo.\n");
 CAJERO
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
	
	archivo = fopen("registro.txt", "w");
	if (archivo == NULL) {
		printf("Error al crear el archivo.\n");
		return 1;
	}
	fprintf(archivo, "Inicio del registro de transacciones.\n");
	fclose(archivo);
	
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
