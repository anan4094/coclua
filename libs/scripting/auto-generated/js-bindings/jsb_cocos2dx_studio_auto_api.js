/**
 * @module cocos2dx_studio
 */
var ccs = ccs || {};

/**
 * @class ActionManagerEx
 */
ccs.ActionManager = {

/**
 * @method playActionByName
 * @return A value converted from C/C++ "cocostudio::ActionObject*"
 * @param {const char*}
 * @param {const char*}
 */
playActionByName : function () {},

/**
 * @method getActionByName
 * @return A value converted from C/C++ "cocostudio::ActionObject*"
 * @param {const char*}
 * @param {const char*}
 */
getActionByName : function () {},

/**
 * @method releaseActions
 */
releaseActions : function () {},

/**
 * @method purgeActionManager
 */
purgeActionManager : function () {},

/**
 * @method shareManager
 * @return A value converted from C/C++ "cocostudio::ActionManagerEx*"
 */
shareManager : function () {},

};

/**
 * @class Bone
 */
ccs.Bone = {

/**
 * @method isTransformDirty
 * @return A value converted from C/C++ "bool"
 */
isTransformDirty : function () {},

/**
 * @method isIgnoreMovementBoneData
 * @return A value converted from C/C++ "bool"
 */
isIgnoreMovementBoneData : function () {},

/**
 * @method updateZOrder
 */
updateZOrder : function () {},

/**
 * @method setTransformDirty
 * @param {bool}
 */
setTransformDirty : function () {},

/**
 * @method getDisplayRenderNode
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getDisplayRenderNode : function () {},

/**
 * @method addChildBone
 * @param {cocostudio::Bone*}
 */
addChildBone : function () {},

/**
 * @method getWorldInfo
 * @return A value converted from C/C++ "cocostudio::BaseData*"
 */
getWorldInfo : function () {},

/**
 * @method getTween
 * @return A value converted from C/C++ "cocostudio::Tween*"
 */
getTween : function () {},

/**
 * @method getParentBone
 * @return A value converted from C/C++ "cocostudio::Bone*"
 */
getParentBone : function () {},

/**
 * @method getBlendType
 * @return A value converted from C/C++ "cocostudio::BlendType"
 */
getBlendType : function () {},

/**
 * @method updateColor
 */
updateColor : function () {},

/**
 * @method getName
 * @return A value converted from C/C++ "std::string"
 */
getName : function () {},

/**
 * @method setOpacity
 * @param {unsigned char}
 */
setOpacity : function () {},

/**
 * @method getDisplayRenderNodeType
 * @return A value converted from C/C++ "cocostudio::DisplayType"
 */
getDisplayRenderNodeType : function () {},

/**
 * @method removeDisplay
 * @param {int}
 */
removeDisplay : function () {},

/**
 * @method updateDisplayedOpacity
 * @param {unsigned char}
 */
updateDisplayedOpacity : function () {},

/**
 * @method setParentBone
 * @param {cocostudio::Bone*}
 */
setParentBone : function () {},

/**
 * @method setZOrder
 * @param {int}
 */
setZOrder : function () {},

/**
 * @method getColliderFilter
 * @return A value converted from C/C++ "cocostudio::ColliderFilter*"
 */
getColliderFilter : function () {},

/**
 * @method setIgnoreMovementBoneData
 * @param {bool}
 */
setIgnoreMovementBoneData : function () {},

/**
 * @method setName
 * @param {std::string}
 */
setName : function () {},

/**
 * @method removeFromParent
 * @param {bool}
 */
removeFromParent : function () {},

/**
 * @method getChildArmature
 * @return A value converted from C/C++ "cocostudio::Armature*"
 */
getChildArmature : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getTweenData
 * @return A value converted from C/C++ "cocostudio::FrameData*"
 */
getTweenData : function () {},

/**
 * @method setColliderFilter
 * @param {cocostudio::ColliderFilter*}
 */
setColliderFilter : function () {},

/**
 * @method getColliderBodyList
 * @return A value converted from C/C++ "cocos2d::Array*"
 */
getColliderBodyList : function () {},

/**
 * @method setBoneData
 * @param {cocostudio::BoneData*}
 */
setBoneData : function () {},

/**
 * @method setArmature
 * @param {cocostudio::Armature*}
 */
setArmature : function () {},

/**
 * @method getNodeToWorldTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getNodeToWorldTransform : function () {},

/**
 * @method setColor
 * @param {cocos2d::Color3B}
 */
setColor : function () {},

/**
 * @method removeChildBone
 * @param {cocostudio::Bone*}
 * @param {bool}
 */
removeChildBone : function () {},

/**
 * @method setChildArmature
 * @param {cocostudio::Armature*}
 */
setChildArmature : function () {},

/**
 * @method getNodeToArmatureTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getNodeToArmatureTransform : function () {},

/**
 * @method getDisplayManager
 * @return A value converted from C/C++ "cocostudio::DisplayManager*"
 */
getDisplayManager : function () {},

/**
 * @method getArmature
 * @return A value converted from C/C++ "cocostudio::Armature*"
 */
getArmature : function () {},

/**
 * @method setBlendType
 * @param {cocostudio::BlendType}
 */
setBlendType : function () {},

/**
 * @method changeDisplayByIndex
 * @param {int}
 * @param {bool}
 */
changeDisplayByIndex : function () {},

/**
 * @method updateDisplayedColor
 * @param {cocos2d::Color3B}
 */
updateDisplayedColor : function () {},

/**
 * @method getBoneData
 * @return A value converted from C/C++ "cocostudio::BoneData*"
 */
getBoneData : function () {},

/**
 * @method Bone
 * @constructor
 */
Bone : function () {},

};

/**
 * @class BatchNode
 */
ccs.BatchNode = {

/**
 * @method getTexureAtlasWithTexture
 * @return A value converted from C/C++ "cocos2d::TextureAtlas*"
 * @param {cocos2d::Texture2D*}
 */
getTexureAtlasWithTexture : function () {},

/**
 * @method removeChild
 * @param {cocos2d::Node*}
 * @param {bool}
 */
removeChild : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocostudio::BatchNode*"
 */
create : function () {},

};

/**
 * @class ArmatureAnimation
 */
ccs.ArmatureAnimation = {

/**
 * @method getSpeedScale
 * @return A value converted from C/C++ "float"
 */
getSpeedScale : function () {},

/**
 * @method play
 * @param {const char*}
 * @param {int}
 * @param {int}
 * @param {int}
 * @param {int}
 */
play : function () {},

/**
 * @method pause
 */
pause : function () {},

/**
 * @method setAnimationInternal
 * @param {float}
 */
setAnimationInternal : function () {},

/**
 * @method gotoAndPause
 * @param {int}
 */
gotoAndPause : function () {},

/**
 * @method resume
 */
resume : function () {},

/**
 * @method stop
 */
stop : function () {},

/**
 * @method setAnimationData
 * @param {cocostudio::AnimationData*}
 */
setAnimationData : function () {},

/**
 * @method setSpeedScale
 * @param {float}
 */
setSpeedScale : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getAnimationData
 * @return A value converted from C/C++ "cocostudio::AnimationData*"
 */
getAnimationData : function () {},

/**
 * @method playByIndex
 * @param {int}
 * @param {int}
 * @param {int}
 * @param {int}
 * @param {int}
 */
playByIndex : function () {},

/**
 * @method gotoAndPlay
 * @param {int}
 */
gotoAndPlay : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 * @param {cocostudio::Armature*}
 */
init : function () {},

/**
 * @method getMovementCount
 * @return A value converted from C/C++ "int"
 */
getMovementCount : function () {},

/**
 * @method setUserObject
 * @param {cocos2d::Object*}
 */
setUserObject : function () {},

/**
 * @method getCurrentMovementID
 * @return A value converted from C/C++ "std::string"
 */
getCurrentMovementID : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocostudio::ArmatureAnimation*"
 * @param {cocostudio::Armature*}
 */
create : function () {},

/**
 * @method ArmatureAnimation
 * @constructor
 */
ArmatureAnimation : function () {},

};

/**
 * @class ArmatureDataManager
 */
ccs.ArmatureDataManager = {

/**
 * @method getAnimationDatas
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getAnimationDatas : function () {},

/**
 * @method removeAnimationData
 * @param {const char*}
 */
removeAnimationData : function () {},

/**
 * @method addArmatureData
 * @param {const char*}
 * @param {cocostudio::ArmatureData*}
 * @param {const char*}
 */
addArmatureData : function () {},

/**
 * @method removeArmatureFileInfo
 * @param {const char*}
 */
removeArmatureFileInfo : function () {},

/**
 * @method getTextureDatas
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getTextureDatas : function () {},

/**
 * @method getTextureData
 * @return A value converted from C/C++ "cocostudio::TextureData*"
 * @param {const char*}
 */
getTextureData : function () {},

/**
 * @method getArmatureData
 * @return A value converted from C/C++ "cocostudio::ArmatureData*"
 * @param {const char*}
 */
getArmatureData : function () {},

/**
 * @method getAnimationData
 * @return A value converted from C/C++ "cocostudio::AnimationData*"
 * @param {const char*}
 */
getAnimationData : function () {},

/**
 * @method addAnimationData
 * @param {const char*}
 * @param {cocostudio::AnimationData*}
 * @param {const char*}
 */
addAnimationData : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method removeArmatureData
 * @param {const char*}
 */
removeArmatureData : function () {},

/**
 * @method getArmatureDatas
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getArmatureDatas : function () {},

/**
 * @method removeTextureData
 * @param {const char*}
 */
removeTextureData : function () {},

/**
 * @method addTextureData
 * @param {const char*}
 * @param {cocostudio::TextureData*}
 * @param {const char*}
 */
addTextureData : function () {},

/**
 * @method isAutoLoadSpriteFile
 * @return A value converted from C/C++ "bool"
 */
isAutoLoadSpriteFile : function () {},

/**
 * @method addSpriteFrameFromFile
 * @param {const char*}
 * @param {const char*}
 * @param {const char*}
 */
addSpriteFrameFromFile : function () {},

/**
 * @method destoryInstance
 */
destoryInstance : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocostudio::ArmatureDataManager*"
 */
getInstance : function () {},

};

/**
 * @class Armature
 */
ccs.Armature = {

/**
 * @method getBone
 * @return A value converted from C/C++ "cocostudio::Bone*"
 * @param {const char*}
 */
getBone : function () {},

/**
 * @method changeBoneParent
 * @param {cocostudio::Bone*}
 * @param {const char*}
 */
changeBoneParent : function () {},

/**
 * @method getTexureAtlasWithTexture
 * @return A value converted from C/C++ "cocos2d::TextureAtlas*"
 * @param {cocos2d::Texture2D*}
 */
getTexureAtlasWithTexture : function () {},

/**
 * @method setAnimation
 * @param {cocostudio::ArmatureAnimation*}
 */
setAnimation : function () {},

/**
 * @method getBoneAtPoint
 * @return A value converted from C/C++ "cocostudio::Bone*"
 * @param {float}
 * @param {float}
 */
getBoneAtPoint : function () {},

/**
 * @method getArmatureTransformDirty
 * @return A value converted from C/C++ "bool"
 */
getArmatureTransformDirty : function () {},

/**
 * @method setVersion
 * @param {float}
 */
setVersion : function () {},

/**
 * @method updateOffsetPoint
 */
updateOffsetPoint : function () {},

/**
 * @method setColliderFilter
 * @param {cocostudio::ColliderFilter*}
 */
setColliderFilter : function () {},

/**
 * @method setName
 * @param {std::string}
 */
setName : function () {},

/**
 * @method removeBone
 * @param {cocostudio::Bone*}
 * @param {bool}
 */
removeBone : function () {},

/**
 * @method getBatchNode
 * @return A value converted from C/C++ "cocostudio::BatchNode*"
 */
getBatchNode : function () {},

/**
 * @method getName
 * @return A value converted from C/C++ "std::string"
 */
getName : function () {},

/**
 * @method getNodeToParentTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getNodeToParentTransform : function () {},

/**
 * @method setParentBone
 * @param {cocostudio::Bone*}
 */
setParentBone : function () {},

/**
 * @method getBoundingBox
 * @return A value converted from C/C++ "cocos2d::Rect"
 */
getBoundingBox : function () {},

/**
 * @method setBatchNode
 * @param {cocostudio::BatchNode*}
 */
setBatchNode : function () {},

/**
 * @method draw
 */
draw : function () {},

/**
 * @method setArmatureData
 * @param {cocostudio::ArmatureData*}
 */
setArmatureData : function () {},

/**
 * @method setTextureAtlas
 * @param {cocos2d::TextureAtlas*}
 */
setTextureAtlas : function () {},

/**
 * @method addBone
 * @param {cocostudio::Bone*}
 * @param {const char*}
 */
addBone : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method getArmatureData
 * @return A value converted from C/C++ "cocostudio::ArmatureData*"
 */
getArmatureData : function () {},

/**
 * @method getParentBone
 * @return A value converted from C/C++ "cocostudio::Bone*"
 */
getParentBone : function () {},

/**
 * @method getVersion
 * @return A value converted from C/C++ "float"
 */
getVersion : function () {},

/**
 * @method getAnimation
 * @return A value converted from C/C++ "cocostudio::ArmatureAnimation*"
 */
getAnimation : function () {},

/**
 * @method getBoneDic
 * @return A value converted from C/C++ "cocos2d::Dictionary*"
 */
getBoneDic : function () {},

/**
 * @method getTextureAtlas
 * @return A value converted from C/C++ "cocos2d::TextureAtlas*"
 */
getTextureAtlas : function () {},

/**
 * @method Armature
 * @constructor
 */
Armature : function () {},

};

/**
 * @class Skin
 */
ccs.Skin = {

/**
 * @method getBone
 * @return A value converted from C/C++ "cocostudio::Bone*"
 */
getBone : function () {},

/**
 * @method getNodeToWorldTransformAR
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getNodeToWorldTransformAR : function () {},

/**
 * @method getNodeToWorldTransform
 * @return A value converted from C/C++ "cocos2d::AffineTransform"
 */
getNodeToWorldTransform : function () {},

/**
 * @method updateTransform
 */
updateTransform : function () {},

/**
 * @method getDisplayName
 * @return A value converted from C/C++ "std::string"
 */
getDisplayName : function () {},

/**
 * @method updateArmatureTransform
 */
updateArmatureTransform : function () {},

/**
 * @method initWithSpriteFrameName
 * @return A value converted from C/C++ "bool"
 * @param {std::string}
 */
initWithSpriteFrameName : function () {},

/**
 * @method initWithFile
 * @return A value converted from C/C++ "bool"
 * @param {std::string}
 */
initWithFile : function () {},

/**
 * @method setBone
 * @param {cocostudio::Bone*}
 */
setBone : function () {},

/**
 * @method createWithSpriteFrameName
 * @return A value converted from C/C++ "cocostudio::Skin*"
 * @param {const char*}
 */
createWithSpriteFrameName : function () {},

/**
 * @method Skin
 * @constructor
 */
Skin : function () {},

};

/**
 * @class ComAttribute
 */
ccs.ComAttribute = {

/**
 * @method getFloat
 * @return A value converted from C/C++ "float"
 * @param {const char*}
 */
getFloat : function () {},

/**
 * @method setFloat
 * @param {const char*}
 * @param {float}
 */
setFloat : function () {},

/**
 * @method setCString
 * @param {const char*}
 * @param {const char*}
 */
setCString : function () {},

/**
 * @method getCString
 * @return A value converted from C/C++ "const char*"
 * @param {const char*}
 */
getCString : function () {},

/**
 * @method getBool
 * @return A value converted from C/C++ "bool"
 * @param {const char*}
 */
getBool : function () {},

/**
 * @method setInt
 * @param {const char*}
 * @param {int}
 */
setInt : function () {},

/**
 * @method getInt
 * @return A value converted from C/C++ "int"
 * @param {const char*}
 */
getInt : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method setBool
 * @param {const char*}
 * @param {bool}
 */
setBool : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocostudio::ComAttribute*"
 */
create : function () {},

};

/**
 * @class ComAudio
 */
ccs.ComAudio = {

/**
 * @method stopAllEffects
 */
stopAllEffects : function () {},

/**
 * @method getEffectsVolume
 * @return A value converted from C/C++ "float"
 */
getEffectsVolume : function () {},

/**
 * @method stopEffect
 * @param {unsigned int}
 */
stopEffect : function () {},

/**
 * @method getBackgroundMusicVolume
 * @return A value converted from C/C++ "float"
 */
getBackgroundMusicVolume : function () {},

/**
 * @method willPlayBackgroundMusic
 * @return A value converted from C/C++ "bool"
 */
willPlayBackgroundMusic : function () {},

/**
 * @method setBackgroundMusicVolume
 * @param {float}
 */
setBackgroundMusicVolume : function () {},

/**
 * @method end
 */
end : function () {},

/**
 * @method isEnabled
 * @return A value converted from C/C++ "bool"
 */
isEnabled : function () {},

/**
 * @method pauseBackgroundMusic
 */
pauseBackgroundMusic : function () {},

/**
 * @method isBackgroundMusicPlaying
 * @return A value converted from C/C++ "bool"
 */
isBackgroundMusicPlaying : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method isLoop
 * @return A value converted from C/C++ "bool"
 */
isLoop : function () {},

/**
 * @method pauseAllEffects
 */
pauseAllEffects : function () {},

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method preloadBackgroundMusic
 * @param {const char*}
 */
preloadBackgroundMusic : function () {},

/**
 * @method resumeAllEffects
 */
resumeAllEffects : function () {},

/**
 * @method setLoop
 * @param {bool}
 */
setLoop : function () {},

/**
 * @method unloadEffect
 * @param {const char*}
 */
unloadEffect : function () {},

/**
 * @method rewindBackgroundMusic
 */
rewindBackgroundMusic : function () {},

/**
 * @method preloadEffect
 * @param {const char*}
 */
preloadEffect : function () {},

/**
 * @method pauseEffect
 * @param {unsigned int}
 */
pauseEffect : function () {},

/**
 * @method resumeBackgroundMusic
 */
resumeBackgroundMusic : function () {},

/**
 * @method setFile
 * @param {const char*}
 */
setFile : function () {},

/**
 * @method setEffectsVolume
 * @param {float}
 */
setEffectsVolume : function () {},

/**
 * @method getFile
 * @return A value converted from C/C++ "const char*"
 */
getFile : function () {},

/**
 * @method resumeEffect
 * @param {unsigned int}
 */
resumeEffect : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocostudio::ComAudio*"
 */
create : function () {},

};

/**
 * @class InputDelegate
 */
ccs.InputDelegate = {

/**
 * @method isAccelerometerEnabled
 * @return A value converted from C/C++ "bool"
 */
isAccelerometerEnabled : function () {},

/**
 * @method setKeypadEnabled
 * @param {bool}
 */
setKeypadEnabled : function () {},

/**
 * @method getTouchMode
 * @return A value converted from C/C++ "cocos2d::Touch::DispatchMode"
 */
getTouchMode : function () {},

/**
 * @method setAccelerometerEnabled
 * @param {bool}
 */
setAccelerometerEnabled : function () {},

/**
 * @method isKeypadEnabled
 * @return A value converted from C/C++ "bool"
 */
isKeypadEnabled : function () {},

/**
 * @method isTouchEnabled
 * @return A value converted from C/C++ "bool"
 */
isTouchEnabled : function () {},

/**
 * @method setTouchPriority
 * @param {int}
 */
setTouchPriority : function () {},

/**
 * @method getTouchPriority
 * @return A value converted from C/C++ "int"
 */
getTouchPriority : function () {},

/**
 * @method setTouchEnabled
 * @param {bool}
 */
setTouchEnabled : function () {},

/**
 * @method setTouchMode
 * @param {cocos2d::Touch::DispatchMode}
 */
setTouchMode : function () {},

};

/**
 * @class ComController
 */
ccs.ComController = {

/**
 * @method setEnabled
 * @param {bool}
 */
setEnabled : function () {},

/**
 * @method isEnabled
 * @return A value converted from C/C++ "bool"
 */
isEnabled : function () {},

/**
 * @method update
 * @param {float}
 */
update : function () {},

/**
 * @method init
 * @return A value converted from C/C++ "bool"
 */
init : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocostudio::ComController*"
 */
create : function () {},

/**
 * @method ComController
 * @constructor
 */
ComController : function () {},

};

/**
 * @class ComRender
 */
ccs.ComRender = {

/**
 * @method getNode
 * @return A value converted from C/C++ "cocos2d::Node*"
 */
getNode : function () {},

/**
 * @method create
 * @return A value converted from C/C++ "cocostudio::ComRender*"
 * @param {cocos2d::Node*}
 * @param {const char*}
 */
create : function () {},

};

/**
 * @class GUIReader
 */
ccs.GUIReader = {

/**
 * @method widgetFromJsonFile
 * @return A value converted from C/C++ "gui::UIWidget*"
 * @param {const char*}
 */
widgetFromJsonFile : function () {},

/**
 * @method getVersionInteger
 * @return A value converted from C/C++ "int"
 * @param {const char*}
 */
getVersionInteger : function () {},

/**
 * @method purgeGUIReader
 */
purgeGUIReader : function () {},

/**
 * @method shareReader
 * @return A value converted from C/C++ "cocostudio::GUIReader*"
 */
shareReader : function () {},

};

/**
 * @class SceneReader
 */
ccs.SceneReader = {

/**
 * @method purgeSceneReader
 */
purgeSceneReader : function () {},

/**
 * @method createNodeWithSceneFile
 * @return A value converted from C/C++ "cocos2d::Node*"
 * @param {const char*}
 */
createNodeWithSceneFile : function () {},

/**
 * @method sceneReaderVersion
 * @return A value converted from C/C++ "const char*"
 */
sceneReaderVersion : function () {},

/**
 * @method getInstance
 * @return A value converted from C/C++ "cocostudio::SceneReader*"
 */
getInstance : function () {},

};
