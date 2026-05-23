// Copyright Spencer Kotrosa
/*-------------------------------------------------------------------------*/
#pragma once
#include "Modules/ModuleManager.h"
/*-------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------*/
/*   Class Functionality                                                   */
/*-------------------------------------------------------------------------*/
#pragma region ClickyUI_ClickyUI.h_Class
class FClickyUIModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
#pragma endregion
/*-------------------------------------------------------------------------*/
