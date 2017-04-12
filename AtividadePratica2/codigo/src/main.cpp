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

  clearScreen(); //Clear the screen each frame

  //CREATE MVP
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 2.0f, 100.f); //create the perspective matrix
  glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(1.7f, 1.7f, -5.0f)); // put the camera on front of the object
  View = glm::scale(View, glm::vec3(1.0f, -1.0f, 1.0f)); //Invert Y of the camera (to adjust the opengl coordinates)
  glm::mat4 Model = glm::mat4(1.0f); // create the Model matrix
  Model = glm::scale(Model, glm::vec3(1.0f, 2.0f, 2.0f)); //Scale the model to cover the object in the camera
  CameraMVP = Projection * View * Model;

  rot += 1.0+rot/100; // represent the rotation value
  glm::mat4 rotat = glm::rotate(glm::mat4(1.0f), rot, glm::vec3(1.0f, 1.0f, 1.0f)); // create a rotation matrix to the object
  for(int i=0; i<objData->faceCount; i++) {
    obj_face *o = objData->faceList[i];

    //For each point, apply the rotation and apply in the Camera space
    glm::vec4 pnt1 = CameraMVP *rotat* glm::vec4(objData->vertexList[o->vertex_index[0]]->e[0],objData->vertexList[o->vertex_index[0]]->e[1],objData->vertexList[o->vertex_index[0]]->e[2],1.0f);
    glm::vec4 pnt2 = CameraMVP *rotat* glm::vec4(objData->vertexList[o->vertex_index[1]]->e[0],objData->vertexList[o->vertex_index[1]]->e[1],objData->vertexList[o->vertex_index[1]]->e[2], 1.0f);
    glm::vec4 pnt3 = CameraMVP *rotat* glm::vec4(objData->vertexList[o->vertex_index[2]]->e[0],objData->vertexList[o->vertex_index[2]]->e[1],objData->vertexList[o->vertex_index[2]]->e[2], 1.0f);

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
	objData->load((char*)"/mnt/d/Computacao/CG/newBlog/CG-2016-2/AtividadePratica2/Files/monkey_head2.obj");

  // Ajusta a função que chama as funções do mygl.h
  DrawFunc = MyGlDraw;

  // Framebuffer scan loop.
  glutMainLoop();

  return 0;
}
