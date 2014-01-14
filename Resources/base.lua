require "Cocos2d"
local anmt = {};
anmt.__index = anmt;
function anmt:register()
    print('register')
	local ele = self['__element__'];
    print(ele)
	if ele and ele.registerScriptHandler then
        print('register successfull')
		ele:registerScriptHandler(function(ev)
			if ev=='enter' and self.enter then
				self:enter();
			elseif ev=='enterTransitionFinish' and self.enterTransitionFinish then
				self:enterTransitionFinish();
			elseif ev=='exit' and self.exit then
				self:exit();
			elseif ev=='exitTransitionStart' and self.exitTransitionStart then
				self:exitTransitionStart();
			elseif ev=='cleanup' and self.cleanup then
				self:cleanup();
			end
		end);
	end
end
function anmt:element()
	return self['__element__'];
end
function anmt:setElement(ele)
	self['__element__']=ele;
end

an = {
	create = function(_,a)
		setmetatable(a,anmt);
		a.base = getmetatable(a);
		return a;
	end
}