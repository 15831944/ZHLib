// Code of ShenZhou
//Kane
// mantian Bug fix may/11/2001

#include <room.h>
#include <ansi.h>

inherit ROOM;

int do_pigua();
void create()
{
	set("short", "清音洞");
	set("long", @LONG
此洞面南背北，加之洞口狭小，是以终年不见阳光。但奇怪的是洞内十分干燥，
也没有什么虫豸。洞壁(wall)上有一些模模糊糊的人形，作扑击格斗之状，像是桃
花岛的一些基本武学图解。
LONG
	);
	set("item_desc", ([
		"wall" : " 壁上有十数个人形，或纵高伏低，或储势待发，每一个都捏着不同指诀，\n"
                         "甚为灵动，似乎是桃花岛的一套奇门武学打根基的招式。\n",
		]));
	set("exits", ([
		"out" : __DIR__"tzfeng",
		]));
	setup();
}

void init()
{
	add_action("do_tanzhi","tanzhi");
	add_action("do_use","use");
}

int do_use(string arg)
{
	object me = this_player();

	if( !arg || arg=="" ) return 0;
	if (!present("fire", me))  return 0;
	if( arg=="fire" )
	{
		write("借着火光映照，你向洞中深处走去。\n");
		me->move(__DIR__"neidong");
	}
	return 1;
}

int do_tanzhi()                
{
	object me, ob, *inv; 
	int check,i;

	me = this_player();
	ob = present("tie bagua", me);

	if (!ob) 
		return notify_fail("你看着图像学着伸指乱弹，结果除了手指又酸又痛，啥都没出现。\n");

	if (me->query("jing") <30) 
		return notify_fail("你的精神无法集中。\n");

	if ( (int)me->query_skill("finger", 1) >= 50 && 
             (int)me->query_skill("finger", 1) <= 200 &&
             ob )
	{
		check = (int)me->query_skill("finger",1);
		check *= check;
		check *= check;
		if ( check < (int)me->query("combat_exp")*10)
		{
			me->recieve_damage("jing",15+random(15));
			me->improve_skill("finger", me->query("int")*2);
			write(CYN"你伸指向铁八卦上的卦象弹去。\n"NOR);
			write("你领悟了基本指法方面的几个疑难。\n");
		}
		else
		{
			write ("你实战经验不足，无法领悟基本指法。\n");
		}	
	} 
	else if ( (int)me->query_skill("finger", 1) > 200 )
	{
		write(HIC"只听“铮”的一声，铁八卦发出一声清响\n"NOR);
	}	  
	else
	{
		write(HIC"你对着铁八卦使上吃奶的劲用力一弹，结果手指疼的跟断了一样。\n"NOR);
	} 
	return 1;
}