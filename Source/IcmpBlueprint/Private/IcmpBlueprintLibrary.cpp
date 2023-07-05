// Copyright SeesePlusPlus LLC. All Rights Reserved.

#include "IcmpBlueprintLibrary.h"

#include "Icmp.h"

UIcmpBlueprintLibrary::UIcmpBlueprintLibrary(
  const FObjectInitializer& ObjectInitializer
) : Super(ObjectInitializer) {
  //
}

void UIcmpBlueprintLibrary::Ping(
  FString TargetAddress,
  float Timeout,
  FIcmpPingResult ResultDelegate
) {
  FIcmp::IcmpEcho(
    TargetAddress,
    Timeout,
    [TargetAddress, ResultDelegate](FIcmpEchoResult Result) {
      ResultDelegate.ExecuteIfBound(TargetAddress, Result.Time);
    }
  );
}