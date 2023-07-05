// Copyright SeesePlusPlus LLC. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "IcmpBlueprintLibrary.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FIcmpPingResult, FString, TargetAddress, float, RTT);

UCLASS()
class UIcmpBlueprintLibrary : public UBlueprintFunctionLibrary {
  GENERATED_UCLASS_BODY()

  /** Sends one or more pings to the TargetAddress.
   *
   * @param Targets the target addresses to ping
   * @param Timeout max time to wait for a reply in seconds
   */
   UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Ping Host",
      Keywords = "ICMP ping echo"
    ),
    Category = "ICMP"
  )
  static void Ping(
    FString TargetAddress,
    float Timeout,
    FIcmpPingResult ResultDelegate
  );
};
