**资源导入**：从外部导入资源时，不能直接往UnrealEngine的Content Browser窗口拖，而是将资源文件夹拷贝到Content文件夹。

### 生成不可销毁的障碍物

1 添加一个生成类，在头文件中定义如下变量：

```cpp
private:
	UPROPERTY(EditAnywhere, Category = "Block Generation")
	TSubclassOf<AUnBreakableBlock> UnBreakableBlock;
	UPROPERTY(EditAnywhere, Category = "Block Generation | Settings")
	int Width;
	UPROPERTY(EditAnywhere, Category = "Block Generation | Settings")
	int Height;
	UPROPERTY(EditAnywhere, Category = "Block Generation | Settings")
	float Scale;
```

**注意**：用TSubclassof来作安全限定，这样在蓝图类中只能设置指定类型。

2 调用SpawnActor来生成障碍物

```cpp
void ABlockGeneration::SpawnUnBreakableBlock()
{
	for (int i = 0; i < Width; ++i)
	{
		for (int j = 0; j < Height; ++j)
		{
			if ((i % 2) && (j % 2))
			{
				FVector position = FVector(i - 7, j - 7, 0) * Scale;
				GetWorld()->SpawnActor<AUnBreakableBlock>(UnBreakableBlock, position, FRotator::ZeroRotator);
			}		
		}
	}
}
```

也可在代码中设置要生成的Actor，这样就不用在蓝图类中手动设置。

```cpp
ABlockGeneration::ABlockGeneration() : Width(15), Height(15), Scale(100.0f)
{
	PrimaryActorTick.bCanEverTick = true;
    // 路径不要写错了,Game前面也需要/
	static ConstructorHelpers::FClassFinder<AUnBreakableBlock> UBBlock(TEXT("/Game/Blueprints/BP_UnBreakableBlock"));
	UnBreakableBlock = UBBlock.Class;
	static ConstructorHelpers::FClassFinder<ABreakableBlock> BBlock(TEXT("/Game/Blueprints/BP_BreakableBlock"));
	BreakableBlock = BBlock.Class;
}
```

### 设置相机视角

1 新建一个继承自CameraActor的类，命名为MainCamera。

2 在MainCamera类中添加一个PlayerController对象和BeginPlayer虚函数，并通过该对象来将自身设为视场相机

```cpp
#include "Kismet/GameplayStatics.h"

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTargetWithBlend(this, 0);
}
```

### 在编辑模式下画点

1 将Tick事件改为编辑模式也能触发

```cpp
PrimaryActorTick.bCanEverTick = WITH_EDITOR; //原本是true
```

2 重写ShouldTickIfViewportsOnly函数

```cpp
bool ABlockGeneration::ShouldTickIfViewportsOnly() const
{
	return WITH_EDITOR;
}
```

3 调用DrawDebugPoint函数画点

```cpp
void ABlockGeneration::DrawDebugPos(const FVector & pos, const FLinearColor & color)
{
	UKismetSystemLibrary::DrawDebugPoint(this, pos, 20.0f, color);
}
```

4 在Tick函数中调用DrawDebugPos

```cpp
void ABlockGeneration::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDrawDebug)	// 用来开启或关闭
	{
		for (auto&point : SpawnPos)
		{
			DrawDebugPos(point, ValidColor);
		}
		for (auto&point : IgnoredPos)
		{
			DrawDebugPos(point, InValidColor);
		}
	}
}
```

**注意**：由于Spawn中的值要游戏开始才会初始化，所以要将初始化的函数声明为可在蓝图类中调用

```cpp
UFUNCTION(BlueprintCallable)
void InitValidPosition();
```

![](D:\Unreal\Pictures\022.png)

### 创建人物

1 新建一个继承自Character的类，并为人物添加移动功能

```cpp
void ABombManCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(FVector::ForwardVector, AxisValue);
}

void ABombManCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(FVector::RightVector, AxisValue);
}
```

2 修改属性让人物模型能跟着移动转向。

![](D:\Unreal\Pictures\023.png)

![](D:\Unreal\Pictures\024.png)

### 多玩家控制

1 新加一个继承自GameViewportClient的类（BombManMPGameViewportClient），重写输入函数，因为引擎默认只会响应id为0的角色的控制。

```cpp
//bool UBombManMPGameViewportClient::InputKey(FViewport* InViewport, int32 ControllerId, FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad)
bool UBombManMPGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	if (IgnoreInput() || EventArgs.IsGamepad() || EventArgs.Key.IsMouseButton())
	{
		return Super::InputKey(EventArgs);
	}
	else
	{
		UEngine* const Engine = GetOuterUEngine();
		const int32 NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
		bool bRet = true;
		FInputKeyEventArgs inputParams = FInputKeyEventArgs(EventArgs);
		for (int32 i = 0; i < NumPlayers; ++i)
		{
			inputParams.ControllerId = i;
			bRet = Super::InputKey(inputParams) && bRet;
		}
		return bRet;
	}
}

bool UBombManMPGameViewportClient::InputAxis(FViewport * InViewport, int32 ControllerId, FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	if (IgnoreInput() || bGamepad || Key.IsMouseButton())
	{
		return Super::InputAxis(InViewport, ControllerId, Key, Delta, DeltaTime, NumSamples, bGamepad);
	}
	else
	{
		UEngine* const Engine = GetOuterUEngine();
		const int32 NumPlayers = Engine ? Engine->GetNumGamePlayers(this) : 0;
		bool bRet = true;
		for (int32 i = 0; i < NumPlayers; ++i)
		{
			bRet = Super::InputAxis(InViewport, i, Key, Delta, DeltaTime, NumSamples, bGamepad) && bRet;
		}
		return bRet;
	}
}
```

**注意**：重写Input Key函数时，上面代码注释的重载函数在UE4.24.3中不能重写，只能用下面那个结构体为参数的重载函数。这两个函数的作用相当于让系统再去处理其它ControllerId的输入信息。

2 在项目设置中将GameViewportClientClass设置为新添加的类BombManMPGameViewportClient

3 在项目设置中将分屏关闭（取消勾选Use Splitscreen）。

4 新添加一个PlayerController类（BombManPlayerController）

```cpp
UCLASS()
class BOMBMAN_API ABombManPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

private:
	APawn* Pawn;
};
```

```cpp
void ABombManPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

    // 根据不同的id来绑定不同的输入
	int32 id = GetLocalPlayer()->GetControllerId();
	if (id == 0)
	{
		InputComponent->BindAxis("MoveForward_P1", this, &ABombManPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight_P1", this, &ABombManPlayerController::MoveRight);
	}
	else if (id == 1)
	{
		InputComponent->BindAxis("MoveForward_P2", this, &ABombManPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight_P2", this, &ABombManPlayerController::MoveRight);
	}
}

void ABombManPlayerController::MoveForward(float AxisValue)
{
    // 每次都要获取当前控制
	Pawn = GetPawn();
	if (Pawn)
	{
		Pawn->AddMovementInput(FVector::ForwardVector, AxisValue);
	}
}

void ABombManPlayerController::MoveRight(float AxisValue)
{
	Pawn = GetPawn();
	if (Pawn)
	{
		Pawn->AddMovementInput(FVector::RightVector, AxisValue);
	}
}
```

5 在项目设置中将Player Controller设置为BombManPlayerController，并且设置好Axis Mappings

6 在BP_BombManGameMode蓝图类中设置在BeginPlay事件中创建玩家二

![](D:\Unreal\Pictures\025.png)

### 游戏中获取游戏模式的两种方式

```cpp
AMyGameMode *GM = GetWorld()->GetAuthGameMode<AMyGameMode>();
UGameplayStatics::GetGameMode(UObject* WorldContextObject);
```

后者是对前者的封装