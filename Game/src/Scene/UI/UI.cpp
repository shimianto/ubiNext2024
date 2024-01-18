#include "stdafx.h"
#include "UI.h"
#include <App/app.h>
#include "../../Graphics3D/Graphics3D.h"

UI::UI()
{
}

void UI::Init()
{
}

void UI::Update()
{
}

void UI::Render()
{
  for (const auto &text : uiTexts_) {
	App::Print (
		text.position.x, 
		text.position.y, 
		text.text,
		text.color.r, text.color.g, text.color.b,
		text.font
	);
  }

  for (const auto &bar : uiBars_) {
	Graphics3D::DrawBar (bar);
  }
}

int UI::InsertNewText (const Vector3 &position, const char *text, const Color &color, void *font)
{
  UIText newText (position, text, color, font);
  uiTexts_.push_back (newText);
  return uiTexts_.size() - 1; // index where text was inserted
}

int UI::InsertNewBar (const Vector3 &position, const Vector3 &size, const float &fill, const Color &color)
{
  UIBar newBar (position, size, fill, color);
  uiBars_.push_back (newBar);
  return uiBars_.size() - 1;
}

UIText UI::GetTextFromId (const int &id)
{
  return uiTexts_[id];
}

UIBar UI::GetBarFromId (const int &id)
{
  return uiBars_[id];
}

void UI::UpdateTextFromId (const int &id, const UIText &text)
{
  uiTexts_[id] = text;
}

void UI::UpdateBarFromId (const int &id, const UIBar &bar)
{
  uiBars_[id] = bar;
}

UIText::UIText (const Vector3 &position, const char *text, const Color &color, void *font) : 
	position (position), text (text), color (color), font (font)
{
}

UIBar::UIBar (const Vector3 &position, const Vector3 &size, const float &fill, const Color &color)
    : position (position), size (size), fill (fill), color (color)
{
  CalculateCoords (position, size);
}

void UIBar::CalculateCoords (const Vector3 &position, const Vector3 &size)
{
  Vector3 v1, v2, v3, v4;
  v1 = position;

  v2 = position;
  v2.y += size.y;

  v3 = position + size;

  v4 = position;
  v4.x += size.x;

  coords = Quad (v1, v2, v3, v4);
}
