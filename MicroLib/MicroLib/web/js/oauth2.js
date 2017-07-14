var oauth2 = {};

(function($,obj) {
    $.extend(obj, {
        BASE_URL: 'http://api-x.sunfuedu.com'
    });

    obj.requestApi = function(access_token, url, method,data, callback) {
		url = obj.BASE_URL + '/' + url;
		
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
                'Authorization': 'Bearer ' + access_token
            }
        }, callback);

        $.ajax(url, settings);
    };
})(jQuery,oauth2);
