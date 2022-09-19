/******************************************************************************
                    Comunicação Mestre e dois Escravo - Sketch para SLAVE
                                 Sketch de Exemplo

                         Criado em 15 de Agosto de 2022
                               por Michel Galvão

  Placa: Arduino Nano
  O sketch usa 4362 bytes (14%) de espaço de armazenamento para programas.
    O máximo são 32256 bytes.
  Variáveis globais usam 406 bytes (19%) de memória dinâmica, deixando 1791 bytes
    para variáveis locais. O máximo são 2048 bytes.


  Blog Eletrogate - Veja este e outros projetos e tutoriais no blog Eletrogate
                            https://blog.eletrogate.com/

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Inclusão da biblioteca
#include <Wire.h> // Biblioteca nativa do core Arduino

// Variáveis globais
const int myAddress = 0x09; // constante armazena o endereço do dispositivo slave

void setup() {
  Serial.begin(115200);  // Configura a taxa de transferência em bits por
  //                        segundo (baud rate) para transmissão serial.
  Serial.println();
  Wire.begin(myAddress); // inicia o dispositivo com o endereço definido anteriormente
  Wire.onReceive(receiveEvent); //registra o evento de recebimento de mensagem
  Serial.println("Software do arduino NANO");
}

void loop() {}

void receiveEvent(int howMany) {
  String message = readString();
  Serial.print(message); // imprime a mensagem recebida
}

String readString() {
  String retorno;
  while (Wire.available()) { // Enquanto houver bytes disponíveis para leitura, ...
    char c = Wire.read(); // recebe o byte como caractere
    retorno += c;
  }
  return retorno;
}