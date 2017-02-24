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

É possível realizar padrões diferentes manipulando o x, o y e o RGBA dos píxeis em loops, como mostra nas imagens abaixo:

![PutPixel](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica1/imagens/draw%20Pixel.jpg)
![PutPixel2](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica1/imagens/draw%20Pixel2.jpg)

### Classe Pixel
Para facilitar o desenvolvimento do trabalho, foi-se criado uma classe Pixel, para representar a posição e cores dos pixels, facilitando também, a depuração, caso o pixel possua posição ou cor inválida.
O cabeçalho do construtor do Pixel ficou da seguitne maneira:
```C
Pixel pixel = Pixel(int x, int y, int* colorArray);
```
E o cabeçalho do método putPixel, utilizando a classe Pixel então
```C
putPixel(Pixel px);
```

## DrawLine
No drawLine é pedido para rasterizar uma linha dado dois pontos quaisquer. Foi utilizado uma generalização do Algorítmo de Bresenham.
Baseado no material da disciplina, o código foi implementado a versão mais básica, servindo apenas para o primeiro octante do plano cartesiano. Logo foi necesário generalizar para os outros 7 octantes.
A generalização foi feita utilizando as variaveis xVariation e yVariation, onde nelas se verificava se a linha cresce ou decresce para x e y. Dependendo do crescimento da reta, foi feito o calculo para determinar se os incrementos/decrementos iam para x ou y. Utilizando os ponteiros straightLine e distortedLine e de acordo com o xVariation e yVariation é feito a reflexão em torno dos eixos x e y para que o incremento seja no octante correto. 

```C
while(*distortedLine < limit) {
  		if (distortion <= 0) {
  			distortion += increaseStraight;
  		}
  		else {
  			distortion += increaseDistortion;
  			*straightLine += 1;
  		}
      *distortedLine += 1;

  		linePosition.setX(x);
  		linePosition.setY(y);

  		if(xLimit != px2.getX())
  		    linePosition.setX( px1.getX() - (linePosition.getX() - px1.getX()));
  		if(yLimit != px2.getY())
  		    linePosition.setY( px1.getY() - (linePosition.getY() - px1.getY()));
          
       //CALCULO DO GRADIENTE
          
      putPixel(Pixel(linePosition.getX(),linePosition.getY(),gradientColor));
```

### Coloração da linha
A coloração da reta foi feita utilizando um algoritmo para calcular a porcentagem da linha dado o ponto atual, assim foi aplicado a cor de acordo com a porcentagem dada usando o seguinte modelo:
```C
for(int index=0 ; index<4 ; index++)
  radientColor[index] = px1.getColor()[index] * distancePercent + px2.getColor()[index] * (1 - distancePercent);
```

## DrawTriangle
No drawTriangle é preciso rasterizar o contorno de um triângulo dado 3 pontos como entrada. As linhas do triangulo precisam alternar de cor, formando um degradê com as 3 cores informadas no Pixel.
Como o drawLine já permite a varianção de cor, o método drawTriangle receberá as 3 cores nos próprios Pixels e rederizará os contornos do triângulo com o drawLine.

## Extra
### DrawCircle
Como extra, foi feito uma função de renderizar círculos.
A função drawCircle rasteriza um círculo, com o centro em um determinado pixel, com o raio dado em um número inteiro e com a cor do contorno definido na cor do pixel.
Para representar o círculo, é preciso converter seu valor de coordenadas polares para o plano cartesiano utilizando as seguintes instruções:
```C
int x = radius * cos(teta);
int y = radius * sin(teta);
```
Onde a variável teta(Θ) representa o ângulo, em coordenadas polares. Variando o teta de 0 a 2*PI dentro de um loop, teremos o desenho completo do círculo.
Foi encontrado um problema nesta etapa em relação a variação teta, se a variação de teta para cada interação do loop for muito grande, o círculo fica com pixels muito espaçado, já se a variação de teta for muito pequena, o círculo fica ineficiente de se renderizar, já que foi gasto uma interação extra para a mesma posição do contorno do círculo. Este problema é conhecido na Matemática como o [Problema do Círculo de Gauss](https://en.wikipedia.org/wiki/Gauss_circle_problem).
Uma solução simples para este problema é utilizando uma generalização do método encontado por Gauss, representado por um somatório dos quadrados do raio do círculo:
>![Solução para o Problema do Círculo de Gauss](https://wikimedia.org/api/rest_v1/media/math/render/svg/bda59a323e2f697120fbd0785b8dc75ce9ccbe5c)

Que pode ser fácilmentne representado no seguinte loop:
```C
int circlePixels = 0;
for(int n = 0; n <= radius; n++)
  circlePixels += sqrt( (radius*radius) - (n*n) );
circlePixels = circlePixels * 4 + 1;
```
A variação de teta então ficou:
```C
float variation = 2*PI / ((float) circlePixels);
```
Infelizmente, é possível observar que o desempenho de rodar 2 multiplicações, 1 subtração e uma raiz quadrada em um somatório não é um eficiente o suficiente (O(n)) para valer a pena a utilização deste algorítmo, logo para ter um desempenho mais eficiente (O(1)), foi feito apenas uma divisão 1f/radius para representar a variação de pixeis do círculo, que dá um valor satisfatório dado o tamanho do raio do círculo.
