--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type TestBP_C
local M = UnLua.Class()
require("LuaPanda").start("127.0.0.1",8818)

-- function M:Initialize(Initializer)
-- end

-- function M:UserConstructionScript()
-- end

function M:ReceiveBeginPlay()
    print("TESTBP:ReceiveBeginPlay",self:IsActorTickEnabled() )
     -- 关键：启用 Tick
    self.bCanEverTick = true
    self:SetActorTickEnabled(true)
    print("TESTBP:ReceiveBeginPlay",self:IsActorTickEnabled() )
end

-- function M:ReceiveEndPlay()
-- end

function M:ReceiveTick(DeltaSeconds)
    print("TESTBP:ReceiveTick")
end

-- function M:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function M:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function M:ReceiveActorEndOverlap(OtherActor)
-- end

return M
