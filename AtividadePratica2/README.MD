# Pipeline Gráfico

O pipeline gráfico é uma sequência de passos que realizam transformações de descrições geométricas, em valores a serem rasterizados na tela.
Nestas transformações, são utilizados matrizes para tirar proveito da paralelização da GPU e coordenadas homogênia para realizar algumas transformções afim, como a translação.

![Pipeline1](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica2/imagens/3d.png)
Fonte: Imagem do resultado

Neste trabalho foi implemntado algumas transformações, estas foram colocadas na ordem que são executadas no código, afim de facilitar o entendimento do funcionamento do código. Outra observação importante é toda a estrutura do pipeline gráfico se executa dentro de uma única função, e tudo dentro da [main.cpp](https://github.com/AraujoJordan/CG-2016-2/blob/master/AtividadePratica2/codigo/src/main.cpp), afim de reduzir as chamadas de função, aumentando o desempenho final. O código Foi feito modularizando em trechos para facilitar a leitura e organização do código.

O código foi feito em C++, e todo o pipeline se encontra na [main.cpp](https://github.com/AraujoJordan/CG-2016-2/blob/master/AtividadePratica2/codigo/src/main.cpp) do projeto. Foi utilizado a biblioteca  [Assimp](http://www.assimp.org/ "Official Assimp website") e [GLM](http://glm.g-truc.net/0.9.8/index.html "Official OpenGL Mathematics website")   para facilitar nas estrutras (leitura de objeto e de manipulação de matrizes/vetores).
## Código na `main()`
### Leitura do modelo 3D

A leitura do modelo 3D  [WaveFront (.obj)](https://en.wikipedia.org/wiki/Wavefront_.obj_file/ "Sobre o Wavefront no Wikipedia") foi feita com a biblioteca [Assimp](http://www.assimp.org/ "Official Assimp website") e é feita apenas uma única vez no método `int main(int argc, char **argv)` para garantir que não seja chamado outra vez no update do `MyGlDraw()`
```cpp
objData = new objLoader();
objData->load((char*)"/mnt/d/Computacao/CG/newBlog/CG-2016-2/AtividadePratica2/Files/pine.obj");
```

## Código no void `MyGlDraw()`
### Limpando a tela
Foi criado um método simples para limpar a tela com pixels pretos utilizando as funções já desenvolvidas [no trabalho passado](https://github.com/AraujoJordan/CG-2016-2/tree/master/AtividadePratica1)
```cpp
//=-=-=-=-=-= CLEAR SCREEN  =-=-=-=-=-=-=-=-=-
  int color[4] = {0,0,0,255};
  for(int i=0;i<=IMAGE_WIDTH;i++)
    for(int j=0;j<=IMAGE_HEIGHT;j++)
      putPixel(Pixel(i,j,color));
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
```
### Criando a Transformação View
A criação da Matrix View foi feito inicialmente para definir como a camera se posicionará no espaço da camera. Ela é criada a partir de um vetor e dois pontos:
* O `camPosition`, vetor da direção pra cima (aponta do centro para cima da camera);
* O `lookAt`, com o ponto em que a camera está apontada;
* O `upDirection` ponto que representa a posição da camera (aponta do centro para cima da camera);

A partir destes 3 valores representados em vetores (`glm::vec3`) se obtem as coordenadas da camera que é definido por xCamera, yCamera e zCamera com o cálculo:

![camCords](https://www.ntu.edu.sg/home/ehchua/programming/opengl/images/Graphics3D_CameraCoord.png)

Onde, `zCamera = Zc`, `xCamera = Xc` e `yCamera = yC`
Imagens pertencentes ao website: [www.ntu.edu.sg](https://www.ntu.edu.sg/home/ehchua/programming/opengl/CG_BasicsTheory.html)

```cpp
  // =-=-=-=-=-=-=-=-=-=-=-=-=-=-=- VIEW =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  glm::mat4 T, B;
  glm::vec3 camPosition(0.0f, 0.0f, 5.0f);
  glm::vec3 lookAt(0.0f, 0.0f, 0.0f);
  glm::vec3 upDirection(0.0f, 1.0f, 0.0f);
  glm::vec3 zCamera = glm::normalize(lookAt - camPosition);
  glm::vec3 xCamera = glm::normalize(glm::cross(upDirection, zCamera));
  glm::vec3 yCamera = glm::normalize(glm::cross(zCamera, xCamera));
  B = glm::mat4(1.0f);
  B[0] = glm::vec4(xCamera, 0.0f);
  B[1] = glm::vec4(yCamera, 0.0f);
  B[2] = glm::vec4(zCamera, 0.0f);
  T = glm::mat4(1.0f);
  T[3] = glm::vec4(-camPosition, 1.0f);
  glm::mat4 matView = glm::transpose(B) * T;
  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
```

`A matriz B` é criada a partir destes 3 vetores, e `a matriz T` é definida com a camPosition.
E a `matView` é criada com a multiplicação da [transposta](https://pt.wikipedia.org/wiki/Matriz_transposta) de `B` * a matriz `T`. Ela é a matriz View.

### Criando a transformação Model
A matriz model representa uma transformação que é aplicada a todos os pontos do universo. Serve para aplicar uma translação/rotação/escala/shear em todos os pontos de todos os objetos inseridos na cena.
Uma matriz identidade é criada na variável matModel para armazenar as transformações, que precisam ser executadas na seguinte ordem:
> matModel = matTranslation * matRotation * matScale

Onde matTranslation é a é a matriz translação desejada, matRotation é a matriz rotação desejada e matSale é a matriz a escala desejada.

Neste código, foi aplicado apenas uma translação e escala
```cpp
  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- MODEL -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  glm::mat4 matModel = glm::mat4(1.0f);
  matModel = glm::translate(matModel, glm::vec3(-200.0f,200.0f,0.0f)) * glm::scale(matModel,glm::vec3(200.0f,-200.0f,200.0f));
  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
```

Lembrando que o GLM por baixo, cria as matrizes transformações que se deseja utilizar,
  ##### Na translação:
  `glm::translate(glm::mat4(1.0f), glm::vec3(dX,dY,dZ))`
  Ele cria a matriz:
  
  ![Matriz translação](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica2/imagens/translation.png)
  
  e a multiplica pela identidade.

  ##### Na rotação:
  `glm::rotate(glm::mat4(1.0f),1.0f, glm::vec3(dX,dY,dZ))`
  Ele cria as seguintes matrizes:
  
  ![Matriz rotação](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica2/imagens/rotation.png)
  
  e as multiplicam pela identidade.

   ##### Na escala:
  `glm::scale(glm::mat4(1.0f),1.0f, glm::vec3(dX,dY,dZ))`
  Ele cria as seguinte matriz:
  
  ![Matriz escala](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica2/imagens/scale.png)
  
  e a multiplica pela identidade.

### Criando a transformação Projection
Neste parte é definida a distância da camera para a nearPlane, criando a matriz projection
```cpp
  //=-=-=-=-=-=-=-=-=-==-=- PROJECTION =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  glm::mat4 matProjection = glm::mat4(1.0f);
  float distanceCamera = 1.5f;
	matProjection[2].w = -1/distanceCamera;
	matProjection[3].z = distanceCamera;
  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
```

![Pipeline2](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica2/imagens/MVP.png)
Fonte: Imagem do código

### É calculada a matriz ModelViewProjection na seguinte linha:

```cpp
  CameraMVP = matProjection * matView * matModel;
```

### E por ultimo foi criado uma transformação
Uma rotação e uma escala são armazenados em uma matriz chamada `transformations`.
```cpp
//=-=-=-=-=-=-=-=-=-=-=-=-=-=- APPLY THE OBJECT TRANSFORMATIONS =-=-=-=-=-=-=-
  rot += 1.0;
  glm::mat4 transformations = glm::rotate(glm::mat4(1.0f), rot, glm::vec3(1.0f, 1.0f, 1.0f)) * glm::scale(glm::mat4(1.0f),glm::vec3(rot/100,rot/100,rot/100)); // create a transformation matrix to the object
```

### Aplicando a matriz no objeto 3D
Para cada ponto do objeto 3D, é multiplicada a transformação `transformations`, e a `CameraMVP`
```cpp
for(int i=0; i<objData->faceCount; i++) {
    obj_face *o = objData->faceList[i];

    //For each point of the object, apply the rotation and apply the MVP
    glm::vec4 pnt1 = CameraMVP * transformations * glm::vec4(objData->vertexList[o->vertex_index[0]]->e[0],objData->vertexList[o->vertex_index[0]]->e[1],objData->vertexList[o->vertex_index[0]]->e[2],1.0f);
    glm::vec4 pnt2 = CameraMVP * transformations * glm::vec4(objData->vertexList[o->vertex_index[1]]->e[0],objData->vertexList[o->vertex_index[1]]->e[1],objData->vertexList[o->vertex_index[1]]->e[2], 1.0f);
    glm::vec4 pnt3 = CameraMVP * transformations * glm::vec4(objData->vertexList[o->vertex_index[2]]->e[0],objData->vertexList[o->vertex_index[2]]->e[1],objData->vertexList[o->vertex_index[2]]->e[2], 1.0f);

  //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    //Draw the triangle lines
    drawTriangle(Pixel(pnt1.x,pnt1.y), Pixel(pnt2.x,pnt2.y),Pixel(pnt3.x,pnt3.y));
  }
```
Estes pontos formam um triangulo, que é renderizado na tela usando o método `drawTriangle()`

Aqui está o vídeo do resultado, clique no thumbnail para acessa-lo no Youtube, (Não se esqueça de configurar em 1080p para uma melhor experiência):

[![Vídeo exemplo](https://raw.githubusercontent.com/AraujoJordan/CG-2016-2/master/AtividadePratica2/imagens/thumbnail.png)](https://www.youtube.com/watch?v=AaCXE870PSs "Vídeo exemplo")


O código completo pode ser averiguado neste [link](https://github.com/AraujoJordan/CG-2016-2/blob/master/AtividadePratica2/codigo/src/main.cpp)
