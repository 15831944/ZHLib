// employ.c
// Create by Rcwiz for HERO.CD

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
	object ob;
	string old_status, new_status;
	int my_level, ob_level, level;

        mapping job = ([
                       "新手导师"  :  "teacher.c",
                       "玩家代表"  :  "assistant.c",
                       "主页维护"  :  "webmaster.c",
                       "游戏宣传"  :  "presell.c",
        ]);

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

	if (! arg || sscanf(arg, "%s %s", arg, new_status) != 2)
		return notify_fail("指令格式：employ <使用者> <职位>\n");

	if (new_status != "新手导师" &&
            new_status != "玩家代表" &&
            new_status != "主页维护" &&
            new_status != "游戏宣传" &&
            new_status != "取消雇佣" )
		return notify_fail("没有这种职位。\n");

	if (! objectp(ob = present(arg, environment(me))) ||
	    ! playerp(ob))
		return notify_fail("你只能改变使用者的职位。\n");

	if (ob->query("viremploy/job") == new_status)
		return notify_fail("该玩家已经担任该职位。\n");

        if (new_status == "取消雇佣")
        {
                  if (! mapp(ob->query("viremploy")))
                           return notify_fail("该玩家没有担任任何职位。\n");

                  CHANNEL_D->do_channel(this_object(), "rumor", 
                             ob->name() + "(" + ob->query("id") + ")所担任"
                             "的职位：" + ob->query("viremploy/job") + " 被取消了！\n");

                  ob->delete("viremploy");
                  "/cmds/adm/grant"->main(me, ob->query("id") + " -d home");
                  ob->delete("can_send_msg");
                  
               	  ob->save();

                  return 1;
        }
        
        CHANNEL_D->do_channel(this_object(), "rumor", 
                             ob->name() + "(" + ob->query("id") + ")被任命为" + HIG +
                             new_status + NOR + "。\n");

        ob->set("viremploy/job", new_status);
        ob->set("viremploy/workroom", job[new_status]);
        ob->set("can_send_msg",1);
        tell_object(ob, HIC "你可以使用msg指令来管理短信息。\n " NOR);
        "/cmds/adm/grant"->main(me, ob->query("id") + " home");

	ob->save();

	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : promote <某人> (权限等级)

用来提升权限等级, (player) (immortal) (apprentice) (wizard)
(arch) (admin)
一个 admin 能提升权限至任何等级, 而 arch 只能提升至 arch。
HELP );
    return 1;
}
