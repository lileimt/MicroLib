var oauth2 = {};

(function($,obj) {
    $.extend(obj, {
        BASE_URL: 'http://api-x.sunfuedu.com'
    });

    obj.requestApi = function(/*access_token,*/ url, method,data, callback) {
		url = obj.BASE_URL + url;
		
        if (method.toLowerCase() != 'get') {
            data = JSON.stringify(data);
        }
        settings = $.extend({
            data: data,
            dataType: 'json',
            type: method,
            contentType: 'application/json',
            timeout: 10000,
            headers: {
                'Authorization': 'Bearer ' + 'cacad8ee62c543f88f516f2deb9e658b'//access_token
            }
        }, callback);

        $.ajax(url, settings);
    };
    //使用同一个接口
    obj.getShareFilesById = function(/*access_token,*/ id,callback){
        obj.requestApi('/microlib/v1/files/'+id+"?share_type=2",'get',{},callback);
    }
    obj.getMyFilesById = function(/*access_token,*/ id,callback){
        obj.requestApi('/microlib/v1/files/'+id+"?share_type=1",'get',{},callback);
    }
    obj.renameFile = function(id,newName,callback){
        var data ={
            newName:newName,
            src_type:"files"
        }
        obj.requestApi('/microlib/v1/files/'+id+'/name','put',data,callback);
    }
    obj.deleteFile = function(ids,callback){
        var data = {
            ids:ids,
            src_type:"files"
        }
        //console.log(data)
        obj.requestApi('/microlib/v1/files/ids/status','delete',data,callback);
    }
    // obj.sendFiles = function(ids,receiveIds,comment,callback){
    //     var data = {
    //         ids:ids,
    //         receiveIds:receiveIds,
    //         comment:comment
    //     }
    //     obj.requestApi('/microlib/v1/files/ids/content','post',data,callback);
    // }
    obj.getStorageHost = function(md5,callback){
        obj.requestApi('/microlib/v1/files/md5?md5='+md5,'get',{},callback);
    }
})(jQuery,oauth2);
