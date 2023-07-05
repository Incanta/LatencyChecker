// Copyright SeesePlusPlus LLC. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogIcmpBlueprint, Log, All);

class FIcmpBlueprintModule : public IModuleInterface {
public:

  /** IModuleInterface implementation */
  virtual void StartupModule() override;
  virtual void ShutdownModule() override;
};