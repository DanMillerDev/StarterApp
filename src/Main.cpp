#include "App.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  cout << "Hello world" << endl;

  App app;

  app.Initialize();
  app.Run();
  app.Destroy();

  return 0;
}
