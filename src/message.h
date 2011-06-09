#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdint.h>

#define MARCA 126
#define TAM_MAX_MESS 32
#define GP  0x107   /* x^8 + x^2 + x + 1 */

/* Defines para o tipo da mensagem */
typedef enum {
    /* Mensagens linha de comando */
    MSG_C = 0,  // cd
    MSG_L,      // ls
    MSG_P,      // put
    MSG_G,      // get
    /* Menssagem Ack e Nack */
    MSG_Y,      // ack
    MSG_N,      // nack
    /* Menssagens de erro*/
    MSG_E1,     // Diretório Inexistente
    MSG_E2,     // Sem Acesso
    MSG_E3,     // Espaço Insuficiente
    MSG_E4,     // Arquivo Inexistente
    /* Informações do Processo */
    MSG_Z,      // Fim de TX
    MSG_I,      // Informação de Troca
    MSG_D,      // Número de Bytes
    MSG_X       // Mostra na Tela 
} TipoDeMenssagem;

/* Bit field para os campos tamnho e sequencia */
typedef struct {
    unsigned char tamanho : 5;
    unsigned char sequencia : 3;
} bitfield;

/* Estrura da Menssagem de Envio */
typedef struct {
    uint8_t marca;
    bitfield tam_seq;
    uint8_t tipo;
    unsigned char *dados;
    uint8_t crc8;
} msg;

#endif /* Final de MESSAGE_H */
