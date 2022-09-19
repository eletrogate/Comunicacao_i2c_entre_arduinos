/******************************************************************************
                    Comunicação Mestre e Escravo - Sketch para MASTER
                                 Sketch de Exemplo

                         Criado em 15 de Agosto de 2022
                               por Michel Galvão

  Placa: Arduino Uno
  O sketch usa 9180 bytes (28%) de espaço de armazenamento para programas.
    O máximo são 32256 bytes.
  Variáveis globais usam 530 bytes (25%) de memória dinâmica. O máximo são 1508 bytes.



  Blog Eletrogate - Veja este e outros projetos e tutoriais no blog Eletrogate
                            https://blog.eletrogate.com/

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Inclusão da biblioteca
#include <Wire.h> // Biblioteca nativa do core Arduino
#include <LiquidCrystal_I2C.h> // Necessária a instalação da bibliteca

// Variáveis globais
const int myAddress = 0x07; // constante armazena o endereço deste dispositivo (master)
const int slaveAddress = 0x08; // constante armazena o endereço do dispositivo slave
float temperatura, pressao, umidade; // variávies do tempo

// Instanciação dos objetos das Classes
LiquidCrystal_I2C lcd(0x27, 16, 2); // Instanciação do objeto da classe do display LCD

void setup() {
  Serial.begin(115200);  // Configura a taxa de transferência em bits por
  //                        segundo (baud rate) para transmissão serial.
  Serial.println();

  lcd.init(); // Inicializa o display LCD I2C
  lcd.backlight(); // Liga a luz de fundo do dispaly LCD I2C
  Wire.begin(myAddress); // Inicia a comunicação I2C
  Wire.onReceive(receiveEvent); //Registra o evento de recebimento de mensagem
  Serial.println("Software do arduino UNO");
}

void loop() {
  Wire.beginTransmission(slaveAddress); // transmite para o dispositivo slave
  Wire.write("getDados");// envia a mensagem
  Wire.endTransmission();  //para de transmitir

  delay(500); // pausa de 500 milissegundos

  // Imprimimos no dispaly LCD I2C o valro das variáveis de pressão, umidadade e temperatura
  lcd.setCursor(0, 0);
  lcd.print("P:");
  lcd.print(pressao / 100); // Converte a presão de Pascal para Hectopascal e a imprime
  lcd.print(" hPa    ");
  lcd.setCursor(0, 1);
  lcd.print("U:");
  lcd.print(umidade);
  lcd.print("% T:");
  lcd.print(temperatura);
  lcd.write(223); // imprime o caractere º (11011111 convertido para decimal 223)
  //                 explicação de como obter: https://blog.eletrogate.com/monitoramento-de-ponto-de-orvalho-com-arduino/#titulo7
  lcd.print("C ");
}

void receiveEvent(int howMany) {
  String message = readString();
  Serial.print(message); // imprime a mensagem recebida


  int index1, index2; // cria as variáveis locais para armazenar os índices de
  //                      extração de substring da String message.

  index1 = 0;
  index2 = message.indexOf('&', index1);
  temperatura = message.substring(index1, index2).toFloat(); // extrai a string e a converte para float

  index1 = index2 + 1;
  index2 = message.indexOf('&', index1);
  pressao = message.substring(index1, index2).toFloat(); // extrai a string e a converte para float

  index1 = index2 + 1;
  index2 = message.indexOf('&', index1);
  umidade = message.substring(index1, index2).toFloat(); // extrai a string e a converte para float
}

String readString() {
  String retorno;
  while (Wire.available()) { // Enquanto houver bytes disponíveis para leitura, ...
    char c = Wire.read(); // recebe o byte como caractere
    retorno += c;
  }
  return retorno;
}