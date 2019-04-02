#ifndef FSM_AVI_REDE_DEFINED_H
#define FSM_AVI_REDE_DEFINED_H

#include "stdint.h"

uint8_t recebe_modelo_frame(void);
uint8_t recebe_id_frame(void);
uint8_t recebe_dados_frame(uint8_t *pDados);
uint8_t frame_decodificado(void);
void exec_decodificador_avirede(uint8_t dado);

#endif
