var channel = {};

(function($,obj){
    obj.setCurDir = function(curDir){
        bridge.slotCurDir(curDir);
    } 
    obj.setNewDir = function(){
        bridge.sigNewDir.connect(function(){
          newDir();
        });
    }
    obj.getDataByType = function(){
        bridge.sigCurType.connect(function(type){
            curType = type;
            util.showTable();
        });
    }
})(jQuery,channel);