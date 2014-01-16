require "CTestScene"

local scene = aux:extendClass('CCTestScene','CTestScene',{'cctext'});
function scene:init()
    self:super('init');
    self.cctext = 'CCTestScene类';
    print('CCTestScene init!!!');
end
function scene:enter()
    self:super('enter');
    print('CCTestScene enter!!!');
end
function scene:exit()
    self:super('exit');
end
function scene:requestDidFinishWithResult(type,result)
    if type == 'Test' then
        print('CCTestScene收到Test请求的回复：' .. aux:table(result));
    elseif type == 'msg' then
        print('CCTestScene收到服务器信息'..aux:table(result));
        RequestManager:sendMessage({data='hello server,I am CCTestScene'});
    end
end
function CreateCCTestScene()
    return aux:create('CCTestScene');
end