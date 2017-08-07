var channel = {};

(function($,obj){
    //============ js调用C++的函数 =======================
    obj.setCurDir = function(id,curDir){
        bridge.slotCurDir(id,curDir);
    } 
    //设置公共目录的工具栏
    obj.setToolBar = function(index){
        bridge.slotChangeToolBar(index);
    }
    
    obj.sendFiles = function(ids){
        bridge.slotSendFiles(ids);
    }

    obj.showSideBar = function(visible){
        bridge.slotSideBar(visible);
    }

    obj.setDeleteEnable = function(enable){
        bridge.slotDeleteEnable(enable);
    }
    //============ C++调用js函数 =========================
    //监听事件--点击按钮新建文件夹
    obj.setNewDir = function(){
        bridge.sigNewDir.connect(function(){
          newDir();
        });
    }

    //监听事件--点击按钮新建公共目录
    obj.setNewCommonDir = function(){
        bridge.sigNewCommonDir.connect(function(id,filename,permission){
           newCommonDir(id,filename,permission); 
        });  
    }

    //监听事件--根据类型选择是显示公共目录还是我的文件
    obj.getDataByType = function(){
        bridge.sigCurType.connect(function(type){
            curType = type;
            util.showTable();
        });
    }

    //监听事件--点击下载按钮获取下载文件的信息
    obj.getCurFiles = function(){
        bridge.sigCurFiles.connect(function(){   //当事件触发时，将数据发送给C++端
            var downloadFiles = getDownloadFiles();//[{id:1,name:"name.apk",size:"1023.99MB",path:"我的文件"},{id:1,name:"name",size:"1.2MB",path:"我的文件"},{id:1,name:"name",size:"1.2MB",path:"我的文件"}]
            bridge.slotCurFiles(JSON.stringify(downloadFiles));
        });
    }
    //监听事件--删除文件
    obj.deleteFiles = function(){
        bridge.sigDeleteFiles.connect(function(){
            deleteFiles();
        });
    }
    
})(jQuery,channel);