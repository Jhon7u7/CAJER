# Proyecto: Simulacion de un cajero automatico:

En este codigo se busca recrear todo el funcionamiento de un cajero automatico. Incluye funcionalidades como consulta de saldo, retiro, deposito, pago a establecimientos e historial de transacciones.

## Definicion de requerimientos:

Se identificaron diversas funcionalidades necesarias:

1.- Consulta de saldo

2.-Depositos en establecimientos

3.- Generar cetificados bancarios

4.- Pagos a establacimientos

## Implementacion del codigo

### Para la consulta de saldo:

____________________________________________________________________________________________

				system("cls");

				printf("Saldo disponible: %.2f\n", saldo);
				
				char consulta[256];
				sprintf(consulta, "Consulta de saldo: %.2f.", saldo);
				registrarTransaccion(consulta);
				break;

____________________________________________________________________________________________


### Para el retiro de dinero:

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
En el codigo implementamos las funciones 

##$
### Para deposito de dinero:

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
## Pago a establecimientos:

____________________________________________________________________________________________
