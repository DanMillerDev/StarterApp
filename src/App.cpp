#include "App.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl3.h"
#include "imgui/imgui_impl_sdlrenderer3.h"
#include <iostream>

using namespace std;

App::App() { isRunning = false; }
App::~App() {}

void App::Initialize() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s",
                 SDL_GetError());
  }

  if (!SDL_CreateWindowAndRenderer(windowName, windowWidth, windowHeight,
                                   SDL_WINDOW_RESIZABLE, &window, &renderer)) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Couldn't initialize window and renderer: %s", SDL_GetError());
  }

  starterTexture = IMG_LoadTexture(renderer, starterImage);
  if (!starterTexture) {
    SDL_Log("Couldn't load starter image");
  }

  SetupIMGUI();

  isRunning = true;
}

void App::Run() {
  while (isRunning) {
    ProcessInput();
    Update();
    Render();
  }
}

void App::Destroy() {
  ImGui_ImplSDLRenderer3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyTexture(starterTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();
}

void App::ProcessInput() {
  SDL_Event event;
  SDL_PollEvent(&event);
  ImGui_ImplSDL3_ProcessEvent(&event);
  ImGuiIO &io = ImGui::GetIO();

  float mouseX, mouseY;
  const int buttons = SDL_GetMouseState(&mouseX, &mouseY);

  io.MousePos = ImVec2(mouseX, mouseY);
  io.MouseDown[0] = buttons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT);
  io.MouseDown[1] = buttons & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT);

  // call class speciific input functions here

  if (event.type == SDL_EVENT_QUIT) {
    isRunning = false;
  }
}

void App::Update() {}

void App::Render() {
  // main window
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);

  SDL_RenderTexture(renderer, starterTexture, NULL, NULL);

  // call class specific render functions here

  RenderIMGUIFrame();
  SDL_RenderPresent(renderer);
}

void App::SetupIMGUI() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer3_Init(renderer);

  SetIMGUIStyle();
}

void App::RenderIMGUIFrame() {
  ImGui_ImplSDLRenderer3_NewFrame();
  ImGui_ImplSDL3_NewFrame();

  ImGui::NewFrame();

  // call class specific render IMGUI functions here
  StarterIMGUI();

  ImGui::Render();

  ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
}

void App::SetIMGUIStyle() {
  ImGuiStyle &style = ImGui::GetStyle();
  ImVec4 *colors = style.Colors;

  // Text and backgrounds
  colors[ImGuiCol_Text] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f); // Dark gray text
  colors[ImGuiCol_WindowBg] =
      ImVec4(0.98f, 0.98f, 0.98f, 1.00f); // Very light background

  // Buttons
  colors[ImGuiCol_Button] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);

  // Sliders
  colors[ImGuiCol_FrameBg] =
      ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // Slider bar background
  colors[ImGuiCol_FrameBgHovered] =
      ImVec4(0.93f, 0.93f, 0.93f, 1.00f); // On hover
  colors[ImGuiCol_FrameBgActive] =
      ImVec4(0.85f, 0.85f, 0.85f, 1.00f); // On drag
  colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);

  // Optional: borders and scrollbars
  colors[ImGuiCol_Border] = ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.70f, 0.70f, 0.70f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

  style.FrameRounding = 6.0f;         // Rounded corners
  style.GrabRounding = 4.0f;          // Slider thumb
  style.FramePadding = ImVec2(10, 6); // Padding inside buttons/sliders
  style.ItemSpacing = ImVec2(10, 10);
}
void App::StarterIMGUI() {
  // setup full size window
  ImGui::SetNextWindowPos(ImVec2(0, 0));
  ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
  ImVec2 buttonSize = ImVec2(120, 40);

  // No title bar, no background, no inputs, no borders
  ImGui::Begin("##invisible_button_window", nullptr,
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                   ImGuiWindowFlags_NoSavedSettings |
                   ImGuiWindowFlags_NoBackground);

  // buttons
  ImGui::SetCursorScreenPos(ImVec2(10, 10));
  if (ImGui::Button("Test Button 1", buttonSize)) {
    cout << "Button 1 pressed" << endl;
  }

  ImVec2 contentSize = ImGui::GetContentRegionAvail();
  ImVec2 centerPos;
  centerPos.x = (contentSize.x - buttonSize.x) * 0.5f + ImGui::GetCursorPosX();
  centerPos.y = (contentSize.y - buttonSize.y) * 0.5f + ImGui::GetCursorPosY();
  ImGui::SetCursorScreenPos(centerPos);
  if (ImGui::Button("Test Button 2", buttonSize)) {
    cout << "Button 2 pressed" << endl;
  }

  // extras
  ImGui::SetCursorScreenPos(ImVec2(10, 60));
  ImGui::SliderInt("Slider", &sliderValue, 0, 10);

  ImGui::SetCursorScreenPos(ImVec2(10, 100));
  ImGui::InputText("Text Field", textBuffer, IM_ARRAYSIZE(textBuffer));

  ImGui::End();
}
