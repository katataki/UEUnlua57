-- EventSystem.lua
local M = {}
M.events = {}

-- 声明/注册事件 事件表里没这个事件就返回空表
function M.DeclareEvent(eventName)
    if not M.events[eventName] then
        M.events[eventName] = {}
    end
    return eventName
end

-- 绑定事件 ,绑定时可以带参数，调用时带的参数会补在这几个之后，通常会填个self
function M.AddListener(eventName, callback, context)
    if not M.events[eventName] then
        M.events[eventName] = {}
    end
    --table.insert在这个事件数组对应事件名的元素（也是一个表，可以当作数组）里插入一个函数和上下文（参数）
    --一个事件名对应多组
    table.insert(M.events[eventName], {
        callback = callback,
        context = context
    })
end

-- 触发事件,此时时的参数会补在绑定时的参数后之后
function M.Broadcast(eventName, ...)
    local listeners = M.events[eventName]
    if not listeners then return end
    
    for _, listener in ipairs(listeners) do
        if listener.context then
            listener.callback(listener.context, ...)
        else
            listener.callback(...)
        end
    end
end

-- 解绑事件
function M.RemoveListener(eventName, callback, context)
    local listeners = M.events[eventName]
    if not listeners then return end
    
    for i = #listeners, 1, -1 do
        local listener = listeners[i]
        if listener.callback == callback and listener.context == context then
            table.remove(listeners, i)
        end
    end
end

-- 解绑全部
function M.Clear(eventName)
    M.events[eventName] = nil
end

return M