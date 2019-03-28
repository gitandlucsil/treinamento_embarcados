
#define FALSO 0
#define VERDADEIRO 1

#define AGUARDA_INICIO_DE_FRAME 0
#define AGUARDA_MODELO          1
#define AGUARDA_ID              2
#define AGUARDA_NUMERO_DE_DADOS 3
#define AGUARDA_DADOS           4
#define AGUARDA_CHECKSUM_1      5
#define AGUARDA_CHECKSUM_2      6
#define AGUARDA_FIM_DE_FRAME    7

uint8_t estado = AGUARDA_INICIO_DE_FRAME;
uint8_t modelo = 0;
uint8_t id = 0;
uint8_t numero_dados = 0;
uint8_t dados[255] = 0;
uint8_t ctDados = 0;
uint8_t cks1 = 0;
uint8_t cks2 = 0;
uint8_t frameDecodificado = FALSO;

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
	pDados = dados;
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
			if(dado = 0xAA){
				estado = AGUARDA_MODELO;
				frameDecodificado = FALSO;
			}else{
				frameDecodificado = FALSO;
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
				numero_dados = dado;
				ctDados = 0;
				estado = AGUARDA_DADOS;
			break;
		case AGUARDA_DADOS:
				dados[ctDados] = dado;
				ctDados++;
				if(ctDados >= numero_dados){
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
			if(dado = 0x55){
				uint16_t checksumRecebido = 0;
				checksumRecebido = cks1 << 8 | cks2;
				uint16_t checksumCalculado = 0;
				uint8_t i  = 0;
				for(i=0;i<numero_dados;i++){
					checksumCalculado += dados[i];
				}
				if(checksumCalculado == checksumRecebido){
					frameDecodificado = VERDADEIRO;
					estado = AGUARDA_INICIO_DE_FRAME;		
				} else{
					estado = AGUARDA_INICIO_DE_FRAME;
				}

			}else{
				estado = AGUARDA_INICIO_DE_FRAME;
			}
			break;
		default:
				estado = AGUARDA_INICIO_DE_FRAME;
			break;
	}
}

