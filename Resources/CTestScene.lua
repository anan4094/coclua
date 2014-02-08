require "TestScene"

local scene = aux:extendClass('CTestScene','TestScene',{'ctext'});
function scene:init()
    self:super('init');
    print('CTestScene init!!!');
    self.ctext = 'CTestScene类';
end
-- function scene:enter()
--     self:base('enter');
--     print('CTestScene enter!!!\n');
--     print(self.ctext ..','.. self.text .. '\n');
-- end
function scene:exit()
    self:spuer('exit');
end
function scene:requestDidFinishWithResult(type,result)
    if type == 'Test' then
        print('CTestScene收到Test请求的回复：' .. aux:table(result));
    elseif type == 'msg' then
        RequestManager:log('CTestScene收到服务器信息:%@',result);
        RequestManager:sendMessage({data='hello server,I am CTestScene'});
    end
end
function CreateCTestScene()
    return aux:create('CTestScene');
end