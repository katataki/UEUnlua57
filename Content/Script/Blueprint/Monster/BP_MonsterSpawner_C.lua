--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_MonsterSpawner_C
local BP_MonsterCharacter_C = UnLua.Class()

-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

--BeginPlay每2s定时生成怪物
function BP_MonsterCharacter_C:ReceiveBeginPlay()
    if not self:HasAuthority() then
        return 
    end
     -- 加载蓝图类（注意加 _C 后缀）
    local BPClass = UE.UClass.Load("/Game/BP_MyGameInstanceSubsystem.BP_MyGameInstanceSubsystem_C")
    local Subsystem = UE.USubsystemBlueprintLibrary.GetGameInstanceSubsystem(self, BPClass)

    if Subsystem then
        print("子系统",Subsystem:GetName(),"初始玩家数",Subsystem.InitialPlayerNum)
        local PlayerCount = Subsystem.InitialPlayerNum
    else
        print("没有子系统")
    end
    
    --记录初始玩家数
    -- local PC = UE.UGameplayStatics.GetPlayerController(self, 0)
    -- print('记录初始玩家数',)
    -- local GameMode = UE.UGameplayStatics.GetGameMode(self)
    -- local PlayerCount = GameMode:GetNumPlayers()
    print('记录初始玩家数',PlayerCount)

    self.MonsterClass = UE4.UClass.Load("/Game/Blueprint/Monster/BP_MonsterCharacter.BP_MonsterCharacter_C")
    self.OriginLocation = UE4.FVector(450,420,108)
    self.MonsterLocation = UE4.FVector()

    UE4.UKismetSystemLibrary.K2_SetTimerDelegate({self, BP_MonsterCharacter_C.OnTimerGenMonster}, 2, true)
end

-- function M:ReceiveEndPlay()
-- end

-- function M:ReceiveTick(DeltaSeconds)
-- end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function M:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function M:ReceiveActorEndOverlap(OtherActor)
-- end

function BP_MonsterCharacter_C:OnTimerGenMonster()
    if GameMgr.IsPause then
        return
    end
    local PlayerCharacter = UE4.UGameplayStatics.GetPlayerCharacter(self, 0)
    if PlayerCharacter == nil then
        return
    end
    --没超上限一直在定点周围生成怪
    if GameMgr.CurrentGenNum ~= GameMgr.MaxNum then
        UE4.UNavigationSystemV1.K2_GetRandomReachablePointInRadius(self, self.OriginLocation, self.MonsterLocation, 2000)
        local PlayerLocation = PlayerCharacter:K2_GetActorLocation()
        local Rot = UE4.UKismetMathLibrary.FindLookAtRotation(self.MonsterLocation, PlayerLocation)
        UE4.UAIBlueprintHelperLibrary.SpawnAIFromClass(self, self.MonsterClass, nil, self.MonsterLocation, Rot)
        GameMgr.CurrentGenNum = GameMgr.CurrentGenNum + 1
        GameMgr.CurrentNum = GameMgr.CurrentNum + 1
    end
end

return BP_MonsterCharacter_C
