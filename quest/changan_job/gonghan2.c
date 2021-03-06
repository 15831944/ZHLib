//发放任务公函2
//配合长安府任务杀野兽任务的道具

#include <ansi.h>
inherit ITEM;



void create()
{
        set_name(NOR + HIY "长安府公函" NOR, ({ "gong han", "gonghan", "han" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "份");
                set("long", "这是一份长安府发放的公函，可以用(read gong han)来阅读。\n");
                set("value", 0);                
        }
        setup();
}

void init()
{
     add_action("do_read","read");     
}

int do_read( string arg )
{
    string msg, space;
    int i;
    msg = "";
    space = "                                            ";
    
    if ( !arg || ( arg != "gong han" && arg != "gonghan" && arg != "han") )
    return notify_fail("你要看什么？\n");

    msg = HIY"                      长安府公函\n\n"NOR;
    msg += WHT"    近日长安城内时有猛兽出没，伤及百姓。兹派遣民间义士\n"NOR;
    msg += "                        "HIC + query("owner") + NOR WHT
           "\n    协助官府剿杀猛兽，以保太平。\n";
    msg += "    据称，时下本城  "WHT;

    for( i=0; i < strlen(query("place"))/2; i++ ) 
    { msg += "\n                  " // + space[0..random(10)]
          + query("place")[(i*2)..(i*2+1)]; } 

    msg += "\n    处野兽出没众多，可径去此处埋伏(ambush)等待予以诛杀。\n";
    msg += HIR"                   速去速回，不得有误！\n";   
    msg += "                   长安知府：梁兴禄 签发"NOR;
    write( msg  +"\n");
    return 1;
}