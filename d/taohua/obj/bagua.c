// Code of JHSH
// /d/taohua/obj/bagua.c
// Lara 2001/11/28
// snowyu 2002/1
#include <ansi.h>
inherit ITEM;

#include "/d/REGIONS.h";

#define ROUTER "/clone/obj/traverser"
/******************* ���ﶨ��ռ��busy***********************/
#define zhanbu_busy 10
/*********************************************************/

static object route_finder;
static object target_room;
// 0: idle, 1: searching
static int status;

int do_route(string, object);
int do_printroute(object);
void init();

void create()
{
	set_name(GRN"������"NOR, ({ "tie bagua", "bagua" }) );
	set_weight(10000);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("long", "�������Ǵ����������������أ����а���ͼ����\n"
			"����ָ�chuzhen <����>\n");
		set("unit", "ö");
		set("wield_msg", GRN "$N�ɿڴ����ó�$n��\n" NOR );
		set("unwield_msg", GRN "$N��$n�Żؿڴ��С�\n" NOR );
		set("value", 1600);
		set("tanzhi",200);
	}
	setup();
}

void init()
{
	add_action("do_divine", "divine");
	add_action("do_divine", "zhanbu");
	add_action("do_chuzhen", "chuzhen");
	add_action("do_printroute", "printroute");
}

int do_divine(string arg)
{
	object ob, where, env, me = this_player();
	mapping myfam;
	string region;
	int i, lvl, diff; 

	if (me->is_busy() || 
            me->query_temp("pending/exercising") || 
            me->query_temp("exit_blocked")) 
		return notify_fail("��������æ���ء�\n");

	myfam = (mapping)me->query("family");	

	if( !myfam || myfam["family_name"] != "�һ���" ) 
		return notify_fail("����һ����ӣ����ܽ�������������ռ����\n");

	if( (lvl = (int)me->query_skill("qimen-wuxing", 1)) < 60 ) 
		return notify_fail("���������еȼ�������\n");

	if( me->query("jingli") < 100 ) 
		return notify_fail("��ľ���������������ռ����\n");

	if( me->query("jing") < 100 ) 
		return notify_fail("��ľ��񲻹���������ռ����\n");

	if (!arg) 
		return notify_fail("��Ҫռ��˭��λ�ã�\n");

	if( !(ob = find_player(arg)) && !(ob = find_living(arg)) ) 
			return notify_fail("����û�����.\n");

	message_vision(HIG"$N����һֻ����������������Ĵָ�����������������ӡ�������î�������ȡ�\n�硢δ���ꡢ�ϡ��硢��������λ��ϸ����������......\n\n"NOR, me);

	me->add("jing", -50);
	me->add("jingli", -50);

	if ( strsrch(base_name(ob), "/kungfu/class/generate/") == 0 )
		return notify_fail("����˲�֪��������Ү...\n");

	if( !(where = environment(ob))) 
		return notify_fail("����˲�֪��������Ү...\n");

	if( !me->visible(ob)) 
		return notify_fail("����˲�֪��������Ү...\n");

	if( !wizardp(me) && wizardp(ob) ) 
		return notify_fail("�ٺ٣���Ȼ�Ҷ���ʦ��ʲô����ͷô��\n");

	if( undefinedp(region = region_names[getuid(where)]) ) 
		return notify_fail("����˲�֪��������Ү...\n");

	env = environment(me);

        diff = (int)(me->query("combat_exp")/(ob->query("combat_exp")+1));

	if( lvl > 120 && !ob->query_temp("apply/name") && 
	    random(lvl / 10 + me->query_int() + diff) > ob->query("kar")*2 )
	{ 
		me->add("jing", -random(200-lvl));
		printf("%s(%s)������%s%s��\n", 
			(string)ob->name(), 
			(string)ob->query("id"), 
			region, 
			(string)where->query("short"));
		if( lvl > 140 )
			do_route(file_name(where), me);
		if( (random(lvl/3)+diff) < ob->query("kar") ) 
			tell_object(ob, HIB"��о����񲻶����ƺ������ڰ��п�������......\n"NOR);
	}
	else if( me->query_int() > random(ob->query("kar") * 3) )
	{
		me->add("jing", -random(200-lvl));
		printf("%s(%s)������%sһ����\n", 
			(string)ob->name(), 
			(string)ob->query("id"), 
			region);
	 	if( (random(lvl/3)+diff) < ob->query("kar")/2 ) 
			tell_object(ob, HIB"��о����񲻶����ƺ������ڰ��п�������......\n"NOR);
	}
	else
	{
		write("���龫���������˰��Σ�ȴ����һ�����á��� \n");
		me->set("jing", 10);
	}
	me->start_busy(2);
	return 1;
}

int do_chuzhen(string arg)
{
	object obj, env, me, owner;
	string dest;
	mapping exit;

	if(!arg) return notify_fail("��Ҫ���ĸ��������\n");

	me = this_player();

	if (me->is_busy() || 
	    me->query_temp("pending/exercising") || 
            me->query_temp("exit_blocked")) 
		return notify_fail("��������æ���ء�\n");

	env = environment(me);	

	if( !env->query("th_buzhen") ) 
		return notify_fail("���ﲢ�޲��������󷨡�\n");

	if( env->query("th_zhen_owner") == me->query("id"))
		return notify_fail("�������������ˣ�ֻ�����󣬲����뿪�󷨣�\n");

	if( !objectp(owner = find_player(env->query("th_zhen_owner"))) ||
	    environment(owner) != env)
	{
	        env->set("long", env->query("org_desc"));
        	env->set("exits", env->query("org_exits"));
	        env->set("cost", env->query("org_cost"));
        	env->delete("org_desc");
	        env->delete("org_cost");
        	env->delete("org_exits");
	        env->delete("th_buzhen");
        	env->delete("th_pozhen");
		env->delete("th_zhen_owner");
	
        	tell_object(env, CYN"һ���������ڶ�������ɢ��ȥ�����澰����Ȼһ�䡣\n"NOR);
		return 1;
	}


	if( me->query_skill("qimen-wuxing", 1) < 60 ) 
		return notify_fail("�������������Ϊ�������޷��������ذ¡�\n");

	if( me->query("jing") < 50)
		return notify_fail("��ľ����㡣\n");
	
	if( me->query_skill("qimen-wuxing",1) < env->query("th_pozhen")/3 )
	{
		message_vision(CYN"$N���ڵ���ڤ˼���룬ͻȻ��ɫ��䣬������Ѫ��\n"NOR,me);
		me->set("jing",1);
		return 1;
	}

	exit = env->query("org_exits");
	dest = exit[arg];

	if(undefinedp(exit[arg])) 
		return notify_fail("�������û�г�·��\n");

	if( !(obj = find_object(dest)) ) call_other(dest, "???");
	if( !(obj = find_object(dest)) ) 
		return notify_fail("�������û�г�·��\n");

	message_vision(CYN"$N��˼Ƭ�̣�������һת����һ������Ȼ��ʧ����Ӱ���١�\n"NOR,me);	

	if( me->move(obj) )
	{
		message( "vision", me->name()+"�첽���˹�����\n"NOR, 
		environment(me), ({me}) );
		return 1;
	}

	return 0;
}

int visit_room(string room_path, mapping traverse_info, mapping room_info, string target)
{
	string room_short, tmp;

	if (! room_info) return 0;
	// taking care of the colors in names
	room_short=explode(room_info["short"], ESC)[0];
	if (sscanf(room_short, "[%*dm%s", tmp) == 2) room_short = tmp;
	if (sscanf(room_short, "[%*d;%*dm%s", tmp) == 3) room_short = tmp;
	if (room_short == target)
	{
		target_room = find_object(room_path);
		if (! target_room)  target_room = load_object(room_path);
		// something wrong with the room, return 1 to prune the search branch
		if (! target_room)
		return 1;
		return -1;   // found room, done
	}
	return 0;      // otherwise, keep going
}

int do_route(string arg, object me)
{
	int ready;

	if (status == 1) return notify_fail("��������·;. �� printroute ����ʾ�����\n");
	if (objectp(route_finder)) destruct(route_finder);
	route_finder = new (ROUTER);
	if (! objectp(route_finder))
	{
		target_room = 0;
		return notify_fail("���,������� "+ROUTER+"?\n");
	}
	status = 1;
	target_room = find_object(arg);
	if (! target_room)  target_room = load_object(arg);
	if (! objectp(target_room))
	{
	    // return notify_fail("Ŀ�귿�� "+arg+" ������.\n");
	    // assume arg is a short name, not file path
	    ready = route_finder->traverse(base_name(environment(me)), (: visit_room :), arg);
	}
	else
	{
		ready = route_finder->find_route(base_name(environment(me)), base_name(target_room));
	}
	if (ready)  return do_printroute(me);
	return notify_fail("�Ѿ���ʼ����·;���� printroute ����ʾ���.\n");
}

int do_printroute(object player)
{
	object me;
	mapping info;
	mixed   route;
	int     i, n, wizp, lvl;
	object  room;
	string  room_file, room_short;

	if (player) me = player;
	else me = this_player();
	lvl = me->query_skill("qimen-wuxing",1);
	if (status == 0) return notify_fail("����û��ռ������ʲô·;.\n");
	if (! objectp(route_finder))
	{
		status = 0;
		target_room = 0;
		route_finder = 0;
		return notify_fail("��֣�object maproute ������.\n");
	}
	if (! route_finder->traverse_finish())
	{
		return notify_fail("��û�ҵ�����ȵ�������.\n");
	}
	status = 0;
	if (target_room)
	{
		route = route_finder->thread_route(base_name(target_room));
	}
	else
	{
		status = 2;
	}
	target_room = 0;
	destruct(route_finder);
	route_finder = 0;

	if (status == 2)
	{
		return notify_fail("û���������.\n");
		status = 0;
	}
	if ((int)route == 1)
	{
		return notify_fail("û��ȥ�˷���ĵ�·.\n");
	}
	if (sizeof(route) <= 1)
	{
		return notify_fail("�㲻���������\n");
	}
	printf("�ҵ��˵�·�������￪ʼ��\n");
	n = sizeof(route);
	if(n > lvl/20) n = lvl/20;
	wizp = wizardp(me);
	for (i=1; i<n; i++)
	{
		room_file = keys(route[i])[0];
		room = find_object(room_file);
		if (! objectp(room) ) room = load_object(room_file);
		if (objectp(room))
		{
			room_short=room->query("short");
		}
		else
		{
			room_short="��֪���Ķ�";
	    }
	    info = route[i][room_file];
	    if (info["dir"] == "cross_river")
		{
			printf("�ڶɹ���");
		}
		else if (strsrch(info["dir"], "out_sea")==0)
		{
			printf("�����ɺ�");
		}
		else
		{
			printf("�� %s ", info["dir"]);
		}
		printf("�� %s %s, ���� %s��\n", room_short, wizp?"("+room_file+")":"", chinese_number(info["dist"]));
	}
	if(n < sizeof(route)) printf("......�������ţ��㷢�־���̫Զ�ˣ�ͷ�Կ�ʼ��Ϳ����.\n");
	return 1;
}