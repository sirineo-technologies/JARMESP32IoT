/*! \file JARM32.cpp
    \brief Library containing useful general functions with JARM-ESP32

    Copyright (C) 2019 Thingsbot Tecnology
    http://www.thingsbot.com.br

 * JARM-IOTM is a library for Engebot hardware use with the JARM ESP32 platform.
 * The library is designed to use serial communication.

 * Current library coverage is:
 *	 - AT command
 *	 - Sigbot - sigfox  payload transfer
 *   - Data conversion in hexadecimal

    Version:		1.0
    Design:			Thingsbot / Sirineo
    Implementation:	Wenderson Ferreira
 */
#include "JARM32.h"

/*
 * Constructor
 */
JARM32::JARM32 (){}


/* Função: inicializa JARM32
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void JARM32::begin()
{
    SERIAL_JARM.begin(BAUDRATE_SERIAL_JARM);
}


/* setLed(led, state) - set the specified LED to the specified state(ON or OFF)
 *
 * It sets the specified LED to the specified state(ON or OFF)
 */
void JARM32::setLed(uint8_t led, uint8_t state)
{
	if(state==LED_ON)
	{
		digitalWrite(led, HIGH);
	}
	if(state==LED_OFF)
	{
		digitalWrite(led, LOW);
	}
}

/* getLED(led) - gets the state of the specified LED
 *
 * It gets the state of the specified LED
 */
uint8_t	JARM32::getLed(uint8_t led)
{
	return digitalRead(led);
}


/* Função: inicializa comunicacao com módulo Sigfox
 * Parâmetros: nenhum
 * Retorno: nenhum
 */
void JARM32::initSigbot()
{
    String status_presenca_frames = "";
    volatile char output;

    /* Testa a presença do modem Sigfox */
    SERIAL_JARM.print(SIGBOT_CMD_VERIFICA_PRESENCA_MODEM);

    while (!SERIAL_JARM.available()){delay(100);}

    while(SERIAL_JARM.available())
    {
        output = (char) SERIAL_JARM.read();
        status_presenca_frames += output;
        delay(10);
    }
}

/* Função: formata frame para ser enviado via Sigfox
 *         (transforma array de bytes em uma Hex-String
 *         para usar no comando AT de envio)
 * Parâmetros: ponteiro para array de dados e tamanho do array
 * Retorno: frame formatado (String)
 */
String JARM32::formataFrameSigfox(const void* ptr_data, uint8_t len)
{
    String frame_sigfox = "";
    uint8_t* bytes = (uint8_t*) ptr_data;
    uint8_t i;

    /* Se o tamanho do frame for menor que 12, faz padding */
    if (len < SIGFOX_UPLINK_MAX_MESSAGE_SIZE)
    {
        i = SIGFOX_UPLINK_MAX_MESSAGE_SIZE;
        while (i-- > len)
        {
            frame_sigfox += "00";
        }
    }

    /* Converte bytes para Hex-String */
    for(i = len - 1; i < len; --i)
    {
        if (bytes[i] < 16) {
            frame_sigfox += "0";
        }
        frame_sigfox += String(bytes[i], HEX);
    }

    return frame_sigfox;
}


/*! Função: garante que haja ao menos 3 micro canais utilizáveis
    *  (condição para envio de frame vias Sigfox)
    \return bool
    \sa garanteMacroMicroCanais()
    */
bool JARM32::garanteMacroMicroCanais()
{
    String status_num_micro_macro_canais = "";
    String status_reset_num_micro_macro_canais = "";
    int macro_canais = 0;
    int micro_canais = 0;
    volatile char output;
    int idx_virgula = 0;
    bool status_ok = false;

    SERIAL_JARM.print(SIGBOT_CMD_NUM_MICRO_MACRO_CANAIS);

    while (!SERIAL_JARM.available()){delay(100);}

    while(SERIAL_JARM.available())
    {
        output = (char) SERIAL_JARM.read();
        status_num_micro_macro_canais += output;
        delay(10);
    }


    /* Obtem numero de micro e macro canais */
    idx_virgula = status_num_micro_macro_canais.indexOf(",");
    macro_canais = status_num_micro_macro_canais.charAt(idx_virgula-1) - 0x30;
    micro_canais = status_num_micro_macro_canais.charAt(idx_virgula+1) - 0x30;

    /* Verifica se é preciso fazer reset dos micro e macro canais */
    if ( (macro_canais == 0) || (micro_canais < 3) )
    {
        //digitalWrite(GPIO_LED_BUILTIN, HIGH);

        status_reset_num_micro_macro_canais = "";
        SERIAL_JARM.print(SIGBOT_CMD_RESET_MICRO_MACRO_CANAIS);

        while (!SERIAL_JARM.available()){delay(100);}

        while(SERIAL_JARM.available())
        {
            output = (char) SERIAL_JARM.read();
            status_reset_num_micro_macro_canais += output;
            delay(10);
        }

        //digitalWrite(GPIO_LED_BUILTIN, LOW);

        status_ok = true;
    }else{
        status_ok = true;
    }
    return status_ok;
}

TSigfox JARM32::newSigfox()
{
    TSigfox dados_sigfox;

    /* Empacota aceleração em pacote de 12 bytes e envia para Sigfox */
    memset(&dados_sigfox, 0, sizeof(TSigfox));

    return dados_sigfox;
}

/* Funcao: formata frame e o envia para Sigfox Cloud
 * Parâmetros: ponteiro para array de dados e tamanho do array.
  * Retorno: nenhum
 */
void JARM32::sendSigfox(const void* ptr_data, uint8_t len)
{
    String frame_sigfox = "";
    String status_envio_de_frame = "";
    volatile char output;

    /* Formata o frame para ser enviado */
    frame_sigfox = formataFrameSigfox(ptr_data, len);

    /* Garante número de macro e micro canais necessários */
    bool status_canais = garanteMacroMicroCanais();

    if(status_canais == true){

        /* Faz o envio do frame */
        status_envio_de_frame = "";
        SERIAL_JARM.print(SIGBOT_CMD_ENVIO_DE_FRAME);
        SERIAL_JARM.print(frame_sigfox);
        SERIAL_JARM.print("\r");

        while (!SERIAL_JARM.available()){delay(100);}

        status_envio_de_frame = "";
        while(SERIAL_JARM.available())
        {
            output = (char) SERIAL_JARM.read();
            status_envio_de_frame += output;
            delay(10);
        }
    }
}

/*! Funcao: Envia comando AT para Sigbot
* Parâmetros: comando AT
* Retorno: nenhum
*/
void JARM32::sendATSigbot(String command, String *dataOut)
{
    String retorno_comando = "";
    volatile char output;

	unsigned int startTime = millis();
	volatile unsigned int currentTime = millis();

    String at_command = "";
	at_command.concat(command);
	at_command.concat("\r");

    /* Excuta o comando AT na Sigbot */
    SERIAL_JARM.print(at_command);

    do
	{
		currentTime = millis();
		if (SERIAL_JARM.available() > 0)
		{
            output = (char) SERIAL_JARM.read();
            retorno_comando += output;
            delay(10);
		}

	} while(((currentTime - startTime) < ATCOMMAND_TIMEOUT) && retorno_comando.endsWith(SIGBOT_ATOK) == false);

    if (retorno_comando.length() != 0) {
		*dataOut = retorno_comando;
	}
}


/*! Funcao: Obtem tensao da Sigbot
* Parâmetros: nenhum
* Retorno: String voltage
*/
String JARM32::getVoltageSigbot()
{
   String tensao_sigbot = "";
   String tensao_lida = "";
   volatile char output;

    /* Obtem a tensao do modulo Sigbot */
    SERIAL_JARM.print(SIGBOT_CMD_TENSAO);

    while (!SERIAL_JARM.available()){delay(100);}

    while(SERIAL_JARM.available())
    {
        output = (char) SERIAL_JARM.read();
        tensao_lida += output;
        delay(10);
    }

     if(tensao_lida != ""){
        tensao_sigbot = tensao_lida.substring(0,4);
    }

    return tensao_sigbot;
}