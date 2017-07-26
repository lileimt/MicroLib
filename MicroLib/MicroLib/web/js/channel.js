var channel = {};

(function($,obj){
    obj.setCurDir = function(curDir){
        bridge.slotCurDir(curDir);
    } 
    //监听事件--点击按钮新建文件夹
    obj.setNewDir = function(){
        bridge.sigNewDir.connect(function(){
          newDir();
        });
    }
    //监听事件--根据类型选择是显示公共目录还是我的文件
    obj.getDataByType = function(){
        bridge.sigCurType.connect(function(type){
            curType = type;
            util.showTable();
        });
    }
})(jQuery,channel);