#include "sgfPCH.h"
#include "demoWorld.h"

DemoGameworld::DemoGameworld()
	:m_pObject(NULL)
{
	
}

//----------------------------------------
DemoGameworld::~DemoGameworld()
{
	SAFE_DELETE(m_pObject);
}

//----------------------------------------
void DemoGameworld::Initialize()
{
	m_pObject = new DemoObject();
	sgf::RHIDevice::Init();
}

//----------------------------------------
void DemoGameworld::Update()
{
	sgf::RHIDevice::Tick();
	m_pObject->Draw();
}

//----------------------------------------
//////////////////////////////////////////
//DemoObject
//////////////////////////////////////////
//----------------------------------------
DemoObject::DemoObject()
{

}

//----------------------------------------
DemoObject::~DemoObject()
{

}

//----------------------------------------
void 
DemoObject::Draw()
{
	
}
