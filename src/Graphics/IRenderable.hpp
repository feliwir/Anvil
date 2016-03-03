/*
************************************
* Copyright (C) 2016 ByteForge
* IRenderable.hpp
************************************
*/

#pragma once

namespace anvil
{
	/**
	 * @class	IRenderable
	 *
	 * @brief	Interface implemented by each object that is drawn on screen.
	 */
	class IRenderable
	{
	public:

		/**
		 * @fn	virtual void IRenderable::Render(int mode) = 0;
		 *
		 * @brief	Renders the given mode.
		 *
		 * @param	mode	The mode.
		 */
		virtual void Render(int mode) = 0;

		/**
		 * @fn	virtual void IRenderable::Update() = 0;
		 *
		 * @brief	Updates this object.
		 */
		virtual void Update() = 0;
	};
}