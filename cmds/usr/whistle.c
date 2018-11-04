// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// whistle.c �һ�����

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;
        string file;

        if (! str)
                return notify_fail("��Ҫ�ٻ�ʲô���\n");

        if (me->is_busy() || me->query("doing"))  
                return notify_fail("��������æ�������п�����˵�ɡ�\n");
                
        if (me->is_in_prison())   
                return notify_fail("�����������أ������ʲô����\n"); 
                
        if (me->is_fighting()) 
                return notify_fail("����������ս����\n"); 
                
                
        if (environment(me)->query("no_magic") || environment(me)->query("no_fly")) 
                return notify_fail("�㷢�������е�Ź֣������������ܽ�����\n");    
                
        if (! stringp(file = me->query("can_whistle/" + str)))
                return notify_fail("�㲻֪������ٻ�������\n");

        if (file_size(file + ".c") < 0 && file_size(file) < 0)
                return notify_fail("�㲻֪������ٻ�������\n");

        if (me->is_ghost())
                return notify_fail("���㻹�������ٻ��ɡ�\n");

        call_other(file, "???");
        ob = find_object(file);
        if (! ob || ! ob->receive_whistle(me))
        {
                message_vision(HIM "$N" HIM "����һ�����ڡ�\n"
                               "Ȼ��ʲôҲû�з��� :)\n", me);
        } else
                ob->set_temp("petowner", me);

        if (me->is_fighting())
                me->start_busy(2 + random(3));

        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : whistle <�����ID>

��ָ��������������������������Ȼ�����һ���ľ���ʩչ���С�
HELP );
        return 1;
}

