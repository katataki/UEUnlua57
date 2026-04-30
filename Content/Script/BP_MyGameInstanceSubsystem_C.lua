--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type BP_MyGameInstanceSubsytem_C
local BP_MyGameInstanceSubsytem_C = UnLua.Class()

function BP_MyGameInstanceSubsytem_C:RecordInitialPlayerNum(PlayerNum)
    self.InitialPlayerNum = PlayerNum
    --print("self.InitialPlayerNum",self.InitialPlayerNum,"PlayerNum:  ",PlayerNum)
end
return BP_MyGameInstanceSubsytem_C