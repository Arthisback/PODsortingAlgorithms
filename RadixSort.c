#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // usei para pegar o limite de uma variavel int para usar no numero aleatorio
#include <time.h>
    
    typedef struct tlist {
        int valor;
        struct tlist* next;
    } tlist;
    typedef struct lista
    {
        tlist *head;
        tlist *tail;
    }list;
    
    typedef struct tqueue {
        int valor;
        struct tqueue* next;
    } tqueue;
    typedef struct fila
    {
        tqueue *head;
        tqueue *tail;
    }queue;

     void startList(list *l){
        l->head= NULL;
        l->tail=NULL;
     }
     void startQueue(queue *q){
        q->head= NULL;
        q->tail=NULL;
     }
     void createList(list *l, int valor){ // funcao usada para criar uma lista
        tlist *new = (tlist*)malloc(sizeof(tlist));
        new->valor = valor;
        new->next = NULL;

        if(l->head == NULL){
           l->head = new;
           l->tail = new;
        } 
        else
        l->tail->next= new;
        l->tail = new;
    }
    void createQueue(queue *q, int valor){ //funcao usada para criar uma fila
        tqueue *new = (tqueue*)malloc(sizeof(tqueue));
        new->valor = valor;
        new->next = NULL;

        if(q->head == NULL){
           q->head = new;
           q->tail = new;
        } 
        else
        q->tail->next= new;
        q->tail = new;
    }
    void printList(list *l){ // funcao usada para printar todos os elementos de uma lista
        tlist *aux = l->head;
        while (aux!=NULL)
        {
            printf("%d \n",aux->valor);
            aux=aux->next;
        }
        printf(" \n");
    }
    void printQueue(queue *q){ // funcao usada para mostrar uma fila
        tqueue *aux = q->head;
        while (aux!=NULL)
        {
            printf("%d \n",aux->valor);
            aux=aux->next;
        }
        printf("\n");
    }
    void listToArray(list *l, tlist *arr, int size){ // funcao usada para transformar uma lista em um array para poder ser ordenado
         tlist* aux = l->head;
         for(int i=0;i<size;i++){
            arr[i]=*aux;
            aux= aux->next;
         }
    }
    void swap(tlist *a, tlist *b){ // funcao usada para trocar a posicao entre dois elementos dentro de um array
        tlist aux;
        aux=*a;
        *a=*b;
        *b=aux;
    }
    int getMax(tlist* arr, int arrsize){
        int maxDigit= arr[0].valor;
        for (int i=0;i<arrsize;i++){
            if (arr[i].valor>maxDigit){
                maxDigit=arr[i].valor;
            }
        }
        return maxDigit;

    }
    void countingSort(tlist* arr, int arrsize, int pos){
        tlist *aux =(tlist*)malloc(arrsize * sizeof(tlist)); // array auxiliar com o tamanho do array principal
        int i;
        int count[10]= {0}; // declarando o countador de 10 posições e inicializando ele com 0
        for (i=0;i<arrsize;i++){
            count[(arr[i].valor/pos) % 10]++;
        }
        for (i=1;i<10; i++){
            count[i]=count[i]+count[i-1];
        }
        for (i=arrsize-1;i>=0;i--){
            aux[count[(arr[i].valor/pos)%10]-1]= arr[i];
            count[(arr[i].valor/pos)%10]--;
        }
        for (i=0;i<arrsize;i++){
            arr[i]=aux[i];
        }
    }
    void radixSort(tlist* arr, int arrsize) { // quicksort
        int maxDigits= getMax(arr,arrsize);
        
        for (int pos=1;maxDigits/pos>0;pos*=10){
            countingSort(arr,arrsize,pos);
        }
    }
      
    int main(){
        // Declaração das variaveis, onde l é o head da lista, arr é o vetor inicial e arr2 é o vetor que sera ordenado apartir da lista e size é a variavel para calcular o tamanho de arr2
        // q é o head da lista
        list l;
        queue q;
        startList(&l);
        startQueue(&q);  
        int arrsize;
        int *arr =(int*)malloc(arrsize * sizeof(int)); // array que o usuario preenche
        tlist *arr2=(tlist*)malloc(arrsize * sizeof(tlist)); // array que vai ser ordenada depois de os elementos de arr tiverem virado uma lista
        
        int choice;
        srand(time(NULL));

        printf("Insira o tamanho desejado do array: \n");
        scanf("%d", &arrsize);
        printf("Deseja preencher o array manualmente ou colocar numeros aleatorios(0 para preencher, 1 para aleatorio) \n");
        scanf("%d",&choice);

        switch (choice)
        {
            case 0:
                for(int i=0;i<arrsize;i++){
                    printf("Digite o numero: \n");
                    scanf("%d",&arr[i]);
                    createList(&l,arr[i]); // aqui a lista é criada
        }
            break;
            
            case 1:
                printf("Criacao de um array aleatorio... \n");
                for(int i=0;i<arrsize;i++){
                    arr[i]=rand()%INT_MAX;
                    createList(&l,arr[i]); // aqui a lista é criada
            }
            break;
        
        default:
            printf("Opção invalida");

            break;
        }
        
        printf("Lista Desordenada:  \n");
        printList(&l);
        
        listToArray(&l, arr2, arrsize); // aqui o array que sera ordenado apartir da lista é criado
        
        printf("Lista Ordenada pelo RadixSort:  \n");
        radixSort(arr2,arrsize); // aqui acontece a ordenação

        for(int i=0;i<arrsize;i++){
            createQueue(&q,arr2[i].valor);
        }
        printQueue(&q);
    }
    