#include "stdafx.h"
#include "Mesh.h"

#include <string>
#include <fstream>
#include <strstream>
#include <App/app.h>

using namespace std;

vector<Triangle> Mesh::LoadTrianglesFromObjectFile (string fileName)
{
  triangles.clear();

  ifstream f (fileName);
  if (!f.is_open())
	return triangles;

  vector<Vector3> vertices;

  while (!f.eof()) {
	char line[128];
	f.getline (line, 128);

	strstream s;
	s << line;

	char junk;

	if (line[0] == 'v') {
	  Vector3 v;
	  s >> junk >> v.x >> v.y >> v.z;
	  vertices.push_back (v);
	}

	if (line[0] == 'f') {
	  int f[3];
	  s >> junk >> f[0] >> f[1] >> f[2];
	  triangles.push_back ({vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1]});
	}
  }

  return triangles;
}
