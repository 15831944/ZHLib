// home.c
// Modify by Rcwiz for HERO.CD

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string msg;
        string workroom;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

	if (file_size(user_path(geteuid(me)) + "workroom.c") <= 0 &&
            file_size("/u/viremploy/" + me->query("viremploy/workroom")) <= 0)
		return notify_fail("��û���Լ��Ĺ����ҡ�\n");

	if (stringp(msg = me->query("env/msg_home")))
		message_vision(msg + "\n", me);

	if (wizardp(me))me->move("/u/" + geteuid(me) + "/workroom.c");

        else me->move("/u/viremploy/" + me->query("viremploy/workroom"));

	return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : home

���ô�һָ���ֱ�ӻص��Լ��Ĺ����ҡ�
������� 'msg_home' ����趨, ���ڳ����˶��ῴ���Ǹ�ѶϢ.
HELP );
    return 1;
}
