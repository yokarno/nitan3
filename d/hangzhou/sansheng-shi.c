// road

#include <ansi.h>
inherit ROOM;
void create()
{
     set("short", "����ʯ");
        set("long", @LONG
�����ã���������������ʯ�ڳ����ģ�����ȥ�ܱ�׾����ʵ���ǿ���ͨ��
��ʯͷ��ֻ������������(zi)���㴫���ˡ��Ĵ������˼���ֻ��Щ��״�������
ʯɢ���ڰ�������ɫ���������ڴ�˵������ˡ�ǰ����������������������
ʯ�����ߵ����˸��������˰��������������ֻ����Σ�������ʯȴ��һֱ���ڵġ�
�·��Ϊ�����������ǵ���Լ�������ﾲ��������ֱ������ʯ�á�
LONG );
        set("item_desc", ([
		"zi": RED"
��˵���Ƴ�ʱ��һ������Բ�����Դ���ã���һ��һ��ȥ���ң���
����·�����ߣ�Բ��Ҫ��һ������ԴҪ����һ���������������
Դ����·�ϣ�����һ�����Ŷ��ӵ��и���Բ����ɫһ��˵��������
��ֲ�������·�������ԭ�����еľ����ң��Ѿ������ˣ�����
��������Ҳ�㲻��ȥ�ˣ�һ����ȥ���Ǹ�Ӥ�����һ���ЦΪ֤����
�������Եʮ�������Ǯ�������������һ����˵�꣬�Ǹ����˾�
�����ˡ���Դ��ȥһ�����Ǹ�Ӥ����Ȼ����Ц�ˡ���ʮ�������
Դ��Լ������������һ������֮ҹ����Ȼ����һ����ͯ������
���� ���� ����ʯ�Ͼɾ��꣬
���� ���� �ͷ����²�Ҫ�ۡ�
���� ���� ��������Զ��ã�
���� ���� ���������Գ��档
��Դ֪��Բ�󣬾�����ǰ�����׽�������ͯ�ֳ�����
���� ���� ��ǰ������ãã��
���� ���� ������Ե�ֶϳ���
���� ���� ��Խɽ��Ѱ�ѱ飬
���� ���� ȴ�����������ơ�
����Ͳ�֪���١�\n"NOR,
	]));
	set("exits", ([
		"south" : "/d/hangzhou/qixi-tai",
        
        ]));
//	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}