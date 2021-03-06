// fotang.c

inherit ROOM;

int do_tao(string arg);
int do_qiao(string arg);
int do_unlock(string arg);

void create()
{
	set("short", "佛堂");
	set("long", @LONG
这是一间佛堂，墙和地板都是砖(brick)砌的。里供着一尊如来佛像(foxiang)，
佛像前是一张供桌。桌上点着盏油灯。屋里有些昏暗。
LONG );
        set("outdoors", "city2");
        set("item_desc", ([
                "foxiang" :      
        "\n这是一尊铜像，栩栩如生，宛若真人,正笑眯眯地望着你。\n",
                "brick" : "\n很普通的石砖，一块一块嵌得很平整。\n",    
        ]) );
	set("exits", ([
  		"south" : "/d/city2/huayuan",
  		"east" : "/d/city2/neitang",
	]));
	set("objects", ([
  		"/d/city2/obj/table" : 1,
	]));
	set("getkey",0);
	set("getbook",0);
	setup();
}

void init()
{
  	add_action("do_qiao", "wa");
  	add_action("do_qiao", "qiao");
  	add_action("do_tao", "tao");
  	add_action("do_unlock", "open");
  	add_action("do_unlock", "unlock");
}


int do_tao(string arg)
{
	object me, ob;
	me = this_player();

	if (arg != "foxiang")
		return notify_fail("你要掏什么？\n");

	if (me->query_temp("marks/爬") )
	{
		message_vision("$N伸手在佛像耳朵里掏了掏。\n", me);
        	if (query("get_key") > 0)
		{
			me->receive_damage("qi", 50);
			write("你掏了半天，什么也没有，看来是被人取走了。\n");
			return 1;
		}
		switch(random(5))
		{
			case 0:
				message_vision("$N掏了一会儿，取出一件小小物事来。\n", me);
				message_vision("$N跃下地来，对着火光一看，却是一枚小钥匙。\n",me);
				ob=new("/d/city2/obj/jinyaos"); 	
 				ob->move(me);
				add("get_key", 1);
				break;
			default:
				message_vision("$N伸手掏了一会儿，什么也没掏到。\n",me);
 				break;
		}
		return 1;
	}
	return notify_fail("你够不着。\n");
}

int do_qiao(string arg)
{
	object me, ob, weapon;
	me = this_player();

	if (arg != "brick")
		return notify_fail("你要撬什么？\n");

	if (me->query_temp("marks/移") )
	{
		if (!objectp(weapon = me->query_temp("weapon")))
			return notify_fail("不用家伙恐怕不行吧！\n");
		message_vision("$N拔出兵刃，将一块方砖撬起。\n",me);
		message("vision","登时露出一块铁板来，板上有个拉环，环下有个锁孔(lock)。\n", environment(me));
		me->set_temp("marks/撬",1);
		return 1;
	}
	else
		message_vision("$N胡乱撬开几块砖，结果什么也没发现。\n", this_player());
	return 1;
}

int do_unlock(string arg)
{
	object ob;
	object me;

	me = this_player();

	if (arg != "lock" )
		return notify_fail("你要开什么？\n");

	if (! me->query_temp("marks/撬"))
		return notify_fail("锁在哪儿啊？\n");

	if (! objectp(ob = present("jin", me)))
	{  
		message_vision("$N猛地一拉铁环，蓦听的飕的一声，一枝机弩从下"
			       "面射了出来，正中$N胸口。\n", me);
		me->die();
		return 1;
	}
	message_vision("$N将金钥匙轻轻插下，只听喀的一声，锁已打开。\n", me);
	if (query("getbook"))
		return notify_fail("你失望地发现书已经被人取走了.\n");

	message_vision("$N伸手进去，摸出一包事物，却是个包袱，打开一看，\n"+
		       "正是一部《四十二章经》。$N忍不住叫了一声。\n",
		       me);
	ob=new("/d/city2/obj/book14_5");
	set("getbook",1);
	ob->move(me);
	return 1;
}

int valid_leave(object me, string dir)
{
        me->delete_temp("marks/爬");
        me->delete_temp("marks/移");
        me->delete_temp("marks/撬");
        return ::valid_leave(me, dir);
}

