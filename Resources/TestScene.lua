require "net"
require "base"

local scene = aux:addClass('TestScene',{'text'});
function scene:init()
    local sceneGame = cc.Scene:create();
    self:setElement(sceneGame);
    print('TestScene init!!!');
    self.text = 'TestScene类';
end
function scene:enter()
    print('TestScene enter!!!');
    self:createLayerMenu();
    RequestManager:addDelegate(self);
    RequestManager:sendTestRequest();
end
function scene:exit()
    RequestManager:removeDelegate(self);
end
function scene:createLayerMenu()
end
function scene:requestDidFinishWithResult(type,result)
    if type == 'Test' then
        print('TestScene收到Test请求的回复：' .. aux:table(result));
    elseif type == 'msg' then
        print('TestScene收到服务器信息'..aux:table(result));
        RequestManager:sendMessage({data='hello server,I am TestScene'});
    end
end
function CreateTestScene()
	return aux:create('TestScene');
end