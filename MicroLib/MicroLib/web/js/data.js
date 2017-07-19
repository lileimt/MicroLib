function ListType(type,curDir){
    this.curListData = {};   //当前列表的数据
    this.curType = type;     //当前列表的类型 0代表公共目录，1代表我的文件
    this.curDir = curDir;    //当前显示的文件夹的名称
}

ListType.prototype.getCurData = function(id,callback){
    if(curType == 0){//获取公共目录的数据
        // oauth2.getShareById(id,{
        //     success:function(data){
        //         curListData = data
        //         tablesort.sort(curListData,"fileName",curSort)
        //         callback()
        //     },error:function(xhr,type,errorThrown){
        //         console.log(xhr);
        //     }
        // })
         curListData = listData
         tablesort.sort(curListData,"fileName",curSort)
    }else{
        // oauth2.getFileById(id,{
        //     success:function(data){
        //         curListData = data
        //         tablesort.sort(curListData,"fileName",curSort)
        //         callback()
        //     },error:function(xhr,type,errorThrown){
        //         console.log(xhr);
        //     }
        // })
    }
}

ListType.prototype.setCurDir = function(curDir){
    this.curDir = curDir;
}

ListType.prototype.checkFile = function(fileName){
    for(var i=0; i<curListData.length; i++){
        var data = curListData[i]
        if(data.fileName == fileName){
            return true;
        }
    }
    return false;
}

ListType.prototype.getIndexOfRename = function(fileName){
    var tempList = curListData
    if(curSort == 0){//降序
        tablesort.sort(tempList,"fileName",1)
    }
    var count = 0;
    //var re = new RegExp("^"+fileName+"(\\(\\d+\\))?$","g")
    for(var i=0; i<curListData.length; i++){
        var data = curListData[i]
        if(data.fileName.indexof(fileName) > 0){
            count++;
            continue;
        }
        if(count != 0){
            return count;
        }
    }
}

ListType.prototype.getNewFileName = function(fileName,isDir){
    var index = getIndexOfRename(fileName)
    var newName = ''
    if(!isDir){
        var fileExtension = fileName.split('.').pop();
        var realName = fileName.split('.').pop();
        newName = realName+'('+index+')';
    }else{
        newName = fileName+'('+index+')';
    }
    return newName;
}

ListType.prototype.createNewDir = function(fileName,callback){
    callback()
}

ListType.prototype.renameFile = function(fileName,isDir,callback){
    //调用接口
    callback()
}

ListType.prototype.deleteFile = function(fileName,callback){
    callback()
}