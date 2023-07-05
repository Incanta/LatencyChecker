// Copyright SeesePlusPlus LLC. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "IcmpBlueprintLibrary.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FIcmpPingResult, FString, TargetAddress, float, RoundTripTime);

UCLASS()
class UIcmpBlueprintLibrary : public UBlueprintFunctionLibrary {
  GENERATED_UCLASS_BODY()

  /** Sends a single ping to the TargetAddress and calls ResultDelegate when finished.
   *
   * @param TargetAddress The target address to ping; can be an IP address or resolvable hostname
   * @param Timeout The max time to wait for a reply in seconds
   * @param ResultDelegate An event that is called when the ping has finished
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
