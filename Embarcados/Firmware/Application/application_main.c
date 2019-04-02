/*
 * application_main.c
 *
 *  Created on: 2 de abr de 2019
 *      Author: Andre
 */
#include "application_main.h"
#include "stdint.h"
#include "lib_utilities.h"
#include "fsm_avi_rede.h"

#define NUMERO_DADOS_VETOR 8

volatile uint8_t run = TRUE;

const uint8_t serialData[] = {0xAA,0x01,0x00,0x01,0x55,0x00,0x35,0x55};

volatile uint8_t modeloDecodificado = 0;
volatile uint8_t idDecodificado = 0;
volatile uint8_t nDadosDecodificados = 0;
volatile uint8_t dadosDecodificados[255];

void app_run(void)
{
    while(1){
    	if(run == TRUE){
    		run = FALSE;
    		uint8_t i = 0;
    		for(i=0;i<NUMERO_DADOS_VETOR;i++){
                exec_decodificador_avirede(serialData[i]);
                if(frame_decodificado() == TRUE){
                	modeloDecodificado = recebe_modelo_frame();
                	idDecodificado = recebe_id_frame();
                	nDadosDecodificados = recebe_dados_frame((uint8_t *)dadosDecodificados);
                }
    		}
    	}
    }
}

uint8_t requisicao_led(uint8_t prioridade,uint32_t atrasoAntes, uint32_t atrasoDepois, uint32_t tempo_ligado, uint32_t tempo_desligado, uint8_t ciclos)
{

}
