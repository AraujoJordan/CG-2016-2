#include "main.h"
#include "definitions.h"
#include "Pixel.h"
#include "mygl.h"
#include "objLoader.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

objLoader *objData;

//-----------------------------------------------------------------------------

glm::mat4 camera(glm::vec3 Translate, glm::vec2 const & Rotate) {
  glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 100.f);
  glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(Translate.x, Translate.y, Translate.z));
  View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
  View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
  return Projection * View * Model;
}

void MyGlDraw(void) {

  glm::mat4 CameraMVP = camera(glm::vec3(2.0f, 2.0f, -5.0f),glm::vec2(0.0f, 0.0f));

  for(int i=0; i<objData->faceCount; i++) {
    obj_face *o = objData->faceList[i];

    glm::vec4 pnt1 = CameraMVP * glm::vec4(objData->vertexList[o->vertex_index[0]]->e[0],objData->vertexList[o->vertex_index[0]]->e[1],objData->vertexList[o->vertex_index[0]]->e[2],1.0f);
    glm::vec4 pnt2 = CameraMVP * glm::vec4(objData->vertexList[o->vertex_index[1]]->e[0],objData->vertexList[o->vertex_index[1]]->e[1],objData->vertexList[o->vertex_index[1]]->e[2], 1.0f);
    glm::vec4 pnt3 = CameraMVP * glm::vec4(objData->vertexList[o->vertex_index[2]]->e[0],objData->vertexList[o->vertex_index[2]]->e[1],objData->vertexList[o->vertex_index[2]]->e[2], 1.0f);

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
	objData->load((char*)"/mnt/d/Computacao/CG/newBlog/CG-2016-2/AtividadePratica2/Files/man.obj");

  // Ajusta a função que chama as funções do mygl.h
  DrawFunc = MyGlDraw;

  // Framebuffer scan loop.
  glutMainLoop();

  return 0;
}
