--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_PlayerCountDetector_C
local BP_PlayerCountDetector_C = UnLua.Class()
local EventSystem = require("EventSystem")
EventSystem.DeclareEvent("OnPlayerJoined")

--构建配置表
    EventConfigs = {
        { MinPlayers = 1, MaxPlayers = 1, EventName = "Event_GroupSmall" },
        { MinPlayers = 2, MaxPlayers = 2, EventName = "Event_GroupLarge" }
    }

-- function BP_PlayerCountDetector_CInitialize(Initializer)
-- end

-- function BP_PlayerCountDetector_CUserConstructionScript()
-- end

function BP_PlayerCountDetector_C:ReceiveBeginPlay()
    if not self:HasAuthority()  then
        return
    end

     --一开始会是0，随着玩家一个个进入新关卡才会增加
    --self.InitialPlayerCount = UE4.UGameplayStatics.GetNumPlayers(self)

    --取出在进入新关卡前GameInstance存储的当前会话玩家数
    local GameInstance = UE4.UGameplayStatics.GetGameInstance(self)
    if GameInstance then
        self.InitialPlayerCount = GameInstance.InitialPlayerCount
    end
    
    for _, config in pairs(self.EventConfigs) do
        if self.InitialPlayerCount >= config.MinPlayers 
           and self.InitialPlayerCount <= config.MaxPlayers then
            EventSystem.Broadcast( "OnPlayerJoined", {
                playerCount = self.InitialPlayerCount
            })
        end
    end
end

-- function BP_PlayerCountDetector_CReceiveEndPlay()
-- end

-- function BP_PlayerCountDetector_CReceiveTick(DeltaSeconds)
-- end

-- function BP_PlayerCountDetector_CReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function BP_PlayerCountDetector_CReceiveActorBeginOverlap(OtherActor)
-- end

-- function BP_PlayerCountDetector_CReceiveActorEndOverlap(OtherActor)
-- end

return BP_PlayerCountDetector_C
