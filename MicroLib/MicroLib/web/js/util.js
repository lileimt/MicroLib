var util = {
    setTableSort:function(curList){
        curListData = curList;
        tablesort.sort(curListData,"fileName",curSort);
    },
    showTable:function(obj) {
        this.setTableSort(obj.curListData.children);
        $(".hui-step").text(obj.curDir.fileName);
        channel.setCurDir(obj.curDir.fileName);
        showListTable(obj.curListData.children);
    }
}