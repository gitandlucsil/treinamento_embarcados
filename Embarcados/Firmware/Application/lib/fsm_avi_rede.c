#include "fsm_avi_rede.h"
#include "stdint.h"

#define AGUARDA_INICIO_DE_FRAME          0
#define AGUARDA_MODELO                   1
#define AGUARDA_ID                       2
#define AGUARDA_NUMERO_DE_DADOS          3
#define AGUARDA_DADOS                    4
#define AGUARDA_CHECKSUM_1               5
#define AGUARDA_CHECKSUM_2               6
#define AGUARDA_FIM_DE_FRAME             7


uint8_t estado = AGUARDA_INICIO_DE_FRAME;

uint8_t modelo = 0;
uint8_t id = 0;
uint8_t nDados = 0;
uint8_t dados[255];
uint8_t cks1 = 0;
uint8_t cks2 = 0;

uint8_t dataCount = 0;

uint8_t frameDecodificado = 0;

uint8_t recebe_modelo_frame(void)
{
    return modelo;
}

uint8_t recebe_id_frame(void)
{
    return id;
}

uint8_t recebe_dados_frame(uint8_t *pDados)
{
	uint8_t i = 0;
	for(i=0;i<nDados;i++){
		pDados[i] = dados[i];
	}
    return nDados;
}

uint8_t frame_decodificado(void)
{
    return frameDecodificado;
}

void exec_decodificador_avirede(uint8_t dado)
{
    
    switch(estado){
        case AGUARDA_INICIO_DE_FRAME:
            if(dado == 0xAA){
                frameDecodificado = 0;
                estado = AGUARDA_MODELO;
            }else{
                frameDecodificado = 0;
            }
            break;
            
        case AGUARDA_MODELO:
            modelo = dado;
            estado = AGUARDA_ID;
            break;
            
        case AGUARDA_ID:
            id = dado;
            estado = AGUARDA_NUMERO_DE_DADOS;
            break;
            
        case AGUARDA_NUMERO_DE_DADOS:
            nDados = dado;
            dataCount = 0;
            estado = AGUARDA_DADOS;
            break;
            
        case AGUARDA_DADOS:
            dados[dataCount] = dado;
            dataCount += 1;
            if(dataCount >= nDados){
                estado = AGUARDA_CHECKSUM_1;
            }
            break;
            
        case AGUARDA_CHECKSUM_1:
            cks1 = dado;
            estado = AGUARDA_CHECKSUM_2;
            break;
            
        case AGUARDA_CHECKSUM_2:
            cks2 = dado;
            estado = AGUARDA_FIM_DE_FRAME;
            break;
        
        case AGUARDA_FIM_DE_FRAME:
            if(dado == 0x55){
                uint16_t checksumRecebido = 0;
                checksumRecebido = cks1;
                checksumRecebido <<= 8;
                checksumRecebido |= cks2;
                
                uint16_t checksumCalculado = 0;
                uint8_t i;
                for(i=0; i<nDados; i++){
                    checksumCalculado += dados[i];
                }
                if(checksumCalculado == checksumRecebido){
                    frameDecodificado = 1;
                    estado = AGUARDA_INICIO_DE_FRAME;
                }else{
                    estado = AGUARDA_INICIO_DE_FRAME;
                }
                
            }else{
                estado = AGUARDA_INICIO_DE_FRAME;
            }
            break;
        
        default:
            estado = AGUARDA_INICIO_DE_FRAME;
    }
}
