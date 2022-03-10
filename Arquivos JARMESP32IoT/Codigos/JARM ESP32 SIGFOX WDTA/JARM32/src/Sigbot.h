/*! \file Sigbot.h
    \brief Library containing useful general functions with Sigfox Module

    Copyright (C) 2019 Thingsbot Tecnology
    http://www.thingsbot.com.br

 * Sigbot is a library for Engebot Sigbot hardware use with the JARM Iot-M platform.
 * The library is designed to use serial communication between Sigbot module and JARM Iot-M.
 * Current library coverage is:
 *	 - AT command
 *	 - Sigfox payload transfer
 *	 - TD1208 temperature read
 *	 - TD1208 ID read
 *	 - TD1208 supply voltage read
 *	 - TD1208 hardware version read
 *	 - TD1208 firmware version read
 *	 - TD1208 power read
 *	 - TD1208 power set
 *   - TD1208 downlink request
 *   - Data conversion in hexadecimal

    Version:		1.0
    Design:			Thingsbot / Sirineo
    Implementation:	Wenderson Ferreira

 */

/*************************************************************************/
/*                                                                       */
/*                           Sigbot 2020                                 */
/*                                                                       */
/*                       Thingsbot Technology                            */
/*                                                                       */
/*                     Firmware for the Sigfox-Modem                     */
/*  Developed by:       Wenderson Machado Ferreira                       */
/*                                                                       */
/*              Sigbot Firmware, Brasilia, Brasil                        */
/*                                                                       */
/*            Sigbot.h       Version 1.0,   05.08.2018                   */
/*                                                                       */
/*************************************************************************/


/**************************************************************/
/*************          Specifications      *******************/
/**************************************************************/

#ifndef SIGBOT_H
#define SIGBOT_H


/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

//! ATcommands responses
const char SIGFOX_AT_OK[] 	= "OK";
const char SIGFOX_AT_ERROR[] 	= "ERROR";
const char SIGFOX_AT_EOL[] 	= "\r\n";
const char SIGFOX_AT_HEADER[] = "AT$";
const char SIGFOX_AT_HEADER_SLASH[] = "AT/";
const char SIGFOX_AT_MANUFACTURER_ERROR[]  = "Manufacturer error";
const char SIGFOX_AT_ID_ERROR[]  = "ID or key error";
const char SIGFOX_AT_STATE_MACHINE_ERROR[]  = "State machine error";
const char SIGFOX_AT_FRAME_SIZE_ERROR[]  = "Frame size error";
const char SIGFOX_AT_MANUFACTURER_SEND_ERROR[]  = "Manufacturer send error";
const char SIGFOX_AT_VOLTAGE_TEMP_ERROR[]  = "Get voltage/temperature error";
const char SIGFOX_AT_CLOSE_ISSUES_ERROR[]  = "Close issues encountered";
const char SIGFOX_AT_API_ERROR[]  = "API error indication";
const char SIGFOX_AT_GET_PN9_ERROR[]  = "Error getting PN9";
const char SIGFOX_AT_GET_FREQUENCY_ERROR[] = "Error getting frequency";
const char SIGFOX_AT_BUILD_FRAME_ERROR[] = "Error building frame";
const char SIGFOX_AT_DELAY_ROUTINE_ERROR[] = "Error in delay routine";
const char SIGFOX_AT_CALLBACK_ERROR[] = "Callback causes error";
const char SIGFOX_AT_TIMING_ERROR[] = "Timing error";
const char SIGFOX_AT_FREQUENCY_ERROR[] = "Frequency error";

//! Maximum packet size Uplink
static int SIGFOX_UPLINK_MAX_MESSAGE_SIZE = 12;

//! Maximum packet size
static int SIGFOX_DOWNLINK_MAX_MESSAGE_SIZE = 8;

//! Max number of chars in Sigfox device ID.
static int MAX_DEVICE_ID_SIZE = 8;

//! Max number of chars in Sigfox PAC code.
static int MAX_DEVICE_PAC_SIZE = 16;

#define TEMPO_MS_ENTRE_ENVIOS_SIGFOX  900000 //ms (= 15 minutos)


/*! @enum Country
 * API country messages
 */
enum Country {
  US = 0 ,
  EU
};

/*! @enum Protocol
 * API protocol messages
 */
enum Protocol {
  SSM = 0 ,
  ATMEL,
  SIGFOX
};

/*! @enum AnswersTypes
 * API answer messages
 */
enum AnswersTypes
{
	SIGFOX_ANSWER_OK = 0,
	SIGFOX_ANSWER_ERROR = 1,
	SIGFOX_NO_ANSWER = 2,
};

/*! @enum CommandTypes
 * Command types
 */
enum CommandTypes
{
	SIGFOX_CMD_SET  = 1, 	// AT$<cmd>=<value>
	SIGFOX_CMD_READ = 2, 	// AT$<cmd>?
	SIGFOX_CMD_DISPLAY = 3, // AT/<cmd>?
};

/*! @enum RegionTypes
 */
enum RegionTypes
{
	SIGFOX_REGION_UNKNOWN 	= 0,
	SIGFOX_REGION_ETSI 		= 1,
	SIGFOX_REGION_FCC 		= 2,
	SIGFOX_REGION_ARIB 		= 3,
};

/*! @enum ZoneTypes
 */
enum ZoneTypes
{
    RCZ_1 = 1,
    RCZ_2 = 2,
    RCZ_3 = 3,
    RCZ_4 = 4
};

/* Typedefs
// Structure / data type
typedef struct __attribute__ ((packed)) sigfox_message
{
    char variavel_1;   //1 byte
    char variavel_2;   //1 byte
    char variavel_3;   //1 byte
    char variavel_4;   //1 byte
    char variavel_5;   //1 byte
    char variavel_6;   //1 byte
    char variavel_7;   //1 byte
    char variavel_8;   //1 byte
    char variavel_9;   //1 byte
    char variavel_10;  //1 byte
    char variavel_11;  //1 byte
    char variavel_12;  //1 byte
                       // = 12 bytes
}TSigfox;
*/


/* Typedefs */
// Structure / data type
typedef struct __attribute__ ((packed)) sigfox_message
{
    short bateria;      //2 bytes
    short temperatura;  //2 bytes
    short humidade;     //2 bytes
    short luminosidade; //2 byte
    char variavel_1;   //1 byte
    char variavel_2;   //1 byte
    char variavel_3;   //1 byte
    char variavel_4;   //1 byte
                       // = 12 bytes
}TSigfox;


/* Definições gerais */
#define SIGBOT_CMD_VERIFICA_PRESENCA_MODEM     "AT\r"
#define SIGBOT_CMD_NUM_MICRO_MACRO_CANAIS      "AT$GI?\r"
#define SIGBOT_CMD_RESET_MICRO_MACRO_CANAIS    "AT$RC\r"
#define SIGBOT_CMD_ENVIO_DE_FRAME              "AT$SF="
#define SIGBOT_CMD_ID                          "AT$I=10\r"
#define SIGBOT_CMD_PAC                         "AT$I=11\r"
#define SIGBOT_CMD_TEMPERATURA                 "AT$T?\r"
#define SIGBOT_CMD_TENSAO                      "AT$V?\r"
#define SIGBOT_CMD_RESET                       "AT$P=0\r"
#define SIGBOT_CMD_SLEEP                       "AT$P=1\r"
#define SIGBOT_CMD_DEEP_SLEEP                  "AT$P=2\r"
#define SIGBOT_CMD_SLEEP_WAKEUP                "\n"
#define BAUDRATE_SERIAL_SIGBOT 9600

#define SIGBOT_ATCOMMAND "AT"
#define SIGBOT_ATOK "OK"
#define SIGBOT_ATID "AT$I=10"
#define SIGBOT_ATPAC "AT$I=11"
#define SIGBOT_ATTEMPERATURE "AT$T?"
#define SIGBOT_ATVOLTAGE "AT$V?"
#define SIGBOT_ATFRAME "AT$SF="
#define SIGBOT_SEND_MESSAGE_RESPONSE ",1"
#define DOWNLINKEND "+RX END"
#define ATCOMMAND_TIMEOUT (3000)
#define ATSIGBOTTX_TIMEOUT (30000)
#define ATDOWNLINK_TIMEOUT (45000)

#endif // SIGBOT_H