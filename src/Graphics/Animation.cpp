/*
************************************
* Copyright (C) 2016 ByteForge
* Animation.cpp
************************************
*/

#include "Animation.hpp"
#include <iostream>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "../Util.hpp"

using namespace anvil;

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::ComputeFrame(std::vector<glm::mat4> &frame_mats, const std::vector<glm::mat4> &rest_mats, std::vector<std::int32_t> &parentIDs, const long long time)
{
	int frame = time * m_framesPerMilliSecond;

	m_poses_mutex.lock();
	const auto& it = m_poses.find(frame);
	m_poses_mutex.unlock();
	if (it == m_poses.end())
	{
		std::vector<glm::mat4> mats;
		unsigned int i=0;
		for (const auto& mat :rest_mats)
		{
			glm::vec4 of = glm::vec4(GetOffsetValue(i, X, frame), GetOffsetValue(i, Y, frame), GetOffsetValue(i, Z, frame), 1.0f);
			glm::quat q = glm::quat(GetOffsetValue(i, W, frame), GetOffsetValue(i, QX, frame), GetOffsetValue(i, QY, frame), GetOffsetValue(i, QZ, frame));

			mats.push_back(glm::toMat4(q));
			//of = rest_mats[i] * of;

			mats[i][0][3] = rest_mats[i][0][3] + of.x;
			mats[i][1][3] = rest_mats[i][1][3] + of.y;
			mats[i][2][3] = rest_mats[i][2][3] + of.z;
			++i;
		}

		//do the parenting
		std::vector<glm::mat4> pivots;
		i=0;
		for(auto& mat : mats)
		{
			std::int32_t parentID = parentIDs[i];
			pivots.push_back(mat);

			//do the parenting
			while (parentID >= 0)
			{
				mat *= pivots[parentID];
				parentID = parentIDs[parentID];
			}
			mat = glm::transpose(mat);
			++i;
		}
		m_poses_mutex.lock();
		const auto& it2 = m_poses.find(frame);
		if (it == m_poses.end())
			m_poses.insert({ frame, AnimationPose(mats) });
		m_poses_mutex.unlock();
	}
}

void Animation::GetFrame(std::vector<glm::mat4> &mats, const long long time)
{
	int frame = time * m_framesPerMilliSecond;

	const auto& it = m_poses.find(frame);
	if (it != m_poses.end())
	{
		mats = it->second.GetData();
		return;
	}
}

glm::f32 Animation::GetOffsetValue(int pivotID, int type, int frame)
{
	const auto& it = m_data.find(pivotID);
	if (it != m_data.end())
	{
		const auto& it2 = it->second.find(type);
		if (it2 != it->second.end())
		{
			return it2->second->GetPoint(frame%m_numFrames);
		}
	}
	return 0.0f;
}

void Animation::AddChannel(int pivot, int type, int interpolation, std::map<int, glm::f32> frames)
{
	const auto& it = m_data.find(pivot);
	if (it == m_data.end())
	{
		std::unordered_map<int, InterpolatePtr> channels;
		InterpolatePtr interpolate = MakeLinearInterpolate();
		for(const auto& frame : frames)
		{

			interpolate->AddPoint(frame.first,frame.second);
		}
		channels.insert({ type, interpolate});
		m_data.insert({pivot, channels});
	}
	else
	{
		InterpolatePtr interpolate  = MakeLinearInterpolate();
		for(const auto& frame : frames)
		{
			interpolate->AddPoint(frame.first,frame.second);
		}
		m_data[pivot].insert({type, interpolate});
	}
}