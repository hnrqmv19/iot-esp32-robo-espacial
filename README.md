# Controle Remoto IoT para Robô Espacial (`iot-esp32-robo-espacial`)

Este projeto consiste na simulação de um sistema de **Controle Remoto de um Robô Espacial** utilizando a placa microcontrolada **ESP32-S3** na plataforma de simulação **Velxio**.

## 🎯 Objetivo da Etapa

O objetivo principal desta etapa é desenvolver o firmware e a simulação de hardware do controle remoto, garantindo:

1. **Leitura dos eixos do joystick analógico** para conversão em comandos direcionais de movimentação do robô.
2. **Controle de parada remota de emergência** via botão (comutador Liga/Desligar).
3. **Sinalização visual do status de conexão/comunicação** no próprio controle remoto usando LEDs indicadores (Verde para ativo/conectado e Vermelho para inativo/desligado).
4. **Monitoramento serial** contínuo dos comandos transmitidos e do estado atual do robô.

## 🛠️ Lista de Componentes do Circuito

* **1x Microcontrolador ESP32-S3**
* **1x Joystick Analógico** (Pinos HOR e VERT conectados aos GPIOs do ESP32)
* **1x Botão / Push-Button** (Parada/Controle do Sistema com `INPUT_PULLUP`)
* **1x LED Verde** (Indicador de status "Conectado/Ligado")
* **1x LED Vermelho** (Indicador de status "Desligado/Parada Remota")
* **Resistores** para limitação de corrente dos LEDs (ex.: 220Ω)

## 📌 Mapeamento de Pinos (Pinout)

| Componente | Pino do Componente | Pino no ESP32-S3 | 
| ----- | ----- | ----- | 
| **Joystick** | Eixo X (HOR) | GPIO 4 | 
| **Joystick** | Eixo Y (VERT) | GPIO 5 | 
| **Botão Stop** | Terminal de Sinal | GPIO 6 | 
| **LED Verde** | Anodo (+) | GPIO 7 | 
| **LED Vermelho** | Anodo (+) | GPIO 15 | 

## ⚙️ Funcionalidades do Sistema

* **Movimentação (Joystick):**
  * **Frente:** Eixo Y < 1000 $\rightarrow$ Motores para frente.
  * **Trás:** Eixo Y > 3000 $\rightarrow$ Motores para trás.
  * **Esquerda:** Eixo X > 3000 $\rightarrow$ Motor direito ativo.
  * **Direita:** Eixo X < 1000 $\rightarrow$ Motor esquerdo ativo.
  * **Parado:** Leituras dentro dos limites centrais (zona morta).

* **Comando de Parada de Emergência:**
  * Pressionar o botão altera o estado global (`sistemaLigado`).
  * Quando **LIGADO**: LED Verde aceso e envio contínuo dos comandos direcionais.
  * Quando **DESLIGADO**: LED Vermelho aceso, motores do robô recebem o comando `DESLIGAR` e o robô para imediatamente.

## 🚀 Como Rodar no Velxio

1. Acesse a plataforma do **Velxio** e abra o projeto do circuito simulado:
   * 🔗 [**Link do Projeto no Velxio**](https://velxio.dev/hnrqmv/edital-final-redes)

2. Verifique se o código do arquivo `.ino` está carregado no ambiente.

3. Inicie a simulação do circuito.

4. Abra o **Monitor Serial** integrado no Velxio para acompanhar a saída de dados a 115200 baud rate.

5. Interaja com os componentes:
   * **Mova o Joystick** para testar as direções (Frente, Trás, Esquerda, Direita).
   * **Pressione o Botão de Emergência** para alternar o estado do robô entre **LIGADO** e **DESLIGADO** e observe a alteração de status nos LEDs Verde e Vermelho.
