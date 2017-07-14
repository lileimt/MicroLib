function appendListTable(data)
{
    var html = '';
    html += '   <tr>';
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
    html += '            <span class="fileName" onclick=openDir('+data.id+')>'+data.fileName+'</span>';
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

    $("#tbody").append(html);
}

function appendViewTable(table)
{
    var html = '';
    html += '   <li class="listBox-item">';
    html += '          <div class="listWrap">';
    html += '              <img src='+table.fileIcon+' class="filetype" />';
    html += '              <input type="checkbox" class="list-checkbox" name="selected" />';
    html += '          </div>';
    html += '          <div class="listTitle">'+table.fileName+'</div>';
    html += '          <div class="popup">';
    html += '            <input type="text" class="rename" />';
    html += '            <button class="hui-btn btn-sure"><img src="img/success.png" /></button>';
    html += '            <button class="hui-btn btn-cancel"><img src="img/close.png" /></button>';
    html += '          </div>';
    html += '        </li>';

    $("#vbody").append(html);
}

function clearListTable(){
    $("#tbody").html('');
}

function showListTable(data)
{
    $.each(data,function(index,value){
        appendListTable(value);
    })
}

function getInfoById(data,id,callback)
{
    for(var i=0; i<data.length; i++){
        var value = data[i];
        if(value.id == id){
            callback(value);
            return false;
        }
        if(value.isDir){
            getInfoById(value.children,id,callback);
        }
    }
}

function openDir(id)
{
    getInfoById(table,id,function(obj){
        if(obj.isDir){
            clearListTable();
            //console.log(obj.children)
            showListTable(obj.children);
        }
    });
}