#include "BVHNode.h"
#include "AABB.h"
BVHNode::BVHNode()
{
	leftNode = nullptr;
	rightNode = nullptr;
	object = std::vector<HittablePtr>{};
	box = AABB(Vec3(-100000, -1000000, -100000), Vec3(1000000, 1000000, 100000));
}

BVHNode BVHNode::build(const std::vector<HittablePtr>& wordPart, std::size_t depth , int minNodeSize)
{
	std::cout << depth <<  "\n";
	BVHNode node;
	node.object = wordPart;
	if (depth == 0)
	{
		isRoot = true;
		box = wordPart[0]->getAABB();
		for (int i = 0; i < object.size(); i++)
		{
			box.expand(wordPart[i]->getAABB());
		}
	}

	if (node.object.size() == 0 )
	{
		return node;
	}
	if (node.object.size() == 1)
	{
		node.box = node.object[0]->getAABB();
		node.leftNode = std::make_unique<BVHNode>(BVHNode());
		node.rightNode = std::make_unique<BVHNode>(BVHNode());
		return node;
	}

	node.box = node.object[0]->getAABB();
	for (int i = 0; i < node.object.size(); i++)
	{
		node.box.expand(node.object[i]->getAABB());
	}

	Vec3 midP(0,0,0);
	for (int i = 0; i < node.object.size();i++)
	{
		midP += ((node.object[i]->getCenter()) / node.object.size());

	}
	std::vector<HittablePtr> leftObject;
	std::vector<HittablePtr> rightObject; 
	int axis = node.box.longestAxis();
	for (int i = 0; i < node.object.size(); i++)
	{
		switch (axis)
		{
		case 0:
			midP.x >= node.object[i]->getCenter().x ? rightObject.push_back(node.object[i]) : leftObject.push_back(node.object[i]);
			break;
		case 1:
			midP.y >= node.object[i]->getCenter().y ? rightObject.push_back(node.object[i]) : leftObject.push_back(node.object[i]);
			break;
		case 2:
			midP.z >= node.object[i]->getCenter().z ? rightObject.push_back(node.object[i]) : leftObject.push_back(node.object[i]);
			break;
		}

	}

	if (leftObject.size() == 0 && rightObject.size() > 0)
	{
		leftObject = rightObject;
	}
	if (rightObject.size() == 0 && leftObject.size() > 0)
	{
		rightObject = leftObject;
	}

	int matches = 0;
	for (int i = 0; i < leftObject.size(); i++)
	{
		for (int j = 0; j < rightObject.size(); j++)
		{
			if (leftObject[i].get() == rightObject[j].get())
			{
				matches += 1;
			}
		}

	}

	if (wordPart.size() > minNodeSize )
	{
		node.leftNode = std::make_unique<BVHNode>(build(leftObject, depth + 1,minNodeSize));
		node.rightNode = std::make_unique<BVHNode>(build(rightObject, depth + 1,minNodeSize));

	}
	else
	{
		node.leftNode = std::make_unique<BVHNode>(BVHNode());
		node.rightNode = std::make_unique<BVHNode>(BVHNode());
	}
	
	return node;
}

bool BVHNode::hit(Ray r, float tMin, float tMax, HitRecord& rec )
{


	if (box.hit(r))
	{
		if (leftNode->object.size() > 0 || rightNode->object.size() > 0)
		{
			HitRecord leftRec, rightRec;
			bool hitLeft = leftNode->hit(r, tMin, tMax, leftRec);
			bool hitRight = rightNode->hit(r, tMin, tMax, rightRec );
			if (hitLeft && hitRight)
			{
				if (leftRec.t < rightRec.t)
				{
					rec = leftRec;
				}
				else
				{
					rec = rightRec;
				}
				return true;
			}
			else if (hitLeft)
			{
				rec = leftRec;
				return true;
			}
			else if (hitRight)
			{
				rec = rightRec;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			bool hitAnything = false;
			double closestSoFar = tMax;
			HitRecord tempRec;
			for (int i = 0; i < object.size(); i++)
			{

				if (object[i]->hit(r, tMin, closestSoFar, tempRec))
				{
					hitAnything = true;
					closestSoFar = tempRec.t;
					rec = tempRec;
				}
			}
			return hitAnything;


		}
	}
	else
	{
		return false;
	}

}
	

	

