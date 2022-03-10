//https://randomnerdtutorials.com/esp32-ssd1306-oled-display-arduino-ide/

#include "SSD1306.h" // alias for #include "SSD1306Wire.h"

//objeto controlador do display de led
/*
  0x3c  :   é um identificador único para comunicação do display
  pino 5 e 4 são os de comunicação (SDA, SDC)   
*/
SSD1306  display(0x3c, 21, 22);

//pino que ligamos o potenciometro
#define PINO_POTENCIOMETRO 32

//utilizado para fazer o contador de porcentagem
int contador;

void setup() {
  
  Serial.begin(115200);
  Serial.println();
  // Inicializa o objeto que controlará o que será exibido na tela
  display.init();

  //gira o display 180º (deixa de ponta cabeça)
 // display.flipScreenVertically();

  //configura a fonte de escrita "ArialMT_Plain_10"
 // display.setFont(ArialMT_Plain_10);


  //configura o pino para fazer a leitura do potenciômetro.
  pinMode(PINO_POTENCIOMETRO, INPUT);

}

void loop() {

  //leitura do valor do potenciometro
  int valor = analogRead(PINO_POTENCIOMETRO);  
  //Serial.println(valor);

  //mapeando o valor do potenciometro para o valor da barra de progresso
  //potenciometro faz a leitura do valor no intervalo de 0 a 4095
  //a barra de progresso espera um valor entre 0 e 100
  contador = map(valor, 4095, 0, 0, 100);

  //limpa todo o display, apaga o contúdo da tela
  display.clear();
 
  //desenha a progress bar
  drawProgressBar();
  drawProgressBar2();
  drawProgressBar3();

  //exibe na tela o que foi configurado até então.
 display.display();
 delay(500);
}


//função para desenhar a progress bar no display
void drawProgressBar() {
  
  Serial.print(">> ");
  Serial.println(contador);
  
  // desenha a progress bar
  /*
   * drawProgressBar(x, y, width, height, value);
    parametros (p):
      p1: x       --> coordenada X no plano cartesiano
      p2: y       --> coordenada Y no plano cartesiano
      p3: width   --> comprimento da barra de progresso
      p4: height  --> altura da barra de progresso
      p5: value   --> valor que a barra de progresso deve assumir
  */
  display.flipScreenVertically(); 
  //      drawProgressBar(x, y, width, height, value);
  display.drawProgressBar(25, 5, 100, 10, contador);
  // configura o alinhamento do texto que será escrito
  //nesse caso alinharemos o texto ao centro
 display.setTextAlignment(TEXT_ALIGN_CENTER);
  
  //escreve o texto de porcentagem
  /*
   * drawString(x,y,text);
    parametros (p):
     p1: x      --> coordenada X no plano cartesiano
     p2: y      --> coordenada Y no plano cartesiano
     p3: string --> texto que será exibido
  */
  display.setFont(ArialMT_Plain_16);
 // display.drawString(64,64,"LUMINOSITY ");
 
 // display.drawString(64, 5, "lux:"+ String(contador) + "%"); ESCREVE VALOR
  
  display.drawString(10, 1, "x :");
 // display.drawString(64,64,"LUMINOSITY");

  
  /*//se o contador está em zero, escreve a string "valor mínimo"
  if(contador == 0){
    display.drawString(64, 45, "Valor mínimo");
  }
  //se o contador está em 100, escreve a string "valor máximo"
  else if(contador == 100){
    display.drawString(64, 45, "Valor máximo");
  }
  */
  
}
// FIM BARRA 1

// INICIO BARRA 2

void drawProgressBar2() {
  
  display.flipScreenVertically(); 
  display.drawProgressBar(25, 29, 100, 10, contador);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 25, "y :");
  
}

// INICIO BARRA 3

void drawProgressBar3() {
  
  display.flipScreenVertically(); 
  display.drawProgressBar(25, 52, 100, 10, contador);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 47, "z :");
   
}




