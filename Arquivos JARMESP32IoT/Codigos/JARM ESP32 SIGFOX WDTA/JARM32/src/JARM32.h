/*! \file JARM32.h
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

/*************************************************************************/
/*                                                                       */
/*                         JARM-ESP32 2019                               */
/*                                                                       */
/*                       Thingsbot Technology                            */
/*                                                                       */
/*                     Firmware for the JARM-IOTM                        */
/*  Developed by:       Wenderson Machado Ferreira                       */
/*                                                                       */
/*              JARM-ESP32 Firmware, Brasilia, Brasil                    */
/*                                                                       */
/*            JARM32.h       Version 1.0,   25.07.2019                   */
/*                                                                       */
/*************************************************************************/


/**************************************************************/
/*************          Specifications      *******************/
/**************************************************************/

/*! \def JARM32_H
    \brief The library flag

 */
#ifndef JARM32_H
#define JARM32_H

/******************************************************************************
 * Includes
 *****************************************************************************/


#if (ARDUINO >= 100)
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#include "Sigbot.h"

/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! DEBUG_JARM-ESP32
/*! Possible values:
 * 	0: No debug mode enabled
 * 	1: debug mode enabled for error output messages
 * 	2: debug mode enabled for both error and ok messages
 */
#define SERIAL_JARM Serial
#define GPIO_ANALOG_PIN_3 32

#define BAUDRATE_SERIAL_JARM 9600

 /*! \def LED_ON
    \brief sets LED ON
 */
/*! \def LED_OFF
    \brief sets LED OFF
 */
#define	LED_ON	1
#define	LED_OFF	0

/* Definições de temporização */
#define TEMPO_BUILTIN_ON_OFF  250   //ms


/*! @enum ModuleTypes
 * Module types
 */
enum ModuleTypes
{
	ZIGBOT  = 1, 	   // ZIGBOT - ZIGBEE 3.0
	SIGBOT = 2, 	   // SIGBOT - SIGFOX LPWAN
	LORABOT_UART = 3,  // LORABOT - LORAWAN LPWAN
  LORABOT_SPI= 4   // LORABOT - LORAWAN LPWAN
};


/******************************************************************************
 * Class
 *****************************************************************************/

/*! @class JARM-ESP32
 *
 * JARM Class defines all the variables and general functions used with JARM-ITOM
 */

 class JARM32
{
  private:

   /*! Função: formata frame para ser enviado via Sigfox
    *         (transforma array de bytes em uma Hex-String
    *         para usar no comando AT de envio)
    \param uint8_t ptr_data : ponteiro para array de dados e
    \param uint8_t len : tamanho do array
    \return frame formatado (String)
    \sa formataFrameSigfox(unsigned char * ptr_data, uint8_t len)
    */
    String formataFrameSigfox(const void* ptr_data, uint8_t len);


    /*! Função: garante que haja ao menos 3 micro canais utilizáveis
    *  (condição para envio de frame vias Sigfox)
    \return void
    \sa garanteMacroMicroCanais()
    */
    bool garanteMacroMicroCanais();


  public:

    //! class constructor
    /*!
    It does nothing
    \return void
    */
    JARM32();

     /*! Funcao: inicializa JARM
    * Parâmetros: nenhum
    * Retorno: nenhum
    */
    void begin();

    //! It sets the specified LED to the specified state(ON or OFF)
    /*!
    \param uint8_t led : the LED to set ON/OFF
    \param uint8_t state : the state to set the LED
    \return void
    \sa setLed(uint8_t led, uint8_t state)
    */
    void setLed(uint8_t led, uint8_t state);

    //! getLed(led) - gets the state of the specified LED
    /*!
    \param uint8_t led : the LED to get state
    \return void
    \sa getLed(uint8_t led)
    */
    uint8_t	getLed(uint8_t led);

    /*! Funcao: inicializa comunicação com módulo Sigbot
    * Parâmetros: nenhum
    * Retorno: nenhum
    */
    void initSigbot();

    /*! Função: Cria estrutura de dados para envio para Sigfox Cloud
    * Parâmetros: nenhum
    * Retorno: TSigfox
    */
    TSigfox newSigfox();

    /*! Funcao: Formata frame e o envia para Sigfox Cloud
    * Parâmetros: ponteiro para array de dados e tamanho do array.
    * Retorno: nenhum
    */
    void sendSigfox(const void* ptr_data, uint8_t len);

    /*! Funcao: Envia comando AT para Sigbot
    * Parâmetros: comando AT
    * Retorno: nenhum
    */
    void sendATSigbot(String command, String *dataOut);

    /*! Funcao: Obtem tensao da Sigbot
    * Parâmetros: nenhum
    * Retorno: String voltage
    */
    String getVoltageSigbot();

};

#endif // JARM32_H