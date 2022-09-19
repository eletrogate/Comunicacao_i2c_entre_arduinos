/******************************************************************************
                    Comunicação Mestre e dois Escravo - Sketch para MASTER
                                 Sketch de Exemplo

                         Criado em 15 de Agosto de 2022
                               por Michel Galvão

  Placa: Arduino Uno
  O sketch usa 5042 bytes (15%) de espaço de armazenamento para programas. 
    O máximo são 32256 bytes.
  Variáveis globais usam 279 bytes (13%) de memória dinâmica, deixando 1791 bytes 
    para variáveis locais. O máximo são 2048 bytes.


  Blog Eletrogate - Veja este e outros projetos e tutoriais no blog Eletrogate
                            https://blog.eletrogate.com/

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Inclusão da biblioteca
#include <Wire.h> // Biblioteca nativa do core Arduino

// Variáveis globais
const int slaveAddressMega = 0x08; // constante armazena o endereço do dispositivo slave Mega
const int slaveAddressNano = 0x09; // constante armazena o endereço do dispositivo slave Nano
int m = 0; // variável de armazenagem do valor para envio para o slave Mega
int n = 0; // variável de armazenagem do valor para envio para o slave Nano

void setup() {
  Wire.begin(); // inicia a comunicação I2C
}

void loop() {
  Wire.beginTransmission(slaveAddressMega); // transmite para o dispositivo slave

  // Cria e formata a mensagem para envio
  String messageM = "O valor de m é ";
  messageM.concat(m);
  messageM.concat("\n");

  Wire.write(messageM.c_str());// envia a mensagem
  Wire.endTransmission();  //para de transmitir

  Wire.beginTransmission(slaveAddressNano); // transmite para o dispositivo slave

  // Cria e formata a mensagem para envio
  String messageN = "O valor de n é ";
  messageN.concat(n);
  messageN.concat("\n");

  Wire.write(messageN.c_str());// envia a mensagem
  Wire.endTransmission();  //para de transmitir

  // atribue um valor entre 0 e 100 para a variável m, através 
  // da função random(); 
  // Documentação: https://www.arduino.cc/reference/en/language/functions/random-numbers/random/
  m = random(0,101);

  // Incrementa o valor da variável n
  n++;
  
  delay(500); // pausa de 500 milissegundos
}