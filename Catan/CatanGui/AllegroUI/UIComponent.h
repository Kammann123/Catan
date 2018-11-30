#pragma once
#include "UIModel.h"
#include "UIController.h"
#include "UIView.h"
#include <list>

class  UIComponent
{
public:

  /* Constructor / Destructor */
 UIComponent(UIModel* model_ );
 ~UIComponent();

/* Getters */
 list<UIController*>& getController(void);
 UIModel* getModel(void);
 UIView* getView(void);

 /* Setters */
 void setModel(UIModel* newModel);
 void setView(UIView* newView);
 void appendController(UIController* newController);
 void removeController(UIController* thisController);
 void clearController(void);


private:
  list<UIController*> controller;
  UIModel* model;
  UIView* view;
};
