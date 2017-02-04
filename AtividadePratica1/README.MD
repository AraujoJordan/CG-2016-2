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