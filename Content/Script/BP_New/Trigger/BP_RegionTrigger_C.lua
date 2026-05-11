--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--
---@type BP_RegionTrigger_C
local BP_RegionTrigger_C = UnLua.Class()

local EventSystem = require("EventSystem")



-- function BP_RegionTrigger_C:Initialize(Initializer)
-- end

-- function BP_RegionTrigger_C:UserConstructionScript()
-- end
-- 绑定事件
local function OnPlayerJoined(playerId)
    print("玩家加入:", playerId)
end

function BP_RegionTrigger_C:ReceiveBeginPlay()
    EventSystem.AddListener("OnPlayerJoined",OnPlayerJoined,self)
end

function BP_RegionTrigger_C:ReceiveEndPlay()
    EventSystem.RemoveListener("OnPlayerJoined",OnPlayerJoined,self)
end

-- function BP_RegionTrigger_C:ReceiveTick(DeltaSeconds)
-- end

-- function BP_RegionTrigger_C:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function BP_RegionTrigger_C:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function BP_RegionTrigger_C:ReceiveActorEndOverlap(OtherActor)
-- end

return BP_RegionTrigger_C
