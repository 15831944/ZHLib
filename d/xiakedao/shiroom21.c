// /d/xiakedao/shiroom21.c ���͵� ʯ��21

inherit ROOM;

int do_study(string arg);
void create()
{
        set("short", "ʯ��");
        set("long", @LONG
���ű������һ��ԭ���Ϸ���һ���������ͨ��ף���������
ʯ���ǰ����ơ�һĨ����ӿ���͸�룬Ͷ�ڶ����ʯ��(wall)�ϡ���
��Ҳ�������������ȸߴ��ɹ�������Ƭ�̼��������⡣
LONG );
        set("exits", ([
                "south" : __DIR__"shihole6",
        ]));
        set("item_desc", ([
                "wall" : @WALL
ǽ�����Ϸ����š����������㡹�������֡��������Ǵ���ʱ��һ��
���ҵĹ��¡�Ҫ�����ɡ�����Ҫ����ļȰ������ֶ��ۣ���һ��ɱ
��ֱ�����˻��ǡ�һ��ע�ƣ�������ʫ���뵱ʩ��ʱ������Ħ���
��ע��߳������Ʊ�ɫ��
WALL
        ]));

        set("no_clean_up", 0);
        set("no_fight", 1);
        set("no_beg", 1);
        setup();
}
void init()
{
        add_action("do_study","think");
}
#include "/d/xiakedao/shiroom.h"
