// search.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;

        seteuid(getuid());

        env = environment(me);
        if (! env->query("outdoors"))
                return notify_fail("�����������Ҹ�ʲô����\n");

        if (me->is_busy())
                return notify_fail("����æ������ͷ���������Ұɣ�\n");

        if (me->is_fighting())
                return notify_fail("һ�ߴ��һ���Ҷ�����ֻ�������ó�����\n");

        if (env->query("no_search") == "all")
                return notify_fail("��ط������Ҳ���ʲô����...\n");

	me->set_temp("pending/searching", 1);
        me->set_short_desc("���ڶ���������");
	message("vision", me->name() + "���������������ʲô�أ�\n",
                environment(me), ({ me }));
        tell_object(me, "�㿪ʼ����������������û��ʲôֵǮ�Ķ�����\n");
	me->start_busy(bind((:call_other, __FILE__, "searching" :), me),
                       bind((:call_other, __FILE__, "halt_searching" :), me));
        return 1;
}

mapping query_default_objects(int score)
{
	if (score < 100)
        	return ([
		  "/clone/money/coin"       : 100000,
                  "/clone/money/silver"     : 20000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 20000,
		  "/d/city/npc/obj/jiudai"  : 10000,
		  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
		  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
	else
	if (score < 400)
        	return ([
		  "/clone/money/coin"       : 10000,
                  "/clone/money/silver"     : 15000,
                  "/clone/misc/jinchuang"   : 15000,
                  "/clone/weapon/dagger"    : 8000,
		  "/d/city/npc/obj/jiudai"  : 8000,
		  "/clone/weapon/duanjian"  : 3000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
		  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
	else
	if (score < 2000)
        	return ([
		  "/clone/money/coin"       : 5000,
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 25000,
                  "/clone/weapon/dagger"    : 20000,
		  "/d/city/npc/obj/jiudai"  : 10000,
		  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
		  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
	else
	if (score < 10000)
        	return ([
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 10000,
		  "/d/city/npc/obj/jiudai"  : 5000,
		  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
		  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
	else
        	return ([
                  "/clone/weapon/changjian" : 8000,
                  "/clone/weapon/blade"     : 8000,
                  "/clone/weapon/gangzhang" : 8000,
		  "/clone/cloth/tiejia"     : 2500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
}

object found(object me, object env)
{
        string  *st;
        mapping ns;
        mapping os;
        object  ob;
        int sum;
        int i;

        os = query_default_objects(me->query("score"));
        if (mapp(env->query("search_objects")))
                os += env->query("search_objects");

        sum = me->query("score") >> 7;
        if (mapp(ns = env->query("no_search")))
        {
                st = keys(ns);
                for (i = 0; i < sizeof(st); i++)
                {
                        if (! ns[st[i]] || sum < ns[st[i]])
                                // can not search this object or
                                // need score
                                map_delete(os, st[i]);
                }
        }

        if (sum > 30) sum = 30;
        sum -= env->query_temp("been/searched");
        if (random(sum + 100) < 93)
                return 0;

        st = keys(os);
        sum = 0;
        for (i = 0; i < sizeof(st); i++)
        {
                if (! intp(os[st[i]]))
                        os[st[i]] = 0;
                sum += os[st[i]];
        }

        if (! sum) return 0;
        sum = random(sum);
        for (i = 0; i < sizeof(st); i++)
        {
                if (sum < os[st[i]])
                {
                        catch(ob = new(st[i]));
                        if (! ob)
                        {
                                log_file("log", sprintf("Can not load object %s.\n", st[i]));
                        }
                        env->add_temp("been/searched", 15);
                        return ob;
                }
                sum -= os[st[i]];
        }

	return 0;
}

int searching(object me)
{
        object env;
        object ob;

        env = environment(me);
        if (me->add_temp("pending/searching", 1) > 6)
        {
                tell_object(me, "���˰��죬�㻹��һ������ֻ���ȷ����ˡ�\n");
                message("vision", me->name() + "̾�˿��������˷�����\n", env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        if (me->query("qi") < 30 ||
            me->query("jing") < 30)
        {
                tell_object(me, "��ʵ��̫ƣ���ˣ�ֻ�÷�����Ѱ�ҡ�\n");
                message("vision", me->name() + "̾�˿�����һ�����ݡ�\n",
			env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        me->receive_damage("qi", 30);
        me->receive_damage("jing", 30);

        ob = found(me, env);
        if (ob)
        {
                if (ob->query("base_unit"))
                        ob->set_amount(random(5) + 1);
                tell_object(me, HIC "��ͻȻ������һ" + ob->query("unit") +
                                ob->name() + HIC "��\n");
                message("visoin", me->name() + "ͻȻ����������֪���ӵ�"
                        "�ϼ�����ʲô������ü����Ц�ġ�\n", env, ({ me }));
                if (! ob->move(me))
                {
                        tell_object(me, "��ϧ" + ob->name() + "������"
                                    "˵̫���ˣ���ֻ���ȷ��ڵ��ϡ�\n");
                }
                me->delete_temp("pending/searching");
                me->add("score", 1);
                me->set_short_desc(0);
                return 0;
        } else
        {
                message_vision(random(2) ? "$N�������������ĵ�����\n"
                                         : "$Nʱ���������ڵ��ϲ���ʲô������\n",
                               me);
                return 1;
        }
}

int halt_searching(object me)
{
        object env;

        env = environment(me);
        me->delete_temp("pending/searching");
        tell_object(me, "�������Ѱ�ҡ�\n");
        message("vision", me->name() + "��չ��һ������̾�˿�����\n", env, ({ me }));
        me->set_short_desc(0);
        return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: search

�ڵ���Ѱ�Ҷ��������ҵ�ʲô�أ�ֻ�����֪����ĳЩ�ط��ܹ��ҵ�
�ö����������󲿷ֵط�ֻ���ҵ�һЩ��ͨ�Ķ�����������ҵ��˶�
������Ľ�������������˶�����һ�㡣
 
HELP );
	return 1;
}