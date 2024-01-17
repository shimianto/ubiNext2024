#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include "../../Graphics3D/Color/Color.h"
#include "../../Math/Vector3/Vector3.h"
#include "../../../glut/include/GL/freeglut_std.h"
#include "../../Math/Quad/Quad.h"

struct UIText
{
  Vector3 position;
  const char *text;
  Color color;
  void *font;

  UIText (const Vector3 &position = Vector3(), const char *text = "", const Color &color = Color(), void *font = GLUT_BITMAP_TIMES_ROMAN_24);
};

struct UIBar
{
  Vector3 position;
  Vector3 size;
  float fill;
  Color color;
  Quad coords;

  UIBar (const Vector3 &position = Vector3(), const Vector3 &size = Vector3 (1, 1), const float &fill = 1, const Color &color = Color());
  void CalculateCoords (const Vector3 &position, const Vector3 &size);
};

class UI
{
  private:
  std::vector<UIText> m_uiText;
  std::vector<UIBar> m_uiBar;

  public:
  
      UI();
      void Init();
      void Update();
      void Render();

      int InsertNewText (const Vector3 &position = Vector3(), const char *text = "", const Color &color = Color(), void *font = GLUT_BITMAP_TIMES_ROMAN_24);
      int InsertNewBar (const Vector3 &position = Vector3(), const Vector3 &size = Vector3 (1, 1), const float &fill = 1, const Color &color = Color());

      UIText GetTextFromId (const int &id);
      UIBar GetBarFromId (const int &id);

      void UpdateTextFromId (const int &id, const UIText &text);
      void UpdateBarFromId (const int &id, const UIBar &bar);
};
