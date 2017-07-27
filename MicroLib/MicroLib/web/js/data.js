function ListType(type,curDir){
    this.totalDir = {};   //当前列表的数据
    this.curPage = {};
    this.curType = type;     //当前列表的类型 0代表公共目录，1代表我的文件
    this.curDir = curDir;    //当前显示的文件夹的名称
    this.titleArr = new Array;
}

ListType.prototype.getCurData = function(id,callback){
    if(curType == 0){//获取公共目录的数据
        oauth2.getShareFilesById(id,{
            success:function(data){
                curPage = data
                tablesort.sort(curPage,"fileName",curSort)
                callback(data)
            },error:function(xhr,type,errorThrown){
                console.log(xhr);
            }
        });
    }else{
        oauth2.getMyFilesByIds(id,{
            success:function(data){
                curPage = data
                tablesort.sort(curPage,"fileName",curSort)
                callback(FormData)
            },error:function(xhr,type,errorThrown){
                console.log(xhr);
            }
        })
    }
}

ListType.prototype.setCurDir = function(curDir){
    this.curDir = curDir;
}

ListType.prototype.setCurPage = function(curPage){
    this.curPage = curPage;
}

ListType.prototype.appendTitleArr = function(curDir){
    this.titleArr.push(curDir);
}
//删除路径导航栏
ListType.prototype.removeTitleArr = function(count){
    var length = this.titleArr.length;
    this.titleArr.splice(length-count-1,count);
}

ListType.prototype.checkFile = function(fileName){
    var children = curPage.children;
    for(var i=0; i<children.length; i++){
        var data = children[i];
        if(data.fileName == fileName){
            return true;
        }
    }
    return false;
}

ListType.prototype.getIndexOfRename = function(fileName){
    var tempList = curPage;
    if(curSort == 0){//降序
        tablesort.sort(tempList,"fileName",1);
    }
    var count = 0;
    //var re = new RegExp("^"+fileName+"(\\(\\d+\\))?$","g")
    var children = tempList.children;;
    for(var i=0; i<children.length; i++){
        var data = children[i];
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
    var index = getIndexOfRename(fileName);
    var newName = '';
    if(!isDir){
        var fileExtension = fileName.split('.').pop();
        var realName = fileName.split('.').pop();
        newName = realName+'('+index+')';
    }else{
        newName = fileName+'('+index+')';
    }
    return newName;
}

ListType.prototype.createNewShareDir = function(data,callback){
    oauth2.requestApi("/microlib/v1/sharefiles/documents","post",data,{
        success:function(data){
            callback(data)
        },error:function(xhr,type,errorThrown){
            console.log(xhr);
        }
    })
}

ListType.prototype.renameFile = function(id,newName,callback){
    var data = {
        newName:newName,
        src_type:"files"
    }
    oauth2.requestApi("/microlib/v1/files/"+id+"/name","put",data,{
        success:function(data){
            callback(data)
        },error:function(xhr,type,errorThrown){
            console.log(xhr);
        }
    })
}

ListType.prototype.deleteFile = function(ids,callback){
    var data = {
        ids:ids,
        src_type:"files"
    }
    oauth2.requestApi("/microlib//v1/files/ids/status","delete",data,{
        success:function(data){
            callback(data)
        },error:function(xhr,type,errorThrown){
            console.log(xhr);
        }
    })
}