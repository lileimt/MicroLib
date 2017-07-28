var channel = {};

(function($,obj){
    //============ js调用C++的函数 =======================
    obj.setCurDir = function(curDir){
        bridge.slotCurDir(curDir);
    } 
    //设置公共目录的工具栏
    obj.setToolBar = function(index){
        bridge.slotChangeToolBar(index);
    }
    
    //============ C++调用js函数 =========================
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

    //监听事件，点击下载按钮获取下载文件的信息
    obj.getCurFiles = function(){
        bridge.sigCurFiles.connect(function(){   //当事件触发时，将数据发送给C++端
            var downloadFiles = [{name:"name",id:1}]
            bridge.slotCurFiles(JSON.stringify(downloadFiles));
        })
    }
})(jQuery,channel);