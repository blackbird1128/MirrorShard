#pragma once
#include "Triangle.h"
#include "Hitable.h"
#include "vec3.h"
#include "Material.h"
#include <memory>
#include <vector>
#include <string>
class Model // helper class to load model 
{
public:
	
	Model() = default;
	void loadFromFile(std::string filename);
	void setMaterial(std::shared_ptr<Material> m);

	std::vector<Triangle> triangles;
private:


	











};

