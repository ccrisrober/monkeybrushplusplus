#ifndef __T2__
#define __T2__

#include <Eigen/Eigen>
#include "scene/Node.hpp"
#include "scene/Component.hpp"

namespace mb
{
	class Transform2: public Component
	{
	public:
		Transform2()
		: Component()
		{
			position = Eigen::Vector3f::Zero();
			scale = Eigen::Vector3f(1.0f, 1.0f, 1.0f);

			positionWorld = Eigen::Vector3f::Zero();
			scaleWorld = Eigen::Vector3f(1.0f, 1.0f, 1.0f);

			forward = Eigen::Vector3f(0.0f, 0.0f, 1.0f);
			left = Eigen::Vector3f(1.0f, 0.0f, 0.0f);
			up = Eigen::Vector3f(0.0f, 1.0f, 0.0f);

			modelMatrix = Eigen::Matrix4f::Identity();
			modelWorldMatrix = Eigen::Matrix4f::Identity();
		}
		Eigen::Vector3f& getPosition()
		{
			return position;
		}
		Eigen::Vector3f& getScale()
		{
			return scale;
		}
		Eigen::Vector3f getPositionWorld()
		{
			return positionWorld;
		}
		Eigen::Vector3f getScaleWorld()
		{
			return scaleWorld;
		}
		void setPosition(float x, float y, float z)
		{
			setPosition(Eigen::Vector3f(x, y, z));
		}
		void setPosition(Eigen::Vector3f newPos)
		{
			position = newPos;
			_updateModelMatrix();
		}
		void translate(float x, float y, float z)
		{
			translate(Eigen::Vector3f(x, y, z));
		}
		void translate(Eigen::Vector3f diff)
		{
			setPosition(position + diff);
		}
		void translate(float dist, Eigen::Vector3f along)
		{
			setPosition(position + (dist * along.normalized()));
		}
		void lookAt(float x, float y, float z)
		{
			lookAt(Eigen::Vector3f(x, y, z));
		}
		void lookAt(Eigen::Vector3f point)
		{
			Eigen::Vector3f oldUp = getUp();
			{

			}
		}
		Eigen::Vector3f getForward() const
		{
			return forward;
		}
		Eigen::Vector3f getLeft() const
		{
			return left;
		}
		Eigen::Vector3f getUp() const
		{
			return up;
		}
	private:
		void _setPosition(const Eigen::Vector3f newPos)
		{
			position = newPos;
			_updateModelMatrix();
		}
		void _setPositionWorld(const Eigen::Vector3f newPos)
		{
			Eigen::Vector3f translation = newPos - positionWorld;

			Node* parent = this->_node->parent();
			if (parent != nullptr)
			{
				//translation = translation * Eigen::Matrix4f::inverse()
			}
			position += translation;
			_updateModelMatrix();
		}
		void _setScale(const Eigen::Vector3f newScale)
		{

		}
		
		void _updateModelMatrix()
		{
		}

		Eigen::Vector3f position;
		Eigen::Vector3f scale;

		Eigen::Vector3f positionWorld;
		Eigen::Vector3f scaleWorld;

		Eigen::Vector3f forward;
		Eigen::Vector3f left;
		Eigen::Vector3f up;

		Eigen::Matrix4f modelMatrix;
		Eigen::Matrix4f modelWorldMatrix;

		friend class Node;
	};
}

#endif