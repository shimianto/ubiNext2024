#include "stdafx.h"
#include "UI.h"
#include <App/app.h>

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
  for (const auto &text : m_uiText) {
	App::Print (
		text.position.x, 
		text.position.y, 
		text.text,
		text.color.r, text.color.g, text.color.b,
		text.font
	);
  }
}

int UI::InsertNewText (const Vector3 &position, const char *text, const Color &color, void *font)
{
  UIText newText (position, text, color, font);
  m_uiText.push_back (newText);
  return m_uiText.size() - 1; // index where text was inserted
}

int UI::InsertNewBar (const Vector3 &position, const Vector3 &size, const float &fill, const Color &color)
{
  UIBar newBar (position, size, fill, color);
  m_uiBar.push_back (newBar);
  return m_uiBar.size() - 1;
}

UIText::UIText (const Vector3 &position, const char *text, const Color &color, void *font) : 
	position (position), text (text), color (color), font (font)
{
}

UIBar::UIBar (const Vector3 &position, const Vector3 &size, const float &fill, const Color &color)
    : position (position), size (size), fill (fill), color (color)
{
}
