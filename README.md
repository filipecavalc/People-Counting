# People Counting
Repositorio destinado para documentação e disponibilização do projeto People Counting desenvolvido para aplicação no ambiente do Ecomuseu na matéria de Engenharia de software II no curso de ciência da computação UNIOESTE FOZ

## Inspirações
Este projeto nasceu a partir da percepção da carência de informações sobre o comportamento dos visitantes dentro do ambiente do ecomuseu. A partir dessa carência será desenvolvido um conjunto de tecnologias que permitirá o mapeamento do comportamento dos visitantes envolvendo:
* Horario de entrada e saída
* Tempo de permanencia no ecomuseu
* Número de visitas

## Arquitetura da Solução
![alt text](https://raw.githubusercontent.com/filipecavalc/People-Counting/master/Arquitetura%20da%20solução.png)

## Descrição da solução

O objetivo da solução é a contagem de visitantes que entram no parque e tempo médio da visita.
As tecnologias que serão utilizadas são:

### ESP8266
ESP8266 é um microcontrolador muito comum para projetos de IOT (Internet Of Things ou Internet das Coisas) que também é uma tecnologia que será utilizada para o projeto.
O objetivo do é atuar como um sniffer não malicioso, com a unica intenção de capturar os MACADDRESS dos dispositivos proximos juntamente com o horario. Essa informação capturada pelo ESP8266 vai ser disparada para um servidor MQTT que ira tratar e salvar esse dado no banco de dados.
![alt text](https://raw.githubusercontent.com/filipecavalc/People-Counting/master/ESP8266%20pinout%20NODEMCU.jpeg)

### MQTT
É conhecido como Message Queuing Telemetry Transport. O MQTT é um protocolo desenvolvido para mensagens leves, ou seja, com foco em pequenas informações como a de sensores e pequenos dispositivos moveis, possui alta latencia e é otimizado para redes TCP/IP não confiáveis.
O MQTT trabalha com um conceito de publicadores e inscritos, onde publicadores são os sensores e pequenos dispositivos que fornecem os dados e os inscritos são bancos de dados ou dispositivos variados que leem os dados em tempo real que o broker recebe e fazem os tratamentos que quiserem.
![alt text](https://raw.githubusercontent.com/filipecavalc/People-Counting/master/MQTT%20DIAGRAM.png)
