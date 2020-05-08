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
			tr.vertex0Normal = Vec3(attrib.normals[3 * idx0.normal_index + 0],
				attrib.normals[3 * idx0.normal_index + 1],
				attrib.normals[3 * idx0.normal_index + 2]);
			tr.vertex1Normal = Vec3(attrib.normals[3 * idx1.normal_index + 0],
				attrib.normals[3 * idx1.normal_index + 1],
				attrib.normals[3 * idx1.normal_index + 2]);
			tr.vertex2Normal = Vec3(attrib.normals[3 * idx2.normal_index + 0],
				attrib.normals[3 * idx2.normal_index + 1],
				attrib.normals[3 * idx2.normal_index + 2]);
			indexOffset += fv;
			tr.computeEdges();
			triangles.push_back(tr);


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
