//设置列表的标题栏
function setTableHeader(){
    $('.hui-table-title').html(''); 

    var html = '';
    html += '<th class="header_name" width="60%">';
    html += '    <input type="checkbox" class="hui-checkbox checkbox" id="allChecked" name="allChecked"/>';
    html += '        名称';
    html += '    <span class="rankImg">';
    html += '        <img class="hui-icon-down" src="img/down.png" />';
    html += '    </span>';
    html += '</th>';
    if(curType == 0){
        html += '<th>创建者</th>';
        html += '<th>大小</th>';
        html += '<th>创建时间</th>'; 
    }else{
        var curDir = util.getCurDir();
        if(curDir.id == 1){ //收到的文件的标题
            html += '<th>发送者</th>';
            html += '<th>大小</th>';
            html += '<th>发送时间</th>'; 
        }else{
            html += '<th>大小</th>';
            html += '<th>创建时间</th>'; 
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
    html += '            <span class="fileName" value='+data.id+' isDir='+data.isDir+' onclick=openDir('+data.id+',this)>'+data.fileName+'</span>';
    html += '          </p>';
    html += '          <div class="hui-table-operate">';
    html += '            <a href="###">下载</a>';
    html += '            <a href="###">发送</a>';
    html += '            <a href="###" class="more">更多</a>';
    html += '            <ul class="hui-moreBox">';
    html += '              <li class="btn-delete">删除</li>';
    html += '              <li class="btn-rename">重命名</li>';
    html += '            </ul>';
    html += '          </div>';
    html += '        </div>';
    html += '      </td>';
    html += '      <td class="check">'+data.ownerName+'</td>';
    html += '      <td class="check">'+data.fileSize+'</td>';
    html += '      <td class="check">'+data.createTime+'</td>';
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
    html += '          <div class="listTitle" >'+data.fileName+'</div>';
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
    html += '    <a class="hui-step" href="###" id='+obj.id+' onclick=gotoFile(this,'+obj.id+')>'+obj.fileName+'</a>';
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
function getInfoById(/*data,*/id,callback){
    // if(id == data.id){
    //     //设置当前的目录
    //     channel.setCurDir(data.fileName)
    //     callback(data);
    //     return false;
    // }else{
    //     if(data.isDir){
    //         var children = data.children;
    //         for(var i=0; i<children.length; i++){
    //             var value = children[i];
    //             getInfoById(value,id,callback);
    //         }
    //     }
    // }
    util.getCurType().getCurData(id,callback);
}

// function getIndexById(data,id){
//     for(var i=0; i<data.length; i++){
//         var value = data[i];
//         if(value.id == id){
//             return i;
//         }
//     }
// }

function openDirParse(data,addHeader)
{
    if(addHeader){
        var curDir = {id:data.id,fileName:data.filename};
        util.getCurType().appendTitleArr(curDir);
        appendTableHeader(data);
    }
    
    if(curType == 0){//切换公共目录的工具栏
        if(util.getCurType().curDir.id == 0){  //根目录
            channel.setToolBar(0);
        }else{//子目录
            channel.setToolBar(2);
        }
    }
    setTableHeader();
    util.setTableSort(data.children);
    util.getCurType().setCurPage(data.children);
    //设置当前的目录
    channel.setCurDir(data.filename);
}

//打开文件夹
function openDir(id,obj=true,addHeader=true){
    var isDir = false;
    if(typeof obj == 'boolean'){
        isDir = obj;
    }else{
        isDir = $(obj).attr('isDir');
    }  
    if(isDir){
        getInfoById(/*util.getTotalDir(),*/id,function(data){
            if(data.isDir){
                openDirParse(data,addHeader);
                showListTable(data.children);
            }
        });
    }
}

function openViewDir(id,obj=true,addHeader=true){
    var isDir = false;
    if(typeof obj == 'boolean'){
        isDir = obj;
    }else{
        isDir = $(obj).attr('isDir');
    } 
    if(isDir){
        getInfoById(/*util.getTotalDir(),*/id,function(data){
            if(data.isDir){
                openDirParse(data,addHeader);
                showViewTable(data.children);
            }
        });
    }
}

//点击表头跳转到相应的文件夹
function gotoFile(obj,id){
    openDirByMode(id);
    var data = $(obj).parent().nextAll(); 
    for(var i=0; i<data.length; i++){
        data[i].remove();
    }
    util.getCurType().removeTitleArr(data.length);
}

function openDirByMode(id){
    if(curMode == 0){
        openDir(id,true,false);
    }else{
        openViewDir(id,true,false);
    }
}

function deleteFile(id){
    var index = getIndexById(util.getCurPage(),id);
    util.getCurPage().splice(index,1);
}

function renameFile(data,oldName,newName){
    $.each(data,function(index,value){
        if(value.fileName == oldName){
            value.fileName = newName;
        }
    });
}

function newDir(){
    if(curMode == 0){  //列表模式
        var data = {
            id:100,
            isDir:true,
            fileName:"新建文件夹",
            ownerName:"lileimt",
            fileSize:"11.1 MB",
            createTime:"11:11"
        };
        var html = htmlListTable(data);
        $("#tbody").prepend(html);
        util.getCurPage().splice(0,0,data)
    }else{

    }
}