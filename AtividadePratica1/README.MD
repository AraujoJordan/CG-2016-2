# Rasterização

Rasterização é o termo usado para descrever o processo de transformar uma imagem vetorial (descrita por funções matemáticas e formas geométricas), em uma imagem "raster" (descrita por uma matriz de pixels).
O processo de rasterização é essencial para a exibição de qualquer imagem vetorial em um display de pixeis (monitor de computador, televisão, display de celular, etc), já que estes estão sempre aumentando de resolução e de quadros por segundo, a eficiência dos algortimos é primordial para a fluidez na exibição de imagens.
Neste trabalho, vou abordar alguns algoritmos de rasterização, focando em 3 principais aplicações:

  - PutPixel
    * Adicionar um pixel em algum local específico do display
  - DrawLine
    * Colocar uma linha de qualquer angulação e tamanho em um display
  - DrawTriangle
    * Desenho de um triangulo (sem preenchimento) com cores da linha variando

## PutPixel
Para a inserção de um pixel na tela, é necessário calcular sua posição exata em bytes. Como cada pixel possui 4 bytes (1 byte para vermelho, 1 para verde, 1 para azul e 1 para a transparência), e o display é organizado como um array de bytes, temos que realizar o seguinte algoritmo para encontrar a posição desejada:
```C
int offset = (x  + y * IMAGE_WIDTH) * 4;
```

Onde offset é a primeira posição desejada, IMAGE_WIDTH é a "largura" da tela e 4 sãos as 4 cores do pixel.
Se por exemplo, precisar pintar de branco o pixel na posição (25,10) em uma tela de 512 pixels de largura, teremos (25+10*512)*4 = 71680, onde 71680 é a posição do array correspondente ao primeira cor RGBA do pixel.

![PutPixel](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica1/imagens/draw%20Pixel.jpg)
![PutPixel2](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica1/imagens/draw%20Pixel2.jpg)

