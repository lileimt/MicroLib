var tablesort = {
    sort:function (array, parm, sortby) {
        var down = function (x, y) {
            if(x.isDir ^ y.isDir){
                if(x.isDir)return -1;
                else return 1;
            } 
            return (eval("x." + parm) > eval("y." + parm)) ? -1 : 1
        }//通过eval对json对象的键值传参
        var up = function (x, y) {
            if(x.isDir ^ y.isDir){
                if(x.isDir)return -1;
                else return 1;
            } 
            return (eval("x." + parm) < eval("y." + parm)) ? -1 : 1
        }
        if(array.length > 0){
            if (sortby == 0) {//down
                array.sort(down)
            }else {
                array.sort(up)
            }
        }  
    }
}