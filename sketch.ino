// Mapeamento de Pinos
const int PIN_JOY_X = 4;       // Eixo X (Pino HOR do Joystick)
const int PIN_JOY_Y = 5;       // Eixo Y (Pino VERT do Joystick)
const int PIN_BTN_STOP = 6;    // Botão Liga/Desliga Remoto
const int PIN_LED_GREEN = 7;   // LED Verde (Status: Ligado/Conectado)
const int PIN_LED_RED = 15;    // LED Vermelho (Status: Desligado)

const int LIMITE_SUPERIOR = 3000;
const int LIMITE_INFERIOR = 1000;

// Variáveis de Controle de Estado
bool sistemaLigado = true;
bool btnAnterior = HIGH;

void setup() {
  Serial.begin(115200);

  // Configuração dos Pinos
  pinMode(PIN_BTN_STOP, INPUT_PULLUP);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);

  // Inicialização do Status dos LEDs
  atualizarLEDs();
  
  Serial.println("==========================================");
  Serial.println("  CONTROLE REMOTO INICIALIZADO (ESP32-S3) ");
  Serial.println("==========================================");
}

void loop() {
  // 1. Verifica constantemente se o botão de desligar/ligar foi pressionado
  verificarBotaoLigaDesliga();

  // 2. Transmissão Contínua de Status/Comandos
  if (sistemaLigado) {
    processarEEnviarJoystick();
  } else {
    Serial.println("Comando: DESLIGAR | Status Robô: DESLIGADO (LED Vermelho)");
  }

  // Define a frequência das mensagens no Monitor Serial (ex: 300ms)
  delay(300); 
}

// ---------------------------------------------------------------
// Função: Monitora o Botão de Desligar/Ligar
// ---------------------------------------------------------------
void verificarBotaoLigaDesliga() {
  bool btnAtual = digitalRead(PIN_BTN_STOP);

  // Detecta o clique (transição do botão)
  if (btnAnterior == HIGH && btnAtual == LOW) {
    sistemaLigado = !sistemaLigado;
    atualizarLEDs();
    
    Serial.println("\n==========================================");
    if (sistemaLigado) {
      Serial.println(">>> Comutação: SISTEMA LIGADO <<<");
      Serial.println("Status: Robô Conectado (LED Verde aceso)");
    } else {
      Serial.println(">>> Comando enviado: DESLIGAR <<<");
      Serial.println("ALERT: Robô parado imediatamente!");
      Serial.println("Status: Robô Desligado (LED Vermelho aceso)");
    }
    Serial.println("==========================================\n");
  }

  btnAnterior = btnAtual;
}

void processarEEnviarJoystick() {
  int xVal = analogRead(PIN_JOY_X); // Leitura HOR
  int yVal = analogRead(PIN_JOY_Y); // Leitura VERT

  String comando = "PARADO";

  // Identificação do Comando pelas Leituras do Joystick
  if (yVal < LIMITE_INFERIOR) {
    comando = "Frente (motores para frente)";
  } else if (yVal > LIMITE_SUPERIOR) {
    comando = "Trás (motores para trás)";
  } else if (xVal > LIMITE_SUPERIOR) {
    comando = "Esquerda (motor direito ativo)";
  } else if (xVal < LIMITE_INFERIOR) {
    comando = "Direita (motor esquerdo ativo)";
  }

  // Imprime CONTINUAMENTE no Monitor Serial
  Serial.print("Comando: ");
  Serial.print(comando);
  Serial.println(" | Status Robô: LIGADO (LED Verde)");
}

void atualizarLEDs() {
  if (sistemaLigado) {
    digitalWrite(PIN_LED_GREEN, HIGH);
    digitalWrite(PIN_LED_RED, LOW);
  } else {
    digitalWrite(PIN_LED_GREEN, LOW);
    digitalWrite(PIN_LED_RED, HIGH);
  }
}