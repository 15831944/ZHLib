// jiaobei.c �̱�
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�̱�");
        set("long", @LONG
������ȫ��̵Ḻ̌����ڵأ�·������һ���(bei)��������
�߾������������ĵ�����������--ȫ��̵Ĵ����ˡ�������һ��ʯ
�ף���֪��ͨ�������������ɽ��·��
LONG
        );
        set("outdoors", "quanzhen");
        set("exits", ([
                "south"   : __DIR__"dajiaochang",
                "northup" : __DIR__"shijie6",
                "eastup" : __DIR__"damen",
                "west" : __DIR__"shijianyan",
        ]));
        set("item_desc", ([
        "bei": CYN"
        ����������
������������������
������������ȫ����
������������������
�������������桡��
������������������
�������������š���
������������������
�������������̡���
������������������
������������������
\n"NOR
        ]) );
        set("objects",([
                CLASS_D("quanzhen") + "/zhou" : 1,
        ]));

        setup();
        replace_program(ROOM);
}

