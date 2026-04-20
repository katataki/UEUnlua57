--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type HPBar_C
local HPBar_C = UnLua.Class()

--function M:Initialize(Initializer)
--end

--function M:PreConstruct(IsDesignTime)
--end

-- function M:Construct()
-- end

--function M:Tick(MyGeometry, InDeltaTime)
--end

function HPBar_C:Update(HP, MaxHP)
    local percent = 1.0
    if MaxHP <= 0 then 
        percent = 1
    else 
        percent = HP / Max
    end 
    self.hpBar:SetPercent(percent)
    local text = string.format("%.0f/%.0f", HP, MaxHP)
    --local hpString = math.ceil(HP).."/"..math.ceil(MaxHP)
    self.hpText:SetText(text)
end

return HPBar_C
