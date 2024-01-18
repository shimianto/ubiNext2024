#include "stdafx.h"
#include "Grid.h"
#include "../../../Graphics3D/Graphics3D.h"

Grid::Grid() : initialized_(false)
{
}

void Grid::Init (const int &width, const int &height, const Vector3 &cellSize, const Vector3 &pos)
{
  initialized_ = true;
  width_ = width;
  height_ = height;
  position_ = pos;
  cellSize_ = cellSize;

  grid_.clear();

  for (int j = 0; j < height; j++) {
	for (int i = 0; i < width; i++) {
	  grid_.push_back (GridElement (position_ + Vector3 (cellSize_.x * i, cellSize_.y * j), cellSize_, 0));
	}
  }
}

GridElement &Grid::GetElement (const int &x, const int &y)
{
  return grid_[x + y*width_];
}

void Grid::DrawGrid2D()
{
  for (const auto &el : grid_) {
	Graphics3D::DrawBar (el.Get2DSurface());
  }
}
