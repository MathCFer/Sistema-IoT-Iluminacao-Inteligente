# Sistema de Iluminação Inteligente com ESP32 e MQTT

## Descrição

Este projeto apresenta um sistema de iluminação inteligente baseado em Internet das Coisas (IoT).

O sistema utiliza um sensor PIR para detecção de movimento, um LED como atuador e uma placa ESP32 responsável pelo processamento e comunicação com a internet.

A comunicação é realizada através do protocolo MQTT utilizando o broker público HiveMQ.

## Componentes Utilizados

- ESP32
- Sensor PIR
- LED
- Resistor 220Ω
- Plataforma Wokwi

## Funcionamento

Quando o sensor PIR detecta movimento:

1. O ESP32 recebe o sinal do sensor.
2. O LED é acionado.
3. Uma mensagem MQTT é enviada para o tópico:

matheus/iluminacao/presenca

Mensagem enviada:

MOVIMENTO_DETECTADO

Quando não há movimento:

SEM_MOVIMENTO

## Comunicação MQTT

Broker:
broker.hivemq.com

Porta:
1883

Protocolo:
MQTT

## Autor

Matheus Carvalho Fernandes
