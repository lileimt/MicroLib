var util = {
    setTableSort:function(curList){
        tablesort.sort(curList,"fileName",curSort);
    },
    showTable:function() {
        var obj = this.getCurType();
        this.setTableSort(obj.curPage);
        this.showHeader();
        channel.setCurDir(obj.curDir.fileName);
        if(curMode == 0){
            showListTable(obj.curPage);
        }else{
            showViewTable(obj.curPage);
        }
    },
    showHeader:function(){
        clearTableHeader();
        showFirstHeader(this.getCurType().curDir.fileName)
        showTableHeader(this.getCurType().titleArr);
    },
    getCurType:function(){
        if(curType == 0){
            return shareFile;
        }else{
            return myFile;
        }
    },
    getCurPage:function(){
        if(curType == 0){
            return shareFile.curPage;
        }else{
            return myFile.curPage;
        }
    },
    getTotalDir:function(){
        if(curType == 0){
            return shareFile.totalDir;
        }else{
            return myFile.totalDir;
        }
    }
}