$(function(){
    //阻止tbody里的右键点击事件
    $(".hui-resize-table").bind("contextmenu", function(e){
        if (e.which == 3) {
            var offset = $(this).offset();
            var relativeX = (e.pageX - offset.left);
            var relativeY = (e.pageY - offset.top);
            $('#operate').show().css({left:relativeX+'px',top:relativeY - 30 +'px'});
            $('html').click(function(){
                $('#operate').hide();
            })
            $("#operate").click(function(event){
                event.stopPropagation();
            });
            $('#tbody,#vbody').bind("contextmenu", function(e){
                if(e.which ==3){
                    $('#operate').hide();
                }
            })
             return false;
        }
    })
    $(".hui-table-title,.hui-path").bind("contextmenu", function(e){
        return false;
    })
    //右键菜单
    $("#tbody").on("contextmenu", 'tr',function(e){
        //右键为3
        if ( e.which == 3) {
            var self = $(this);
            $('#operate').hide();

            $('#rightKey').show().css({left:e.pageX+'px',top:e.pageY-30+'px'});
            self.find('.hui-checkbox').prop('checked',true);
            self.find('td').addClass('bground boderColor')
            self.siblings().find('.hui-checkbox').prop('checked',false);
            self.siblings().find('td').removeClass('bground boderColor')
           
            //重命名
            $('.rightKeyRename').off('click').bind('click',function(){
                var inputBox = self.find('.hui-popup');
                var input = self.find('.hui-popup').children('.hui-rename');
                var txt = self.find('.fileName').text();
                inputBox.show();
                input.val(txt);
                input.focus();
                self.siblings().find('.hui-popup').hide();
                $('#rightKey').hide();
            });
            //删除
            $('.rightKeyDelete').off('click').bind('click',function(){
                if(self.find('.hui-checkbox').prop('checked')){
                    var id = self.find('.fileName').attr('value');
                    oauth2.deleteFile([id],function(data){
                        if(data.error_code == 0){
                            deleteFile(id);
                            self.remove();
                        }
                    })
                }
                $('#rightKey').hide();
            });
            //鼠标点击除右键菜单外的其他地方，隐藏菜单
            $('html').off('click').click(function(){
                $('#rightKey').hide();
            })
            $('.hui-resize-table').off('contextmenu').bind("contextmenu", function(e){
                if(e.which ==3){
                    $('#rightKey').hide();
                }
            })
            $('#rightKey').off('click').click(function(event){
                event.stopPropagation();
            });
        }
        return false;
    });

    //鼠标经过行变色和显示更多
    $('#tbody').on('mouseenter','tr',function(){
        if($(this).find("input[name='checked']").prop("checked")){
            $(this).find('td').addClass('boderColor').removeClass('bground');
        }else{
            $(this).find('td').addClass('boderColor');
        }
        if(!$(this).find('.hui-popup').is(":hidden")){
            $(this).find('.hui-table-operate').hide();
            $(this).find('.hui-content').css('padding-right','0')
        }else{
            $(this).find('.hui-table-operate').show();
            $(this).find('.hui-content').css('padding-right','100px')
        }
    })
    $('tbody').on('mouseleave','tr',function(){
        if($(this).find("input[name='checked']").prop("checked")){
             $(this).find('td').addClass('bground boderColor');
        }else{
            $(this).find('td').removeClass('boderColor bground');
        }
        $(this).find('.hui-table-operate').hide();
        $(this).find('.hui-content').css('padding-right','0')

        $('.hui-moreBox').hide();
    })
    //更多操作
    $('#tbody').on('click','.more',function(){
        $(this).next('.hui-moreBox').toggle();
    })
    //发送文件
    $('#tbody').on('click','.send',function(){
        var id = $(this).closest('td').find('.fileName').attr('value');
        channel.sendFiles([id]);
    });
    $('#tbody').on('click','.btn-rename,.btn-delete',function(){
        $('.hui-moreBox').hide();
    })
    //重命名
    $('#tbody').on('click','.btn-rename',function(){
        var inputBox = $(this).closest('tr').find('.hui-popup');
        var input = $(this).closest('tr').find('.hui-popup').children('.hui-rename');
        var txt = $(this).closest('tr').find('.fileName').text();
        inputBox.show();
        input.val(txt);
        input.focus();
        $(this).closest('tr').find('.hui-checkbox').prop('checked',true);
        $(this).closest('tr').siblings().find('.hui-popup').hide();
    })
    //取消重命名
    $('#tbody').on('click','.btn-cancel',function(){
         $(this).closest('.hui-popup').hide();
         $(this).closest('tr').find('.hui-checkbox').prop('checked',false);
    })
    //确定重命名 ——按钮
    $('#tbody').on('click','.btn-sure',function(){
        var id = $(this).closest('td').find('.fileName').attr('value');
        var oldName = $(this).closest('td').find('.fileName').text();
        var newName = $(this).prev('.hui-rename').val();
        renameFile(util.getCurPage(),id,oldName,newName,function(data){
            if(data == 0){
                $(this).closest('td').find('.fileName').text(newName);
            }
            $(this).closest('.hui-popup').hide();
            $(this).closest('tr').find('.hui-checkbox').prop('checked',false);
        }); 
    })
    //重命名 —— 回车
    $(document).keyup(function(event){
        var target = event.target;
        if(event.keyCode==13){
            if($('#sample2').is(':visible')){
                $(target).closest('tr').find(".btn-sure").trigger("click");
            }else{
                $(target).closest('li').find(".btn-sure").trigger("click");
            }
        }
    });
    //全选
    $(".hui-table-title").on('click','#allChecked',function(e){
        e.stopPropagation();
        if($("#allChecked").prop("checked")){
             $("input[name='checked']").prop("checked", true);
             $('#tbody').find('td').addClass('bground boderColor');
        }else{
             $("input[name='checked']").prop("checked", false);
             $('#tbody').find('td').removeClass('bground boderColor');
        }
    });
    var allSelect = function(){
        var number =  $("input[name='checked']").length;
        var count =  $("input[name='checked']:checked").length;
        if(number == count){
            $("#allChecked").prop("checked", true);
        }else{
            $("#allChecked").prop("checked", false);
        }
    }
    //选择框
    $('#tbody').on('click','.hui-checkbox',function(e){
        e.stopPropagation();
        allSelect();
        if($(this).prop("checked")){
            $(this).closest('tr').find('td').addClass('bground boderColor');
        }else{
            $(this).closest('tr').find('td').removeClass('bground boderColor');
        }
    });
    //点击行选中
    $('#tbody').on('click','.check',function(){
        $(this).closest('tr').find('td').addClass('bground boderColor');
        $(this).closest('tr').find('.hui-checkbox').prop("checked",true);
        $(this).closest('tr').siblings().find('td').removeClass('bground boderColor');
        $(this).closest('tr').siblings().find('.hui-checkbox').prop("checked",false);
        $("#allChecked").prop("checked", false);
    });
    //删除
    $('#tbody').on('click','.btn-delete',function(){
        var self =  $(this);
        var id = self.closest('tr').find('.fileName').attr('value');
        oauth2.deleteFile([id],function(data){
            if(data.error_code == 0){
                deleteFile(id);
                self.closest('tr').remove();
            }
        })
    });
    //刷新
    $('#refreshBtn').bind('click',function(){
        tablesort.sort(util.getCurPage(),"name",curSort)
        if($('#sample2').is(':visible')){
            clearListTable();
            showListTable(util.getCurPage());
        }else{
            clearViewTable();
            showViewTable(util.getCurPage());
        }
    })
    //排序类型
    $('#rankBtn').bind('click',function(){
       $('.rankBox').toggle();
    });
    $('.rankIcon').bind('click',function(){
        if($(this).find('img').attr('src')=='img/down.png'){
             $(this).find('img').attr('src','img/up.png');
             curSort = 1
             tablesort.sort(util.getCurPage(),"name",curSort)
        }else{
            $(this).find('img').attr('src','img/down.png');
            curSort = 0
            tablesort.sort(util.getCurPage(),"name",curSort)
        }
        clearListTable();
        showListTable(util.getCurPage());
    });
    $('.hui-table-title').on('click','.header_name',function(){
        if($(this).find('img').attr('src')=='img/down.png'){
            $(this).find('img').attr('src','img/up.png');
            curSort = 1
            tablesort.sort(util.getCurPage(),"name",curSort)
        }else{
            $(this).find('img').attr('src','img/down.png');
            curSort = 0
            tablesort.sort(util.getCurPage(),"name",curSort)
        }
        clearListTable();
        showListTable(util.getCurPage());
    });
    //切换排列
    $('#cutBtn').bind('click',function(){
        if($('#sample2').is(':visible')){
            $(this).attr('src','img/tile.png')
            $('#sample2').hide();
            $('#sample1').show();
            clearListTable();
            showViewTable(util.getCurPage());
            curMode = 1;
        }else{
            $(this).attr('src','img/list.png')
            $('#sample1').hide();
            $('#sample2').show();
            clearViewTable();
            showListTable(util.getCurPage());
            curMode = 0;
        }
    })
    //大图标 选择文件
    $('#vbody').on('mouseenter','.listBox-item',function(){
        $(this).find("input[name='selected']").show();
    })
    $('#vbody').on('mouseleave','.listBox-item',function(){
        if($(this).find("input[name='selected']").prop('checked')){
            $(this).find("input[name='selected']").show();
        }else{
            $(this).find("input[name='selected']").hide();
        }
    })
     //全选
    $("#imgAllChecked").bind('click',function(){
        if($("#imgAllChecked").prop("checked")){
             $("input[name='selected']").prop("checked", true).show();
             $('.listBox').find('.listWrap').addClass('active');
         }else{
             $("input[name='selected']").prop("checked", false).hide();
             $('.listBox').find('.listWrap').removeClass('active');
         }
    });
    //单击选择
    $('#vbody').on('click','.listWrap,.list-checkbox',function(){
        if($(this).closest('.listWrap').find('.list-checkbox').prop('checked')){
            $(this).closest('.listWrap').find('.list-checkbox').prop('checked',false)
            $(this).closest('.listWrap').removeClass('active');
        }else{
            $(this).closest('.listWrap').find('.list-checkbox').prop('checked',true)
            $(this).closest('.listWrap').addClass('active');
        }
        var number =  $("input[name='selected']").length;
        var count =  $("input[name='selected']:checked").length;
        if(number == count){
            $("#imgAllChecked").prop("checked", true);
        }else{
            $("#imgAllChecked").prop("checked", false);
        }
    });

    //右键菜单
    $("#vbody").on("contextmenu", "li",function(e){
        //右键为3
        if ( e.which == 3) {
            var self = $(this);

            $('#rightKey').show().css({left:e.pageX+'px',top:e.pageY-30+'px'});

            //点击右键选中当前文件
            self.find('.list-checkbox').prop('checked',true);
            self.find('.listWrap').addClass('active')
            self.siblings().find(".list-checkbox").hide();
            self.siblings().find('.list-checkbox').prop('checked',false);
            self.siblings().find('.listWrap').removeClass('active');
            $("#imgAllChecked").prop("checked", false);
                   
            //重命名
            $('.rightKeyRename').off('click').bind('click',function(){
                var inputBox = self.find('.popup');
                var input = self.find('.popup').children('.rename');
                var txt = self.find('.listTitle').text();
                inputBox.show();
                input.val(txt);
                input.focus();
                self.siblings().find('.popup').hide();
                $('#rightKey').hide();
            });

            //删除
            $('.rightKeyDelete').off('click').bind('click',function(){
                if(self.find('.list-checkbox').prop('checked')){
                    var fileName = self.find('.listTitle').text();
                    var index = getIndexByName(util.getCurPage(),fileName);
                    util.getCurPage().splice(index,1);
                    self.remove();
                }
                $('#rightKey').hide();
            });
            //鼠标点击除右键菜单外的其他地方，隐藏菜单
            $('html').off('click').click(function(){
                $('#rightKey').hide();
            })
            $("#rightKey").off('click').click(function(event){
                event.stopPropagation();
            });
            $('.hui-resize-table').off('contextmenu').bind("contextmenu", function(e){
                if(e.which ==3){
                    $('#rightKey').hide();
                }
            })
        }
        return false;
    });

    //取消重命名
    $('#vbody').on('click','.popup .btn-cancel',function(){
        $(this).closest('li').find('.popup').hide();
        $(this).closest('li').find('.list-checkbox').prop('checked',false);
        $(this).closest('li').find('.listWrap').removeClass('active');
    });
    //确定重命名 ——按钮
    $('#vbody').on('click','.popup .btn-sure',function(){
        var id = $(this).closest('li').find('.listTitle').attr('value');
        var oldName = $(this).closest('li').find('.listTitle').text();
        var newName = $(this).prev('.rename').val();
        
        renameFile(util.getCurPage(),id,oldName,newName,function(data){
            if(data == 0){
                $(this).closest('li').find('.listTitle').text(newName);
            }
            $(this).closest('li').find('.popup').hide();
            $(this).closest('li').find('.list-checkbox').prop('checked',false);
            $(this).closest('li').find('.listWrap').removeClass('active');
        });
    })
    
    //点击返回按钮
    $(".hui-arrows").click(function(){
        var span = $("#tablebar > span").last();
        var id = span.children("a.hui-step").attr("id");
        if(id != 0){
            span.remove();
            util.getCurType().removeTitleArr(1);
            span = $("#tablebar > span").last();
            id = span.children("a.hui-step").attr("id");
            openDirByMode(id);
        }
    })
});