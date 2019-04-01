#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN    D3    
#define SS_PIN     D8   
#define LED        D1

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

int frequencia = 7000;
int duracao = 100;
int duracao2 = 2000;


void setup() 
{
  Serial.begin(115200);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  pinMode(D1, OUTPUT);
  digitalWrite(D1,LOW);
  pinMode(D0, OUTPUT); // Acende led Vermelho
  digitalWrite(D0,LOW); // Led Vermelho
  pinMode(D2, OUTPUT); // Acende led Azul 
  digitalWrite(D2,LOW); // Led Azul 
  pinMode(D4, LOW); // On the left hand, at the buzzer!!
}

void loop() 
{
  // Procura por cartao RFID
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona o cartao RFID
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();

  if (conteudo.substring(1) == "E9 85 CF 56" || conteudo.substring(1) == "09 16 D4 2B" || conteudo.substring(1) == "55 00 6E 1A" ) //UID 1 - Cartao
  {
    tone(D4, frequencia, duracao);
    delay(200);
    tone(D4, frequencia, duracao);
    Serial.println("Liberado !");
    Serial.println();
    digitalWrite(D1, HIGH);     // LIGA LED OU/ ativa rele, abre trava solenoide
    digitalWrite(D2, HIGH); //LIGA LED AZUL DE LIBERAÇÃO.
    delay(6000);              // DELAY /espera 6 segundos
    digitalWrite(D1, LOW);  // DESlIGA LED OU /desativa rele, fecha  trava solenoide
    digitalWrite(D2, LOW); // Desliga led de liberação
    }
  else
  {
  tone(D4, frequencia, duracao2);
  Serial.println("Não Liberado !");
    Serial.println();
    digitalWrite(D0, HIGH); //LIGA LED VERMELHO DE ACESSO NEGADO
    delay(6000);              // DELAY /espera 6 segundos
    digitalWrite(D0, LOW); // Desliga led de acesso negado
  }
}
