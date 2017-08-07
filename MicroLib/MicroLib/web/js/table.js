//设置列表的标题栏
function setTableHeader(){
    $('.hui-table-title').html(''); 

    var img = "down"
    if(curSort == 1)img = "up";

    var html = '';
    html += '<th class="header_name" width="60%">';
    html += '    <input type="checkbox" class="hui-checkbox checkbox" id="allChecked" name="allChecked"/>';
    html += '        名称';
    html += '    <span class="rankImg">';
    html += '        <img class="hui-icon-down" src="img/'+img+'.png" />';
    html += '    </span>';
    html += '</th>';
    if(curType == 0){
        html += '<th>创建者</th>';
        html += '<th>大小</th>';
        html += '<th width="20%">创建时间</th>'; 
    }else{
        var curDir = util.getCurDir();
        if(curDir.id == 1){ //收到的文件的标题
            html += '<th>发送者</th>';
            html += '<th>大小</th>';
            html += '<th width="20%">发送时间</th>'; 
        }else{
            html += '<th>大小</th>';
            html += '<th width="20%">创建时间</th>'; 
        }
    }

    $('.hui-table-title').append(html);
}
//追加列表
function htmlListTable(data){
    data.fileIcon = util.getFileIcon(data);

    var html = '';
    html += '   <tr class="check">';
    html += '      <td>';
    html += '        <input type="checkbox" class="hui-checkbox checkbox" name="checked" />';
    html += '        <div class="hui-content">';
    html += '          <img class="hui-file-type" src='+data.fileIcon+' />';
    html += '          <div class="hui-popup">';
    html += '            <input type="text" class="hui-rename" />';
    html += '            <button class="hui-btn btn-sure"><img src="img/success.png" /></button>';
    html += '            <button class="hui-btn btn-cancel"><img src="img/close.png" /></button>';
    html += '          </div>';
    html += '          <p class="hui-ellipsis check">';
    html += '            <span class="fileName" value='+data.id+' isDir='+data.isDir+' md5='+data.md5+' permission='+data.permission+' onclick=openDir('+data.id+',this)>'+data.name+'</span>';
    html += '          </p>';
    html += '          <div class="hui-table-operate">';
    html += '            <a href="###" class="download">下载</a>';
    html += '            <a href="###" class="send">发送</a>';
    html += '            <a href="###" class="more">更多</a>';
    html += '            <ul class="hui-moreBox">';
    html += '              <li class="btn-delete">删除</li>';
    html += '              <li class="btn-rename">重命名</li>';
    html += '            </ul>';
    html += '          </div>';
    html += '        </div>';
    html += '      </td>';
    if(curType == 0){
        html += '      <td class="check">'+data.ownername+'</td>';
        var size = data.isDir == 1?'':data.filesize;
        html += '      <td class="check size">'+size+'</td>';
        html += '      <td class="check">'+data.createTime+'</td>';
    }else{
        var curDir = util.getCurDir();
        if(curDir.id == 1){ //收到的文件的标题
            html += '      <td class="check">'+data.ownername+'</td>';
            var size = data.isDir == 1?'':data.filesize;
            html += '      <td class="check size">'+size+'</td>';
            html += '      <td class="check">'+data.createTime+'</td>';
        }else{
            var size = data.isDir == 1?'':data.filesize;
            html += '      <td class="check size">'+size+'</td>';
            html += '      <td class="check">'+data.createTime+'</td>';
        }
    }
    html += '    </tr>';

    return html;
}

function appendListTable(data){
    var html = htmlListTable(data);
    $("#tbody").append(html);
}
//追加视图显示
function appendViewTable(data){
    data.fileIcon = util.getFileIcon(data);

    var html = '';
    html += '       <li class="listBox-item" isDir='+data.isDir+' ondblclick=openViewDir('+data.id+',this)>';
    html += '          <div class="listWrap">';
    html += '              <img src='+data.fileIcon+' class="filetype" />';
    html += '              <input type="checkbox" class="list-checkbox" name="selected" />';
    html += '          </div>';
    html += '          <div class="listTitle" value='+data.id+' md5='+data.md5+' permission'+data.permission+' size='+data.size+'>'+data.name+'</div>';
    html += '          <div class="popup">';
    html += '            <input type="text" class="rename" />';
    html += '            <button class="hui-btn btn-sure"><img src="img/success.png" /></button>';
    html += '            <button class="hui-btn btn-cancel"><img src="img/close.png" /></button>';
    html += '          </div>';
    html += '        </li>';

    $("#vbody").append(html);
}

//追加列表头
function showFirstHeader(text){
    var html = '';
    html += '<span>';
    html += '    <a class="hui-step first" href="###" id="0" onclick=gotoFile(this,0)>'+text+'</a>';
    html += '</span>';

    $('#tablebar').append(html);
}

function appendTableHeader(obj){
    var html = '';
    html += '<span>';
    html += '    <span> ＞ </span>';
    html += '    <a class="hui-step" href="###" id='+obj.id+' onclick=gotoFile(this,'+obj.id+')>'+obj.name+'</a>';
    html += '</span>';

    $('#tablebar').append(html);
} 

function clearTableHeader(){
    $('#tablebar').html('');
}

//清空表格内容
function clearListTable(){
    $("#tbody").html('');
}

function clearViewTable(){
    $("#vbody").html('');
}

//显示列表
function showListTable(data){
    clearListTable();
    $.each(data,function(index,value){
        appendListTable(value);
    });
}
//显示视图
function showViewTable(data){
    clearViewTable();
    $.each(data,function(index,value){
        appendViewTable(value);
    });
}

//显示路径导航栏
function showTableHeader(data){
    $.each(data,function(index,value){
        appendTableHeader(value);
    });
}

//通过id值获取信息
function getInfoById(data,id,callback){
    if(id == data.id){
         callback(data);
         return false;
    }else{
        var son = data.son;
        for(var i=0; i<son.length; i++){
            var value = son[i];
            if(value.isDir == 1){
                getInfoById(value,id,callback);
            }
            
        }
    }
}

function getIndexById(data,id){
    for(var i=0; i<data.length; i++){
        var value = data[i];
        if(value.id == id){
            return i;
        }
    }
}

function openDirParse(data,addHeader){
    var curDir = {id:data.id,name:data.name};
    util.getCurType().setCurDir(curDir);

    if(addHeader){
        util.getCurType().appendTitleArr(curDir);
        appendTableHeader(data);
    }

    if(curType == 0){//切换公共目录的工具栏
        if(util.getCurType().curDir.id == 0){  //根目录
            channel.setToolBar(0);
        }else{//子目录
            console.log("curType == 1")
            channel.setToolBar(2);
        }
    }
    setTableHeader();
    util.setTableSort(data.son);
    util.getCurType().setCurPage(data.son);
    //设置当前的目录
    channel.setCurDir(data.name);
}

//打开文件夹
function openDir(id,obj=1,addHeader=true){
    var isDir = 2;
    if(typeof obj == 'number'){
        isDir = obj;
    }else{
        isDir = $(obj).attr('isDir');
    }
    if(isDir == 1){
        console.log(util.getTotalDir())
        getInfoById(util.getTotalDir(),id,function(data){
            openDirParse(data,addHeader);
            showListTable(data.son);
        });
    }
}

function openViewDir(id,obj=1,addHeader=true){
    var isDir = 2;
    if(typeof obj == 'number'){
        isDir = obj;
    }else{
        isDir = $(obj).attr('isDir');
    } 
    if(isDir == 1){
        getInfoById(util.getTotalDir(),id,function(data){
            openDirParse(data,addHeader);
            showViewTable(data.son);
        });
    }
}

//点击表头跳转到相应的文件夹
function gotoFile(obj,id){
    console.log("goto id="+id)
    openDirByMode(id);
    var data = $(obj).parent().nextAll(); 
    for(var i=0; i<data.length; i++){
        data[i].remove();
    }
    util.getCurType().removeTitleArr(data.length);
}

function openDirByMode(id){
    if(curMode == 0){
        openDir(id,1,false);
    }else{
        openViewDir(id,1,false);
    }
}

function sendFileIds(){
    var all = null;
    var ids = [];
    if(curMode == 0){
        all = $("input[name='checked']:checked");
        $.each(all,function(index,value){
            var id = $(value).closest('tr').find('.fileName').attr('value');
            ids.push(id);
        })
    }else{
        all = $("input[name='selected']:checked");
        $.each(all,function(index,value){
            var id = $(value).closest('li').find('.listTitle').attr('value');
            ids.push(id);
        })
    }
    return ids
}

function deleteFile(id){
    var index = getIndexById(util.getCurPage(),id);
    util.getCurPage().splice(index,1);
}

function deleteFiles(){
    console.log('deleteFiles')
    var all = null;
    var ids = [];
    if(curMode == 0){
        all = $("input[name='checked']:checked");
        console.log(all)
        $.each(all,function(index,value){
            console.log($(value))
            var id = $(value).closest('tr').find('.fileName').attr('value');
            ids.push(id);
        })
    }else{
        all = $("input[name='selected']:checked");
        $.each(all,function(index,value){
            var id = $(value).closest('li').find('.listTitle').attr('value');
            ids.push(id);
        })
    }
    console.log(ids)
    //oauth2.deleteFile(ids,function(data){
    //    if(data.error_code == 0){
            $.each(ids,function(index,value){
                deleteFile(value);
            })
            $.each(all,function(index,value){
                if(curMode == 0){
                    $(value).closest('tr').remove();
                }else{
                    $(value).closest('li').remove();
                }
            })
    //    }
    //})
}

function renameFile(data,id,oldName,newName,callback){
    oauth2.renameFile(id,newName,function(value){
        if(value.error_code == 0){
            $.each(data,function(index,value){
                if(value.name == oldName){
                    value.name = newName;
                }
            });
        }
        callback(value.error_code);
    })
}

function newDir(){
    if(curMode == 0){  //列表模式
        var data = {
            id:100,
            isDir:1,
            name:"新建文件夹",
            ownername:"lileimt",
            filesize:"11.1 MB",
            createTime:"11:11"
        };
        var html = htmlListTable(data);
        $("#tbody").prepend(html);
        util.getCurPage().splice(0,0,data)
    }else{

    }
}

function getDownloadFiles(){
    var all = null;
    var downloadFiles = [];
    if(curMode == 0){
        all = $("input[name='checked']:checked");
        $.each(all,function(index,value){
            var obj = $(value).closest('tr').find('.fileName');
            var id = obj.attr('value');
            var md5 = obj.attr('md5');
            var filename = obj.text();
            var size = $(value).closest('tr').find('size').text();
            var data = {
                id:id,
                md5:md5,
                name:filename,
                size:size,
                path:"MicroLib"
            }
            downloadFiles.push(data);
        });
    }else{
        all = $("input[name='selected']:checked");
        $.each(all,function(index,value){
            var obj = $(value).closest('li').find('.listTitle');
            var id = obj.attr('value');
            var md5 = obj.attr('md5');
            var filename = obj.text();
            var size = obj.attr('size');
            var data = {
                id:id,
                md5:md5,
                name:filename,
                size:size,
                path:"MicroLib"
            }
            downloadFiles.push(data);
        });
    }
    return downloadFiles;
}