#pragma once
#include "../../MVC/Observer.h"
#include "WindowsUI.h"

class UIView : public Observer
{
public:

 UIView(WindowsUI* interface_);
 ~UIView();

  /*
  * draw()
  * Método que dibuja el objeto en pantalla
  */
  virtual void draw(void) = 0;

private:
  WindowsUI* interface;

};
