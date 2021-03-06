// unique.c

// This function returns 1 if this_object() is not the unique clone in
// the mud. Note that calling this function on master copy always return
// 0.
#include <dbase.h>
#include <ansi.h>
#include <name.h>
inherit F_OBSAVE;

nomask int violate_unique()
{
        object *ob;

        if( !clonep(this_object()) ) return 0;

        // Find all the cloned instance of this_object()
        ob = filter_array( children(base_name(this_object())), (: clonep :) );

        return sizeof(ob) > 1;
}

// This function returns the replica of this_object() if any.
object create_replica()
{
        string replica;
        object obj;

        seteuid(getuid());
        if( stringp(replica = this_object()->query("replica_ob")) )
                obj = new(replica);
        else
                obj = 0;
        destruct(this_object());
        return obj;
}

int do_enchase(object me, object tessera)
{
        mapping *ins;
        mapping data, spe_data, ench;
        string  *apply;
        string  fn;
        object ob = this_object();

        if (tessera->query("can_be_enchased"))
                return notify_fail(tessera->name() + "只能镶嵌到自造10lvl兵器上。\n");

        if (! mapp(tessera->query("enchase")))
                return notify_fail(tessera->name() + "不能发挥魔力，"
                                   "没有必要镶嵌在" + name() + "上面。\n");

        if (tessera->is_item_make())
                return notify_fail(tessera->name() + "非镶嵌物品，不能被镶嵌在" + name() + "上面。\n");

        if (me->query_skill("certosina", 1) < 200)
                return notify_fail("你觉得你的镶嵌技艺还不够"
                                   "娴熟，不敢贸然动手。\n");

        if (! query("enchase/flute"))
                return notify_fail(name() + "上没有凹槽用来镶嵌宝石。\n");

        if ((int)query("enchase/used") >= query("enchase/flute"))
                return notify_fail(name() + "上的凹槽已经被镶满了。\n");

        if (tessera->is_rune_ob() && query("enchase/rune" + tessera->query("enchase/SN")))
                return notify_fail(name() + "上的凹槽里已经镶嵌此符文,再镶嵌会产生魔性冲突。\n");

        ench = tessera->query("enchase");
        if (! undefinedp(ench["type"]))
        {
                if (ench["type"] != "all" &&
                    ench["type"] != query("skill_type") &&
                    ench["type"] != query("armor_type"))
                        return notify_fail(tessera->name() + "的魔力属性不适合镶嵌在" + name() + "上。\n");
        }

        if (me->query_skill("certosina", 1) / 3 + random(me->query_skill("certosina", 1)) < 180)
        {
                message_sort(HIM "听得“喀啦”一声，只见" + tessera->name() + HIM "撞在$n" +
                             HIM "上，片片裂开。\n" NOR, me, ob);
                tell_object(me, HIC "你镶嵌" + tessera->name() + CYN "失败了。\n" NOR);
                fn = base_name(tessera) + C_FILE_EXTENSION;
                if (sscanf(fn, "/data/enchase/%*s")) 
                        rm(fn);

                destruct(tessera);
                me->start_busy(1);
                return 1;
        }

        message_sort(HIM "听得“喀啦”一声，$N" HIM "将" + tessera->name() +
                     HIM "镶嵌到了$n" HIM "上面的凹槽里，只见" + tessera->name() + HIM
                     "隐隐的发出一团奇异的光芒，环绕在$n" HIM "的周围，随即变得平静。\n" NOR, me, ob);
        tell_object(me, HIC "你感受" + name() + HIC "发生了"
                    "不可言喻的变化。\n" NOR);

        if (query("skill_type"))
                spe_data = tessera->query("enchase/wspe_data");
        else
        if (query("armor_type"))
                spe_data = tessera->query("enchase/aspe_data");
        
        if (! mapp(spe_data)) spe_data = ([ ]);
        apply = keys(spe_data);
        data = query("enchase/spe_data");
        if (! mapp(data)) data = ([ ]);
        
        for(int i = 0; i<sizeof(apply); i++)
                if (undefinedp(data[apply[i]]))
                        data[apply[i]] = spe_data[apply[i]];
                else
                        data[apply[i]] += spe_data[apply[i]];

        set("enchase/spe_data", data);

        ins = query("enchase/inset");
        if (! ins) ins = ({ });
        ins += ({ (["name" : tessera->query("name"), "id" : tessera->query("id"),
                    "cur_firm" : tessera->query("enchase/cur_firm"), 
                    "SN" : tessera->query("enchase/SN"), 
                    "spe_data" : spe_data]) });

        set("enchase/inset", ins);
        add("enchase/used", 1);
        add("enchase/SN", tessera->query("enchase/SN"));
        if (tessera->is_rune_ob()) 
                set("enchase/rune" + tessera->query("enchase/SN"), 1); 
        // add_weight(tessera->query_weight());
        save();
        fn = base_name(tessera) + C_FILE_EXTENSION; 
        if (sscanf(fn, "/data/enchase/%*s")) 
                rm(fn);

        destruct(tessera);
        me->start_busy(1);
        return 1;
}

// 接受存盘数据的接口函数
int receive_dbase_data(mixed data)
{
        if (! mapp(data))
                return 0;

        if (data["enchase"])
                set("enchase", data["enchase"]);

        return 1;
}

// 进行保存数据的接口函数
mixed save_dbase_data()
{
        mapping data;
        //object  user;

        data = ([ ]);

        if (query("enchase"))
                data += ([ "enchase" : query("enchase") ]);
                
        return data;
}

int save()
{
        //int res;

        if (base_name(this_object()) + ".c" == __FILE__)
                return 0;

        return ::save();
}

int remove()
{
        save();
}
