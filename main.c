#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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
    /* code */

      /* Declaracion de variables */
    FILE *fp,*ofp;
    char *text;
    char *textPalabras;
    char copyText[100];
    char *ptr;
    char *separador= ":"; 
    int N = 100;
    char ch;
   
    

    /* Inicializamos la cabeza de la lista */ 
    struct nodo *head = NULL;
    struct nodo* temp;
    int contadorNodos = 0;

    printf("Principio de archivo, %s",text);

    /* 
        Prueba de crear pares a partir del archivo palabras.txt
    */

    fp = fopen("palabras.txt","r");

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

    while (fscanf(fp,"%s",textPalabras) != EOF)
    {
        pair par;
        printf("Dentro del while antes del strtok %s \n",textPalabras);
        
        par = createPair(textPalabras,separador);

        agregarNodo(&head, par);
    
        printf("Valores del par CAD1: %s y de CAD2: %s \n",par.cad1,par.cad2);
    }

    temp = head;
    while(temp -> next != NULL ) {
        printf("Este es el par del nodo, cad1: %s y cad2:%s \n",temp -> data.cad1 , temp -> data.cad2);
        temp = temp -> next;
    }

    printf("Este es el par del ULTIMO nodo, cad1: %s y cad2:%s \n",temp -> data.cad1 , temp -> data.cad2);

    fclose(fp);

    /* 
    
    printf("Este es el textPalabra antes del strtok, %s",textPalabras);

    ptr = strtok(textPalabras,separador);

    printf("Este es el textPalabra luego del strtok, %s",textPalabras);

    */

    /* Abriendo txt */ 

    fp = fopen("Archivo1.txt", "r");
    ofp = fopen("file_replace_output.txt", "w+");
    /* Verificacion de error al abrir un archivo */
    if(fp == NULL || ofp == NULL) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

   
    while ( !feof(fp) )
    {
       
       char *ptr;
       char *verificar;
       char subString;
       int i;
        /* Alocando memoria para un array de chars */ 
        
        verificar = (char*) malloc( sizeof(char) *N  );
        
        /* Alocando memoria para un array de chars */ 
        
    
        
        /* Verificando error al apartar memorio */
        
        if (verificar == NULL) {
            printf("Error obteniendo espacio de memorio\n");
            exit(1);
        }

        fscanf(fp,"%s",copyText);
       
       /*
        printf("PTR: %s \n",ptr);
        printf("%s \n",copyText);
        */

        /* 
            Verificamos caracter por caracter para verificar si hay
            un signo de puntuacion en la palabra, en caso positivo,
            se lo quitamos a la palabra y lo guardamos para ser agregado al final.
        */
        for(i = 0; i < strlen(copyText); i++){
            printf("caracter %c \n",copyText[i]);
            if(copyText[i] == '.'){
                printf("Entro en el if");
                subString = copyText[i];
                printf("valor de subString %c",subString); 
                /* 
                ptr = strtok(copyText,subString);
                printf("Valor de PTR %c",ptr);
                */
            }
        }
      

         struct nodo* temporal;

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


       
        fprintf(ofp,"%s ",copyText);
        
      /*
        if (ptr != NULL ) {
            fprintf(ofp,"%c",ptr);
        }
       */ 
        
        
     /* 
        printf("line[%06d]:  contents: %s", contadorLinea,
        prueba);
        printf("TEXTO DE TEXT,%s",prueba);
        textLength = strlen(prueba);

        printf("TAMANO DE PRUEBA %d",textLength);

        
    */

    }
    

    rewind(ofp);

    while (1) {

        ch = fgetc(ofp);

        if (ch == EOF) {

            break;

        }

        printf("%c", ch);

    }

    /* Probando la funcion fscan */

    /* 

    while(fscanf(fp,"%s",text) !=EOF ) {
        printf("%s %d \n", text,contadorLinea);
        strcat(text,text);
        contadorLinea = contadorLinea + 1;
    }

    */

    printf("\n\n -- \n\n");

    printf("%s",text);

    fclose(fp);

    /* comparacion de strings */

    
    
    return 0;
}
