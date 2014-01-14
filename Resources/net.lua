--[[
--1:bulit-in function
RequestManager::addDelegate(userObject)                 
RequestManager::removeDelegate(userObject)
RequestManager::sendRequest(type,data,userData)
RequestManager::requestDidFinish(type,result)

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
function RequestManager:obtainHttpUrl(type,param)
	return 'http://m.weather.com.cn/data/101010100.html?id=1';
end

function RequestManager:receiveSocketMessage(data)
	self:requestDidFinish('hehe',data.hehe)
end

function RequestManager:finishedTestRequest(type,result,userData)
    self:requestDidFinish(type,result.weatherinfo)
end

function RequestManager:sendTestRequest( ... )
	self:sendRequest('Test',{d='test',a={'test1','dfdkjdf'}},3.14)
end


-- costom code end