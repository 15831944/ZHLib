//                ��׼��������ʾ��                                   |
// by yuchang


#include <ansi.h>
inherit ROOM;

string look_window();
string look_hua();
string look_teapot();
string left_teacup();
string right_teacup();
void del_tea();

string l_cup,r_cup;
int pot;

void create()
{
 set("short", YEL"�嶥С��"NOR);
 set("long", @LONG
����һ����Ԩ������С�ݣ�ӭ�ſɼ������С���⣨window�����޾��ı̿ա�
���������а��裬һ����һ�������Σ�������һС��ark�����Եø���ྻ���ˡ�
С����ǽ���裬ǽ�Ϲ���һ���ֻ���hua�������Դ˼�������֮�硣
LONG
);
 set("no_fight", "1");
 set("no_steal", "1");
 set("valid_startroom", 1);

 set("item_desc",([
     "hua": (: look_hua :),
     "window": (: look_window :),
     "chuang": (: look_window :),
     "bed":"һ��С����������ŵþ�Ȼ�������ƺ����ܹ��о���������ɢ��������������\n",
     "table":"����һ��ľ��Բ��С�������ϵ�С�������и�С�����teapot��������С�豭��teacup����\n",
     "chair":"�������԰ڷ�������ľ�ʿ��Ρ�\n",
     "left chair":"һ��ľ�ʿ��Σ�����С������ߡ�\n",
     "right chair":"һ��ľ�ʿ��Σ�����С�����ұߡ�\n",
     "door":"�������߶�������ȥ���Ƿ嶥�����ˡ�\n",
     "ark":"һ��С���񣬿��Դ�������ȡ��take��ʳ�\n",
     "teapot": (: look_teapot :),
     "teacup":"�ֱ���ڲ���������ߵ������մ�С�������ŵ�ϸ��,���Ǻÿ���\n",
     "left teacup": (: left_teacup :),
     "right teacup": (: right_teacup :),
 ]));

 set("exits", ([
     "down":"/u/yuchang/tianzun",
     ]));

 setup();
 call_other("/clone/board/yuchang_b","???");
}

void init()
{
        add_action("do_take","take");
 add_action("do_sleep","sleep");
 add_action("do_nomore","more");
 add_action("do_nomore","cat");
 add_action("do_pin","pin");
 add_action("do_paocha","paocha");
 add_action("do_daocha","daocha");
}

string look_hua()
{
 message_vision(""CYN"$N������ǽ�ϵĻ���ȥ����ʱ��Ĭ���"NOR"\n",this_player());
 write("
    ����һ���嵭��Զ��ɽˮ�������������Ƶ�
�շ����Լ�ɼ���������������嶥����¶��С
�ݵ�һ�ǣ����˲��������޾���˼���������Ϸ�
�հ״���һ��Сʫ��"HIW"

            ��  ��

        ��ɽ����Ϫ������
        ��赭�������顣
        ���ʳ��伸���£�
        ����ƻ��ַ��ǡ�"NOR"

    �����¶˻���һ����̵����˷��ơ�\n\n");

 return "������ؿ��ţ���ʱ��˼��������þò���ƽ����\n";
}

int do_nomore()
{
 if(this_player()->query("id")=="yuchang" || this_player()->query("id")=="yuchang")
  return 0;

 write("Ҫ�����ﻹ��ר�ĵ�ĺá���\n");
 message_vision("$N�����Լ����Ǹ���ľ�ϣ���Ȼ�������￴���롣\n",this_player());
 return 1;
}

int do_take(string arg)
{
        object take_obj,me;
 string meme;

        me=this_player();

 if(!arg) return notify_fail("��Ҫ��ʲô�أ�<tang/apple/nosh/tea>\n");

        if(me->query("id")!="yuchang" || me->query("name")!="�˷���")
  meme="����������";
 else meme="���������";

 if(arg=="tang")
 {
  if(me->query("id")!="yuchang" || me->query("name")!="�˷���")
   return notify_fail("����˭��ƾ��Ҳ����������ֻ������˸�����˶���\n");

  take_obj=new("/u/spark/obj/tang-ren-er");
 }

 if(arg=="apple") take_obj=new("/clone/gift/jinkuai");
 if(arg=="tea") take_obj=new("/clone/gift/xiandan");
 if(arg=="nosh") take_obj=new("/clone/gift/yuebing");

 if(!take_obj) return notify_fail("��Ҫ��ʲô�أ�<tang/apple/nosh/tea>\n");

 if(arg=="apple" && present("ping guo",me)) return notify_fail("������ô������\n");
 if(arg=="nosh" && present("dian xin",me)) return notify_fail("������ô������\n");
 if(arg=="tea" && present("cha ye",me)) return notify_fail("������ô������\n");

        take_obj->move(me);
 message_vision("$N"+meme+"����С���ӣ�ȡ����һ"+take_obj->query("unit")+take_obj->query("name")+"��\n",me);

        return 1;
}

int do_sleep()
{
 object me=this_player();
 int jing,jingli,neili,qi;

 if(me->query("id")!="sleep" || me->query("name")!="�˷���")
 {
  write("�ѵ������ɱ��˵Ĵ���ȥ˯��̫����ò�˰ɡ�\n");
  return 1;
 }

 jing=me->query("max_jing");
 jingli=me->query("max_jingli");
 neili=me->query("max_neili");
 qi=me->query("max_qi");

 message_vision(""MAG"$Nӯӯ���򴲱ߣ�����ЪϢ��Ƭ�̡�"NOR"\n",me);
 message_vision(""MAG"$NС����������þ������ȡ�"NOR"\n",me);

 me->set("jingli",jingli);
 me->set("jing",jing);
 me->set("neili",neili);
 me->set("qi",qi);

 return 1;
}

string look_window()
{
 string sights;

 if(time()-query_temp("looktime")<5)
  return "���޾�������ϸ�ۣ��α��ٴ���̾��Ȼ��\n";

 message_vision(""CYN"$N�߽����ߣ�������������ȥ��"NOR"\n",this_player());
 switch(random(10))
 {
  case 0:sights="ֻ���޾��̿գ���Զ���䡣";
  break;
  case 1:sights="����������������Զ����̾������̣�µµ���壿";
  break;
  case 2:sights="ֻ��ɽ��������翣��˵��������ޱȡ�";
  break;
  case 3:sights="ȴ������ãã��������Ӱ��";
  break;
  case 4:sights="���������裬��̾����ϡ���书���˷�����ȴ������ܼ���";
  break;
  case 5:sights="ֻ��Ⱥɽ����������������磬����Ϊ֮���ԡ�";
  break;
  case 6:sights="ȴ����ʲԲԣ��޴��ŵ㣬������̾������Ŀ��ãã����������ڡ�";
  break;
  case 7:sights="����ɽ��ĸ¹���ӣ�������֮ܰ����Ȼ����";
  break;
  case 8:sights="ֻ���羰������ȴ̾Ⱥɽǧ�꣬���±�Ǩ����ν���㣬��ԼԶԶ��";
  break;
  case 9:
   if(this_player()->query("id")=="spark")
   sights="������ز�ã�����ؾ��������κΣ�ֻ��������һ�ᡣ";
   else sights="������ز�ã�����ؾͲ�֪������˭��ֻ��������һ�ᡣ";
  break;
 }

 if(this_player()->query("id")!="naihe") set_temp("looktime",time());
 return ""HIW"����������ȥ��"+sights+""NOR"\n";
}

string look_teapot()
{
 if(pot>0) return "һ��С��������������������Ĳ�ˮ������԰����������ȣ�daocha����\n";
 else return "һ��С�������߿տյġ��������һ�������ȣ�paocha����\n";
}

string left_teacup()
{
 if(l_cup!="ok") return "��ߵ�С������տյģ���Ȳ軹���ȵ�һ����daocha���ٺȰɣ�\n";
 else return "������ߵ�С���ӣ�����ʢ�����嵭�Ĳ�ˮ�������Ʒ����pin������\n";
}

string right_teacup()
{
 if(r_cup!="ok") return "�ұߵ�С������տյģ���Ȳ軹���ȵ�һ����daocha���ٺȰɣ�\n";
 else return "�����ұߵ�С���ӣ�����ʢ�����嵭�Ĳ�ˮ�������Ʒ����pin������\n";
}

int do_pin(string arg)
{
 object me=this_player();

 if(arg=="left teacup")
 {
  if(l_cup!="ok") return notify_fail("�Ɑ����û���أ������˼��Ҫ�Ե��Ɑ�ӣ�\n");
  if((int)me->query("water") >= (int)me->max_water_capacity())
   return notify_fail("��Ȼ��ȷʵ�úȣ�����ʵ���ǺȲ����ˡ�\n");

  message_vision(""MAG"$N����С���Ѳ�ˮһ��������˵��������ˬ���𣬻�ζ���"NOR"\n",me);
  me->add("water", 30+random(30));
  l_cup="not";
  return 1;
 }

 if(arg=="right teacup")
 {
  if(r_cup!="ok") return notify_fail("�Ɑ����û���أ������˼��Ҫ�Ե��Ɑ�ӣ�\n");
  if((int)me->query("water") >= (int)me->max_water_capacity())
   return notify_fail("��Ȼ��ȷʵ�úȣ�����ʵ���ǺȲ����ˡ�\n");

  message_vision(""MAG"$N����С���Ѳ�ˮһ��������˵��������ˬ���𣬻�ζ���"NOR"\n",me);
  me->add("water", 30+random(30));
  r_cup="not";
  return 1;
 }

 if(arg=="tea" || arg=="cha")
  return notify_fail("�������������Ĳ�ѽ���ǲ�����ֱ�����Ų���ࣿ\n");

 if(arg=="pot" || arg=="teapot")
 {
  write("��ô�����ŵĶ���������Ҳ��ó�����\n");
  message_vision(""CYN"$N����������������࣬���뻹�Ƿ���������"NOR"\n",me);
 }

 write("���������ʲô����ʲô���������ʲô��ʲôʲô������\n");
 return 1;
}

void del_tea()
{
        destruct(present("cha ye",this_player()));
}

int do_paocha()
{
 object me=this_player();

 if(!present("cha ye",me)) return notify_fail("�㻹�����õ��Ҷ���ݲ�ɣ�\n");

 if(time()-query_temp("paochatime")<5)
  return notify_fail("�ⲻ�Ǹ��ݹ������ݣ�\n");

 if(pot>0)
 {
  message_vision(""CYN"$N��ʣ�µĲ�ˮ������"NOR"\n",me);
  pot=0;
 }

 message_vision(""CYN"$Nȡ��һС���Ҷ�Ž������ٵ����ȡ����ˮ���������Ⱥ�������һ���衣"NOR"\n",me);
 message_vision(""MAG"��ʱ����������������磡"NOR"\n",me);
 pot=(5+random(5));
 call_out("del_tea",0);
 set_temp("paochatime",time());
 return 1;
}

int do_daocha(string arg)
{
 if(!arg) return notify_fail("��Ҫ���ĵ�ѽ������ֻ���������ӣ�teacup����һ���ڲ����ߣ�һ�����ұߡ�\n");

 if(pot<1) return notify_fail("�����Ĳ�ˮ�������ˣ�����������һ����˵�ɡ�\n");

 if(arg=="left teacup")
 {
  if(l_cup=="ok") message_vision(""CYN"$N����߱������ʣ�赹������������һ���Ȳ衣"NOR"\n",this_player());
  else message_vision(""CYN"$N������������ߵ�С���������˲�ˮ��"NOR"\n",this_player());

  l_cup="ok";
  pot--;
  return 1;
 }

 if(arg=="right teacup")
 {
  if(r_cup=="ok") message_vision(""CYN"$N���ұ߱������ʣ�赹������������һ���Ȳ衣"NOR"\n",this_player());
  else message_vision(""CYN"$N�����������ұߵ�С���������˲�ˮ��"NOR"\n",this_player());

  r_cup="ok";
  pot--;
  return 1;
 }

 if(arg=="teacup" || arg=="cup")
  return notify_fail("������������������ˮ�������Ƿֿ��������������������\n");

 write("��Ҫ���ĵ�ѽ������ֻ���������ӣ�teacup����һ���ڲ����ߣ�һ�����ұߡ�\n");
 return 1;
}

