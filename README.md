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

 ° Validaciones de errores.

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
	    D -->|6| K[Salir];
	    K --> L[Fin];
## 5| Mejoras en el codigo:

Implementacion del registro de la fecha y hora en la que se realizan las operaciones bancarias.

____________________________________________________________________________________________

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
____________________________________________________________________________________________

Se agrego dos funciones, una para cargar datos y otra para guardar datos.

____________________________________________________________________________________________

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
____________________________________________________________________________________________

Se agrego la opcion de certificado bancario.

____________________________________________________________________________________________
	
	// Función que valide si el correo es válido a travéz de su formato
	int esCorreoValido(const char* correo) {
	    int atPos = -1;
	    int dotPos = -1;
	@@ -138,15 +138,15 @@ int esCorreoValido(const char* correo) {
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
	//validaciòn del correo electrònico
	        if (strlen(correo) == 0) {
	            printf("No se ha ingresado ningún correo. Intente nuevamente.\n");
	            continue;
	@@ -176,17 +176,11 @@ int main() {
		printf("Ingrese su tarjeta de crédito o débito para continuar\n");
		system("pause");
		system("cls");
		
		srand(time(NULL));
		int numeroCuenta = rand();
		printf("Número de cuenta: %d\n", numeroCuenta);
		
		char inicio[256];
		sprintf(inicio, "Número de cuenta asignado: %d.", numeroCuenta);
		registrarTransaccion(inicio);
		printf("ID del usuario: %d\n", numeroCuenta);
	
		do {
			system("cls");
			mostrarmenu();
			printf("Ingrese una opción: ");
			if (scanf("%d", &x) == 1) {

____________________________________________________________________________________________
