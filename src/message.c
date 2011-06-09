#include "message.h"

/* Computa o CRC8 para a menssagem (TIPO + DADOS)
 * polinômio = x^8 + x^2 + x^1 + x^0
 */
uint8_t crc8 (unsigned char *menssagem) {
    unsigned int crc; /*, i;
    unsigned char temp;

    for (i = 0; ; i++) {
        if (menssagem[i] != 0) {
            menssagem[i] = ~(menssagem[i] ^ GP);
            
            menssagem[i+1] = temp;
        }        
    }
*/    
    return (crc = 1);
}


unsigned int crc32(unsigned char *message) {
    int i, j;
    unsigned int byte, crc, mask;

    i = 0;
    crc = 0xFFFFFFFF;

    while (message[i] != 0) {
        byte = message[i]; // Get next byte.
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) { // Do eight times.
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }
    return ~crc;
}

uint8_t OWComputeCRC8( uint8_t in_data, uint8_t seed )
{
    uint8_t bits_left;
    uint8_t temp;

    for( bits_left = 8; bits_left > 0; bits_left-- ) {
        temp = ((seed ^ in_data) & 0x01);

        if( temp == 0 ) {
            seed >>= 1;
        }
        else {
            seed ^= 0x18;  // 24 - 0001 1000 
            seed >>= 1;    // deslocamento
            seed |= 0x80;  // 128 - 1000 0000
        }

        in_data >>= 1;
    }
    
    return seed;    
}
