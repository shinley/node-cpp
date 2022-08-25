const addon = require('./build//Release/addon.node')

console.log("js--log=>",addon.getObj({name:"zhangsan"}));