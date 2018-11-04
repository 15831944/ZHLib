// mktitle.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string who;

	if (! arg)
        {
                write("�����ڵĳƺţ�" + me->query("title") + "\n");
                return 1;
        }

        if (! wizardp(me))
                return notify_fail("ֻ����ʦ�����޸ĳƺš�\n");

	if (sscanf(arg, "%s %s", who, arg) == 2)
	{
	    	if (! objectp(ob = find_player(who)))
			return notify_fail("û�� " + who + " �����ҡ�\n");

		if (wiz_level(me) < 3)
			return notify_fail("��ĵȼ�����������޸ĳƺš�\n");
	} else
		ob = me;

	if (arg == "none") 
	{
		ob->delete("title");
		write((ob == me ? "��" : ob->name(1)) + "�����ȡ���ˡ�\n");

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
		return notify_fail("������̫���ˣ���һ����һ��ġ�����һ��ġ�\n");

	ob->set("title", arg + NOR);
	write("��ȡ������š�\n");

	        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : title <���> | none
 
���ָ���������Ϊ�Լ�ȡһ��������ͷ�Σ�����ֻ����
ʦ�ſ���ʹ�ã������ϣ���������ʹ�� ANSI �Ŀ�����
Ԫ�ı���ɫ�����������µĿ����ִ���

$BLK$ - ��ɫ		$NOR$ - �ָ�������ɫ
$RED$ - ��ɫ		$HIR$ - ����ɫ
$GRN$ - ��ɫ		$HIG$ - ����ɫ
$YEL$ - ����ɫ		$HIY$ - ��ɫ
$BLU$ - ����ɫ		$HIB$ - ��ɫ
$MAG$ - ǳ��ɫ		$HIM$ - �ۺ�ɫ
$CYN$ - ����ɫ		$HIC$ - ����ɫ
$WHT$ - ǳ��ɫ		$HIW$ - ��ɫ
 
����ϵͳ�Զ������ִ�β�˼�һ�� $NOR$��

HELP
        );

        return 1;
}
