# People Counting

Repositorio destinado para documentação e disponibilização do projeto People Counting desenvolvido para aplicação no ambiente do Ecomuseu na matéria de Engenharia de software II no curso de ciência da computação UNIOESTE FOZ

## Inspirações

Este projeto nasceu a partir da percepção da carência de informações sobre o comportamento dos visitantes dentro do ambiente do ecomuseu. A partir dessa carência será desenvolvido um conjunto de tecnologias que permitirá o mapeamento do comportamento dos visitantes envolvendo:
* Horario de entrada e saída
* Tempo de permanencia no ecomuseu
* Número de visitas

## Arquitetura da Solução
<br /><img alt="DIAGRAMA DA ARQUITETURA" src="https://raw.githubusercontent.com/filipecavalc/People-Counting/master/Arquitetura%20da%20solu%C3%A7%C3%A3o.png" width="700">

## Descrição da solução

O objetivo da solução é a contagem de visitantes que entram no parque e tempo médio da visita.
As tecnologias que serão utilizadas são:

### ESP8266

ESP8266 é um microcontrolador muito comum para projetos de IOT (Internet Of Things ou Internet das Coisas) que também é uma tecnologia que será utilizada para o projeto.
O objetivo do é atuar como um sniffer não malicioso, com a unica intenção de capturar os MACADDRESS dos dispositivos proximos juntamente com o horario. Essa informação capturada pelo ESP8266 vai ser disparada para um servidor MQTT que ira tratar e salvar esse dado no banco de dados.
<br /><img alt="DIAGRAMA DO ESP8266" src="https://raw.githubusercontent.com/filipecavalc/People-Counting/master/ESP8266%20pinout%20NODEMCU.jpeg" width="400">

### MQTT

É conhecido como Message Queuing Telemetry Transport. O MQTT é um protocolo desenvolvido para mensagens leves, ou seja, com foco em pequenas informações como a de sensores e pequenos dispositivos moveis, possui alta latencia e é otimizado para redes TCP/IP não confiáveis.
O MQTT trabalha com um conceito de publicadores e inscritos, onde publicadores são os sensores e pequenos dispositivos que fornecem os dados e os inscritos são bancos de dados ou dispositivos variados que leem os dados em tempo real que o broker recebe e fazem os tratamentos que quiserem.
<br /><img alt="DIAGRAMA DO MQTT" src="https://raw.githubusercontent.com/filipecavalc/People-Counting/master/MQTT%20DIAGRAM.png" width="400">

## Hardware projetado

Este é o esquemático do harware a ser projetado.
<br /><img alt="ESQUEMA DO PROJETO DO HARDWARE" src="https://raw.githubusercontent.com/filipecavalc/People-Counting/master/Projeto%20do%20Hardware.png" width="650">

Esta é a imagem do protótipo desenvolvido para testes.
<br /><img alt="PROTÓTIPO DO HARWARE" src="https://raw.githubusercontent.com/filipecavalc/People-Counting/master/Prot%C3%B3tipo%20do%20Hardware.png" width="400">

## Códigos para os ESP8266's

São dois códigos diferentes:

### Coleta dos dados

[Sniffer code](https://github.com/filipecavalc/People-Counting/blob/master/C%C3%B3digos%20do%20ESP8266/Sniffer/Sniffer.ino)

#### Lógica

* Inicializa a porta serial;
* Configura o modo de operação para Station
* Desabilita o modo "promiscuous" do ESP8266
* Realiza conexão em um acess point para obter internet
* Sincroniza o relogio para vincular o tempo em que os dados estão sendo coletados
* Configura o callback do metodo que coleta os dados
  * Monta os dados em formato JSON
  * Envia os dados em formato JSON para a saída Serial
* Habilita o modo "promiscuous" do ESP8266
* Configura o temporizador de retorno de chamada do canal

### Envio dos dados para o Broker MQTT

[MQTT post code](https://github.com/filipecavalc/People-Counting/blob/master/C%C3%B3digos%20do%20ESP8266/MQTTPOST/MQTTPOST.ino)

#### Lógica

* Inicializa porta serial
* Configura o modo de operação para Station
* Realiza conexão em um acess point para obter internet
* Conecta ao broker MQTT
* Loop
  * Espera o buffer do Serial receber dados
  * Quando recebe dados na porta serial:
    * Checa a conexão com WiFi
      * Se não estiver conectado tenta restabelecer a conexão
    * Checa a conexão com o broker MQTT
      * Se não estiver conectado tenta restabelecer a conexão
   * Envia os dados para o broker MQTT

## Código para salvar dados que passam pelo broker no MongoDB

[Como Iniciar o script](https://github.com/filipecavalc/People-Counting/tree/master/mqtt-mongo-recorder)

[MongoDB config file](https://github.com/filipecavalc/People-Counting/blob/master/mqtt-mongo-recorder/config.js)

[Script de tratamento dos dados](https://github.com/filipecavalc/People-Counting/blob/master/mqtt-mongo-recorder/server.js)

Este código realiza a conexão com o broker para "ouvir" a passagem dos dados e salvar no banco de dados.
Os dados da mensagem devem estar sendo enviados no padrão JSON, dados fora do formato JSON serão recusados e não serão salvos.
