--
-- DESCRIPTION
--
-- @COMPANY ngcod.com
-- @AUTHOR 天空游荡的鱼
-- QQ:708888157
--
-- @DATE 2021.12.28
--

require "UnLua"
require "GameMgr"

local UI_CreateRoom_C = Class()

--function UI_CreateRoom_C:Initialize(Initializer)
--end

--function UI_CreateRoom_C:PreConstruct(IsDesignTime)
--end

function UI_CreateRoom_C:Construct()
    self.btnCreate.OnPressed:Add(self, UI_CreateRoom_C.OnClickCreate)
end

function UI_CreateRoom_C:OnClickCreate()
    local GameInstance = UE4.UGameplayStatics.GetGameInstance(self)
    GameInstance.MapName = self.txtRoomName:GetText()
    GameInstance.MaxPlayer = GameMgr.MAX_PLAYER_COUNT
    print("AAA",GameInstance.MaxPlayer,GameMgr.MAX_PLAYER_COUNT)
    local bUseLan = false
    local SelectedOption = self.ComboBoxNet:GetSelectedOption()
    if SelectedOption == "Lan" then
        bUseLan = true
    end
    
    print("Lan"..tostring(lan))
    local PlayerController = UE4.UGameplayStatics.GetPlayerController(self, 0)
    local SessionProxy = UE4.UCreateSessionCallbackProxy.CreateSession(self, PlayerController, GameInstance.MaxPlayer, bUseLan)
    SessionProxy.OnSuccess:Add(self, UI_CreateRoom_C.OnSuccess)
    SessionProxy.OnFailure:Add(self, UI_CreateRoom_C.OnFailure)

    print("创建会话")
    --UCreateSessionCallbackProxy 创建会话代理需要调用 Activate() 才会执行：
    SessionProxy:Activate()

    -- 创建会话,调蓝图版本函数
    --self:CreateSession(GameInstance.MaxPlayer, bUseLan)
end

function UI_CreateRoom_C:OnSuccess() 
    print('创建成功')
    UE4.UGameplayStatics.OpenLevel(self, '/Game/Maps/MapLobby', true, 'listen')

    -- 使用控制台命令执行 ServerTravel
    -- local PC = self:GetOwningPlayer()
    -- if PC then
    --     PC:ExecuteConsoleCommand("ServerTravel /Game/Maps/MapLobby?listen")
    -- end
        -- 获取 World 并使用 ServerTravel
    -- local World = self:GetWorld()
    -- if World then
    --     -- 关键：使用 ServerTravel 而不是 OpenLevel
    --     -- 添加 ?listen 参数保持服务器监听状态
    --     World:ServerTravel("/Game/Maps/MapLobby?listen")
    --     print('打开新关卡Lobby')
        
    -- else
    --     print('Error: World is nil!')
    -- end
end

function UI_CreateRoom_C:OnFailure()
    print('创建失败')
end
 
--function UI_CreateRoom_C:Tick(MyGeometry, InDeltaTime)
--end

return UI_CreateRoom_C
