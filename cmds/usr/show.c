
inherit F_CLEAN_UP;
#include <ansi.h>

mapping places = ([
"yangzhou"      :         "map_yangzhou",
"baling"         :         "map_baling",
"changan"          :         "map_changan",
"chengdu"          :         "map_chengdu",
"dingxiang"        :         "map_dingxiang",
"gaoli"        :         "map_gaoli",
"hefei"       :         "map_hefei",
"jiujiang"          :         "map_jiujiang",
"leshou"      :         "map_leshou",
"lingnan"       :         "map_lingnan",
"luoyang"      :         "map_luoyang",
 "mayi"       :         "map_mayi",
"pengliang"       :         "map_pengliang",
"xiangyang"       :         "map_xiangyang",
"xingyang"      :         "map_xingyang",
"xucheng"       :         "map_xucheng",
"yuyang"       :         "map_yuyang",
]);

int main(object me, string arg)
{
        string info, dir, tmp;
        string *list;
        object here;
        
        here = environment(me);
        if (sscanf(base_name(here), "/d/%s/%s", dir, tmp) != 2)
                 return notify_fail("�޵�ǰλ�õ���Ϣ��\n");

        tmp = filter_color(here->short());
        
        list = keys(places);        
        if (member_array(dir, list) == -1)
                  return notify_fail("�޵�ǰλ�õ���Ϣ��\n");

        info = read_file("/doc/help/" + places[dir]);
        info = color_filter(info);
        //info = filter_color(info);
        info = replace_string(info, tmp, NOR + HIR + BLINK + tmp + NOR);
        write(info + "\n");
        //write("dir == " + dir + "  tmp == " + tmp + "\n");
        //info = color_filter(read_file("/help/));

        return 1;
}
int help(object me)
{
	write(@HELP

���ָ�������ʾ�㵱ǰ����λ�á�

HELP
	);
	return 1;
}
