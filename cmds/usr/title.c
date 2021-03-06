// mktitle.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string who;

	if (! arg)
        {
                write("你现在的称号：" + me->query("title") + "\n");
                return 1;
        }

        if (! wizardp(me))
                return notify_fail("只有巫师才能修改称号。\n");

	if (sscanf(arg, "%s %s", who, arg) == 2)
	{
	    	if (! objectp(ob = find_player(who)))
			return notify_fail("没有 " + who + " 这个玩家。\n");

		if (wiz_level(me) < 3)
			return notify_fail("你的等级不够帮玩家修改称号。\n");
	} else
		ob = me;

	if (arg == "none") 
	{
		ob->delete("title");
		write((ob == me ? "你" : ob->name(1)) + "的外号取消了。\n");

		return 1;
	}

        arg = replace_string(arg, "$BLK$", BLK);
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);

        if (strlen(filter_color(arg)) > 48 || strlen(arg) > 72)
		return notify_fail("这个外号太长了，想一个短一点的、响亮一点的。\n");

	ob->set("title", arg + NOR);
	write("你取好了外号。\n");

	        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : title <外号> | none
 
这个指令可以让你为自己取一个响亮的头衔，但是只有巫
师才可以使用，你如果希望在外号中使用 ANSI 的控制字
元改变颜色，可以用以下的控制字串：

$BLK$ - 黑色		$NOR$ - 恢复正常颜色
$RED$ - 红色		$HIR$ - 亮红色
$GRN$ - 绿色		$HIG$ - 亮绿色
$YEL$ - 土黄色		$HIY$ - 黄色
$BLU$ - 深蓝色		$HIB$ - 蓝色
$MAG$ - 浅紫色		$HIM$ - 粉红色
$CYN$ - 蓝绿色		$HIC$ - 天青色
$WHT$ - 浅灰色		$HIW$ - 白色
 
其中系统自动会在字串尾端加一个 $NOR$。

HELP
        );

        return 1;
}
