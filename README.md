# Proyecto: Simulacion de un cajero automatico:

En este codigo se busca recrear todo el funcionamiento de un cajero automatico. Incluye funcionalidades como consulta de saldo, retiro, deposito, pago a establecimientos e historial de transacciones.


## 1| Definicion de requerimientos iniciales:

Se identificaron diversas funcionalidades necesarias:

1.- Consulta de saldo.

2.-Depositos.

3.-Retiro.

4.- Pagos a establacimientos.

5.- Historial.


## 2| Implementacion del codigo


### Para la consulta de saldo:

Permite mostrar el fondo que tenemos en la cuenta.
____________________________________________________________________________________________

	system("cls");

	printf("Saldo disponible: %.2f\n", saldo);
				
	char consulta[256];
	sprintf(consulta, "Consulta de saldo: %.2f.", saldo);
	registrarTransaccion(consulta);
	break;

____________________________________________________________________________________________

### Para el deposito de dinero:

Perminte agregar fundos a la cuenta.

____________________________________________________________________________________________

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
	} else {
		printf("Monto inválido. Intente nuevamente.\n");
		limpiarBuffer();
	}
}

____________________________________________________________________________________________

### Para el retiro de dinero:

Gestiona los retiros de sald, verificando su disponibilidad.

____________________________________________________________________________________________
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
		} else {
			printf("Saldo insuficiente.\n");
		}
	} else {
		printf("Monto inválido. Intente nuevamente.\n");
		limpiarBuffer();
	}
}
____________________________________________________________________________________________

### Pago a establecimientos:

Realiza pagos validando la Id del establecimiento.
____________________________________________________________________________________________

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


____________________________________________________________________________________________

## Historial de trasacciones:

Muestra todas las transacciones realizadas por el usuario.
____________________________________________________________________________________________

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

____________________________________________________________________________________________


## 3| Pruebas:

Se realizaron diversas pruebas para asegurar el correcto funcionamiento del programa:

### Casos de exito:
 ° Deposito y retiro con un saldo suficiente.
 
 ° Actualizacion del saldo en tiempo real.
 
 ° Actualizacion del historial en tiempo real.

### Casos de error:
 ° No se registran las transacciones en registro.txt.
 
 ° Pago a establecimientos no registrados

 ° Intentos de retiro mayor al saldo disponible

## 4| Diagrama de flujo

	graph TD;
	    A[Inicio] --> B[Ingresar tarjeta];
	    B --> C[Generar número de cuenta];
	    C --> D[Mostrar menú];
	    D -->|1| E[Consultar saldo];
	    D -->|2| F[Hacer depósito];
	    D -->|3| G[Retirar dinero];
	    D -->|4| H[Pago a establecimientos];
	    D -->|5| I[Mostrar historial];
	    D -->|6| J[Generar certificado];
	    D -->|7| K[Salir];
	    K --> L[Fin];
