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

    obj.getShareFilesById = function(/*access_token,*/ id,callback){
        obj.requestApi('/microlib/v1/documents/'+id,'get',{},callback);
    }
    obj.getMyFilesById = function(/*access_token,*/ id,callback){
        obj.requestApi('/microlib/v1/myfiles/'+id,'get',{},callback);
    }
})(jQuery,oauth2);
