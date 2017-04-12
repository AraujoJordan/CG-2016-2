#include "main.h"
#include "definitions.h"
#include "Pixel.h"
#include "mygl.h"
#include "objLoader.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

objLoader *objData;
glm::mat4 CameraMVP;

float rot = 0.0f;

//-----------------------------------------------------------------------------

void clearScreen() {
  int color[4] = {0,0,0,255};
  for(int i=0;i<=IMAGE_WIDTH;i++)
    for(int j=0;j<=IMAGE_HEIGHT;j++)
      putPixel(Pixel(i,j,color));
}

void MyGlDraw(void) {

  clearScreen();

  // View
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

  // Model
  glm::mat4 matModel = glm::mat4(1.0f);
  matModel = glm::translate(matModel, glm::vec3(-200.0f,200.0f,0.0f)) * glm::scale(matModel,glm::vec3(200.0f,-200.0f,200.0f));

  // Projection
  glm::mat4 matProjection = glm::mat4(1.0f);
  float distanceCamera = 1.5f;
	matProjection[2].w = -1/distanceCamera;
	matProjection[3].z = distanceCamera;

  // Perspective
  // glm::mat4 transPersp = glm::mat4(1.0f);
  // transPersp[3] = glm::vec4((IMAGE_WIDTH-1)/2,(IMAGE_HEIGHT-1)/2, 0.0f, 1.0f);
  //
  // glm::mat4 scalePersp = glm::mat4(1.0f);
  // scalePersp[0].x = IMAGE_WIDTH/2;
  // scalePersp[1].y = IMAGE_HEIGHT/2;
  //
  // glm::mat4 InvertY = glm::mat4(1.0f);
  // InvertY[1].y = -1.0f;
  //
  // glm::mat4 matScreen = transPersp * scalePersp * InvertY;

  CameraMVP = matProjection * matView * matModel;
  // std::cout<<glm::to_string(CameraMVP)<<std::endl;

  //CALCULTE MODELS
  rot += 1.0; // represent the rotation value
  glm::mat4 model = glm::rotate(glm::mat4(1.0f), rot, glm::vec3(1.0f, 1.0f, 1.0f)) * glm::scale(glm::mat4(1.0f),glm::vec3(rot/100,rot/100,rot/100)); // create a rotation matrix to the object

  for(int i=0; i<objData->faceCount; i++) {
    obj_face *o = objData->faceList[i];

    //For each point, apply the rotation and apply in the Camera space
    glm::vec4 pnt1 = CameraMVP *model* glm::vec4(objData->vertexList[o->vertex_index[0]]->e[0],objData->vertexList[o->vertex_index[0]]->e[1],objData->vertexList[o->vertex_index[0]]->e[2],1.0f);
    glm::vec4 pnt2 = CameraMVP *model* glm::vec4(objData->vertexList[o->vertex_index[1]]->e[0],objData->vertexList[o->vertex_index[1]]->e[1],objData->vertexList[o->vertex_index[1]]->e[2], 1.0f);
    glm::vec4 pnt3 = CameraMVP *model* glm::vec4(objData->vertexList[o->vertex_index[2]]->e[0],objData->vertexList[o->vertex_index[2]]->e[1],objData->vertexList[o->vertex_index[2]]->e[2], 1.0f);

    //Draw the triangle lines
    drawTriangle(Pixel(pnt1.x,pnt1.y), Pixel(pnt2.x,pnt2.y),Pixel(pnt3.x,pnt3.y));
  }
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv) {

  // Inicializações.
  InitOpenGL(&argc, argv);
  InitCallBacks();
  InitDataStructures();

  objData = new objLoader();
	objData->load((char*)"/mnt/d/Computacao/CG/newBlog/CG-2016-2/AtividadePratica2/Files/pine.obj");

  // Ajusta a função que chama as funções do mygl.h
  DrawFunc = MyGlDraw;

  // Framebuffer scan loop.
  glutMainLoop();

  return 0;
}
