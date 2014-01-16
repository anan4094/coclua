--[[
--1:bulit-in function
RequestManager::addDelegate(userObject)                 
RequestManager::removeDelegate(userObject)
RequestManager::sendRequest(type,data,userData)
RequestManager::requestDidFinish(type,result)
RequestManager::sendMessage(msg)

--2:custom function
RequestManager::send(w+)Request([param...])  --function name unnecessary
    self:sendRequest(...)  --necessary
end
RequestManager::finished(w+)Request([param...])  --function name necessary
    self:requestDidFinish(...)  --necessary
end

--3:userObject
userObject:requestDidFinishWithResult(type,result)

]]--
RequestManager = RequestManager or {}

-- custom code start
-- if you implement next function,c++ couldn't call NetworkHook::obtainHttpUrl to obtain http url
-- use c++ NetworkHook::obtainHttpUrl ,remove it
function RequestManager:obtainHttpUrl(type,param)
	return 'http://m.weather.com.cn/data/101010100.html?action='.. param.action;
end

function RequestManager:receiveSocketMessage(data)
	self:requestDidFinish('msg',data)
end

-- custom add function
function RequestManager:finishedTestRequest(type,result,userData)
    self:requestDidFinish(type,result)
end

function RequestManager:sendTestRequest( ... )
	self:sendRequest('Test',{action='api_name'},998);
end


-- costom code end