/******************************************************************************
                    Comunicação Mestre e Escravo - Sketch para SLAVE
                                 Sketch de Exemplo

                         Criado em 12 de Agosto de 2022
                               por Michel Galvão

  Placa: Arduino Nano
  O sketch usa 14864 bytes (48%) de espaço de armazenamento para programas.
    O máximo são 30720 bytes.
  Variáveis globais usam 559 bytes (27%) de memória dinâmica. O máximo são 1489 bytes.


  Blog Eletrogate - Veja este e outros projetos e tutoriais no blog Eletrogate
                            https://blog.eletrogate.com/

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Inclusão da biblioteca
#include <Wire.h> // Biblioteca nativa do core Arduino
#include <Adafruit_BMP280.h> // Necessária a instalação da bibliteca
#include <DHT.h> // Necessária a instalação da bibliteca

// Variáveis globais
const int myAddress = 0x08; // constante armazena o endereço deste dispositivo (slave)
const int masterAddress = 0x07; // constante armazena o endereço do dispositivo master
const int bmp280Address = 0x76; // constante armazena o endereço do dispositivo master
const int DHTPIN = 2; // constante armazena o pino ao qual o DHT11 está conectado
const uint8_t DHTTYPE = DHT11; // constante armazena o tipo do DHT (DHT11)
float temperatura, pressao, umidade; // variávies do tempo
bool recebido = false; // variável de controle do envio da confirmação de recebimento

// Instanciação dos objetos das Classes
Adafruit_BMP280 bmp; // Instanciação do objeto da classe do BMP280
DHT dht(DHTPIN, DHTTYPE); // Instanciação do objeto da classe do DHT11

void setup() {
  Serial.begin(115200);  // Configura a taxa de transferência em bits por
  //                        segundo (baud rate) para transmissão serial.
  Serial.println();

  bmp.begin(bmp280Address); // Inicializa o BMP280 no endereço I2C
  dht.begin(); // Inicializa o DHT11
  Wire.begin(myAddress); // inicia o dispositivo com o endereço definido anteriormente
  Wire.onReceive(receiveEvent); //registra o evento de recebimento de mensagem
  Serial.println("Software do arduino NANO");

  // Atribui os valores iniciais das variáveis do tempo
  temperatura = bmp.readTemperature();
  pressao = bmp.readPressure();
  umidade = dht.readHumidity();
}

void loop() {
  if (recebido) { // se true, será enviado a mensagem de confirmação
    // Atribui os valores das variáveis do tempo
    temperatura = bmp.readTemperature();
    pressao = bmp.readPressure();
    umidade = dht.readHumidity();

    Wire.beginTransmission(masterAddress); // transmite para o dispositivo master

    // Cria e formata a mensagem para envio
    String message;
    message.concat(temperatura);
    message.concat("&");
    message.concat(pressao);
    message.concat("&");
    message.concat(umidade);
    message.concat(";\n");

    Wire.write(message.c_str());// envia a mensagem
    Wire.endTransmission();  //para de transmitir
    recebido = false; // atribui o valor false para a variável de controle do
    //                    envio da confirmação de recebimento.
  }
}

void receiveEvent(int howMany) {
  String message = readString();
  Serial.print(message); // imprime a mensagem recebida
  recebido = true; // atribui o valor true para a variável de controle do
  //                    envio da confirmação de recebimento.
}

String readString() {
  String retorno;
  while (Wire.available()) { // Enquanto houver bytes disponíveis para leitura, ...
    char c = Wire.read(); // recebe o byte como caractere
    retorno += c;
  }
  return retorno;
}