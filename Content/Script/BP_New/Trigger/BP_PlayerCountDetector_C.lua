--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_PlayerCountDetector_C
local BP_PlayerCountDetector_C = UnLua.Class()
-- 显式声明要覆盖的函数
-- BP_PlayerCountDetector_C.Overridden = {
--     "ReceiveBeginPlay",
--     "ReceiveTick",
-- }

-- function BP_PlayerCountDetector_C:Initialize(Initializer)
-- end

-- function BP_PlayerCountDetector_C:UserConstructionScript()
-- end

function BP_PlayerCountDetector_C:ReceiveBeginPlay()
    print(11222)
end

-- function BP_PlayerCountDetector_C:ReceiveEndPlay()
-- end

function BP_PlayerCountDetector_C:ReceiveTick(DeltaSeconds)
    print("111")
end

-- function BP_PlayerCountDetector_C:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
-- end

-- function BP_PlayerCountDetector_C:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function BP_PlayerCountDetector_C:ReceiveActorEndOverlap(OtherActor)
-- end

return BP_PlayerCountDetector_C
