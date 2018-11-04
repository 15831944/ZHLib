// go.c

#include <config.h>

inherit F_CLEAN_UP;

mapping default_dirs = ([
        "north":        "����",
        "south":        "�Ϸ�",
        "east":         "����",
        "west":         "����",
        "northup":      "����",
        "southup":      "�ϱ�",
        "eastup":       "����",
        "westup":       "����",
        "northdown":    "����",
        "southdown":    "�ϱ�",
        "eastdown":     "����",
        "westdown":     "����",
        "northeast":    "����",
        "northwest":    "����",
        "southeast":    "����",
        "southwest":    "����",
        "up":           "����",
        "down":         "����",
        "enter":        "����",
        "out":          "����",
]);

static  mapping empty_mapping = ([ ]);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string dest, mout, min, dir, blk, gud, skill, thing_msg;
        object env, obj, blocker, thing;
        mapping block;
        mixed old_target;
        int result;
        int sen_cost;
        mapping exit;
        object *f_obs, *ob;
        object temp_ob;
	mixed flee;
        mapping my, my_temp;
        mapping my_env, my_armor;

        int i, my_dex, count = 0;

        if (! arg) return notify_fail("��Ҫ���ĸ������ߣ�\n");

        if (me->over_encumbranced())
                return notify_fail("��ĸ��ɹ��أ��������á�\n");

        if (me->query_temp("on_bantan"))
                return notify_fail("�㻹����̯�ӣ����ܾ���ô�뿪��\n");

        if (me->is_busy())
                return notify_fail("��Ķ�����û����ɣ������ƶ���\n");

        env = environment(me);
        if (! env) return notify_fail("������Ҳȥ���ˡ�\n");

        if (me->is_fighting())
        {
                me->clean_up_enemy();
                f_obs = me->query_enemy();
        } else
                f_obs = ({ });

        if (arrayp(ob = env->query_temp("guarded/" + arg)))
                f_obs += ob;

        my = me->query_entire_dbase();
        my_temp = me->query_entire_temp_dbase();
        if (! my_temp) my_temp = empty_mapping;

        my_armor = my_temp["armor"];
        if (! my_armor) my_armor = empty_mapping;

        my_env = my["env"];
        if (! my_env) my_env = empty_mapping;

        if (sizeof(f_obs))
        {
                int fp, gp;
                object g_ob;

                fp  = (int)me->query_skill("dodge");
                fp += my["dex"] * 5;
                fp  = my["dex"] * fp / 30;
		if (flee = my_temp["success_flee"])
		{
			if (stringp(flee)) write(flee);
			f_obs = ({ });
		}
                foreach (g_ob in f_obs)
                {
                        if (! g_ob) continue;
                        if (! living(g_ob) || g_ob == me ||
			    g_ob->is_busy()) continue;

                        // calculate flee power & guard power
                        gp  = g_ob->query_skill("dodge");
                        gp += g_ob->query("dex") * 5;
                        gp  = g_ob->query("dex") * gp / 30;

                        if ((fp / 2 + random(fp)) < (gp * 3 / 4))
                        {
                                me->start_busy(1);
                                if (me->is_fighting(g_ob))
                                {
                                        message_vision("$N���Ʋ��ã�ת��Ҫ�ߣ�"
                                                       "��$nһ��������ǰ������"
                                                       "����û��ô���ף�\n",
                                                       me, g_ob);
                                        tell_object(me, "������ʧ�ܡ�\n");
                                } else
                                {
                                        message_vision("$N�����뿪����$nһ��"
                                                       "��ס�����ţ��������"
                                                       "������û�ţ�\n",
                                                       me, g_ob);
                                        tell_object(me, "�㱻��ס��ȥ·��\n");
                                }
                                return 1;
                        }
                }
        }
	map_delete(my_temp, "success_flee");

        if (! mapp(exit = env->query("exits")) || undefinedp(exit[arg]))
        {
                if (query_verb() == "go")
                        notify_fail("�������û�г�·��\n");
                return 0;
        }

        notify_fail("�����ȥ��\n");
        result = env->valid_leave(me, arg);
        if (! result) return 0;
	if (result < 0 || environment(me) != env)
		// I needn't let the character do anymore,
		// because everything has been dong in the
		// fucntion::valid_leave()
		return 1;

        dest = exit[arg];
        if (! (obj = find_object(dest)))
                if (! objectp(obj = load_object(dest)))
                        return notify_fail(sprintf("Ŀ������޷��ҵ�����"
						   "���� %s �ƶ���\n", dest ) );

/*
        if (my_temp["is_riding"] &&
            arg != "north"     && arg != "south" &&
            arg != "east"      && arg != "west" &&
	    arg != "northeast" && arg != "southeast" &&
	    arg != "northwest" && arg != "southwest")
                return notify_fail("�������û�����������Ϲ�ȥ��\n");
*/

        if (! undefinedp(default_dirs[arg]))
                dir = default_dirs[arg];
        else
        {
                if (stringp(env->query_room_id(arg)))
                        dir = env->query_room_id(arg);
                else
                        dir = arg;
        }

        if (me->is_fighting())
        {
		if (my["race"] != "����")
		{
			if (mout = me->query("fleeout_message"))
		                mout = me->name() + "��" + dir + mout + "��\n";

			else
		                mout = me->name() + "��" + dir + "�Ӵܶ�ȥ��\n";
			if (min = me->query("fleein_message"))
		                min = me->name() + min + "��\n";
			else
		                min = me->name() + "ҡҡ�λεĴ��˳�����������š�\n";
		} else
		{
	                mout = me->name() + "��" + dir + "���ܶ�ȥ��\n";
	                min = me->name() + "����ײײ�����˹�����ģ���е��Ǳ���\n";
		}

        } else
        {
                if (objectp(thing = my_armor["cloth"]))
                        thing_msg = "����" + thing->query("name");
                else
		if (userp(me))
                        thing_msg = "һ˿���ҵ�";
		else
			thing_msg = "";

                if (objectp(thing = my_temp["weapon"]))
                        thing_msg += "��ִ" + thing->query("name");

                if (my["race"] != "����")
                {
                        if(mout = me->query("leave_msg"))
                                mout = me->name() + "��" + dir + mout +" ��\n";
                        else
                                mout = me->name() + "������" + dir + "һ�ܾ���ʧ�ˡ�\n";
                        if(min = me->query("arrive_msg"))
                                min += " ��\n";
                        else
                                min = me->name() + "���ش��˳�������������������š�\n";
                } else
                {
			object riding;
                        if (objectp(riding = my_temp["is_riding"]))
                        {
                                mout = me->name() + "����" + riding->name() +
				       "��" + dir + "���۶�ȥ��\n";
                                min = me->name() + thing_msg + "����" +
				      riding->name() + "һ·���۶�����\n";
                        } else
                        {
                                mout = me->name() + "��" + dir + "�뿪��\n";
                                min = me->name() + thing_msg + "���˹�����\n";
                        }
                }
        }

	if (! wizardp(me) || ! my_env["invisible"])
        	message("vision", mout, environment(me), ({me}) );

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(me);
#endif

        // move I to dest
        me->remove_all_enemy(1);
        map_delete(my_temp, "pending");
        if (objectp(obj) && ! my_env["invisible"])
                message("vision", min, dest, ({ me }));

        me->move(dest);
        if (environment(me) != env)
        {
                object competitor;
                if (competitor = me->query_competitor())
                {
                        me->lost();
                        competitor->win();
                }
	        all_inventory(env)->follow_me(me, arg);
        }
        return 1;
}

void do_flee(object me)
{
        mapping exits;
        string *directions;

        if (! environment(me) || ! living(me)) return;
        exits = environment(me)->query("exits");
        if (! mapp(exits) || ! sizeof(exits)) return;
        directions = keys(exits);
        tell_object(me, "�������һ���������...\n");
        main(me, directions[random(sizeof(directions))]);
}

static mapping r_dirs = ([
        "north":        "south",
        "south":        "north",
        "east":         "west",
        "west":         "east",
        "northup":      "southdown",
        "southup":      "northdown",
        "eastup":       "westdown",
        "westup":       "eastdown",
        "northdown":    "southup",
        "southdown":    "northup",
        "eastdown":     "westup",
        "westdown":     "eastup",
        "northeast":    "southwest",
        "northwest":    "southeast",
        "southeast":    "northwest",
        "southwest":    "northeast",
        "up":           "down",
        "down":         "up",
        "enter":        "out",
        "out":          "enter",
]);

string query_reverse(string dir)
{
	if (undefinedp(r_dirs[dir]))
		return 0;

        return r_dirs[dir];
}

int help(object me)
{
        write(@HELP
ָ���ʽ : go <����>
 
������ָ���ķ����ƶ���
 
HELP );
        return 1;
}
