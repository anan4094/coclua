#include "JsonUtil.h"

USING_NS_CC;
JsonUtil::JsonUtil()
{

}

JsonUtil::~JsonUtil()
{

}

std::string JsonUtil::jsonStringWithObject(Object* object)
{
    Json::Value jsonValue = JsonUtil::jsonValueWithObject(object);
    
    Json::FastWriter writer;
    std::string jsonString = writer.write(jsonValue);
    
    return jsonString;
}

std::string JsonUtil::jsonStringWithArray(Array* array)
{
    Json::Value jsonValue = JsonUtil::jsonValueWithArray(array);
    
    Json::FastWriter writer;
    std::string jsonString = writer.write(jsonValue);
    
    return jsonString;
}

std::string JsonUtil::jsonStringWithDictionary(Dictionary* dictionary)
{
    Json::Value jsonValue = JsonUtil::jsonValueWithDictionary(dictionary);
    
    Json::FastWriter writer;
    std::string jsonString = writer.write(jsonValue);
    
    return jsonString;
}

Json::Value JsonUtil::jsonValueWithObject(cocos2d::Object* object)
{
    Json::Value jsonValue;
    
    if ((dynamic_cast< Array*>(object) ? true : false)) {
        jsonValue = JsonUtil::jsonValueWithArray((Array*)object);
    }else if ((dynamic_cast< Dictionary*>(object) ? true : false)){
        jsonValue = JsonUtil::jsonValueWithDictionary((Dictionary*)object);
    }else if ((dynamic_cast< String*>(object) ? true : false)){
        String *string = (String*)object;
        jsonValue = string->getCString();
    }else if ((dynamic_cast< Bool*>(object) ? true : false)){
        Bool *boolObject = (Bool*)object;
        jsonValue = boolObject->getValue();
    }else if ((dynamic_cast< Integer*>(object) ? true : false)){
        Integer *integerObject = (Integer*)object;
        jsonValue = integerObject->getValue();
    }else if ((dynamic_cast< Float*>(object) ? true : false)){
        Float *floatObject = (Float*)object;
        jsonValue = floatObject->getValue();
    }else if ((dynamic_cast< Double*>(object) ? true : false)){
        Double *doubleObject = (Double*)object;
        jsonValue = doubleObject->getValue();
    }
    
    return jsonValue;
}

Json::Value JsonUtil::jsonValueWithArray(Array* array)
{
    Json::Value jsonValue = Json::Value( Json::arrayValue );
    if (array == NULL) {
        return jsonValue;
    }
    
    Object *pObject;
    int i = 0;
    CCARRAY_FOREACH(array, pObject)
    {
        Json::Value subJsonValue;
        subJsonValue = JsonUtil::jsonValueWithObject(pObject);
        jsonValue[i++] = subJsonValue;
    }
    return jsonValue;
}

Json::Value JsonUtil::jsonValueWithDictionary(Dictionary* dictionary)
{
    Json::Value jsonValue = Json::Value( Json::objectValue );
    if (dictionary == NULL) {
        return jsonValue;
    }
    
    DictElement* pElement = NULL;
    CCDICT_FOREACH(dictionary, pElement)
    {
        const char* key = pElement->getStrKey();
        Object *objectValue = pElement->getObject();
        Json::Value subJsonValue = JsonUtil::jsonValueWithObject(objectValue);
        jsonValue[key] = subJsonValue;
    }
    return jsonValue;
}

Object* JsonUtil::objectWithString(const std::string& jsonString)
{
    Object *jsonObject = NULL;
    
    Json::Reader reader;
    Json::Value root;
    
    std::string str = jsonString;
    // reader将Json字符串解析到root，root将包含Json里所有子元素
    if (reader.parse(str, root))  
    {
        jsonObject = JsonUtil::objectWithJsonValue(root);
    }
    return jsonObject;
}

Object* JsonUtil::objectWithJsonValue( Json::Value value)
{
    Object *object = NULL;
    switch ( value.type() )
    {
        case Json::nullValue:{
        }break;
        case Json::intValue:
        {
            object = Integer::create(value.asInt());
        }break;
        case Json::uintValue:
        {
            object = Integer::create(value.asInt());
        }break;
        case Json::realValue:
        {
            object = Double::create(value.asDouble());
        }break;
        case Json::booleanValue:
        {
            object = Bool::create(value.asBool());
        }break;
        case Json::stringValue:
        {
            object = String::create(value.asString());
        }break;
        case Json::arrayValue:
        {
            Array *array = Array::create();
            object = array;
            
            int size = value.size();
            for ( int index =0; index < size; ++index )
            {
                Object *subObject = JsonUtil::objectWithJsonValue(value[index]);
                if (subObject != NULL) {
                    array->addObject(subObject);
                }
            }
        }break;
        case Json::objectValue:
        {
            Dictionary *dictionary = Dictionary::create();
            object = dictionary;
            
            Json::Value::Members members( value.getMemberNames() );
            for ( Json::Value::Members::iterator it = members.begin();
                 it != members.end();
                 ++it )
            {
                const std::string &name = *it;
                Object *subObject = JsonUtil::objectWithJsonValue(value[name]);
                if (subObject != NULL) {
                    dictionary->setObject(subObject, name);
                }
            }
            
        }break;
        default:
        {
        
        }break;
    }
    return object;
}