#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

/*MÉTODO MONTANTE*/
/*

	|	2		5 		6	|	1	|
	|	7 		8		8	|	2	|
	|	6		9		2	|	4	|


*/

//auxiliar para validacion global
char aux[50];

//funcion que valida solo numeros
int validar_entero(char *n){
	int i,longi;
	longi = strlen(n);
	for(i=0;i<longi;i++)
		if(isdigit(n[i])==0)
			return 1;
	return 0;
}

int validar_real(char* n) {
    char *ap_final;
    double valor = strtod(n, &ap_final);
    return !(*ap_final == '\0' || isspace(*ap_final) != 0);
}

int main() {

    // Declaración de variables.
    float  matrizAuxiliar[10][10], matriz[10][10];
	int pivote=0, pivoteAnterior = 1, iteracion = 0;
    float renglonAux[10];
    float respuestas[10];
    //0 -> true (como si fuera bandera)
    int status = 0;

    //Ingresa los valores de la matriz
    int ecuaciones=0, incognitas=0;

    printf("\t---------CALCULADORA DE RAICES -> M%cTODO MONTANTE----------\n",212);
    // Validación de que es una matriz cuadrada.

    do{


    	do{
    		printf("\n\tIngrese el n%cmero de ecuaciones a resolver : ",163);
    		//validacion solo ingresar numeros y no letras
    		gets(aux);
    		if(validar_entero(aux)==1){
    			printf("\n\n\t-----------ERROR DE DATO INGRESADO--------------");
			}
    	}while(validar_entero(aux)==1);
		ecuaciones=atoi(aux);

		do{
    		printf("\n\tIngrese el n%cmero de incognitas a encontar : ",163);
    		gets(aux);
    		if(validar_entero(aux)==1){
    			printf("\n\n\t-----------ERROR DE DATO INGRESADO--------------");
			}
    	}while(validar_entero(aux)==1);
    	incognitas=atoi(aux);

    	if(ecuaciones != incognitas){
    		printf("\n\n\t-----EL N%cMERO DE ECUACIONES E INC%cGNITAS NO COINCIDEN----\n\n",233,224);
		}
	//Lo va a seguir pidiendo si no cumple que la matriz sea de n*n
    }while(ecuaciones != incognitas);
    system("cls");
	//Espacio para posteriormente guardar las constantes
    incognitas++;

    // Ingreso de coeficientes y constantes.
    int columna=0,renglon=0;
    printf("\n\t            INGRESE : \n");
    for(renglon=0; renglon<ecuaciones ;renglon++){
    	printf("\n");
    	for(columna=0 ;columna<incognitas-1 ;columna++){
            do{
                printf("\n\tEl coeficiente #%i de la ecuaci%cn %i : ",columna+1,162,renglon+1);
                // validacion solo ingresas numeros, no letras
                gets(aux);
                if(validar_real(aux)==1){
                    printf("\n\n\t-----------ERROR DE DATO INGRESADO--------------");
                }
            }while(validar_real(aux)==1);
    		matriz[renglon][columna] = atof(aux);
		}
		do{
			printf("\n\tLa constante de la ecuaci%cn %i : ",162,renglon+1);
			//incognitas-1 por que aumetamos 1 para guardar el espacio
			  // validacion solo ingresas numeros, no letras
            gets(aux);
            if(validar_real(aux)==1){
                printf("\n\n\t-----------ERROR DE DATO INGRESADO--------------");
            }
		}while(validar_real(aux)==1);
		matriz[renglon][incognitas-1]=atof(aux);
	}

    int REN=ecuaciones;
    int COL=incognitas;

    // Se hace una iteracion por cada renglon de la matriz (cada ecuacion)
    //Mientras que las iteraciones sean menor al número de renglones (verticalmenete)
    while(iteracion < REN){

        	// Conseguimos el pivote
        	pivote = matriz[iteracion][iteracion];

        	// Mientras el pivote valga 0, intercambiamos renglones
        	while (pivote == 0){
                    // repetimos en cada renglón
                int renglon_intercambio;
                for(renglon_intercambio = iteracion + 1; renglon_intercambio < REN; renglon_intercambio++) {
                    // revisamos si el posible pivote es 0
                    if(matriz[renglon_intercambio][iteracion] != 0) {
                        // Itercambiamos renglones con una matriz auxiliar
                        int c=0;
                        //se mueve horizontalmente a la derecha
                        //se repite hasta terminar de cambiar ambos renglones
                        for(c = 0; c < COL; c++) {
                            //renglon[0] = matriz[1][0]
                            renglonAux[c] = matriz[renglon_intercambio][c];					//	[0][0]=	0		[0][1]=	9	|	[0][2]=	6
                            //matriz[1][0]= matriz[0][0]								//	[1][0]=	3		[1][1]=	6	|	[1][2]=	4
                            matriz[renglon_intercambio][c] = matriz[iteracion][c];
                            //matriz[0][0] = renglonAux[0]
                         matriz[iteracion][c] = renglonAux[c];
                        }
                        break;
                    }

                }

            	// Volvemos a sacar pivote para verificar si es diferete de 0
            	//si es diferente de 0 se salta el if de abajo
            	//si llega al if de bajo es por que toda la columna es de 0´s
            	pivote = matriz[iteracion][iteracion];
            	// Si no se encuentra un pivote diferente a 0, solución única no tiene.
            	if(pivote == 0){
                	// Aquí checamos si no tiene solución o tiene un número infinito de soluciones.
                	int i=0;
                	for(i = 0; i < ecuaciones; i++){
                    	float resp;
                        //CASO 2
                    	if (matriz[i][i] == 0){																	//CASO 1
						//CASO 1																//		[0][0]=0	[0][1]=	3	|	[0][2]=	2
                        	int columna_revisar, bandera_diferente_cero = 0;					//		[1][0]=0	[1][1]=	0	|	[1][2]=	6     NO TIENE SOLUCION
                        	// revisar hay puros ceros a la derecha
                        	for(columna_revisar = iteracion + 1; columna_revisar < COL - 1; columna_revisar++) {
                                if (matriz[i][columna_revisar] != 0){
                                    bandera_diferente_cero = 1;
                                    break;
                                }
                        	}
                        	// si fueron puros ceros y la respuesta es 1, entonces no tiene solución
                        	if (!bandera_diferente_cero && matriz[i][COL] == 0)
                                bandera_diferente_cero = 1;
                            // si fueron puros ceros en los coeficientes, tiene infinitas soluciones
                        	if (bandera_diferente_cero){
                                break;
                        	}
                        	printf("\n\t-----------NO TIENE SOLUCI%cN-----------\n",224);
                        	return 0;
                    	}																						//CASO 2
                    	//ultimo paso #resultante/pivote										//		[0][0]=3	[0][1]=	0	|	[0][2]=	2
                    	resp = matriz[i][COL-1] * 1.0 / matriz[i][i];							//		[1][0]=0	[1][1]=	4	|	[1][2]=	6	respuestas[0]= 2/3
                    	respuestas[i] = resp;
                	}
                	//CASO 3
                	printf("\n\t--------------HAY INFINITAS SOLUCIONES----------\n");
                	status = 1;																				//CASO 3  DEPENDEN DE OTRAS
                	return 0;																		//		[0][0]=0	[0][1]=3	[0][2]=7	|	[0][2]=	2
            	}																					//		[1][0]=0	[1][1]=2	[1][2]=9	|	[1][2]=	6  SOLUCIONES INFINITAS
        	}																						//		[2][0]=0	[2][1]=	4	[2}[8]=7 	|	[1][2]=	8

        	system("cls");
       		printf("\t---------SOLUCI%cN------------\n\n",224);

        	//Llega aqui cuando el pivote es diferente de 0
        	// 1 PASO.- Pasamos el renglón de la matriz a una matriz nueva.
        	int C=0;
        	for(C = 0; C < COL; C++){
            	matrizAuxiliar[iteracion][C] = matriz[iteracion][C];
        	}

        	// 2 PASP.- Ponemos 0´s en lo faltante de la columna del pivote.
        	int R=0;
        	for(R = 0; R < REN; R++){
        		//para no poner un 0 donde esta el pivote
            	if(iteracion != R){
                	matrizAuxiliar[R][iteracion] = 0;
            	}
        	}

        	// 3 PASO.- Sacar el valor de la posición según la matriz anterior.
        	//calculamos el resto de la matriz
        	printf("\n");
        	int iR=0,N=0;
        	for(iR = 0; iR < REN; iR++){
            	for(N = 0; N < COL; N++){
            		//is´s anidados para no calcular el valor donde esten los pivotes
                	if(iR != iteracion) {
                    	if( N != iteracion){
                        	matrizAuxiliar[iR][N] = (((matriz[iR][N] * pivote) - (matriz[iteracion][N] * matriz[iR][iteracion])) / (pivoteAnterior));
                    	}
                	}
                	//imprime la matriz del ultimo paso
                	printf("\t%.2f",matrizAuxiliar[iR][N]);
            	}
            	 printf("\n");
        	}

        	iteracion++;
        	pivoteAnterior = pivote;

        	// Actualizamos la matriz copiando la auxiliar.
        	int M=0,A=0;
        	for(M= 0; M < REN; M++){
            	for(A= 0; A < COL; A++)
                	matriz[M][A] = matrizAuxiliar[M][A];
        	}
    }
 // si tiene soluciones , las imprime
  if(status==0){
        printf("\n\n\t-----SOLUCIONES %cNICAS-------\n\n",233);
        int p;
        for(p= 0; p < ecuaciones; p++){
            float resp=0;
            resp = matriz[p][COL-1] * 1.0 / matriz[p][p];
            printf("\tx_%d = %.2f" , p + 1, resp);
        }
    }

    return 0;
}



