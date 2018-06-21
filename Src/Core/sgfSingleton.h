#pragma once
/********************************************************************
	created:	2018/06/21
	created:	21:6:2018   19:07
	filename: 	E:\SimpleGameFramework\Src\Core\sgfSingleton.h
	file path:	E:\SimpleGameFramework\Src\Core
	file base:	sgfSingleton
	file ext:	h
	author:		Xiexuelong
	
	purpose:	
*********************************************************************/

namespace sgf
{
	template<typename T>
	class TSingleton
	{
	public:
		static T&	Instance()
		{
			static T fs_instance;
			return fs_instance;
		}
	};
}
