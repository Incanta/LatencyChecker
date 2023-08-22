// Copyright Incanta Games. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "LatencyCheckerLibrary.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FPingResult, FString, TargetAddress, float, RTT);

UCLASS()
class ULatencyCheckerLibrary : public UBlueprintFunctionLibrary {
  GENERATED_UCLASS_BODY()

  /** Sends one or more pings to the TargetAddress.
   *
   * @param Targets the target addresses to ping
   * @param Timeout max time to wait for a reply in seconds
   */
   UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Ping Host (ICMP)",
      Keywords = "ICMP ping echo"
    ),
    Category = "Latency"
  )
  static void PingIcmp(
    FString TargetAddress,
    float Timeout,
    FPingResult ResultDelegate
  );

   UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Ping Host (HTTP)",
      Keywords = "HTTP ping echo"
    ),
    Category = "Latency"
  )
  static void PingHttp(
    FString TargetAddress,
    float Timeout,
    FPingResult ResultDelegate
  );



   UFUNCTION(
    BlueprintCallable,
    meta = (
      DisplayName = "Ping Host (WebSockets)",
      Keywords = "WebSocket WS ping echo"
    ),
    Category = "Latency"
  )
  static void PingWebSockets(
    FString TargetAddress,
    float Timeout,
    int Attempts,
    FPingResult ResultDelegate
  );
};
