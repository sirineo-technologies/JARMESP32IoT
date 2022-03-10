#include <Wire.h>
#include <OneWire.h>
#include "DFRobot_SHT20.h"
#include "SSD1306.h"
#include "OLEDDisplayUi.h"
#include "JARM32.h"

/******************************************************************************
 * Definitions & Declarations
 *****************************************************************************/

/************************* LDR ********************************/
#define ANALOG_LDR 32 //JARM-ESP32
#define BRILHO_MAX_IN 4095
#define BRILHO_MIN_IN 0
#define BRILHO_MAX_OUT 255
#define BRILHO_MIN_OUT 0
#define FREQUENCIA 5000
#define RESOLUTION 8
#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  120        /*- 60 = 1 MIN - 300 - 5MIN Time ESP32 will go to sleep (in seconds) */

SSD1306  display(0x3c, 21, 22);
DFRobot_SHT20    sht20;
JARM32 jarm;

int ledChannel = 0;
int dutyCycle = 0;

void setup()
{
  delay(1000);

  display.init();
  display.flipScreenVertically();

  delay(100);

  sht20.initSHT20();
  sht20.checkSHT20();

  delay(100);

  ledcSetup(ledChannel, FREQUENCIA, RESOLUTION);
  ledcWrite(ledChannel, dutyCycle);

  jarm.begin();
  delay(100);

  jarm.initSigbot();

  /*
    Configurando a JARM32 para despertar a cada 5s
  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
 // esp_deep_sleep_start();  // Função que chama o tempo de definido para hibernação
}

void loop()
{
   display.clear();
   formata_e_envia_dados();
   esp_deep_sleep_start();  // Função que chama o tempo de definido para hibernação
   // delay(4000);
   //esp_restart();
}


short le_bateria(void)
{
    float tensao_lida = 0.0;
    short tensao_1byte = 0;

    tensao_lida = jarm.getVoltageSigbot().toFloat();

    if (isnan(tensao_lida)) {
      return tensao_lida;
    }

    tensao_1byte = (short) tensao_lida;

    return tensao_1byte;
}

short le_temperatura(void)
{
    float temperatura_lida = 0.0;
    short temperatura_1byte = 0;

    temperatura_lida = sht20.readTemperature();

    if (isnan(temperatura_lida)) {
      return temperatura_lida;
    }

    short temp_tmp = temperatura_lida  * 100;
    temperatura_1byte = (short) temp_tmp;

    return temperatura_1byte;
}

short le_humidade(void)
{
    float humidade_lida = 0.0;
    short humidade_1byte = 0;

    humidade_lida = sht20.readHumidity();

    if (isnan(humidade_lida)) {
      return humidade_lida;
    }
    short humid_tmp = humidade_lida  * 100;
    humidade_1byte = (short) humid_tmp;

    return humidade_1byte;
}

short le_luminosidade(void)
{
    int luminosidade_lida = 0;
    short luminosidade_1byte = 0;

    luminosidade_lida = analogRead(ANALOG_LDR);
    dutyCycle = map(luminosidade_lida, BRILHO_MIN_IN, BRILHO_MAX_IN, BRILHO_MIN_OUT, BRILHO_MAX_OUT);
    //ledcWrite(ledChannel, dutyCycle);

    if (isnan(luminosidade_lida)) {
      return luminosidade_lida;
    }

    luminosidade_1byte = (short) luminosidade_lida;

    return luminosidade_1byte;
}

void formata_e_envia_dados(void)
{
    TSigfox dados_sigfox = jarm.newSigfox();

    short bateria = le_bateria();
    short temperatura = le_temperatura();
    short humidade = le_humidade();
    short luminosidade = le_luminosidade();

    mostrarDados(bateria, temperatura, humidade, luminosidade);

    dados_sigfox.bateria = bateria;
    dados_sigfox.temperatura = temperatura;
    dados_sigfox.humidade = humidade;
    dados_sigfox.luminosidade = luminosidade;

    jarm.sendSigfox(&dados_sigfox, sizeof(TSigfox));
}

void mostrarDados(short bateria, short temperatura, short humidade, short luminosidade)
{
  String volt = String(bateria);
  String temp = String(temperatura);
  String umid = String(humidade);
  String lux = String(luminosidade);

  display.setFont(ArialMT_Plain_10);
  display.drawString(12,5,"SiriNEO Technologies");
  display.drawString(20,15,"TEMP-C= " + temp + " °C");
  display.drawString(20,25,"Umid= " + umid + " %");
  display.drawString(20,35,"Lum=  " + lux + " lux");
  display.drawString(20,45,"Bat=  " + volt + " v");
  display.display();

}
