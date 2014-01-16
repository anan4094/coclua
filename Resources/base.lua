require "Cocos2d"
aux = {};
aux.classes = {};
local proto = {};
aux.proto = proto;
proto.__index = proto;
function proto:register()
	local ele = self['__element__'];
	if ele and ele.registerScriptHandler then
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
function proto:element()
	return self['__element__'];
end
function proto:setElement(ele)                                                                                           
	rawset(self,'__element__',ele);
	self:register();
end
function proto:super(method,...)
	local info = debug.getinfo(2,'nf');
	if not info then return; end
	local funcname = info.name;
	local func = info.func;
	local mt = getmetatable(self);
	while mt and mt.__name__ do
		if not funcname then
			for k,v in pairs(mt) do
				if v == func then
					funcname = k;
					break;
				end
			end
		end
		if funcname and rawget(mt,funcname) == func then
			print('call super<'..method..'> in  class['..mt.__name__..']<'..funcname..'>');
			mt = getmetatable(mt);
			if mt and mt[method] then
				local ret = mt[method](self,arg);
				return ret;
			else
				print('can\'t find super<'..method..'> in  class['..mt.__name__..']<'..funcname..'>');
				return;
			end
		end
		mt = getmetatable(mt);
	end
	print('you need call super method in correct environment');
end

--public function
function aux:addClass(name,property)
	local cl=aux.classes[name];
	if cl then
		print('lua_class ' .. name .. ' already exist!!!');
		return;
	end
	cl = {};
	setmetatable(cl,proto);
	cl.__index = cl;
	aux.classes[name] = cl;
	cl.__name__ = name;
	cl.__property__ = property;
	cl.__newindex = function(_,k,v)
		if type(v) == 'function' then
			rawset(_,k,v);
		else
			print('class '.._.__name__ .. ' don\'t have '.. k ..' property');
		end
	end
	return cl;
end

function aux:extendClass(name,supername,property)
	local sucl=aux.classes[supername];
	if not sucl then
		print('lua_class ' .. supername .. ' don\'t exist!!!');
		return;
	end
	local cl = self:addClass(name,property);
	if not cl then return end;
	cl.__supername__ = supername;
	setmetatable(cl,sucl);
	return cl;
end

function aux:create(name)
	local cl=self.classes[name];
	if not cl then
		print('lua_class '..name ..' don\'t exist!!!');
		return;
	end
	local a = {};
	local b = cl;
	while b and b.__property__ do
		for i,v in ipairs(b.__property__) do
			a[v]=false;
		end
		b = getmetatable(b);
	end
	rawset(a,'__class__',name);
	setmetatable(a,cl);
	return a;
end
--this function make you to view content of table easy
--e.g aux:table({x=1,y=2})
--return 
--"{
--     "x":1,
--     "y":2
---}"
function aux:table(tabl,tab)
	if tab == nil then tab = 0 end
	local ret = '{\n';
	local sp = self:tab(tab+1);
	local fl = 1;
	local isarray = true;
	for k,v in pairs(tabl) do
		if type(k)=='number' and fl == k then
			fl = fl+1;
		else
			isarray = false;
			break;
		end
	end
	if isarray then
		ret = '[\n';
		for i=1,fl-1 do
			local vstr;
			local v = tabl[i];
			if type(v) == 'table' then
				vstr = self:table(v,tab+1);
			elseif type(v) == 'string' then
				vstr = '"' .. self:fstring(v) .. '"';
			elseif type(v) == 'boolean' then
				if v then vstr = 'true' else vstr = 'false' end
			elseif type(v) == 'number' then
				vstr = ''..v;
			else
				vstr = '<' .. type(v) .. '>';
			end
			ret = ret .. sp .. vstr;
			sp = ',\n'..self:tab(tab+1)
		end
		ret = ret .. '\n';
		ret = ret .. self:tab(tab) .. ']';
		return ret;
	end
	for k,v in pairs(tabl) do
		local vstr;
		if type(v) == 'table' then
			vstr = self:table(v,tab+1);
		elseif type(v) == 'string' then
			vstr = '"' .. self:fstring(v) .. '"';
		elseif type(v) == 'boolean' then
			if v then vstr = 'true' else vstr = 'false' end
		elseif type(v) == 'number' then
			vstr = ''..v;
		else
			vstr = '<' .. type(v) .. '>';
		end
		ret = ret .. sp .. '"' ..k ..'":'..vstr;
		sp = ',\n'..self:tab(tab+1)
	end
	ret = ret .. '\n';
	ret = ret .. self:tab(tab) .. '}';
	return ret;
end
-- private function
-- aux:tab and aux:fstring service for aux:table,so you can ignore them
function aux:tab(a)
	local ret = '';
	for i=1,a do
		ret = ret .. '    ';
	end
	return ret;
end

function aux:fstring(str)
	local s = string.gsub(str,'\\','\\\\');
	s = string.gsub(s,'/','\\/');
	s = string.gsub(s,'"','\\\"');
	s = string.gsub(s,'\t','\\t"');
	s = string.gsub(s,'\f','\\f');
	s = string.gsub(s,'\b','\\b');
	s = string.gsub(s,'\n','\\n');
	s = string.gsub(s,'\r','\\r');
	return s;
end