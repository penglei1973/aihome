#include <stdio.h>
#include <json/json.h>

/********************************************************************************************
 *作者：草根老师(程姚根)
 *
 *json-test.c测试程序功能如下:
 *
 *1.创建一个json对象
 *2.给json对象加入成员，并且赋值
 *3.以字符串的形式输出json对象
 *4.将json格式的字符串转成json对象
 *5.获取json对象的成员值
 *
 *编译:
 *x86平台编译 :gcc json-test.c -o  json-test -ljson
 *ARM平台编译 :需要指定交叉编译,通过 -I 指定头文件所在路径 -L 指定库所在路径  -l指定库名
 *
 */

void print_json_object_member(json_object *new_object,const char *field)
{

    //根据指定对象的成员名，获取这个成员对象的json对象
    struct json_object *object = json_object_object_get(new_object, field);
    //获取json对象的类型
    enum json_type object_type = json_object_get_type(object);
    
    switch(object_type){
        case json_type_int:
            //printf("new_obj.%s json_object_get_type()=%s\n", field,json_type_to_name(object_type));
            printf("new_obj.%s json_object_get_int()=%d\n", field,json_object_get_int(object));
            break;

        case json_type_string:
            //printf("new_obj.%s json_object_get_type()=%s\n", field,json_type_to_name(object_type));
            printf("new_obj.%s json_object_get_string()=%s\n", field,json_object_get_string(object));
            break;
    }
    printf("\n-------------------------------------------------------\n");
    
    //释放json对象
    json_object_put(object);

    return;
}

void print_json_object(json_object *j_object)
{
    print_json_object_member(j_object,"temp");
    print_json_object_member(j_object,"humidity");
    print_json_object_member(j_object,"triaxialX");
    print_json_object_member(j_object,"triaxialY");
    print_json_object_member(j_object,"triaxialZ");
    print_json_object_member(j_object,"userName");
    print_json_object_member(j_object,"passWord");
    
    return;
}


int main(int argc, const char *argv[])
{
    json_object *new_obj;
    json_object *my_object;
    unsigned char *my_object_string;
    unsigned char json_fromat_string[1024];

    //创建一个空的json对象
    my_object = json_object_new_object();
    
    //以key-value的形式添加json对象的成员
    json_object_object_add(my_object, "temp", json_object_new_int(20));
    json_object_object_add(my_object, "humidity", json_object_new_int(10));
    json_object_object_add(my_object, "triaxialX", json_object_new_int(10));
    json_object_object_add(my_object, "triaxialY", json_object_new_int(20));
    json_object_object_add(my_object, "triaxialZ", json_object_new_int(30));
    json_object_object_add(my_object, "userName", json_object_new_string("cyg"));
    json_object_object_add(my_object, "passWord", json_object_new_string("123456"));    
    
    //将json对象内容，转成json格式的字符串
    my_object_string = (char *)json_object_to_json_string(my_object);
    printf("my_object.to_string()=%s\n", my_object_string);

    //将json格式的字符串转成json对象
    new_obj = json_tokener_parse(my_object_string);
    printf("new_obj.to_string()=%s\n", json_object_to_json_string(new_obj));
    
    //输出json对象的成员
    print_json_object(new_obj);
    
    //释放json对象
    json_object_put(my_object);
    json_object_put(new_obj);

    return 0;
}

