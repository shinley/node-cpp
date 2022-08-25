#include <napi.h>
#include<iostream>
#include<string>
using namespace Napi;

Napi::Value getObj( const CallbackInfo& info ){
  Env env = info.Env();
  // 为了精简示例代码，就不对数据类型进行检测了。

  // 接收并解析js传来的对象。
  Napi::Object obj = info[0].As<Napi::Object>();
  // Napi::Object obj = info[0].ToObject();
  std::string name = obj.Get(static_cast<napi_value>(Napi::String::New(info.Env(),"name"))).As<Napi::String>();
  std::cout << "c++_log=>" << name << std::endl;

  // 准备返回给js，c++对象
  Napi::Object result = Napi::Object::New(env);
  result.Set(Napi::String::New(env,"name"),Napi::String::New(env,name));
  result.Set(Napi::String::New(env,"age"),Napi::Number::New(env,36));
  result.Set(Napi::String::New(env,"height"),Napi::Number::New(env,175));
  result.Set(Napi::String::New(env,"weight"),Napi::Number::New(env,66.5));

   Napi::Object result1 = Napi::Object::New(env);
  result1.Set(Napi::String::New(env,"name"),Napi::String::New(env,name+"1"));
  result1.Set(Napi::String::New(env,"age"),Napi::Number::New(env,38));
  result1.Set(Napi::String::New(env,"height"),Napi::Number::New(env,180));
  result1.Set(Napi::String::New(env,"weight"),Napi::Number::New(env,70.5));

  // 准备返回给js，c++数组
  Napi::Array resultArr = Napi::Array::New(env);
  // 给数组赋值 
  resultArr.Set(Napi::Number::New(env,0), result);
  resultArr.Set(Napi::Number::New(env,1), result1);

  return resultArr;
}

Napi::Object Init(Env env, Object exports){

  exports.Set(Napi::String::New(env,"getObj"),Napi::Function::New(env,getObj));
  return exports;
}

NODE_API_MODULE(addon,Init);