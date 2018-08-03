#pragma once
/*************************************
	created: 2018/08/03 07:30 
	filename:	G:\Visual Studio 2015\SimpleGameFrame\Game\SGF\demoWorld.h
	file path:	G:\Visual Studio 2015\SimpleGameFrame\Game\SGF
	file base:	demoWorld
	file ext:	h	
	author: 	Xiexuelong
	
	purpose:
*************************************/

class DemoObject
{
public:
	DemoObject();
	virtual ~DemoObject();
	void	Draw();
};

class DemoGameworld : public sgf::GameWorld
{

public:
	DemoGameworld();
	virtual ~DemoGameworld();
	virtual void Initialize() override;
	virtual void Update() override;
private:
	DemoObject*	m_pObject;
};