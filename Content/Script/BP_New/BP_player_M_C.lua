--
-- DESCRIPTION
--
-- @COMPANY www.ngcod.com
-- @AUTHOR 天空游荡的鱼
-- QQ:708888157
--
-- @DATE ${date} ${time}
--

require "UnLua"

local BP_player_M_C = Class()

--Initializer是蓝图的配置
function BP_player_M_C:Initialize(Initializer)
    if Initializer then
        -- self.BaseColor = Initializer[0]
        self.InProf = Initializer[0]
    end
    self.bMySelf = true
end

function BP_player_M_C:ReceiveBeginPlay()
    self.Life = 500
    self.MaxLife = 500

    if self:HasAuthority() then
        if self.BaseColor ~= nil then
            self.Color = self.BaseColor
        end
        if self.InProf ~= nil then
            self.prof = self.InProf
        end
    end
    if self:HasAuthority() then
        local Weapon = self:SpawnWeapon()
        if Weapon then
            -- 按阵营改下武器颜色以标记
            -- local MID = Weapon.Mesh:CreateDynamicMaterialInstance(0)
	        -- if MID and self.Color then
		    --     MID:SetVectorParameterValue("BodyColor", self.Color)
            -- end
            Weapon:K2_AttachToComponent(self.Mesh, "RightHandSocket", UE4.EAttachmentRule.SnapToTarget,UE4.EAttachmentRule.SnapToTarget,UE4.EAttachmentRule.SnapToTarget)
            self.Weapon = Weapon
        end
    end
  
    --切换动画模式为动画蓝图，根据预设序号确定动画蓝图
    self.Mesh:SetAnimationMode(0)
    if self.prof == 1 then
        self:ChangeMesh('/Game/Role/Swat/Swat.Swat', '/Game/Blueprint/Swat/ABP_Swat.ABP_Swat_C')
    elseif self.prof == 2 then
        self:ChangeMesh('/Game/Role/Sophie/Sophie.Sophie', '/Game/Blueprint/Sophie/ABP_Sophie.ABP_Sophie_C')
    elseif self.prof == 3 then
        self:ChangeMesh('/Game/Role/Alex/Alex.Alex', '/Game/Blueprint/Alex/ABP_Alex.ABP_Alex_C')
    end
    -- local MID = self.Mesh:CreateDynamicMaterialInstance(0)
	-- if MID and self.Color then
	-- 	MID:SetVectorParameterValue("BodyColor", self.Color)
    -- end
    
    local HPBar = self.HPBar:GetUserWidgetObject()
    self.HPBar:SetVisibility(false)
    --初始化血量显示
    HPBar:Update(self.PlayerInfo.Life,self.PlayerInfo.MaxLife)
    --HPBar.hpBar:SetPercent(1)

    local UI_PlayerInfo = self.UI_PlayerInfo:GetUserWidgetObject()
    UI_PlayerInfo:SetPlayerInfo(self.PlayerInfo)

    --默认是隐藏的，这里方便测试都显示血条先
    self.HPBar:SetVisibility(true)
    --不是玩家0，就不是本机，只显示别人的血条UI
    local Player0 = UE4.UGameplayStatics.GetPlayerCharacter(self, 0)
    if Player0 and Player0.PlayerInfo.Name ~= self.PlayerInfo.Name then
        self.bMySelf = false
        --self.HPBar:SetVisibility(true)
        return
    end
end

--换模型和动画蓝图
function BP_player_M_C:ChangeMesh(strMesh, strAnim)
    local Mesh = UE4.UObject.Load(strMesh)
    --self.Mesh.SkeletalMesh = Mesh
    self.Mesh:SetSkeletalMeshAsset(Mesh,false)

    local AnimAsset = UE4.UClass.Load(strAnim)
    self.Mesh.AnimAsset = AnimAsset
    --self.Mesh:SetAnimClass(AnimAsset)
end

function BP_player_M_C:SpawnWeapon()
    local World = self:GetWorld()
	if not World then
		return
	end
	local WeaponClass = UE4.UClass.Load("/Game/BP_New/Weapon/BP_Weapon.BP_Weapon_C")
	local NewWeapon = World:SpawnActor(WeaponClass, UE4.FTransform(), UE4.ESpawnActorCollisionHandlingMethod.AlwaysSpawn, self, self)
	return NewWeapon
end


function BP_player_M_C:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
    if self.IsDead then
        return
    end

    local Controller = self:GetController()
    --玩家角色控制器类
    local BP_PlayerController_M_C = UE.UClass.Load("/Game/BP_New/BP_PlayerController_M.BP_PlayerController_M_C")
    if BP_PlayerController_M_C == nil then
        return
    end
    --怪物角色控制器类
    local BP_MonsterController_C = UE.UClass.Load("/Game/Blueprint/Monster/BP_MonsterController.BP_MonsterController_C")
    if BP_MonsterController_C == nil then
        return
    end

    --自己的控制器肯定是玩家控制器
    local BP_PlayerController_M = Controller:Cast(BP_PlayerController_M_C)
    if BP_PlayerController_M == nil then 
        return 
    end


    if InstigatedBy:IsA(BP_MonsterController_C) then
        print("玩家",BP_PlayerController_M.PlayerInfo.Name,"受到","Monster","攻击，受到伤害",Damage)
        BP_PlayerController_M:Event_Hurt(BP_PlayerController_M.PlayerInfo.Name, "Monster", Damage)
    end
    if InstigatedBy:IsA(BP_PlayerController_M_C) then
        --屏蔽友伤
        if BP_PlayerController_M.PlayerInfo.Team == InstigatedBy.PlayerInfo.Team then
            return
        end
        BP_PlayerController_M:Event_Hurt(BP_PlayerController_M.PlayerInfo.Name, InstigatedBy.PlayerInfo.Name, Damage)
    end
end

function BP_player_M_C:Died()
    self.IsDead = true
    self.CapsuleComponent:SetCollisionEnabled(UE4.ECollisionEnabled.NoCollision)
    local Controller = self:GetController()
    if Controller then
        Controller:UnPossess()
    end
    self.TimerDie = UE4.UKismetSystemLibrary.K2_SetTimerDelegate({self, BP_player_M_C.Destory}, 15, true)
end

function BP_player_M_C:Destory()
    if self.Weapon then
        self.Weapon:K2_DestroyActor()
        self.Weapon = nil
    end
    self:K2_DestroyActor()
end

function BP_player_M_C:Fire_RPC(Dir)
    --Server
    if self.Weapon == nil then
        return
    end
    self.Weapon:Event_Fire(Dir)
end

--function BP_player_M_C:ReceiveEndPlay()
--end


function BP_player_M_C:ReceiveTick(DeltaSeconds)
    -- if  self.bMySelf then
    --     return
    -- end

    if self.IsDead then
        self.HPBar:SetVisibility(false)
        return
    end

    --更新血条UI朝向摄像机
    local cameraLoc = UE4.UGameplayStatics.GetPlayerCameraManager(self, 0):GetCameraLocation()
    local hpLoc = self.HPBar:K2_GetComponentLocation()
    local rot = UE4.UKismetMathLibrary.FindLookAtRotation(hpLoc, cameraLoc)
    self.HPBar:K2_SetWorldRotation(rot,false,nil,false)

    local HPBar = self.HPBar:GetUserWidgetObject()
    self.HPBar:SetVisibility(false)
    --初始化血量显示
    HPBar:Update(self.PlayerInfo.Life,self.PlayerInfo.MaxLife)
    --HPBar.hpBar:SetPercent(1)

    local UI_PlayerInfo = self.UI_PlayerInfo:GetUserWidgetObject()
    UI_PlayerInfo:SetPlayerInfo(self.PlayerInfo)
end

--function BP_player_M_C:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
--end

--function BP_player_M_C:ReceiveActorBeginOverlap(OtherActor)
--end

--function BP_player_M_C:ReceiveActorEndOverlap(OtherActor)
--end

return BP_player_M_C