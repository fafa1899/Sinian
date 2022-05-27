#include "SinianApi.h"

#include <glad/glad.h>

#include <stdio.h>

void PrepareGraphicContext(LoadProc load) {
  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)(load))) {
    printf("Failed to initialize GLAD");
    return;
  }
}