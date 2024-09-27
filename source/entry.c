#include <stdio.h>
#include "block.h"
#include "entry.h"

/* Função que cria uma entry, reservando a memória necessária e
* inicializando-a com a string e o bloco de dados de entrada.
* Retorna a nova entry ou NULL em caso de erro.
*/
struct entry_t *entry_create(char *key, struct block_t *value){
    if(!key || !value){
        return NULL;
    }

    struct entry_t *entry = malloc(sizeof(struct entry_t));
    if(!entry){
        return NULL;
    }

    entry->key = key;
    entry->value = value;
    return entry;
}

/* Função que compara duas entries e retorna a ordem das mesmas, sendo esta
* ordem definida pela ordem das suas chaves.
* Retorna 0 se as chaves forem iguais, -1 se e1 < e2,
* 1 se e1 > e2 ou -2 em caso de erro.
*/
int entry_compare(struct entry_t *e1, struct entry_t *e2){
    if(!e1 || !e2 || !e1->key || !e2->key){
        return -2;
    }

    return (strcmp(e1->key, e2->key) == 0) ? 0 : (strcmp(e1->key, e2->key) > 0) ? 1 : -1;
}

/* Função que duplica uma entry, reservando a memória necessária para a
* nova estrutura.
* Retorna a nova entry ou NULL em caso de erro.
*/
struct entry_t *entry_duplicate(struct entry_t *e){
    if(!e || !e->key || !e->value){
        return NULL;
    }

    struct entry_t *entry_dup = malloc(sizeof(struct entry_t));
    if(!entry_dup){
        return NULL;
    }

    entry_dup->key = strdup(e->key);
    entry_dup->value = block_duplicate(e->value);
    if(!entry_dup->key || !entry_dup->value){
        free(entry_dup->key);
        block_destroy(entry_dup->value);
        return NULL;
    }

    return entry_dup;
}

/* Função que substitui o conteúdo de uma entry, usando a nova chave e
* o novo valor passados como argumentos, e eliminando a memória ocupada
* pelos conteúdos antigos da mesma.
* Retorna 0 (OK) ou -1 em caso de erro.
*/
int entry_replace(struct entry_t *e, char *new_key, struct block_t *new_value){
    if(!e || !e->key || !e->value || !new_key || !new_value){
        return -1;
    }

    free(e->key);
    e->key = new_key;

    block_destroy(e->value);
    e->value = new_value;

    return 0;
}

/* Função que elimina uma entry, libertando a memória por ela ocupada.
* Retorna 0 (OK) ou -1 em caso de erro.
*/
int entry_destroy(struct entry_t *e){
    if(!e){
        return -1;
    }
    if(e->key){
        free(e->key);
        e->key = NULL;
    }
    if(e->value){
        block_destroy(e->value);    
    }
    free(e);
    e = NULL;
    return 0;
}