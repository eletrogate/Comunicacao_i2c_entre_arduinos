/******************************************************************************
                    Comunicação Mestre e Escravo - Sketch para SLAVE
                                 Sketch de Exemplo

                         Criado em 12 de Agosto de 2022
                               por Michel Galvão

  Placa: Arduino Nano
  O sketch usa 5266 bytes (17%) de espaço de armazenamento para programas.
    O máximo são 30720 bytes.
  Variáveis globais usam 465 bytes (22%) de memória dinâmica, deixando 1583 bytes
    para variáveis locais. O máximo são 2048 bytes.


  Blog Eletrogate - Veja este e outros projetos e tutoriais no blog Eletrogate
                            https://blog.eletrogate.com/

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Inclusão da biblioteca
#include <Wire.h> // Biblioteca nativa do core Arduino

// Variáveis globais
const int myAddress = 0x08; // armazena o endereço deste dispositivo (slave)
const int masterAddress = 0x07; // armazena o endereço do dispositivo master
bool recebido = false; // variável de controle do envio da confirmação de recebimento

void setup() {
  Serial.begin(115200);  // Configura a taxa de transferência em bits por
  //                        segundo (baud rate) para transmissão serial.
  Serial.println();

  Wire.begin(myAddress); // inicia o dispositivo com o endereço definido anteriormente
  Wire.onReceive(receiveEvent); //registra o evento de recebimento de mensagem
  Serial.println("Software do arduino NANO");
}

void loop() {
  if (recebido) { // se true, será enviado a mensagem de confirmação
    Wire.beginTransmission(masterAddress); // transmite para o dispositivo master

    // Cria e formata a mensagem para envio
    String message;
    message.concat("A mensagem foi recebida");
    message.concat("\n");

    Wire.write(message.c_str());// envia a mensagem
    Wire.endTransmission();  //para de transmitir
    recebido = false;
  }
}

void receiveEvent(int howMany) {
  String message = readString();
  Serial.print(message); // imprime a mensagem recebida
  recebido = true;
}

String readString() {
  String retorno;
  while (Wire.available()) { // Enquanto houver bytes disponíveis para leitura, ...
    char c = Wire.read(); // recebe o byte como caractere
    retorno += c;
  }
  return retorno;
}