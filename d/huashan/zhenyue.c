// zhenyue.c

inherit ROOM;

void create()
{
        set("short", "������");
	set("long", @LONG
�������бڶ������ı����ֱ��գ���ɫ��������ǰ����(jing)����
����������ǧҶ���������������Ϊƽ̹���ϡ���ɽ���οͶ��ڴ�������
Ϣ�ټ���ǰ�С������м����ª�����磬���Ƕ�����ճ��ߣ�����ͷ��
ЪϢ�ڴˡ�
LONG );
        set("exits", ([ /* sizeof() == 3 */
            "northdown"  : __DIR__"jinsuo",
            "eastup"     : __DIR__"yunu",
            "southwest"  : __DIR__"lianpath1",
        ]));
        set("objects", ([
            __DIR__"npc/gao-genming" : 1,
        ]));
        set("item_desc", ([
            "jing" : "����ˮɫ��͸�����ֿ�����\n",
        ]));

        set("outdoors", "huashan" );
        set("resource/water", 1);

        setup();
}
 
int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("gao genming", this_object())))
                return 1;

        if (dir == "eastup")
                return guarder->permit_pass(me, dir);

        return 1;
}
