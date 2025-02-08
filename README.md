# tarefa_u4c6o12t
Repositório da tarefa 6 (unidade 4, capítulo 6) do curso de capacitação em sistemas embarcados - embarcatech

Este projeto tem por objetivo apresentar os conceitos de interfaces de comunicação seriais, utilizando I2C e UART e o display SSD1306.

### pio_matrix, led_matrix e numbers_frames
Módulos responsáveis por operar a matriz de leds WS2812. 

pio_matrix.h programa a máquina de estados (PIO) responsável por implementar o protocolo de comunicação serial.

led_matrix.h cria uma API para comunicação com o WS2812, expondo a função led_matrix_draw(uint number), onde "number" é o número (de 0 a 9) que deve ser exibido na matriz de leds. Está função também garante que as linhas que estão invertidas sejam reoorientadas, desta forma a montagem das imagens é simplificada (caso contrário o desenvolvedor precisaria espelhar o posicionamento dos pixels nas linhas invertidas). 

numbers_frames.h define a representação dos números a serem exibidos na matriz de leds. Os números estão representandos em hexadecimal (AA9900 por exemplo), em uma matriz tridimensional de 10x25x6.

### display.h e fonts.h
Módulos responsáveis por imprimir caracteres no display SSD1306.

fonts.h possui o bitmap 8x8 de cada umas letras de A à Z (tanto maiúsculas quanto minúsculas) e dos números de 0 à 9. Cada caractere é representado por 8 valores hexadecimais (linhas). Cada hexadecimal representa os bits das colunas, onde 0 é apagado e 1 é aceso. Dessa forma o caractere 'A' é exibido conforme abaixo:

{ 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00}

    0x0C => 0000 1100 => ..XX....
    0X1E => 0001 1110 => .XXXX...
    0x33 => 0011 0011 => XX..XX..
    0x33 => 0011 0011 => XX..XX..
    0x3F => 0011 1111 => XXXXXX..
    0x33 => 0011 0011 => XX..XX..
    0x33 => 0011 0011 => XX..XX..
    0x00 => 0000 0000 => ........

display.h é reponsável por estabelecer a comunicação com o display SSD1306 via I2C, definindo os comandos a serem enviados para a exibição dos caracteres. Os caracteres de fonts.h são decodificados e os pixels correspondentes são ligados/desligados para a formação do caractere.

### buttons.h e leds.h
O módulo buttons.h é responsável por inicializar e associar eventos aos botões. Este módulo também efetua o debounce via software.

O módulo leds.h é responsável por inicializar o led RGB e oferece uma interface simples para acende-los individualmente.

### main
main.h é responsável por importar todos os módulos supracitados e inicializá-los. Ao chamar o inicializador dos botões, são passados callbacks para os botões tratando as interrupções geradas pelos mesmos. 
Quando o botão A é pressionado, o led verde é acesso/apagado e uma mensagem sobre o seu estado é enviada para o serial monitor via UART e para o display (Ex.: O led verde foi ligado). 
Quando o botão B é pressionado, o led azul é acesso/apagado e uma mensagem sobre o seu estado é enviado para o serial monitor via UART e para o display (Ex.: O led azul foi desligado). 
No loop principal, os comandos recebidos do serial monitor via UART são tratados de acordo com o tipo: caracteres de 'A' à 'Z' (maiúsculas ou minúsculas) são exibidos no display SSD1306 ('Recebido o caractere W') e números de '0' à '9' são exibidos na matriz de leds.

### Vídeo apresentação

Disponível em [https://drive.google.com/file/d/1LokzC3jO6lpfDtH65UGW_AYkk2fy00oC/view?usp=sharing](https://drive.google.com/file/d/1LokzC3jO6lpfDtH65UGW_AYkk2fy00oC/view?usp=sharing)
