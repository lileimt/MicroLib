var util = {
    setTableSort:function(curList){
        tablesort.sort(curList,"name",curSort);
    },
    showTable:function() {
        var obj = this.getCurType();
        this.setTableSort(obj.curPage);
        this.showHeader();
        channel.setCurDir(obj.curDir.id,obj.curDir.name);
        if(curMode == 0){
            showListTable(obj.curPage);
        }else{
            showViewTable(obj.curPage);
        }
    },
    showHeader:function(){
        clearTableHeader();
        setTableHeader();
        showFirstHeader(this.getCurType().curDir.name)
        showTableHeader(this.getCurType().titleArr);
    },
    getCurType:function(){
        if(curType == 0){
            return shareFile;
        }else{
            return myFile;
        }
    },
    getCurDir:function(){
        return this.getCurType().curDir;
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
    },
    getSuffix:function(fileName){
        var index1 = fileName.lastIndexOf(".");
        var index2 = fileName.length;
        var suffix = fileName.substring(index1+1,index2);
        return suffix;
    },
    getFileIcon:function(data){
        var iconPath = "filetype/";
        if(data.isDir == 1){
            return iconPath+"barcode_result_page_type_file_dir_icon.png";
        }else{
            var suffix = this.getSuffix(data.name);
            if(suffix == 'apk'){
                return iconPath+"barcode_result_page_type_apk_icon.png";
            }else if(suffix == 'doc' || suffix == 'docx'){
                return iconPath+"barcode_result_page_type_doc_icon.png";
            }else if(suffix == 'html' || suffix == 'htm'){
                return iconPath+"barcode_result_page_type_html_icon.png";
            }else if(suffix == 'jpg' || suffix == 'jpeg' || suffix == 'png' || suffix == 'bmp' || suffix == 'git' || suffix == 'icon'){
                return iconPath+"barcode_result_page_type_img_icon.png";
            }else if(suffix == 'mp3'){
                return iconPath+"barcode_result_page_type_music_icon.png";
            }else if(suffix == 'pdf'){
                return iconPath+"barcode_result_page_type_pdf_icon.png";
            }else if(suffix == 'ppt' || suffix == 'pptx'){
                return iconPath+"barcode_result_page_type_ppt_icon.png";
            }else if(suffix == 'torrent'){
                return iconPath+"barcode_result_page_type_torrent_icon.png";
            }else if(suffix == 'mp4' || suffix == 'mkv' || suffix == 'rmvb'){
                return iconPath+"barcode_result_page_type_vedio_icon.png";
            }else if(suffix == 'vcf'){
                return iconPath+"barcode_result_page_type_vcf_icon.png";
            }else if(suffix == 'txt'){
                return iconPath+"barcode_result_page_type_txt_icon.png";
            }else if(suffix == 'vsd'){
                return iconPath+"barcode_result_page_type_vsd_icon.png";
            }else if(suffix == 'xls' || suffix == 'xlsx'){
                return iconPath+"barcode_result_page_type_xls_icon.png";
            }else if(suffix == 'zip' || suffix == 'rar' || suffix == 'gz'|| suffix == '7z'){
                return iconPath+"barcode_result_page_type_zip_icon.png";
            }else{
                return iconPath+"barcode_result_page_type_unkonwn_icon.png";
            }
        }
    }
}