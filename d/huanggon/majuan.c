// majuan.c.c ��Ȧ

inherit ROOM;

void create()
{
        set("short", "��Ȧ");
        set("long", @LONG
�ʼ���Ȧ,��Ȼ�Ǻ����Ƽ�.һ�������������,һƥƥӢͦ
��ͷ����,���㲻��������ԭ�������ڵ�׳ΰ����.
LONG
        );
        set("exits", ([
                "east" : __DIR__"houhuayuan2",
        ]) );
        set("objects", ([
        ]) );
        setup();
        replace_program(ROOM);
}

