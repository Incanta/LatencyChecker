// Copyright Incanta Games. All Rights Reserved.

#include "LatencyChecker.h"

#define LOCTEXT_NAMESPACE "FLatencyCheckerModule"

DEFINE_LOG_CATEGORY(LogLatencyChecker);

void FLatencyCheckerModule::StartupModule() {
  // This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FLatencyCheckerModule::ShutdownModule() {
  // This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
  // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLatencyCheckerModule, LatencyChecker)
