//Room: /d/city/shuyuan2.c

#define STORY_TOC "/doc/legend/toc"
inherit ROOM;

void create()
{
        set("short", "��Ժ���");
        set("long", @LONG
��������Ժ��ͼ��ݣ�����������һ����Ⱦ�����ϵ����(shelf)��
�������е������ǵ���ѡ����¼�������еķ���������������ġ�ң
Զĥ��ȥ�Ĵ�˵��������Ķ�(read)����Щ���ϵĹ��¡�
LONG);
        set("item_desc", ([
            "shelf" : "�˴��Ѿ������Ų���ˡ�\n",
        ]));
        set("objects", ([
                "/d/room/roomnpc/teagirl":1,
        ]));
        set("exits", ([
            "down" : __DIR__"shuyuan",
        ]));
	set("no_clean_up", 0);
        setup();
}

