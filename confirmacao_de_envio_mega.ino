/******************************************************************************
                    Comunicação Mestre e Escravo - Sketch para MASTER
                                 Sketch de Exemplo

                         Criado em 15 de Agosto de 2022
                               por Michel Galvão

  Placa: Arduino Mega
  O sketch usa 6190 bytes (2%) de espaço de armazenamento para programas.
    O máximo são 253952 bytes.
  Variáveis globais usam 460 bytes (5%) de memória dinâmica, deixando 7786 bytes
    para variáveis locais. O máximo são 8192 bytes.



  Blog Eletrogate - Veja este e outros projetos e tutoriais no blog Eletrogate
                            https://blog.eletrogate.com/

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Inclusão da biblioteca
#include <Wire.h> // Biblioteca nativa do core Arduino

// Variáveis globais
const int myAddress = 0x07; // armazena o endereço deste dispositivo (master)
const int slaveAddress = 0x08; // constante armazena o endereço do dispositivo slave
int x = 0; // variável de armazenagem do valor para envio

void setup() {
  Serial.begin(115200);  // Configura a taxa de transferência em bits por
  //                        segundo (baud rate) para transmissão serial.
  Serial.println();

  Wire.begin(myAddress); // inicia a comunicação I2C
  Wire.onReceive(receiveEvent); //registra o evento de recebimento de mensagem
  Serial.println("Software do arduino MEGA");
}

void loop() {
  Wire.beginTransmission(slaveAddress); // transmite para o dispositivo slave

  // Cria e formata a mensagem para envio
  String message = "O valor de x é ";
  message.concat(x);
  message.concat("\n");

  Wire.write(message.c_str());// envia a mensagem
  Wire.endTransmission();  //para de transmitir

  x++; // incremento da variável
  delay(500); // pausa de 500 milissegundos
}

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