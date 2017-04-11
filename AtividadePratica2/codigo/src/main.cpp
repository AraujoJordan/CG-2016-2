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
void MyGlDraw(void) {

  for(int i=0; i<objData->faceCount; i++)
  {
    obj_face *o = objData->faceList[i];

    drawLine(
      Pixel(objData->vertexList[o->vertex_index[0]]->e[0],objData->vertexList[o->vertex_index[0]]->e[1]),
      Pixel(objData->vertexList[o->vertex_index[1]]->e[0],objData->vertexList[o->vertex_index[1]]->e[1]));

   drawLine(
     Pixel(objData->vertexList[o->vertex_index[1]]->e[0],objData->vertexList[o->vertex_index[1]]->e[1]),
     Pixel(objData->vertexList[o->vertex_index[2]]->e[0],objData->vertexList[o->vertex_index[2]]->e[1]));

     drawLine(
       Pixel(objData->vertexList[o->vertex_index[2]]->e[0],objData->vertexList[o->vertex_index[2]]->e[1]),
       Pixel(objData->vertexList[o->vertex_index[0]]->e[0],objData->vertexList[o->vertex_index[0]]->e[1]);
  }
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv) {
  // Inicializações.
  InitOpenGL(&argc, argv);
  InitCallBacks();
  InitDataStructures();

  objData = new objLoader();
	objData->load("/mnt/d/Computacao/CG/newBlog/CG-2016-2/AtividadePratica2/Files/monkey_head2.obj");

  // Ajusta a função que chama as funções do mygl.h
  DrawFunc = MyGlDraw;

  // Framebuffer scan loop.
  glutMainLoop();

  return 0;
}
