//                标准描述长度示例                                   |
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
 set("short", YEL"峰顶小屋"NOR);
 set("long", @LONG
这是一间临渊而建的小屋，迎门可见对面的小窗外（window）是无尽的碧空。
屋子里少有摆设，一床，一桌，两椅，桌旁有一小柜（ark），显得格外洁净怡人。
小桌近墙而设，墙上挂着一幅字画（hua），更显此间主人恬淡之风。
LONG
);
 set("no_fight", "1");
 set("no_steal", "1");
 set("valid_startroom", 1);

 set("item_desc",([
     "hua": (: look_hua :),
     "window": (: look_window :),
     "chuang": (: look_window :),
     "bed":"一铺小床，被褥叠放得井然有序，你似乎还能够感觉到那里在散发着幽幽香气。\n",
     "table":"这是一张木质圆型小桌，桌上的小托盘里有个小茶壶（teapot）和两个小茶杯（teacup）。\n",
     "chair":"桌子两旁摆放着两张木质靠椅。\n",
     "left chair":"一张木质靠椅，放在小桌的左边。\n",
     "right chair":"一张木质靠椅，放在小桌的右边。\n",
     "door":"门往东边而开，出去就是峰顶旷地了。\n",
     "ark":"一个小橱柜，可以从里面拿取（take）食物。\n",
     "teapot": (: look_teapot :),
     "teacup":"分别放在茶壶左右两边的两个陶瓷小杯，有着雕花细纹,很是好看。\n",
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
 message_vision(""CYN"$N凝神往墙上的画看去，立时沉默不语。"NOR"\n",this_player());
 write("
    这是一幅清淡悠远的山水国画，云雾萦绕的
险峰间隐约可见密林青葱郁郁。峰顶上显露着小
屋的一角，让人不禁产生无尽遐思。画的左上方
空白处有一首小诗："HIW"

            淡  泊

        幽山闲云溪边隐，
        清茶淡饭两悦情。
        休问尘间几更事，
        日落黄昏又繁星。"NOR"

    画的下端还有一个简短的落款：浪翻云。\n\n");

 return "你呆呆地看着，霎时间思潮起伏，久久不得平静。\n";
}

int do_nomore()
{
 if(this_player()->query("id")=="yuchang" || this_player()->query("id")=="yuchang")
  return 0;

 write("要解迷嘛还是专心点的好……\n");
 message_vision("$N觉得自己真是个大笨木瓜，居然想在这里看代码。\n",this_player());
 return 1;
}

int do_take(string arg)
{
        object take_obj,me;
 string meme;

        me=this_player();

 if(!arg) return notify_fail("你要拿什么呢？<tang/apple/nosh/tea>\n");

        if(me->query("id")!="yuchang" || me->query("name")!="浪翻云")
  meme="毫不客气地";
 else meme="轻轻柔柔地";

 if(arg=="tang")
 {
  if(me->query("id")!="yuchang" || me->query("name")!="浪翻云")
   return notify_fail("你是谁？凭你也想来这里拿只属于闪烁的糖人儿！\n");

  take_obj=new("/u/spark/obj/tang-ren-er");
 }

 if(arg=="apple") take_obj=new("/clone/gift/jinkuai");
 if(arg=="tea") take_obj=new("/clone/gift/xiandan");
 if(arg=="nosh") take_obj=new("/clone/gift/yuebing");

 if(!take_obj) return notify_fail("你要拿什么呢？<tang/apple/nosh/tea>\n");

 if(arg=="apple" && present("ping guo",me)) return notify_fail("你拿那么多想干嘛？\n");
 if(arg=="nosh" && present("dian xin",me)) return notify_fail("你拿那么多想干嘛？\n");
 if(arg=="tea" && present("cha ye",me)) return notify_fail("你拿那么多想干嘛？\n");

        take_obj->move(me);
 message_vision("$N"+meme+"打开了小柜子，取出了一"+take_obj->query("unit")+take_obj->query("name")+"。\n",me);

        return 1;
}

int do_sleep()
{
 object me=this_player();
 int jing,jingli,neili,qi;

 if(me->query("id")!="sleep" || me->query("name")!="浪翻云")
 {
  write("难道你想躺别人的床上去睡？太不礼貌了吧。\n");
  return 1;
 }

 jing=me->query("max_jing");
 jingli=me->query("max_jingli");
 neili=me->query("max_neili");
 qi=me->query("max_qi");

 message_vision(""MAG"$N盈盈走向床边，躺下歇息了片刻。"NOR"\n",me);
 message_vision(""MAG"$N小憩醒来，觉得精神奕奕。"NOR"\n",me);

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
  return "如无静心慢看细观，何必临窗慨叹自然！\n";

 message_vision(""CYN"$N走近窗边，静静地往外望去。"NOR"\n",this_player());
 switch(random(10))
 {
  case 0:sights="只见无尽碧空，悠远深邃。";
  break;
  case 1:sights="但觉宇宙苍穹无限深远，可叹人生苦短，碌碌何义？";
  break;
  case 2:sights="只见山间云雾缥缈，端的是浪漫无比。";
  break;
  case 3:sights="却见雾意茫茫，朦胧无影。";
  break;
  case 4:sights="忽见飞鸟翱翔，可叹纵有稀世武功，此分自在却又如何能及？";
  break;
  case 5:sights="只见群山连绵起伏，大气磅礴，不禁为之入迷。";
  break;
  case 6:sights="却见天际苍苍，无从着点，不禁感叹人生，目标茫茫有如无穷天壁。";
  break;
  case 7:sights="忽见山间母鹿哺子，心中温馨之意油然而起。";
  break;
  case 8:sights="只见风景秀丽，却叹群山千年，人事变迁，何谓永恒，相约远远？";
  break;
  case 9:
   if(this_player()->query("id")=="spark")
   sights="但见天地苍茫，忽地就想起了奈何，只觉得心里一酸。";
   else sights="但见天地苍茫，忽地就不知想起了谁，只觉得心里一酸。";
  break;
 }

 if(this_player()->query("id")!="naihe") set_temp("looktime",time());
 return ""HIW"你往窗外望去，"+sights+""NOR"\n";
}

string look_teapot()
{
 if(pot>0) return "一个小茶壶，里边泡着香气四溢的茶水。你可以把它倒出来喝（daocha）。\n";
 else return "一个小茶壶，里边空空的。你可以泡一壶茶来喝（paocha）。\n";
}

string left_teacup()
{
 if(l_cup!="ok") return "左边的小杯子里空空的，想喝茶还是先倒一杯（daocha）再喝吧！\n";
 else return "这是左边的小杯子，里面盛满了清淡的茶水，你可以品尝（pin）它。\n";
}

string right_teacup()
{
 if(r_cup!="ok") return "右边的小杯子里空空的，想喝茶还是先倒一杯（daocha）再喝吧！\n";
 else return "这是右边的小杯子，里面盛满了清淡的茶水，你可以品尝（pin）它。\n";
}

int do_pin(string arg)
{
 object me=this_player();

 if(arg=="left teacup")
 {
  if(l_cup!="ok") return notify_fail("这杯子里没茶呢，你的意思是要吃掉这杯子？\n");
  if((int)me->query("water") >= (int)me->max_water_capacity())
   return notify_fail("虽然茶确实好喝，但你实在是喝不下了。\n");

  message_vision(""MAG"$N端起小杯把茶水一饮而尽，说不出的清爽甘甜，回味无穷。"NOR"\n",me);
  me->add("water", 30+random(30));
  l_cup="not";
  return 1;
 }

 if(arg=="right teacup")
 {
  if(r_cup!="ok") return notify_fail("这杯子里没茶呢，你的意思是要吃掉这杯子？\n");
  if((int)me->query("water") >= (int)me->max_water_capacity())
   return notify_fail("虽然茶确实好喝，但你实在是喝不下了。\n");

  message_vision(""MAG"$N端起小杯把茶水一饮而尽，说不出的清爽甘甜，回味无穷。"NOR"\n",me);
  me->add("water", 30+random(30));
  r_cup="not";
  return 1;
 }

 if(arg=="tea" || arg=="cha")
  return notify_fail("你这是想喝哪里的茶呀？是不是想直接拿着茶壶灌？\n");

 if(arg=="pot" || arg=="teapot")
 {
  write("那么不文雅的动作，亏你也想得出来！\n");
  message_vision(""CYN"$N拿起茶壶刚想往嘴里灌，想想还是放了下来。"NOR"\n",me);
 }

 write("你这是想干什么？饮什么？饮哪里的什么？什么什么？？？\n");
 return 1;
}

void del_tea()
{
        destruct(present("cha ye",this_player()));
}

int do_paocha()
{
 object me=this_player();

 if(!present("cha ye",me)) return notify_fail("你还是先拿点茶叶再泡茶吧！\n");

 if(time()-query_temp("paochatime")<5)
  return notify_fail("这不是刚泡过吗？又泡？\n");

 if(pot>0)
 {
  message_vision(""CYN"$N把剩下的茶水倒掉。"NOR"\n",me);
  pot=0;
 }

 message_vision(""CYN"$N取出一小撮茶叶放进茶壶里，再到外边取回了水，以内力热壶泡起了一壶茶。"NOR"\n",me);
 message_vision(""MAG"顿时整个房间里茶香四溢！"NOR"\n",me);
 pot=(5+random(5));
 call_out("del_tea",0);
 set_temp("paochatime",time());
 return 1;
}

int do_daocha(string arg)
{
 if(!arg) return notify_fail("你要往哪倒呀？这里只有两个杯子（teacup），一个在茶壶左边，一个在右边。\n");

 if(pot<1) return notify_fail("茶壶里的茶水都喝完了，还是先泡上一壶再说吧。\n");

 if(arg=="left teacup")
 {
  if(l_cup=="ok") message_vision(""CYN"$N把左边杯子里的剩茶倒掉，重新斟了一杯热茶。"NOR"\n",this_player());
  else message_vision(""CYN"$N提起茶壶，往左边的小杯里斟满了茶水。"NOR"\n",this_player());

  l_cup="ok";
  pot--;
  return 1;
 }

 if(arg=="right teacup")
 {
  if(r_cup=="ok") message_vision(""CYN"$N把右边杯子里的剩茶倒掉，重新斟了一杯热茶。"NOR"\n",this_player());
  else message_vision(""CYN"$N提起茶壶，往右边的小杯里斟满了茶水。"NOR"\n",this_player());

  r_cup="ok";
  pot--;
  return 1;
 }

 if(arg=="teacup" || arg=="cup")
  return notify_fail("你是想用内力劈开茶水，让它们分开两条，倒向两个杯子里？\n");

 write("你要往哪倒呀？这里只有两个杯子（teacup），一个在茶壶左边，一个在右边。\n");
 return 1;
}

