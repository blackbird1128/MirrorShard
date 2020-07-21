#define TINYOBJLOADER_IMPLEMENTATION
#include "Model.h"
#include <stdexcept>
#include "tiny_obj_loader.h"


void Model::loadFromFile(std::string filename)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str())) {
		throw std::runtime_error(warn + err);
	}
	for (int i = 0; i < materials.size(); i++)
	{
		std::cout << materials[i].name << std::endl;
	}
	bool validTexCords = true;
	bool validNormalInformation = true;
	std::string modelNameInformation; // used to report error 
	for (auto shape : shapes)
	{
		std::size_t indexOffset = 0;
		for (std::size_t f = 0; f < shape.mesh.num_face_vertices.size(); ++f)
		{
			Triangle tr;
			int fv = shape.mesh.num_face_vertices[f];
			tinyobj::index_t &idx0 = shape.mesh.indices[indexOffset];
			tinyobj::index_t &idx1 = shape.mesh.indices[indexOffset + 1];
			tinyobj::index_t &idx2 = shape.mesh.indices[indexOffset + 2];
	

			tr.vertex0 = Vec3(attrib.vertices[3 * idx0.vertex_index + 0],
					attrib.vertices[3 * idx0.vertex_index + 1],
					attrib.vertices[3 * idx0.vertex_index + 2]);
			tr.vertex1 = Vec3(attrib.vertices[3 * idx1.vertex_index + 0],
				attrib.vertices[3 * idx1.vertex_index + 1],
				attrib.vertices[3 * idx1.vertex_index + 2]);
			tr.vertex2 = Vec3(attrib.vertices[3 * idx2.vertex_index + 0],
				attrib.vertices[3 * idx2.vertex_index + 1],
				attrib.vertices[3 * idx2.vertex_index + 2]);

			// Vertex normals
			if (idx0.normal_index != -1 || idx1.normal_index != -1 && idx2.normal_index != 1)
			{
				
				tr.vertex0Normal = Vec3(attrib.normals[3 * idx0.normal_index + 0],
					attrib.normals[3 * idx0.normal_index + 1],
					attrib.normals[3 * idx0.normal_index + 2]);
				tr.vertex1Normal = Vec3(attrib.normals[3 * idx1.normal_index + 0],
					attrib.normals[3 * idx1.normal_index + 1],
					attrib.normals[3 * idx1.normal_index + 2]);
				tr.vertex2Normal = Vec3(attrib.normals[3 * idx2.normal_index + 0],
					attrib.normals[3 * idx2.normal_index + 1],
					attrib.normals[3 * idx2.normal_index + 2]);
			}
			else
			{
				validNormalInformation = false;
				modelNameInformation = shape.name;
			}
			if (idx0.texcoord_index != -1 && idx1.texcoord_index != -1 && idx2.texcoord_index != -1)
			{
				tr.vertex0uv = Vec3(attrib.texcoords[2 * idx0.texcoord_index], attrib.texcoords[2 * idx0.texcoord_index + 1], 0);
				tr.vertex1uv = Vec3(attrib.texcoords[2 * idx1.texcoord_index], attrib.texcoords[2 * idx1.texcoord_index + 1], 0);
				tr.vertex2uv = Vec3(attrib.texcoords[2 * idx2.texcoord_index], attrib.texcoords[2 * idx2.texcoord_index + 1], 0);
			}
			else
			{
				validTexCords = false;
				modelNameInformation = shape.name;
			}
			indexOffset += fv;
			tr.computeEdges();
			triangles.push_back(tr);


		}
		if (!validNormalInformation)
		{
			std::cout << "[ERROR] model \"" << modelNameInformation << "\" don't have valid normal information \n";
		}
		if (!validTexCords)
		{
			std::cout << "[WARNING] model \"" << modelNameInformation << "\" don't have valid texture index add them or use a Color texture instead " << std::endl;
		}
	
	}

	std::cout << "triangles numbers : " << triangles.size() << "\n"; 
}

void Model::setMaterial(std::shared_ptr<Material> m)
{
	for (auto i = 0; i < triangles.size(); i++)
	{

		triangles[i].setMaterial(m);

	}
}

void Model::scale(float scaleFactor)
{
	for (int i = 0; i < triangles.size(); i++)
	{
		triangles[i].vertex0 = triangles[i].vertex0 * scaleFactor;
		triangles[i].vertex1 = triangles[i].vertex1 * scaleFactor;
		triangles[i].vertex2 = triangles[i].vertex2 * scaleFactor;
		triangles[i].computeEdges();
	}
}
