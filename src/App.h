#ifndef APP
#define APP

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

class App {
public:
  App();
  ~App();
  // Setup
  void Initialize();
  void Run();
  void Destroy();

  // Update loop
  void ProcessInput();
  void Update();
  void Render();

  // IMGUI
  void SetupIMGUI();
  void RenderIMGUIFrame();
  void SetIMGUIStyle();
  void StarterIMGUI();

  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *starterTexture;

  bool isRunning;

private:
  int windowWidth = 1024;
  int windowHeight = 1024;
  const char *starterImage = "assets/starter.png";
  const char *windowName = "App";
  int sliderValue = 0;
  char textBuffer[128] = "";
};

#endif
