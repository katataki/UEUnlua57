--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

-- local BP_MonsterCharacter_C = Class("BP_CharacterBase_C")
local BP_MonsterCharacter_C = Class()

function BP_MonsterCharacter_C:Initialize(Initializer)
    self.Life = 100
    self.Damage = 1
end

--function BP_MonsterCharacter_C:UserConstructionScript()
--end

function BP_MonsterCharacter_C:ReceiveBeginPlay()
    self.Sphere.OnComponentHit:Add(self, BP_MonsterCharacter_C.OnComponentHit_Sphere)
end

--怪物是拿球撞人，撞到就扣血
function BP_MonsterCharacter_C:OnComponentHit_Sphere(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit)
    print("Hit Player")
    local BP_CharacterBase_C = UE.UClass.Load("/Game/BP_CharacterBase.BP_CharacterBase_C")
	local Character = OtherActor:Cast(BP_CharacterBase_C)
    --应用伤害到触发者
	if Character then
		local Controller = self.Instigator:GetController()
		UE4.UGameplayStatics.ApplyDamage(Character, self.Damage, Controller, self.Instigator, self.DamageType)
	end
end

function BP_MonsterCharacter_C:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
    if self.IsDead then
        return
    end
    self.Life = math.max(self.Life - Damage, 0)
    if self.Life <= 0 then
        self.IsDead = true
        self.CapsuleComponent:SetCollisionEnabled(UE4.ECollisionEnabled.NoCollision)
        local Controller = self:GetController()
        if Controller then
            Controller:UnPossess()
        end
        self.Sphere:SetCollisionEnabled(UE4.ECollisionEnabled.NoCollision)
        InstigatedBy:Event_KillMonster()
        --self:Die(InstigatedBy.ID)
        
        self.TimerDie = UE4.UKismetSystemLibrary.K2_SetTimerDelegate({self, BP_MonsterCharacter_C.Destory}, 5, true)
    end
end

-- function BP_MonsterCharacter_C:Died()
--     self.IsDead = true
--     self.CapsuleComponent:SetCollisionEnabled(UE4.ECollisionEnabled.NoCollision)
--     local Controller = self:GetController()
--     if Controller then
--         Controller:UnPossess()
--     end

--     local MyInterface = UE.UClass.Load("/Game/BPI_Interfaces.BPI_Interfaces_C")
--     local mode = UE4.UGameplayStatics.GetGameMode(self)
--     MyInterface.NotifyEnemyDied(mode)

--     self.Sphere:SetCollisionEnabled(UE4.ECollisionEnabled.NoCollision)
-- end

function BP_MonsterCharacter_C:Destory()
    if self.Weapon then
        self.Weapon:K2_DestroyActor()
    end
    self:K2_DestroyActor()
end

--function BP_MonsterCharacter_C:ReceiveEndPlay()
--end

-- function BP_MonsterCharacter_C:ReceiveTick(DeltaSeconds)
-- end

--function BP_MonsterCharacter_C:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
--end

--function BP_MonsterCharacter_C:ReceiveActorBeginOverlap(OtherActor)
--end

--function BP_MonsterCharacter_C:ReceiveActorEndOverlap(OtherActor)
--end

return BP_MonsterCharacter_C
