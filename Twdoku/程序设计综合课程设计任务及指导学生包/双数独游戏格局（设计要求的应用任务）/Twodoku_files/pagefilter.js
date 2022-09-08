MTLastPos=0;
HaveGL=0;  //Чтобы каждый раз не проверять при скроле, есть ли поле с рекламой для прокрутки
ScrollLimHide=800; //Растояние до конца таблицы, чтобы скрыть верхнюю пагинацию
TopScrollGlueVisible=true;
Spins={};


jQuery(document).ready(function() {
    //setTimeout( MLoadTrends,3000);
    jQuery(document).on('click','.filtercheckbox',function(e){
        var s=this.id;
        var HiddenInput=$('#'+s+'_v');
        var v=$(HiddenInput).val();
        v++;
        if (v>2) v=0;
        //$(HiddenInput).val(v);
        SetFilterBoxVal(s,v);
    });

    GetSpins();

    jQuery(document).on('click','.filterspin',function(e){
        var s=this.id;
        var HiddenInput=$('#'+s+'_v');
        var v=$(HiddenInput).val();
        v++;
        if (v>Spins[s]) v=0;
        //$(HiddenInput).val(v);
        SetSpinVal(s,v);
    });
});


function SetSpinVal(s,v) {
    if (v===undefined) v=$('#'+s+'_v').val();  else {
        $('#'+s+'_v').val(v);
    }

    $('#'+s+' img').attr('src',SiteName+'/img/icon/filter/'+s+'/'+v+'.png');
}


function GetSpins() {
    $('.filterspin').each(function (){
        var s=$(this).attr('id');
        Spins[s]=parseInt($(this).attr('abbr'));
        SetSpinVal(s);
    });
}


function SetFilterBoxVal(s,v) {
    if (v===undefined) {
        v=$('#'+s+'_v').val();
    } else {
        $('#'+s+'_v').val(v);
    }
    $('#'+s).removeClass('filtercheckbox_1');
    $('#'+s).removeClass('filtercheckbox_2');
    if (v>0) {
        $('#'+s).addClass('filtercheckbox_'+v);
    }
}



if (typeof setFilterFunc === 'function') setFilterFunc();