
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", HIY"���"NOR);
    set("long", @LONG
����ڹ��߻谵���������ƣ���Լ�ɼ������������ϣ������ϣ�
�����϶����˺��һ�����͡�����������ͽ�Ƕ��Ŵ��СС�ķ���
ߵ�ݣ����������͡����ڹ��������Ĳ�����ഫ���ĳɹ����¼�ʱ
�����ģ��������ʧ�ޣ����ϵĽ����԰�������࣬�߲߰����ġ�
LONG
        );

    set("exits", ([
                "east"  : __DIR__"cedian1",
              "west"  : __DIR__"cedian2",
              "south" : __DIR__"guangchang",

    ]));

    set("time", time());

    set("objects", ([
                                __DIR__"obj/xiang" : 1,
                                    __DIR__"npc/zhirilama" : 1,
                                CLASS_D("xueshan")+"/lazhang" : 1,
                                __DIR__"npc/xiang-ke" : 2,
    ]));

    setup();
        "/clone/board/xueshan_b"->foo();
  
}

void  init()
{
        return;
}


