// By yuchang@zhyx
#include <ansi.h> 
inherit ROOM;
void create()
{
        set("short", "Ծ����");
        set("long", @LONG  
�����ǳ���������Ծ����,���м�������ʯ����
�������������̽�����ʯ��ͷ�������㾦��Ϊʯ
��ƽ������������
LONG
        ); 
        set("item_desc", ([       
"ʯ��ͷ" : "������һȦ������Բ���������ĽӺۣ���������Ŀ��Ĳ�죬
�ػᵱ��ʯ�ƺ��Թ�ȥ,�㲻���붥һ��(ding)Ȧ��!\n",          
                          ]));
        set("exits", ([
               "west" : "/d/changan/fengxu2",
                      ]));
        set("no_clean_up", 0);
        setup();
} 
void init()
{
  object me = this_player();
        add_action("do_ding", "ding");
        add_action("do_ba", "ba"); 
        add_action("do_zhuan", "zhuan");
}
void check_longtou()
{
    object me;
    me = this_player();
if(query("longtou")==6)
{
   message_vision(HIC"��ͻȻ�о���ͷ���˺ܶ�,�ƺ����԰�(ba)������!��\n"NOR, this_player());
      me->set_temp("ba_longtou",1);
remove_call_out("on_del");
call_out("on_del", 10);
}
}
int do_ba(string arg)
{
        object me;
        me = this_player(); 
   if( !me->query_temp("ba_longtou")) return 0;   
     if( !arg || arg=="" ) return notify_fail("��Ҫ��ʲô����!\n");
            if( arg=="��ͷ" ) {
             write(HIB"��һ�ѽ���ͷ���������� \n"NOR); 
         write(HIR"��ͷ�ƺ�����������ת��������ת�ıߺ���? \n"NOR); 
             me->delete_temp("ba_longtou");             this_player()->set_temp("zhuan_longtou", 1);
             return 1;
       }
}
 int do_ding(string arg)
{
        object zhu, me=this_player();

        if( !arg || arg=="" ) return 0;

        if( arg=="Ȧ��" )
                             { 
if(query("longtou")<6)
{                                             message_vision(
HIR"$N����ͷ�·���Ȧ���������϶���һ��!\n"NOR, this_player());
add("longtou",1);
check_longtou();
return 1;
                }
delete("longtou");
 message_vision(HIG"�㶥��ͷ��,��ͷ�����˻�ȥ!\n"NOR, this_player());
                return 1;
        }
        return 1;
}
int do_zhuan(string arg)
{
        object me; 
    object room;
    string dir;
             me = this_player();
 if (!me->query_temp("zhuan_longtou")) 
return 0;
      if( !arg || arg=="" ) return notify_fail("��Ҫתʲô����!\n");
      if( sscanf(arg, "%s", dir)==1 ) {
    if( dir=="left" ) {
   message_vision(HIC"$N����ͷ����ת��һת��\n"NOR, this_player()); 
            add("zhuanmen", 1); 
return 1;
}
 else if( dir=="right") {
         if (query("zhuanmen")) {   
message_vision(HIC"$N����ͷ��ת�˻�ȥ��\n"NOR, this_player()); 
  message_vision(HIC"��������ԭλ����Ȼ����ǰ˿�����졣\n"NOR, this_player());
this_player()->delete_temp("zhuan_longtou"); 
        if( room = find_object("/d/ygbz/yuanzi") ) { 
            room->set("exits/down", "/d/ygbz/jindi");
    message("vision", "�������������Ÿ�������һ��Ķ�������е�Ť�����𵴡�\n",me );
    message("vision", "ͻȻ�����������ˮλ�½��˺ö�,�����������ȥ�ˡ�\n",room ); 
 message("channel:chat", HBRED"�����ء�"+me->query("name")+"�ɹ����������������!!\n"NOR,users());
  call_out("on_guanmen", 180);
}
}
return 1;
        }
        else {
            write("����ת���ĸ�����?\n");
            return 1;
        }
}
}
void on_guanmen(object room)
{ 
      if( room = find_object("/d/ygbz/yuanzi") ) 
            room->delete("exits/down");
delete("longtou");  
 message_vision(HIG"ͻȻ�������ǵ�������ˮλ������!\n"NOR, room);
}

void on_del()
{
  object me = this_player();

if (!me) return 0;

if (environment(me)!=this_object())
{
delete("longtou");
remove_call_out("on_del");
return 0;
}
  call_out("on_del", 10);
}