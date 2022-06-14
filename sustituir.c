#include <stdio.h>
#include <stdlib.h>
#include <string.h>



/* 
    Jose Matias Gonzalez Valarezo
    15-10627
*/

/* 
    Definicion de los pares de caracteres
*/
typedef struct
{
    /* data */

    char cad1[100];
    char cad2[100];

} pair ;

/* 
    Definicion de nodos/elementos de la doble lista enlazada
*/

struct nodo
{
    /* data */
    pair data;
    struct nodo* prev;
    struct nodo* next;


};

/* 
    Funcion que se encarga crear una nueva instancia
    de un pair, a partir del argumento separador
    y una linea del archivo de palabras.txt
*/
pair createPair(char *linea, char *separador) {
    char *ptr;
    pair newPair;

    ptr = strtok(linea,separador);

    strcpy(newPair.cad1,ptr);
    ptr = strtok(NULL,separador);
    strcpy(newPair.cad2,ptr);


    return newPair;
    
}


/*
    Funcion que crea y agrega un nodo al final de la lista.
    Si head es NULL entonces la lista esta vacia y agregamos
    el nuevo nodo en head. En caso contrario debemos recorrer
    la lista hasta el ultimo nodo y agregar el nuevo nodo luego 
    de este.
 */ 
void agregarNodo(struct nodo** head, pair p) {

    
    struct  nodo* newNode = malloc(sizeof(struct nodo));
    struct nodo* temporal;
    newNode ->data = p;
    newNode -> next = NULL;

    temporal = *head;

    
    /* Si la lista esta vacia, colocamos el nuevo nodo como cabeza */ 
    if (*head == NULL) {
        newNode -> prev = NULL;
        *head = newNode;
        return;
    }

    /* 
    
        Caso contrario recorremos la lista hasta el ultimo elemento
        e insertamos al nuevo nodo como el ultimo elemento, colocando el
        prev del nuevo nodo como el ultimo nodo anterior y next como NULL.
    
    */ 

    while (temporal -> next != NULL)
    {
        temporal = temporal -> next;
    }

    temporal -> next = newNode;
    newNode -> prev = temporal;

}



int main(int argc, char const *argv[])
{
    

    /* Declaracion de variables 
        - fp file descriptor
        - textPalabras, array para alocar strings
        - copyText, array para alocar strings al leer los archivos
        a cambiar.
        - ptr, char para tomar subStrings
        - separador, string con constante valor ":"
        - N int con valor fijo, para calcular malloc de arrays
        - j variable para un ciclo for, para verificar strings.
    */
    FILE *fp;
    char *textPalabras;
    char copyText[100];
    char *ptr;
    char *separador= ":"; 
    int N = 100;
    /* Variables para manejar el input*/
    int j = 1;
    
    

    /* Inicializamos la cabeza de la lista */ 
    struct nodo *head = NULL;
    

    /* 
        Crear pares a partir del archivo palabras.txt
        la posicion 1 de argv siempre debe contener
        el primer archivo de texto que contiene los
        pares cad1:cad2
    */

    fp = fopen(argv[1],"r");

    if (fp == NULL)
    {
        printf("Error al abrir el archivo \n");
        exit(1);
    }

      /* Alocando memoria para un array de chars */ 
    
    textPalabras = (char*) malloc( sizeof(char) *N  );
    
    /* Verificando error al apartar memorio */
    
    if (textPalabras == NULL) {
        printf("Error obteniendo espacio de memoria\n");
        exit(1);
    }


    /* 
        Leemos el archivo de los pares de palabras y los
        procesamos con las funciones createPair y agregarNodo
        de manera que dentro de la lista enlazada quedan
        almacenados las keys Cad1.
    */
    while (fscanf(fp,"%s",textPalabras) != EOF)
    {
        pair par;
        
        par = createPair(textPalabras,separador);

        agregarNodo(&head, par);
   
    }

    /* Cerramos el archivo */

    fclose(fp);


    /* Abriendo txt */ 

    for(j = 2; j < argc; j++) {
        fp = fopen(argv[j], "r");
    
        /* Verificacion de error al abrir un archivo */
        if(fp == NULL ) {
            printf("Error al abrir el archivo\n");
            exit(1);
        }


        /* 
            Recorremos el archivo que contiene el texto
            a modificar, en cada lectura verificamos
            si la palabra que se esta leyendo actulmente
            se encuentra en la lista enlazada, en caso 
            positivo la reemplazamos por su respectiva
            Cad2, en caso negativo simplemente imprimimos
            la palabra.
        */
    
        while ( !feof(fp) )
        {
        
            /* 
                - subString string utilizado para almacenar signos de puntuacion.
                - dobleCheck,tripleCheck y finalCheck son strings utilizados para
                almacenar las palabras y modificarlas en distintas situaciones.
                - temporal es un apuntador a un nodo, en este caso al head de la
                lista enlazada.
                - i,k,v son ints utilizados para los ciclos for de esta seccion.
                - verificacion es un int utilizado para colocar el caracter \0 al
                final de una palabra al construirla caracter por caracter.
                - flag es un int , que como indica su nombre cumple la funcion de 
                un flag para un condicional.   
            */
            char subString[2];
            char dobleCheck[100];
            char tripleCheck[100];
            char finalCheck[100];
            struct nodo* temporal;
            int i;
            int k;
            int verificacion;
            int flag;
            int posicion;
            int v;
        
            fscanf(fp,"%s ",copyText);
            
            /* 
                Verificamos caracter por caracter para verificar si hay
                un signo de puntuacion en la palabra, en caso positivo,
                se lo quitamos a la palabra y lo guardamos para ser agregado al final.
            */
           
            for(i = 0; i < strlen(copyText); i++){
                
                ptr = NULL;
                if(copyText[i] == '.' || copyText[i] == ',' || copyText[i] == ';' ){
                   
                    subString[0] = copyText[i];
                    subString[1] = '\0';
                    
                    
                    ptr = strtok(copyText,subString);
                    
                }
            }
            /* 
                Verificamos la palabra caracter por caracter, mientras vamos
                generando substrings, si conseguimos que un substrings es 
                igual a una cadena cad1 la guardamos junto a variables de
                contexto para saber cual palabra debemos copiar/modificar antes 
                de imprimir.
            */
             for(k = 0; k < strlen(copyText); k++){
                flag = 0;
                verificacion = k + 1;
                dobleCheck[k] = copyText[k];
                dobleCheck[verificacion] = '\0';
                
                /* 
                    Verificamos primero el head
                    si conseguimos la palabra la retornamos
                    caso contrario buscamos en el siguiente
                    elemento de la lista
                */

                temporal = head;

                if (strcmp(temporal->data.cad1,dobleCheck) == 0) {
                    strcpy(tripleCheck,temporal->data.cad2);
                    flag = 1;
                }

                /* 
                    Verificacion de la lista de nodos, menos el ultimo
                */

                while(temporal->next != NULL) {
                    if (strcmp(temporal->data.cad1,dobleCheck) == 0) {
                        strcpy(tripleCheck,temporal->data.cad2);
                        flag = 1;
                    }   
                    temporal = temporal->next;
                }

                /* 
                    Verificacion del ultimo nodo
                */

                if (strcmp(temporal->data.cad1,dobleCheck) == 0) {
                    strcpy(tripleCheck,temporal->data.cad2);
                    flag = 1;
                }


                /* Si se consiguio una cadena cad1 entra en el if*/
                if(flag == 1) {
                   
                    strcpy(finalCheck,tripleCheck);
                    strcpy(tripleCheck,"");
                    posicion = k;
                }
            
            }
   
            /* 
                Verificamos primero el head
                si conseguimos la palabra la retornamos
                caso contrario buscamos en el siguiente
                elemento de la lista
            */
            
            temporal = head;

            if (strcmp(temporal->data.cad1,copyText) == 0) {
                strcpy(copyText,temporal->data.cad2);
            }
            

            /* 
                Verificacion de la lista de nodos, menos el ultimo
            */

            while(temporal->next != NULL) {
                if (strcmp(temporal->data.cad1,copyText) == 0) {
                    strcpy(copyText,temporal->data.cad2);
                }   
                temporal = temporal->next;
            }
            

            /* 
                Verificacion del ultimo nodo
            */

            if (strcmp(temporal->data.cad1,copyText) == 0) {
                strcpy(copyText,temporal->data.cad2);
            }
            

            /* 
                Si finalCheck es distinto de "" y posicion > 0
                entonces vamos a cambiar lo que obtuvimos del texto
                por la cadena guardada en finaCheck, caracter por caracter.
                Por ultimo reiniciamos posicion y finalCheck
            */
            if (posicion != 0 && strcmp(finalCheck,"") != 0 ) {
               
                
                for (v = posicion;v >= 0; v-- ) {
                    copyText[v] = finalCheck[v];
                }
                posicion = 0;
                strcpy(finalCheck,"");
                
            }
           
            /* 
                Si eliminamos un signo de puntuacion, se lo agregamos
            */
            if (ptr != NULL ) {
                
                strcat(copyText,subString);
            }
            
            printf("%s ",copyText); 
            
        }
        
        /* Si faltan archivos por procesar ... */
        if ( j + 1 < argc) {
             printf("\n--");
        }
        printf("\n");
        fclose(fp);
    }
    
 
    
    return 0;
}
