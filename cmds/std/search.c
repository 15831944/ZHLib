// search.c

// ��һ��ROOM��Ѱ����Ʒ
// ����SCORE�Ĳ�ͬ��Ѱ�ҵĶ���ͼ���Ҳ��ͬ��
// ROOM�������û���������search_objects����������ָ��������
// �������е�ĳЩ��Ʒ���������ʡ�Ҳ��������no_search ָ����
// ����������С��ĳһ��ֵ�Ͳ����ҵ��������ֵΪ�㣬��ô����
// ���ĸ��˵Ľ��������������Ʒ�����Բ������ҵ�������������
// �����������÷��ݵ���ʽ����Ҳ��������ʱ���������Ǳ�����ʾ
// ���ݵĻ�������ʱ������ʾ�Ƿ�����ʱ����Ѱ��Ϣ��

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;

        seteuid(getuid());

        env = environment(me);

        if (me->is_busy())
                return notify_fail("����æ������ͷ���������Ұɣ�\n");

        if (me->is_fighting())
                return notify_fail("һ�ߴ��һ���Ҷ�����ֻ�������ó�����\n");

        if (env->query("no_search") == "all")
                return notify_fail("��ط������Ҳ���ʲô��������\n");

        me->set_temp("pending/searching", 1);
        me->set_short_desc("���ڶ���������");

        message("vision", HIC "ֻ��" + me->name() + HIC "�����������Ĵ�����"
                          "��������֪���ڸ�ʲô��\n" NOR,
                environment(me), ({ me }));

        tell_object(me, HIC "�㿪ʼ����������������û��ʲôֵǮ�Ķ�����\n" NOR);
        me->start_busy(bind((:call_other, __FILE__, "searching" :), me),
                       bind((:call_other, __FILE__, "halt_searching" :), me));
        return 1;
}

mapping query_default_objects(object me)
{
        int score = me->query("score");

        if (! environment(me)->query("outdoors"))
                return ([ ]);

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
                  "/clone/cloth/tiejia"     : 3500, ]);
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
                  "/clone/cloth/tiejia"     : 3500, ]);
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
                  "/clone/cloth/tiejia"     : 3500, ]);
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
                  "/clone/cloth/tiejia"     : 3500, ]);
        else
                return ([
                  "/clone/weapon/changjian" : 8000,
                  "/clone/weapon/blade"     : 8000,
                  "/clone/weapon/gangzhang" : 8000,
                  "/clone/cloth/tiejia"     : 2500, ]);
}

object found(object me, object env)
{
        mixed  *st;
        mapping cs, ns;
        mapping os;
        object  ob;
        mixed   sob;
        int sum;
        int i;

        os = query_default_objects(me);
        if (mapp(cs = env->query_temp("search_objects")))
                os += cs;

        if (mapp(cs = env->query("search_objects")))
                os += cs;

        sum = me->query("score") >> 7;
        if (mapp(ns = env->query_temp("no_search")))
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
        if (env->query_temp("been/searched") > 0)
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
                        if (stringp(st[i]))
                                ob = new(st[i]);
                        else
                        if (objectp(st[i]))
                                ob = st[i];
                        else
                        if (functionp(st[i]))
                                ob = evaluate(st[i], me, env);

                        if (! objectp(ob))
                                return 0;

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
                tell_object(me, HIY "�����˰��죬�������һ������ֻ�÷�����\n" NOR);
                message("vision", HIC + me->name() + HIC "̾�˿��������˷�����\n" NOR,
                                  env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        if (me->query("qi") < 30 ||
            me->query("jing") < 30)
        {
                tell_object(me, HIY "��ʵ��̫ƣ���ˣ�ֻ�÷�����Ѱ�ҡ�\n" NOR);
                message("vision", HIC + me->name() + HIC "̾�˿�����һ�����ݡ�\n" NOR,
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

                tell_object(me, HIW "��ͻȻ������һ" + ob->query("unit") + ob->name() +
                                HIW "��\n" NOR);

                message("visoin", HIW + me->name() + HIW "ͻȻ����������֪���ӵ�"
                                "�ϼ�����ʲô������\n" NOR, env, ({ me }));

                if (! ob->move(me, 1))
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
                switch (random(8))
                {
                case 0:
                        message_vision(HIC "$N" HIC "̾�˿������������������Ĳ�"
                                       "����\n" NOR, me);
                        break;
                case 1:
                        message_vision(HIC "$N" HIC "�ýŲ��˲���ǰ�������ƺ���"
                                       "��Ѱʲô��\n" NOR, me);
                        break;
                case 2:
                        message_vision(HIC "$N" HIC "������üͷ������������ϸ��"
                                       "���ŵ����һ�С�\n" NOR, me);
                        break;
                case 3:
                        message_vision(HIC "$N" HIC "��ת��ͷ����ϸ���˿������"
                                       "���档\n" NOR, me);
                        break;
                case 4:
                        message_vision(HIC "$N" HIC "ת�����ӣ������ʹ��̤��̤"
                                       "���棬̽����ʵ��\n" NOR, me);
                        break;
                case 5:
                        message_vision(HIC "$N" HIC "���˾����ֽ��ſ�ʼ�Ĵ���"
                                       "�������Ź���Χ��һ�С�\n" NOR, me);
                        break;
                case 6:
                        message_vision(HIC "$N" HIC "̽�����ӣ���������Χ�ĵ���"
                                       "���û��˼��¡�\n" NOR, me);
                        break;
                default:
                        message_vision(HIC "$N" HIC "����һ�����������ڵ��ϲ���"
                                       "ʲô������\n" NOR, me);
                        break;
		}
                return 1;
        }
}

int halt_searching(object me)
{
        object env;

        env = environment(me);
        me->delete_temp("pending/searching");
        tell_object(me, HIY "�������Ѱ�ҡ�\n" NOR);
        message("vision", HIC + me->name() + HIC "��չ��һ������̾�˿�����\n"
                          NOR, env, ({ me }));
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