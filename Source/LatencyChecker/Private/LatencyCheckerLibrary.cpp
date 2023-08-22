// Copyright Incanta Games. All Rights Reserved.

#include "LatencyCheckerLibrary.h"

#include "Icmp.h"
#include "Http.h"
#include "WebSocketsModule.h"
#include "IWebSocket.h"
#include "Misc/Guid.h"

ULatencyCheckerLibrary::ULatencyCheckerLibrary(
  const FObjectInitializer& ObjectInitializer
) : Super(ObjectInitializer) {
  //
}

void ULatencyCheckerLibrary::PingIcmp(
  FString TargetAddress,
  float Timeout,
  FPingResult ResultDelegate
) {
  FIcmp::IcmpEcho(
    TargetAddress,
    Timeout,
    [TargetAddress, ResultDelegate](FIcmpEchoResult Result) {
      ResultDelegate.ExecuteIfBound(TargetAddress, Result.Time);
    }
  );
}

void ULatencyCheckerLibrary::PingHttp(
  FString TargetAddress,
  float Timeout,
  FPingResult ResultDelegate
) {
  TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
  Request->SetVerb("GET");
  Request->SetURL(TargetAddress);
  double RequestStartTime = FPlatformTime::Seconds();
  Request->OnProcessRequestComplete().BindLambda([RequestStartTime, ResultDelegate, TargetAddress](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess)
  {
    double RequestEndTime = FPlatformTime::Seconds();
    double ResponseTime = RequestEndTime - RequestStartTime;
    if (bSuccess && Response.IsValid())
    {
      ResultDelegate.ExecuteIfBound(TargetAddress, ResponseTime);
    }
    else
    {
      ResultDelegate.ExecuteIfBound(TargetAddress, -1);
    }
  });

  Request->ProcessRequest();
}

void ULatencyCheckerLibrary::PingWebSockets(
  FString TargetAddress,
  float Timeout,
  int Attempts,
  FPingResult ResultDelegate
) {
  TSharedPtr<IWebSocket> WebSocket = FWebSocketsModule::Get().CreateWebSocket(TargetAddress);

  if (Attempts < 1 ) {
    ResultDelegate.ExecuteIfBound(TargetAddress, -1);
    return;
  }

  double * ResponseTimes = new double[Attempts];
  int * NextAttempt = new int;
  NextAttempt[0] = 0;
  for (int i = 0; i < Attempts; i++) {
    ResponseTimes[i] = 0;
  }

  WebSocket->OnConnectionError().AddLambda([TargetAddress, ResultDelegate](const FString& Error) {
    UE_LOG(LogTemp, Display, TEXT("WebSocket connection error: %s"), *Error);
    ResultDelegate.ExecuteIfBound(TargetAddress, -1);
  });
  WebSocket->OnConnected().AddLambda([WebSocket]() {
    UE_LOG(LogTemp, Display, TEXT("WebSocket connected"));
    double Now = FPlatformTime::Seconds();
    FString Message = FString::SanitizeFloat(Now, 6);
    WebSocket->Send(Message);
  });
  WebSocket->OnMessage().AddLambda([
    WebSocket,
    TargetAddress,
    ResponseTimes,
    NextAttempt,
    Attempts,
    ResultDelegate
  ](const FString& Message) mutable {
    if (Message.StartsWith(TEXT("Request served by ")) || ResponseTimes == nullptr || NextAttempt == nullptr) {
      return;
    }

    double Now = FPlatformTime::Seconds();
    double OriginalTime = FCString::Atod(*Message);

    double ResponseTime = Now - OriginalTime;

    int Index = *NextAttempt;
    ResponseTimes[Index] = ResponseTime;
    *NextAttempt = Index + 1;

    if (Index + 1 >= Attempts) {
      double Total = 0;
      for (int i = 0; i < Attempts; i++) {
        Total += ResponseTimes[i];
      }
      double RTT = Total / Attempts;

      ResultDelegate.ExecuteIfBound(TargetAddress, RTT);

      if (ResponseTimes != nullptr) {
        delete[] ResponseTimes;
        ResponseTimes = nullptr;
      }

      if (NextAttempt != nullptr) {
        delete NextAttempt;
        NextAttempt = nullptr;
      }

      if (WebSocket.IsValid()) {
        if (WebSocket->IsConnected()) {
          WebSocket->Close();
        }

        WebSocket->OnConnectionError().Clear();
        WebSocket->OnConnected().Clear();
        WebSocket->OnMessage().Clear();
      }
    } else {
      double Now2 = FPlatformTime::Seconds();
      FString Message2 = FString::SanitizeFloat(Now2, 6);
      WebSocket->Send(Message2);
    }
  });

  WebSocket->Connect();
}
