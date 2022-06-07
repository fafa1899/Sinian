// MaterialLambert.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <BoxGeometry.h>
#include <Lights/AmbientLight.h>
#include <Lights/PointLight.h>
#include <Mesh.h>
#include <MeshBasicMaterial.h>
#include <MeshLambertMaterial.h>
#include <PerspectiveCamera.h>
#include <Renderer.h>
#include <Scene.h>
#include <Texture.h>

#include <iostream>

#include <GLFW/glfw3.h>

using namespace std;
using namespace Sinian;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

const char* title = "MaterialLambert";

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

const float zoomSpeed = 0.2f;
const float MouseSensitivity = 0.1f;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// camera
shared_ptr<PerspectiveCamera> camera = nullptr;

// Renderer
shared_ptr<Renderer> renderer = nullptr;

shared_ptr<Mesh> CreateCubeMesh() {
  shared_ptr<BoxGeometry> geometry = make_shared<BoxGeometry>();

  const char* texturePath1 = "D:/MyHub/Sinian/Resources/Textures/container.jpg";

  shared_ptr<Texture> texture = Texture::ReadFile2Texture(texturePath1);
  // std::shared_ptr<MeshBasicMaterial> material =
  //    make_shared<MeshBasicMaterial>();
  std::shared_ptr<MeshLambertMaterial> material =
      make_shared<MeshLambertMaterial>();
  material->Map(texture);

  std::shared_ptr<Mesh> mesh = make_shared<Mesh>(geometry, material);

  return mesh;
}

shared_ptr<PointLight> CreatePointLight() {
  shared_ptr<PointLight> pointLight = make_shared<PointLight>();
  pointLight->WorldPosition(1.2f, 1.0f, 2.0f);

  shared_ptr<BoxGeometry> geometry = make_shared<BoxGeometry>();

  std::shared_ptr<MeshBasicMaterial> material =
      make_shared<MeshBasicMaterial>();
  material->Color(glm::vec3(1.0f, 1.0f, 1.0f));

  std::shared_ptr<Mesh> mesh = make_shared<Mesh>(geometry, material);
  mesh->LocalScale(0.2f, 0.2f, 0.2f);

  pointLight->Add(mesh);

  return pointLight;
}

shared_ptr<AmbientLight> CreateAmbientLight() {
  shared_ptr<AmbientLight> ambientLight =
      make_shared<AmbientLight>(glm::vec3(1.0f, 1.0f, 1.0f), 0.2f);
  return ambientLight;
}

int main() {
  // glfw: initialize and configure
  // ------------------------------
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow* window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  PrepareGraphicContext((LoadProc)glfwGetProcAddress);

  // camera
  camera = make_shared<PerspectiveCamera>(
      50.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
  camera->WorldModelTranform(
      glm::vec3(0.0f, 0.0f, 5.0f),
      glm::vec3(glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f)));

  shared_ptr<Scene> scene = make_shared<Scene>();
  shared_ptr<Mesh> mesh = CreateCubeMesh();

  scene->Add(mesh);

  shared_ptr<PointLight> pointLight = CreatePointLight();
  scene->Add(pointLight);

  scene->Add(CreateAmbientLight());

  // Renderer
  renderer = make_shared<Renderer>();
  renderer->SetSize(SCR_WIDTH, SCR_HEIGHT);
  renderer->SetClearColor(glm::vec4(0.05f, 0.05f, 0.05f, 1.0f));

  // render loop
  // -----------
  while (!glfwWindowShouldClose(window)) {
    // per-frame time logic
    // --------------------
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // std::cout << 1.0/deltaTime << std::endl;

    // input
    processInput(window);

    // render
    renderer->Render(scene, camera);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
    // etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  // if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  //	camera.ProcessKeyboard(FORWARD, deltaTime);
  // if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  //	camera.ProcessKeyboard(BACKWARD, deltaTime);
  // if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  //	camera.ProcessKeyboard(LEFT, deltaTime);
  // if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  //	camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width
  // and height will be significantly larger than specified on retina displays.
  renderer->SetSize(width, height);

  camera->Aspect(float(width) / height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset =
      lastY - ypos;  // reversed since y-coordinates go from bottom to top

  if (GLFW_PRESS == glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    auto euler = glm::degrees(camera->WorldEulerAngles());
    euler.y += -xoffset;
    euler.x += yoffset;

    bool constrainPitch = true;
    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch) {
      if (euler.x > 89.0f) euler.x = 89.0f;
      if (euler.x < -89.0f) euler.x = -89.0f;
    }

    camera->WorldEulerAngles(glm::radians(euler));
  } else if (GLFW_PRESS ==
             glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE)) {
    // xoffset * = ;
    // yoffset * = ;

    xoffset *= (MouseSensitivity * 0.05f);
    yoffset *= (MouseSensitivity * 0.05f);

    const auto& position = camera->WorldPosition();
    glm::vec3 moveDir = -xoffset * camera->Right() + -yoffset * camera->Up();
    camera->WorldPosition(position + moveDir);
  }

  lastX = xpos;
  lastY = ypos;
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  auto position = camera->WorldPosition();
  position += camera->Front() * static_cast<float>(yoffset) * zoomSpeed;
  camera->WorldPosition(position);
}
